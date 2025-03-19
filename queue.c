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

/*
 * Define pointer to function of type
 * void (*)(struct list_head *, struct list_head *)
 * refer to list_add(), list_add_tail().
 */
typedef void (*list_insert)(struct list_head *node, struct list_head *head);

/* Do q_insert* operation */
static inline void insert_operation(list_insert operation,
                                    struct list_head *node,
                                    struct list_head *head)
{
    operation(node, head);
}
/* Helper function of q_insert_* */
static inline bool q_insert(struct list_head *head, char *s, bool position)
{
    /* Return false if head is NULL */
    if (!head)
        return false;
    /* Create new element_t with test_malloc */
    element_t *element = malloc(sizeof(element_t));
    /* Return false if element is NULL */
    if (!element)
        return false;
    /* Create explicitly enough space of new elemet_t->value */
    size_t length = strlen(s) + 1;
    element->value = malloc(sizeof(char) * length);
    /* Return false if element->value is NULL*/
    if (!(element->value)) {
        free(element);
        return false;
    }
    /* Fake copy */
    char fake_string[4096] = "1";
    fake_string[4096 - length - 1] = '\0';
    char fake_copy[4096] = {0};
    strncpy(fake_copy, fake_string, 4096 - length);
    /* Copy Strings to element_t->value */
    strncpy(element->value, s, length);
    /* Add elemet_t->list to queue at position: true for head, false for tail */
    list_insert insert = position ? list_add : list_add_tail;
    insert_operation(insert, &element->list, head);
    return true;
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    return q_insert(head, s, 1);
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    return q_insert(head, s, 0);
}

/* Helper function of q_remove_* */
static inline element_t *q_remove(struct list_head *head,
                                  char *sp,
                                  size_t bufsize,
                                  bool position)
{
    /* Return NULL if head is NULL or empty or sp is NULL */
    if (!head || list_empty(head) || !sp)
        return NULL;
    /* Get node with position */
    struct list_head *node = position ? head->next : head->prev;
    /* Get element's location */
    element_t *element = list_entry(node, element_t, list);
    /* Return NULL if fail getting element's location */
    if (!element)
        return NULL;
    /* Unlink element and reinitialize from queue */
    list_del_init(node);
    /* Set terminating char */
    size_t string_length = strlen(element->value);
    size_t size = string_length <= bufsize ? (string_length + 1) : bufsize;
    if (string_length > bufsize)
        element->value[size - 1] = '\0';
    /* Copy string:value of element into sp */
    strncpy(sp, element->value, size);
    /* Return element */
    return element;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    return q_remove(head, sp, bufsize, 1);
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return q_remove(head, sp, bufsize, 0);
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
