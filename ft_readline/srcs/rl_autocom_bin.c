/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_autocom_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:53:31 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/21 17:19:38 by aashara-         ###   ########.fr       */
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
}

static void		rl_autocom_sort_bin(char **res, size_t size)
{
	size_t	i;
	size_t	j;
	char	*elem;
	char	*tmp;

	if (size < 2)
		return ;
	i = 0;
	j = size - 1;
	elem = res[size >> 1];
	while (i <= j)
	{
		while (ft_strcmp(res[i], elem) < 0)
			++i;
		while (ft_strcmp(res[j], elem) > 0)
			--j;
		if (i <= j) {
			tmp = res[i];
			res[i++] = res[j];
			res[j--] = tmp;
		}
	}
	if (j > 0)
		rl_autocom_sort_bin(res, j);
	if (size > i)
		rl_autocom_sort_bin(res + i, size - i);
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
	if (!(res = ft_darnew(bin_size)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl_autocom_get_bins(res, word, path);
	rl_autocom_sort_bin(res, bin_size);
	ft_free_dar(path);
	return (res);
}
