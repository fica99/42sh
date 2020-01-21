/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_autocom_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:53:31 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/21 19:28:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static size_t		rl_autocom_bin_size(char *word, char **path)
{
	short	i;
	short	j;
	size_t	counter;
	char	**content;

	j = -1;
	counter = 0;
	while (path[++j])
	{
		if ((content = ft_dir_content(path[j], 0)))
		{
			i = -1;
			while (content[++i])
			{
				if (!ft_strcmp(content[i], ".") ||
				!ft_strcmp(content[i], ".."))
					continue ;
				if (!ft_strncmp(content[i], word, ft_strlen(word)))
					++counter;
			}
			ft_free_dar(content);
		}
	}
	return (counter);
}

static void			rl_autocom_get_builtins(char **res, char *word, short index)
{
	char	*buf;
	int		fd;
	short	len;
	int		gnl;

	buf = NULL;
	len = ft_strlen(word);
	if ((fd = open(RL_BUILTINS_LIST, RL_OPEN_BUILTINS_LIST,
		RL_PERM_BUILTINS_LIST)) == -1)
		rl_err("42sh", "open() error", NOERROR);
	while ((gnl = get_next_line(fd, &buf)) > 0)
	{
		if (!ft_strncmp(buf, word, len))
			res[++index] = buf;
		else
			ft_strdel(&buf);
	}
	if (gnl < 0)
		rl_err("42sh", "get_next_line() error", NOERROR);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", NOERROR);
}

static void			rl_autocom_get_bins(char **res, char *word, char **path)
{
	short	i;
	short	j;
	short	index;
	char	**content;

	j = -1;
	index = -1;
	while (path[++j])
	{
		if ((content = ft_dir_content(path[j], 0)))
		{
			i = -1;
			while (content[++i])
			{
				if (!ft_strcmp(content[i], ".") ||
				!ft_strcmp(content[i], ".."))
					continue ;
				if (!ft_strncmp(content[i], word, ft_strlen(word)))
					if (!(res[++index] = ft_strdup(content[i])))
						err_exit("42sh", "malloc() error", NULL, ENOMEM);
			}
			ft_free_dar(content);
		}
	}
	rl_autocom_get_builtins(res, word, index);
}

static size_t		rl_autocom_builtins_size(char *word)
{
	char	*buf;
	size_t	size;
	int		fd;
	short	len;
	int		gnl;

	buf = NULL;
	size = 0;
	len = ft_strlen(word);
	if ((fd = open(RL_BUILTINS_LIST, RL_OPEN_BUILTINS_LIST,
		RL_PERM_BUILTINS_LIST)) == -1)
		rl_err("42sh", "open() error", NOERROR);
	while ((gnl = get_next_line(fd, &buf)) > 0)
	{
		if (!ft_strncmp(buf, word, len))
			++size;
		ft_strdel(&buf);
	}
	if (gnl < 0)
		rl_err("42sh", "get_next_line() error", NOERROR);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", NOERROR);
	return (size);
}

char				**rl_autocom_bin(char *word)
{
	char	*env_path;
	char	**path;
	size_t	bin_size;
	char	**res;

	if (!(env_path = get_env("PATH", ENV)))
		env_path = "\0";
	if (!(path = ft_strsplit(env_path, ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	bin_size = rl_autocom_bin_size(word, path);
	bin_size += rl_autocom_builtins_size(word);
	if (!(res = ft_darnew(bin_size)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl_autocom_get_bins(res, word, path);
	ft_free_dar(path);
	return (res);
}
