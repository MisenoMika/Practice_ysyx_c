#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>
#include <assert.h>
struct ListNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list, void (*free_func)(void *));
void List_clear_destroy(List *list, void (*free_func)(void *));

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);
void List_cpy_one(List* list, void *value);
void List_cpy_create(List* src, List *dest);
void List_print(List *list);
/*LIST_FOREACH(list, first, next, cur)*/
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
/*
* === equal to ===
*
* _node = L->S;
* V = _node;
*
* while(_node != NULL) {
*    // 使用 V（当前节点）
*
*    _node = _node->next;
*    V = _node;
* }
*/