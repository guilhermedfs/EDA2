#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node
{
    struct node *next;  /* The next element */
    long int data;           /* The associated data */
} node;
 

void list_add_node( node **list, node *node )
{
    node->next = *list;
    *list = node;
}
 

void list_concat( node **l0, node *l1 )
{
    /* We find the address of the pointer that needs to be updated */
    while (*l0)
        l0 = &((*l0)->next);
   
    /* We update it to point to the new tail */
    *l0 = l1;
}
 

void my_qsort( node **list )
{
    /* Sorting an empty list is trivial */
    if (!*list)
        return;
 
    /* Extract the pivot */    
    node *pivot = *list;
    int data = pivot->data;
    node *p = pivot->next;
    pivot->next = NULL;
 
    /* Construct left and right lists in place in a single pass*/
    node *left = NULL;
    node *right = NULL;
 
    while (p)
    {
        node *n = p;  
        p = p->next;
        if (n->data<data)
            list_add_node( &left, n );
        else
            list_add_node( &right, n );
    }
 
    /* We now sort left and right */
    /* If left and right are of vastly different lengths, the complexity won't be O(n log n) */
    my_qsort( &left );
    my_qsort( &right );
 
    /* We now concatenate lists [this is inefficient, but doesn't hurt complexity] */
    node *result = NULL;
    list_concat( &result, left );
    list_concat( &result, pivot );
    list_concat( &result, right );
    *list = result;
}
 
/*
 * Allocate a new node, with the specified next pointer and data
 */
node *list_make_node( node *next, int data )
{
    node *n = malloc( sizeof(node) );
    n->next = next;
    n->data = data;
 
    return n;
}
 
/*
 * Frees a list
 * Note that we pass the address of the list, so the caller's variable
 * is properly set to NULL after execution.
 */
void list_free( node **list )
{
    while (*list)
    {
        node *node = *list;
        *list = (*list)->next;
        free( node );
    }
 
    /* Exiting the loop ensure *list is NULL, and the caller had its variable updated */
}
 
/*
 * Returns true or false if a list is ordered or not
 * This is strictly a utility function and is not used in sorting
 * Complexity: O( len(list) )
 */
bool list_is_ordered( node *list )
{
    bool first = true;
    int data;
    while (list)
    {
        if (first)
        {
            data = list->data;
            first = false;
        }
        else
        {
            if (list->data<data)
                return false;
            data = list->data;
        }
        list = list->next;
    }
    return true;
}
 
/*
 * Utility to display a list.
 */
void list_display( node *list, long int n )
{
    for(int i = 0; i<n; i++){
        if (i == n - 1){
            printf( "%ld", list->data);
        }
        else {
            printf( "%ld ", list->data);
        }   
        list = list->next;
    }
    printf("\n");
}
 
/*
 * Main takes a single optional argument: the length of the list to be sorted
 */
int main( int argc, char **argv )
{
    long int num;
    int n;
    /* How many node to we create */
    
    /* Building initial data */
    node *list = NULL;

    while(scanf("%d %ld", &n, &num) != EOF){
        if(n == 1){
            list = list_make_node(list, num);
        }if(n == 2){
            my_qsort(&list);
            list_display(list, num);
        }
    }
 
    list_free(&list);
 
    return 0;
}