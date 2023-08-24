#include "shell.h"

/**
 * is_cmd - file is an exe cmd
 * @info: the input info struct
 * @path: path to the file
 *
 * Return: if yes 1, 0 if not
 */
int is_cmd(info_t *info, char *path)
{
	struct stat sta;

	(void)info;
	if (!path || stat(path, &sta))
		return (0);

	if (sta.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: PATH string
 * @start: index starts
 * @stop: index stop
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, kk = 0;

	for (kk = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[kk++] = pathstr[j];
	buf[kk] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the input info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: cmd full path
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, actual_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, actual_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			actual_pos = j;
		}
		j++;
	}
	return (NULL);
}
