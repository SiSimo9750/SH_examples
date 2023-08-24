#include "shell.h"

/**
 * list_len - get length of linked list
 * @h: first node pointer
 *
 * Return: list size
 */
size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: first node pointer
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *nodd = head;
	size_t n = list_len(head), m;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; nodd; nodd = nodd->next, i++)
	{
		str = malloc(_strlen(nodd->str) + 1);
		if (!str)
		{
			for (m = 0; m < n; m++)
				free(strs[m]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nodd->str);
		strs[n] = str;
	}
	strs[n] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - returns node starts with prefix
 * @node: head pointer
 * @prefix: string
 * @c: the next character after prefix
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: list head pinter
 * @node: node pointer
 *
 * Return: index of node or -1 on error
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
