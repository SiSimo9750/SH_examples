#include "shell.h"

/**
 * add_node - adds a node to the list debut
 * @head: pointer to head node
 * @str: field of node string
 * @num: node index used
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *novo_head;

	if (!head)
		return (NULL);
	novo_head = malloc(sizeof(list_t));
	if (!novo_head)
		return (NULL);
	_memset((void *)novo_head, 0, sizeof(list_t));
	novo_head->num = num;
	if (str)
	{
		novo_head->str = _strdup(str);
		if (!novo_head->str)
		{
			free(novo_head);
			return (NULL);
		}
	}
	novo_head->next = *head;
	*head = novo_head;
	return (novo_head);
}

/**
 * add_node_end - adds a node to the list ending
 * @head: pointer to head node
 * @str: field of node
 * @num: node index used
 *
 * Return: new size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *novo_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	novo_node = malloc(sizeof(list_t));
	if (!novo_node)
		return (NULL);
	_memset((void *)novo_node, 0, sizeof(list_t));
	novo_node->num = num;
	if (str)
	{
		novo_node->str = _strdup(str);
		if (!novo_node->str)
		{
			free(novo_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = novo_node;
	}
	else
		*head = novo_node;
	return (novo_node);
}

/**
 * print_list_str - display the string element
 * @h: pointer to first node
 *
 * Return: size
 */
size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - remove node from certain index
 * @head: pointer to first node
 * @index: index of node to delete
 *
 * Return: success 1, 0 failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *pre_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			pre_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes
 * @head_ptr: pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *nex_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		nex_node = node->next;
		free(node->str);
		free(node);
		node = nex_node;
	}
	*head_ptr = NULL;
}
