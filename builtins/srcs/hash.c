/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:18:15 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/05 15:43:00 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void			print_hash(char **path)
{
	short	i;
	short	index;
	char	**content;
	int		j;

	index = -1;
	j = -1;
	while (path[++j])
	{
		if ((content = ft_dir_content(path[++j], 1)))
		{
			ft_dar_sort(content);
			i = -1;
			while (content[++i])
			{
				ft_putstr(content[i]);
				ft_putchar('=');
				ft_putstr(path[j]);
				ft_putchar('/');
				ft_putendl(content[i]);
			}
			ft_free_dar(content);
		}
	}
}

int					hash(int ac, char **av)
{
	char	*env_path;
	char	**path;

	(void)ac;
	(void)av;
	if (!(env_path = get_var("PATH", ENV)))
		return (0);
	if (!(path = ft_strsplit(env_path, ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_dar_sort(path);
	print_hash(path);
	ft_free_dar(path);
	return (0);
}
