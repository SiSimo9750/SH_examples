#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: input parameter struct
 * @buf: input address
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rr = 0;
	size_t len_pp = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rr = getline(buf, &len_pp, stdin);
#else
		rr = _getline(info, buf, &len_pp);
#endif
		if (rr > 0)
		{
			if ((*buf)[rr - 1] == '\n')
			{
				(*buf)[rr - 1] = '\0'; /* remove trailing newline */
				rr--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = rr;
				info->cmd_buf = buf;
			}
		}
	}
	return (rr);
}

/**
 * get_input - gets a line minus newline
 * @info: input parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t rr = 0;
	char **buf_pp = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rr = input_buf(info, &buf, &len);
	if (rr == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_pp = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_pp = buf; /* else not a chain, pass back buffer from _getline() */
	return (rr); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: input parameter struct
 * @buf: buffer to reqd
 * @i: input size
 *
 * Return: will be r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rr = 0;

	if (*i)
		return (0);
	rr = read(info->readfd, buf, READ_BUF_SIZE);
	if (rr >= 0)
		*i = rr;
	return (rr);
}

/**
 * _getline - gets the next line of input
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr
 *
 * Return: will be s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t kk;
	ssize_t rr = 0, s = 0;
	char *pp = NULL, *new_pp = NULL, *ch;

	pp = *ptr;
	if (pp && length)
		s = *length;
	if (i == len)
		i = len = 0;

	rr = read_buf(info, buf, &len);
	if (rr == -1 || (rr == 0 && len == 0))
		return (-1);

	ch = _strchr(buf + i, '\n');
	kk = ch ? 1 + (unsigned int)(ch - buf) : len;
	new_pp = _realloc(pp, s, s ? s + kk : kk + 1);
	if (!new_pp) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (s)
		_strncat(new_pp, buf + i, kk - i);
	else
		_strncpy(new_pp, buf + i, kk - i + 1);

	s += kk - i;
	i = kk;
	pp = new_pp;

	if (length)
		*length = s;
	*ptr = pp;
	return (s);
}

/**
 * sigintHandler - blocks controlC
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
