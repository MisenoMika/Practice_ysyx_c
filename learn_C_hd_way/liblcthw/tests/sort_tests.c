#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

//char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 100000
#define STR_LEN 10
char **values;



char **create_values() {
    char **values = malloc(sizeof(char*) * NUM_VALUES);
    if (!values) return NULL;

    for (int i = 0; i < NUM_VALUES; i++) {
        values[i] = malloc(STR_LEN + 1); 
        check_mem(values[i]);

        for (int j = 0; j < STR_LEN; j++) {
            values[i][j] = 'a' + rand() % 26; 
        }
        values[i][STR_LEN] = '\0';
    }

    return values;
error:
    log_err("Failed to create values");
    return NULL;
}

clock_t start, end;
List *create_words()
{
    int i = 0;
    List *words = List_create();
    values = create_values();
    for(i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    printf("Expected output: {\"1234\", \"NDSS\", \"XXXX\", \"abcd\", \"xjvef\"}\n");
    List *words = create_words();

    printf("\nbefore sorted\n");
    //List_print(words);
    // should work on a list that needs sorting
    start = clock();

    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");

    end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime spent on bubble sort: %f seconds\n", time_spent);

    printf("\nafter sorted\n");
    //List_print(words);

    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create();
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();
    //List_print(words);
    // should work on a list that needs sorting
    start = clock();
    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime spent on merge sort: %f seconds\n", time_spent);

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");
    //List_destroy(res2);
    //List_destroy(res);

    List_destroy(words);
    return NULL;
}

char *test_node_mv() 
{
    List *words = create_words();
    ListNode *next_1 = mv_right(words->first, 1);
    printf("next_1: %s ; expected : %s\n", (char *)next_1->value, (char *)words->first->next->value);
    mu_assert(strcmp(next_1->value, words->first->next->value) == 0, "Nodeptr doesn't point to the right location");

    ListNode *next_2 = mv_right(words->first, 2);
    printf("next_2: %s ; expected : %s\n", (char *)next_2->value, (char *)words->first->next->next->value);
    mu_assert(strcmp(next_2->value, words->first->next->next->value) == 0, "Nodeptr doesn't point to the right location");

    ListNode *prev_1 = mv_left(words->last, 1);
    printf("prev_1: %s ; expected : %s\n", (char *)prev_1->value, (char *)words->last->prev->value);
    mu_assert(strcmp(prev_1->value, words->last->prev->value) == 0, "Nodeptr doesn't point to the right location");

    ListNode *prev_2 = mv_left(words->last, 2);
    printf("prev_2: %s ; expected : %s\n", (char *)prev_2->value, (char *)words->last->prev->prev->value);
    mu_assert(strcmp(prev_2->value, words->last->prev->prev->value) == 0, "Nodeptr doesn't point to the right location");

    List_destroy(words);
    return NULL;
}
char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    printf("\n");
    mu_run_test(test_node_mv);
    printf("\n");
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);