#include "shell.h"

/**
 * get_history_file - gets the file
 * @info: input parameter struct
 *
 * Return: the file in the string
 */

char *get_history_file(info_t *info)
{
	char *bu, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);
	bu = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!bu)
		return (NULL);
	bu[0] = 0;
	_strcpy(bu, direc);
	_strcat(bu, "/");
	_strcat(bu, HIST_FILE);
	return (bu);
}

/**
 * write_history - creates a file, or add to an old one
 * @info: the input parameter struct
 *
 * Return: success 1, -1 otherwise
 */
int write_history(info_t *info)
{
	ssize_t f_description;
	char *f_name = get_history_file(info);
	list_t *node = NULL;

	if (!f_name)
		return (-1);

	f_description = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (f_description == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, f_description);
		_putfd('\n', f_description);
	}
	_putfd(BUF_FLUSH, f_description);
	close(f_description);
	return (1);
}

/**
 * read_history - reads from history file
 * @info: the input parameter struct
 *
 * Return: history count on success, or 0
 */
int read_history(info_t *info)
{
	int j, la = 0, l_counter = 0;
	ssize_t fdesciption, rdlen, fsize = 0;
	struct stat st;
	char *bu = NULL, *f_name = get_history_file(info);

	if (!f_name)
		return (0);

	fdesciption = open(f_name, O_RDONLY);
	free(f_name);
	if (fdesciption == -1)
		return (0);
	if (!fstat(fdesciption, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bu = malloc(sizeof(char) * (fsize + 1));
	if (!bu)
		return (0);
	rdlen = read(fdesciption, bu, fsize);
	bu[fsize] = 0;
	if (rdlen <= 0)
		return (free(bu), 0);
	close(fdesciption);
	for (j = 0; j < fsize; j++)
		if (bu[j] == '\n')
		{
			bu[i] = 0;
			build_history_list(info, bu + la, l_counter++);
			la = j + 1;
		}
	if (la != j)
		build_history_list(info, bu + la, l_counter++);
	free(bu);
	info->histcount = l_counter;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds to a history linked list
 * @info: Structure containing potential arguments
 * @buf: buffer paramnetr
 * @linecount: the history linecount, histcount
 *
 * Return: will be 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nodd = NULL;

	if (info->history)
		nodd = info->history;
	add_node_end(&nodd, buf, linecount);

	if (!info->history)
		info->history = nodd;
	return (0);
}

/**
 * renumber_history - update the history linked list
 * @info: Structure containing potential arguments
 *
 * Return: the new history count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
