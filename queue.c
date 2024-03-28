#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head) {
        return;
    }
    if (list_empty(head)) {
        free(head);
        return;
    }
    struct list_head *q = head->next;
    element_t *t = NULL;
    while (q->next != head) {
        struct list_head *r = q->next;
        INIT_LIST_HEAD(q);
        t = container_of(q, element_t, list);
        free(t->value);
        free(t);
        q = r;
    }
    INIT_LIST_HEAD(q);
    t = container_of(q, element_t, list);
    free(t->value);
    free(t);
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    /* Return false if head is NULL */
    if (!head) {
        return false;
    }
    /* Create new element_t with malloc */
    element_t *e = malloc(sizeof(element_t));
    /* Return false if e is NULL */
    if (!e) {
        return false;
    }
    /* Create explicitly enough space of new elemet_t->value */
    int len = strlen(s) + 1;
    e->value = malloc(sizeof(char) * len);
    /* Return false if e->value is NULL*/
    if (!(e->value)) {
        free(e);
        return false;
    }
    /* Copy Strings into element_t->value */
    strncpy(e->value, s, len);
    /* Add elemet_t->list to head */
    list_add(&e->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    /* Return false if head is NULL */
    if (!head) {
        return false;
    }
    /* Create new element_t with malloc */
    element_t *e = malloc(sizeof(element_t));
    /* Return false if e is NULL */
    if (!e) {
        return false;
    }
    /* Create explicitly enough space of new elemet_t->value */
    int len = strlen(s) + 1;
    e->value = malloc(sizeof(char) * len);
    /* Return false if e->value is NULL*/
    if (!(e->value)) {
        free(e);
        return false;
    }
    /* Copy Strings into element_t->value */
    strncpy(e->value, s, len);
    /* Add elemet_t->list to head */
    list_add_tail(&e->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    /* Return NULL if head is NULL or empty or sp is NULL */
    if (!head || list_empty(head) || !sp) {
        return NULL;
    }
    /* get first element's location */
    element_t *removed_e = list_entry(head->next, element_t, list);
    /* return NULL if fail getting element's location */
    if (!removed_e) {
        return NULL;
    }
    /* remove first element from head of queue */
    list_del_init(head->next);
    /* copy string:value of element into sp */
    strncpy(sp, removed_e->value, bufsize);
    /* return element */
    return removed_e;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    /* Return NULL if head is NULL or empty or sp is NULL */
    if (!head || list_empty(head) || !sp) {
        return NULL;
    }
    /* get last element's location */
    element_t *removed_e = list_entry(head->prev, element_t, list);
    /* return NULL if fail getting element's location */
    if (!removed_e) {
        return NULL;
    }
    /* remove first element from head of queue */
    list_del_init(head->prev);
    /* copy string:value of element into sp */
    strncpy(sp, removed_e->value, bufsize);
    /* return element */
    return removed_e;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return 0;
    }
    int size = 0;
    const struct list_head *count = head;
    while (count->next != head) {
        count = count->next;
        size++;
    }
    return size;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    /* Return false if head is NULL or empty */
    if (!head || list_empty(head)) {
        return false;
    }
    /* Declare an int to store [size of nodes in queue / 2] */
    int n = q_size(head) / 2;
    /* Iterate through head [n/2] times */
    while (n > 0) {
        head = head->next;
        n--;
    }
    /* Declare a pointer to element_t */
    /* And store middle node by calling list_entry() */
    element_t *removed_e = list_entry(head->next, element_t, list);
    /* Remove middle node */
    list_del_init(head->next);
    /* Free middle node's element_t->value */
    free(removed_e->value);
    /* Free middle node: element_t */
    free(removed_e);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
