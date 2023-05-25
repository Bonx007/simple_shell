#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * is_cmd_in_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (pathstr == NULL)
	{
		return (NULL);
	}

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(cmd))
		{
			return (cmd);
		}
	}

	while (pathstr[i])
	{
		if (pathstr[i] == ':' || pathstr[i] == '\0')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(path))
			{
				return (path);
			}
			if (pathstr[i] == '\0')
			{
				break;
			}
			curr_pos = i + 1;
		}
		i++;
	}
	return (NULL);
}
