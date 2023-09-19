#include <stdlib.h>
#include "dbl_lst.h"
#include "dbl_lst_priv.h"

/*
**	Creates a new node by calling constructor and appends the node to the end
**	of the list headed by *head.
**	args is passed as an argument when calling constructor.
**	If *head is NULL, then the pointer to the new node will be assigned to
**	*head.
**	Returns NULL in case of error, or the pointer to the new node in case of
**	success.
*/
void	*add_node_new(void **head, void *(*constructor)(void *), void *args)
{
	dbl_lst_t	*new_node;

	if (head == NULL)
		return (NULL);
	new_node = constructor(args);
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	append_node(head, new_node);
	return (new_node);
}

/*
**	Insert a new node by calling constructor and inserts the node as the next
**	node of the node specified by paramter node_precede. 
**	args is passed as an argument when calling constructor.
**	If node_precede is NULL, the function returns NULL immediately. 
**	Returns NULL in case of error, or the pointer to the new node in case of
**	success.
*/
void	*insert_node_new(void *node_precede, void *(*constructor)(void *), void *args)
{
	dbl_lst_t	*new_node;

	if (node_precede == NULL)
		return (NULL);
	new_node = constructor(args);
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	insert_node(node_precede, new_node);
	return (new_node);
}

/*
**	Appends node to the end of list headed by *head.
**	If *head is NULL, then the pointer to *node will be assigned to *head.
**	If head is NULL or node is NULL, function returns -1 without doing anything.
**	Function returns 0 otherwise
*/
int	append_node(void **head, void *node)
{
	dbl_lst_t	*cur_last_node;

	if (head == NULL || node == NULL)
		return (-1);
	if (*head == NULL)
	{
		((dbl_lst_t *)node)->prev = NULL;
		*head = node;
		return (0);
	}
	cur_last_node = *head;
	while (cur_last_node->next != NULL)
		cur_last_node = cur_last_node->next;
	cur_last_node->next = node;
	((dbl_lst_t *)node)->prev = cur_last_node;
	return (0);
}

/*
**	Insert node_insert behind node_precede.
**	If either node_precede or node_insert is NULL, function returns -1 without
**	doing anything.
**	Function returns 0 otherwise.
*/
int	insert_node(void *node_precede, void *node_insert)
{
	dbl_lst_t	*node_precede_cast;
	dbl_lst_t	*node_insert_cast;
	dbl_lst_t	*node_next;
	
	node_precede_cast = node_precede;
	node_insert_cast = node_insert;
	if (node_precede == NULL || node_insert == NULL)
		return (-1);
	node_next = node_precede_cast->next;
	node_precede_cast->next = node_insert;
	node_insert_cast->prev = node_precede;
	node_insert_cast->next = node_next;
	if (node_next != NULL)
		node_next->prev = node_insert;
	return (0);
}

/*
**	Deletes node from a list with *head as the first node, calling destructor
**	on node in the process and finally freeing node.
**	destructor can be NULL, in which case no destructor will be called, but
**	memory allocated for each node will still be freed.
**	destructor should only perform any necessary cleanup operations using
**	members within node and should not free node itself.
**	destructor should return 0 if successful, or any other value in case of
**	error. If destructor does not return 0, this function returns without
**	freeing node. 
**	If node is NULL, nothing is done. 
**	If node->prev is NULL (implying node is the first node in list) and head
**	is NULL, nothing is done. This ensures node is not freed unless variable
**	storing the pointer to the first node can be updated. 
**	No check is performed to confirm node is within the same list as *head.
*/
void	delete_node(void **head, void *node, int (*destructor)(void *))
{
	dbl_lst_t	*node_prev;
	dbl_lst_t	*node_next;

	node_prev = ((dbl_lst_t*) node)->prev;
	node_next = ((dbl_lst_t*) node)->next;
	if (node == NULL || (node_prev == NULL && head == NULL))
		return ;
	if (destructor != NULL && destructor(node))
		return ;
	if ((node_prev != NULL && node_prev->next != node)
		|| (node_next != NULL && node_next->prev != node))
	{
		free(node);
		return ;
	}
	if (node_prev != NULL)
		node_prev->next = node_next;
	else
		*head = node_next;
	if (node_next != NULL)
		node_next->prev = node_prev;
	free(node);
}

/*
**	Deletes whole list of which *head is a node of.
**	Even if *head is not the first node, function will seek the first node and
**	free the whole list. 
**	*head will be set to NULL by the time the function returns. 
**	destructor can be NULL, in which case no destructor will be called, but
**	memory allocated for each node will still be freed.
*/
void	delete_list(void **head, int (*destructor)(void *))
{
	dbl_lst_t	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp != NULL)
		delete_node((void **) &tmp, tmp, destructor);
	*head = NULL;
}
