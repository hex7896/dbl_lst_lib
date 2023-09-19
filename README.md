# dbl_lst_lib
A library for simulating polymorphic doubly-linked lists in C. <br>

## Functions
### add_node_new(void **head, void *(*constructor)(void *), void *args)
Creates a new node by calling `constructor` and appends the node to the end of the list headed by `*head`. <br>
`args` is passed as an argument when calling `constructor`.<br>

### insert_node_new(void *node_precede, void *(*constructor)(void *), void *args)
Insert a new node by calling `constructor` and inserts the node as the next node after `node_precede`. <br>
`args` is passed as an argument when calling `constructor`.<br>

### append_node(void **head, void *node)
Appends `node` to the end of list headed by `*head`. <br>

### insert_node(void *node_precede, void *node_insert)
Insert `node_insert` behind `node_precede`. <br>

### delete_node(void **head, void *node, int (*destructor)(void *))
Deletes `node` from a list headed by `*head`, calling `destructor` on `node` in the process and finally freeing `node`.<br>
`destructor` can be `NULL`, in which case no destructor will be called, but memory allocated for `node` will still be freed.<br>
`destructor` should only perform any necessary cleanup operations using members within `node` and should not free `node` itself. <br>
`destructor` should return 0 if successful, or any other value in case of error.<br>
If `destructor` does not return 0, this function returns without freeing `node`. <br>

### delete_list(void **head, int (*destructor)(void *))
Deletes whole list of which `*head` is a node of.<br>
Even if `*head` is not the first node, function will seek the first node and free the whole list. <br>
`*head` will be set to `NULL` by the time the function returns. <br>
`destructor` can be `NULL`, in which case no destructor will be called, but memory allocated for each node will still be freed. <br>
