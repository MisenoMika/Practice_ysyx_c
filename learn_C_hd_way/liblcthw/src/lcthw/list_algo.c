#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>
int val_swap(ListNode *node1, ListNode *node2) {
    void *tmp = node1->value;
    
    void *node1_prev = node1->value;
    void *node2_prev = node2->value;

    node1->value = node2->value;
    node2->value = tmp;

    check((node1->value == node2_prev), "SWAP FAILURE");
    check((node2->value == node1_prev), "SWAP FAILURE");

    return 0;
error:
    return 1;
}


int is_list_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

int List_bubble_sort(List *list, List_compare cmp) {
    ListNode *cur, *next;
    cur = list->first;
    int sorted = 0;
    if(list->count == 0) {
        log_warn("Empty list!");
        return 0;
    } else if(list->count == 1) {
        log_info("Only one node in the list, already sorted");
        return 0;
    } else if(is_list_sorted(list)) {
        log_info("Already sorted");
        return 0;
    }

    next = cur->next;
    while(!sorted){
        while(next) {
            if(cmp(cur->value, next->value) > 0) {
                val_swap(cur, next);
            }

            cur = next;
            next = cur->next ? cur->next : NULL;
            
        }
        if(is_list_sorted(list)){
            sorted = 1;
        }
        cur = list->first;
        next = cur->next ? cur->next : NULL;
    }

    return 0;
}

/*
int partition(List *list, int start, int end, List_compare cmp) {
    ListNode *first = mv_right(list->first, start);
    ListNode *cur = first;
    void *pivot = first->value;
    int i = start;

    for(int j = start + 1; j <= end; j++) {
        if(cmp(mv_right(list->first, j)->value, pivot) < 0) {
            i++;
            ListNode *node_i = mv_right(list->first, i);
            ListNode *node_j = mv_right(list->first, j);
            val_swap(node_i, node_j);
        }
    }
    ListNode *node_i = mv_right(list->first, i);
    val_swap(first, node_i);
    
    return i;
}
*/
/*
void quick_sort(List *list, int start, int end, List_compare cmp) {
    check(list, "Invalid list");
    if(list->count == 0) {
        log_warn("Empty list!");
        return;
    } else if(list->count == 1) {
        log_info("Only one node in the list, already sorted");
        return;
    } else if(is_list_sorted(list)) {
        log_info("Already sorted");
        return;
    }

    int mid = 0;

    if(end > start) {
        mid = partition(list, start, end, cmp);
        quick_sort(list, start, mid - 1, cmp);
        quick_sort(list, mid + 1, end, cmp);
    }

    return;
error:
    return;
}
*/

//增加查表
int partition(List *list, int start, int end, List_compare cmp, ListNode **index_map)
{
    ListNode *first = index_map[start];   

    void *pivot = first->value;
    int i = start;

    for(int j = start + 1; j <= end; j++) {
        if(cmp(index_map[j]->value, pivot) < 0) {
            i++;
            val_swap(index_map[i], index_map[j]);  
        }
    }

    val_swap(index_map[start], index_map[i]);

    return i;
}


void quick_sort(List *list, int start, int end, List_compare cmp) {
    check(list, "Invalid list");

    static ListNode **index_map = NULL;

    if(start == 0 && end == list->count - 1) {
        index_map = malloc(sizeof(ListNode*) * list->count);

        ListNode *cur = list->first;
        for(int i = 0; i < list->count; i++) {
            index_map[i] = cur;
            cur = cur->next;
        }
    }

    if(end > start) {
        int mid = partition(list, start, end, cmp, index_map);
        quick_sort(list, start, mid - 1, cmp);
        quick_sort(list, mid + 1, end, cmp);
    }

    if(start == 0 && end == list->count - 1) {
        free(index_map);
        index_map = NULL;
    }

error:
    return;
}

List *List_merge_sort(List *list, List_compare cmp) {
    printf("\nExpected output: {\"1234\", \"NDSS\", \"XXXX\", \"abcd\", \"xjvef\"}\n");
    printf("\nbefore merge sort\n");
    //List_print(list);
    quick_sort(list, 0, list->count - 1, cmp);
    printf("\nafter merge sort\n");
    //List_print(list);
    return list;
}


ListNode *mv_right(ListNode *first, int steps) {
    check(first->next, "No next node");
    ListNode *tmp = first;
    ListNode *after_mv = tmp;

    for(int i = 0; i < steps; i++) {
        tmp = after_mv;
        after_mv = tmp->next;
        check(after_mv, "No next node while moving the node pointer");
    }

    return after_mv;

error:
    log_warn("no next node while moving the node pointer");
    return NULL;
}


ListNode *mv_left(ListNode *end, int steps) {
    check((end->prev), "No previous node");
    ListNode *tmp = end;
    ListNode *after_mv = tmp;

    for(int i = 0; i < steps; i++) {
        tmp = after_mv;
        after_mv = tmp -> prev;
        check(after_mv, "No prev node while moving the node pointer");
    }

    return after_mv;
error:
    log_warn("no previous node while moving node pointer");
    return NULL;
}

/*
lcthw 有序链表思路速记:
    每次push后调用一次bubble_sort即可*/

