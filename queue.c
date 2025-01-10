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
    /* remove last element from head of queue */
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
    /**
     * Return false if head is NULL or head is empty
     * Else return true if head is singular
     */
    if (!head || list_empty(head)) {
        return false;
    } else if (list_is_singular(head)) {
        return true;
    }
    /* Declare a pointer p1 to location of head's next */
    struct list_head **p1 = &head->next;
    /* Loop while true */
    while (1) {
        /* Break if head is empty or head is singular or *p1 is point to head */
        if (list_empty(head) || list_is_singular(head) || *p1 == head) {
            break;
        }
        /**
         * Declare a pointer e1 which point to entry which hold @list
         * where *p1 point to
         */
        element_t *e1 = list_entry(*p1, element_t, list);
        /* Declare a pointer strToCompare which point to e1’s @value */
        char *strToCompare = e1->value;
        /* Declare a pointer p2 which point to location of p1’s next */
        struct list_head **p2 = &(*p1)->next;
        /* Declare an int foundDuplicate and set it to false */
        int foundDuplicate = 0;
        /* Loop while *p2 is not point to head */
        while ((*p2) != head) {
            /**
             * Declare a pointer e2 which point to entry which hold
             * @list where p2 point to
             */
            element_t *e2 = list_entry(*p2, element_t, list);
            /**
             * Declare a pointer strCandidate which point to e2’s
             * member @value
             */
            char *strCandidate = e2->value;
            /**
             * If strToCompare and strCandidate are equal then
             * Set foundDuplicate to true
             * Delete entry which holding p2
             * Else Set p2 point to location of p2’s next
             */
            if (strcmp(strToCompare, strCandidate) == 0) {
                foundDuplicate = 1;
                list_del_init(*p2);
                free(e2->value);
                free(e2);
            } else {
                p2 = &(*p2)->next;
            }
        }
        /**
         * If foundDuplicate is true then delete entry which holding p1
         * Else set p1 point to location of p1’s next
         */
        if (foundDuplicate) {
            list_del_init(*p1);
            free(e1->value);
            free(e1);
        } else {
            p1 = &(*p1)->next;
        }
    }
    return true;
}

/**
 *  Helper function of q_swap
 *  Swap memory address of two nodes
 */
void swap(struct list_head **node1, struct list_head **node2)
{
    struct list_head *temp;
    temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    /* Do nothing if head is NULL or empty or singular */
    if (!head || list_empty(head) || list_is_singular(head))
        return;
    /* Declare p1, p2 to perform swap and set starting position */
    struct list_head **p1 = NULL;
    struct list_head **p2 = &head;
    p1 = &(*p2)->next;
    p2 = &(*p1)->next;
    while ((*p1) != head && (*p1)->next != head) {
        /**
         * About the loop:
         * First change related @next value.
         * Second change related @prev value.
         */

        /* Swap related @next value */
        swap(p1, p2);
        p1 = &(*p1)->next;
        swap(p1, p2);
        /* Set starting position of p1 and p2, relate to @prev */
        p1 = &(*p1)->prev;
        p2 = &(*p2)->prev;
        /* Swap related @prev value*/
        swap(p1, p2);
        p1 = &(*p1)->prev;
        swap(p1, p2);
        /* Set next round position */
        p1 = &(*p2)->next;
        p2 = &(*p1)->next;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    q_reverseK(head, q_size(head));
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
    /* Do nothing if head is NULL or empty or singular */
    if (!head || list_empty(head) || list_is_singular(head))
        return;
    /* Store number of nodes */
    int n = q_size(head);
    /* Do nothing if k is less than equal 1 or k > number of nodes */
    if (k <= 1 || k > n)
        return;
    /* Declare indirect pointer:p1, p2 of node and initialize */
    struct list_head **p1 = &head->next;
    struct list_head **p2 = p1;
    for (int i = 0; i < k - 1; i++)
        p2 = &(*p2)->next;
    /* Declare n_reverse: times of each reverse */
    int n_reverse = k / 2;
    /* Declare round: times of each n_reverse */
    int round = n / k;
    /* Declare p_next: position of next round */
    struct list_head **p_next = &(*p2)->next->next;
    /* Loop round times of reverse */
    for (int i = 0; i < round; i++) {
        int j = 0;
        while (j++ < n_reverse) {
            if (&(*p1)->next == p2) {
                /* Change relative @next */
                swap(&(*p1)->next, &(*p2)->next);
                swap(p1, &(*p2)->prev->next);
                /* Set starting position of p1 and p2, relate to @prev */
                p1 = &(*p1)->prev;
                p2 = &(*p2)->prev;
                /* Change relative @prev */
                swap(&(*p1)->prev, &(*p2)->prev);
                swap(&(*p1)->next->next->prev, p2);
            } else {
                /* Change relative @next */
                swap(&(*p1)->next, &(*p2)->next);
                swap(p1, p2);
                swap(&(*p1)->next->prev, &(*p2)->next->prev);
                swap(&(*p1)->prev, &(*p2)->prev);
                /* Set next reverse position */
                p1 = &(*p1)->next;
                p2 = &(*p2)->prev->prev->next;
            }
        }
        /* Set next round position */
        p1 = &(*p_next)->prev->prev->next;
        p2 = p1;
        for (int l = 0; l < k - 1; l++)
            p2 = &(*p2)->next;
        p_next = &(*p2)->next->next;
    }
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
