#ifndef DBL_LST_H
# define DBL_LST_H

void	*add_node_new(void **head, void *(*constructor)(void *), void *args);
void	*insert_node_new(void *node_precede, void *(*constructor)(void *), void *args);
int		append_node(void **head, void *node);
int		insert_node(void *node_precede, void *node_insert);
void	delete_node(void **head, void *node, int (*destructor)(void *));
void	delete_list(void **head, int (*destructor)(void *));

#endif
