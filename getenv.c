#include "shell.h"

/**
 * get_environ - get the string array copy of our env
 * @info: Structure containing potential arguments
 * Return: will 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - delete env var
 * @info: Structure containing potential arguments
 *
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or edit new one
 *
 * @info: Structure containing potential arguments
 * @var: the string env var
 * @value: the env var value
 *  Return: will be 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *b = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	b = malloc(_strlen(var) + _strlen(value) + 2);
	if (!b)
		return (1);
	_strcpy(b, var);
	_strcat(b, "=");
	_strcat(b, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = b;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), b, 0);
	free(b);
	info->env_changed = 1;
	return (0);
}
