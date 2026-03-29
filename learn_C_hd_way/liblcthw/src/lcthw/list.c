#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <string.h>
List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    ListNode *cur = list->first;
    while(cur) {
        ListNode *next = cur->next;
        free(cur);
        cur = next;
    }
    free(list);
}


void List_clear(List *list, void (*free_func)(void *))
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->value && free_func) {
            free_func(cur->value);
        }
    }
}


void List_clear_destroy(List *list, void (*free_func)(void*))
{
    List_clear(list, free_func);
    List_destroy(list);
}


void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;
    return;
error:
    log_err("Failed to calloc memory");
    return;
}

void List_cpy_one(List *list, void *value){
    ListNode *target = NULL;
    LIST_FOREACH(list, first, next, cur){
        if(cur->value == value) {
            target = cur;
            break;
        }
    }

    if(target){
        List_push(list, target->value);
    } else {
        log_info("No corresponding value found");
    }

    return;

}

void List_cpy_create(List* dest, List *src) {
    check(src && dest, "Invalid list");

    if(src->count == 0) {
        log_err("empty source list!");
    } 

    LIST_FOREACH(src, first, next, cur) {
        /*void *load = calloc(1, sizeof(*(cur->value)) * strlen(cur->value) + 1);
        check_mem(load);
        memcpy(load, cur->value, sizeof(*(cur->value)) * strlen(cur->value) + 1);
        */
        char *load = strdup(cur->value);
        List_push(dest, load);
    }
    return;
error:
    return;
}

void List_print(List *list) {
    int i = 1;
    LIST_FOREACH(list, first, next, cur) {
        printf("Node %d: %s\n", i++, (char*)cur->value);
    }
    fflush(stdout);
    return;
}

void *List_pop(List *list)
{
    assert(list->first);
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

/*remove the first node in list and return it*/
void *List_shift(List *list)
{
    ListNode *node = list->first;
    return (node != NULL) ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}