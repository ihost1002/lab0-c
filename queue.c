#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    return NULL;
}

/* Free all storage used by queue */
void q_free(struct list_head *head) {}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    return -1;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    /* Return false if head is NULL or empty */
    if (!head || list_empty(head))
        return false;
    struct list_head *slow = head;
    for (const struct list_head *fast = head->next;
         fast != head && fast->next != head; fast = fast->next->next)
        slow = slow->next;
    element_t *element = list_first_entry(slow, element_t, list);
    /* Update previous node to next node of middle, and reinitialize middle */
    list_del_init(slow->next);
    /* Free all storage used by element, which member list is middle node. */
    q_release_element(element);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    /* Return false if head is NULL or head is empty. */
    if (!head || list_empty(head))
        return false;
    /* Return true if head is singular. */
    if (list_is_singular(head))
        return true;
    /* Declare a pointer p1 to location of head's next. */
    struct list_head **p1 = &head->next;
    /* Loop while true. */
    while (1) {
        /*
         * Exit loop if head is empty or head is singular or *p1 is point to
         * head.
         */
        if (list_empty(head) || list_is_singular(head) || (*p1 == head))
            break;
        /**
         * Declare a pointer e1 which point to entry which hold list
         * where *p1 point to.
         */
        element_t *e1 = list_entry(*p1, element_t, list);
        /* Declare a pointer base_string which point to e1’s value. */
        const char *base_string = e1->value;
        /* Declare a pointer p2 which point to next location of *p1. */
        struct list_head **p2 = &(*p1)->next;
        /* Declare found_duplicate and set it to false. */
        bool found_duplicate = 0;
        /* Loop while *p2 is not point to head. */
        while ((*p2) != head) {
            /**
             * Declare a pointer e2 which point to entry which hold
             * list where p2 point to.
             */
            element_t *e2 = list_entry(*p2, element_t, list);
            /**
             * Declare a pointer candidate_string which point to e2’s
             * member value.
             */
            const char *candidate_string = e2->value;
            /**
             * If base_string and candidate_string are equal, then set
             * found_duplicate to true, delete entry which holding p2,
             * else update p2's value to next location *p2.
             */
            if (strcmp(base_string, candidate_string) == 0) {
                found_duplicate = 1;
                list_del_init(*p2);
                q_release_element(e2);
            } else {
                p2 = &(*p2)->next;
            }
        }
        /**
         * If found_duplicate is true then delete entry which holding p1,
         * else set p1 point to location of p1’s next
         */
        if (found_duplicate) {
            list_del_init(*p1);
            q_release_element(e1);
        } else {
            p1 = &(*p1)->next;
        }
    }
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
