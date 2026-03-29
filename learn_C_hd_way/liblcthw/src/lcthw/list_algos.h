#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>

typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *list, List_compare cmp);
int val_swap(ListNode *node1, ListNode *node2);

int partition(List *list, int start, int end, List_compare cmp, ListNode **index_map);
ListNode *mv_right(ListNode *first, int steps);
ListNode *mv_left(ListNode *end, int steps);
List *List_merge_sort(List *list, List_compare cmp);
void quick_sort(List *list, int start, int end, List_compare cmp);
#endif