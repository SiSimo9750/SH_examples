#include "shell.h"

/**
 * _myhistory - displays the history list
 *
 * @info: Structure containing potential arguments
 *
 *  Return: will be 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets alias
 * @info: input parameter struct
 * @str: the string
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *pp, ch;
	int rett;

	pp = _strchr(str, '=');
	if (!pp)
		return (1);
	ch = *pp;
	*pp = 0;
	rett = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pp = ch;
	return (rett);
}

/**
 * set_alias - sets alias
 * @info: input parameter struct
 * @str: the string
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *pp;

	pp = _strchr(str, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias
 * @node: the alias input node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *pp = NULL, *aa = NULL;

	if (node)
	{
		pp = _strchr(node->str, '=');
		for (aa = node->str; aa <= pp; aa++)
			_putchar(*aa);
		_putchar('\'');
		_puts(pp + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin
 * @info: Structure containing potential arguments
 
 *  Return: will be 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *pp = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		pp = _strchr(info->argv[j], '=');
		if (pp)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
