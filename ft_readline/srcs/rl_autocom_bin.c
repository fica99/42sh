/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_autocom_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:53:31 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/03 22:33:15 by aashara-         ###   ########.fr       */
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

static void			rl_autocom_get_builtins(char **res, char *word,
											char **builtins, short index)
{
	int		j;
	short	len;

	j = -1;
	len = ft_strlen(word);
	while (++j < RL_BUILTINS_COUNT)
		if (!ft_strncmp(builtins[j], word, len))
			if (!(res[++index] = ft_strdup(builtins[j])))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
}

static void			rl_autocom_get_files(char **res, char *word,
										char **path, char **builtins)
{
	short	i;
	short	index;
	char	**content;
	int		j;

	index = -1;
	j = -1;
	while (path[++j])
	{
		if ((content = ft_dir_content(path[++j], 0)))
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
	rl_autocom_get_builtins(res, word, builtins, index);
}

static void			rl_autocom_set_builtins(char *builtins[15])
{
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "export";
	builtins[3] = "set";
	builtins[4] = "env";
	builtins[5] = "fc";
	builtins[6] = "bg";
	builtins[7] = "fg";
	builtins[8] = "env";
	builtins[9] = "hash";
	builtins[10] = "unset";
	builtins[11] = "type";
	builtins[12] = "test";
	builtins[13] = "exit";
	builtins[14] = "pwd";
}

char				**rl_autocom_bin(char *word)
{
	char		*env_path;
	char		**path;
	size_t		bin_size;
	char		**res;
	static char	*builtins[RL_BUILTINS_COUNT];

	if (!*builtins)
		rl_autocom_set_builtins(builtins);
	if (!(env_path = get_var("PATH", ENV)))
		env_path = "\0";
	if (!(path = ft_strsplit(env_path, ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	bin_size = rl_autocom_bin_size(word, path) + RL_BUILTINS_COUNT;
	if (!(res = ft_darnew(bin_size)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl_autocom_get_files(res, word, path, builtins);
	ft_free_dar(path);
	return (res);
}
