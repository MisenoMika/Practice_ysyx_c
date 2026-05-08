#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}


char *test_destroy()
{
    void (*free_func)(void*) = NULL;
    List_clear_destroy(list, free_func);
    //mu_assert(list == NULL, "Not free completely");
    return NULL;

}


char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}


char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");
    mu_assert(List_first(list) != NULL, "Fisrt Node is NULL");
    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 1, "Wrong count after shift.");

    return NULL;
}

char *test_print()
{
    printf("\nprint list test\n");
    List_print(list);
    return NULL;
}

char *test_cpy()
{
    mu_assert(List_count(list) != 0, "List is empty");

    char *val_first = list->first->value;
    List_cpy_one(list, val_first);
    char *val_last = list->last->value;
    mu_assert(val_first == val_last, "Failed to copy the first node to the list tail");
    
    return NULL;
}

char *test_cpy_whole_list()
{
    mu_assert(List_count(list) != 0, "List is empty");
    printf("\nList Copy test\n");
    List *another_list = List_create();
    List_cpy_create(another_list, list);
    List_print(another_list);

    printf("\nList with one node copy test\n");
    List *list_one_node = List_create();
    List *list_one_another = List_create();
    
    List_push(list_one_node, test1);
    List_cpy_create(list_one_another, list_one_node);
    List_print(list_one_another);


    List_clear_destroy(list_one_another, free);
    List_clear_destroy(another_list, free);
    List_clear_destroy(list_one_node, NULL);
    return NULL;
}
char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_cpy);
    mu_run_test(test_cpy_whole_list);
    mu_run_test(test_print);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);