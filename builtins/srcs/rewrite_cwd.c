/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_cwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:47:52 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 14:38:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	path_back(void)
{
	int i;

	i = ft_strlen(g_curr_dir) - 1;
	while (g_curr_dir[i] != '/')
		--i;
	if (!i)
		i++;
	ft_bzero(&g_curr_dir[i], ft_strlen(&g_curr_dir[i]));
}

void		path_add(char *tmp)
{
	int len;

	len = ft_strlen(g_curr_dir) - 1;
	if (g_curr_dir[len] != '/')
		g_curr_dir[len + 1] = '/';
	ft_strcat(g_curr_dir, tmp);
}

static void	rewrite_global(char **split_path)
{
	char **tmp;

	if (!split_path)
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	tmp = split_path;
	while (*split_path)
	{
		if (!ft_strcmp(*split_path, "."))
		{
			split_path++;
			continue ;
		}
		else if (!ft_strcmp(*split_path, ".."))
			path_back();
		else
			path_add(*split_path);
		split_path++;
	}
	ft_free_dar(tmp);
}

static void	rewrite_cwd(char *path)
{
	if (*path == '/')
	{
		ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
		ft_memcpy(g_curr_dir, path, ft_strlen(path));
		remove_slashes();
	}
	else
		rewrite_global(ft_strsplit(path, '/'));
}

int			change_wdir(char *path, t_flag no_links)
{
	char	*tmp;
	int		ret;

	if (!(tmp = ft_strdup(g_curr_dir)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	rewrite_cwd(path);
	if ((ret = chdir(g_curr_dir)) < 0)
	{
		ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
		ft_memcpy(g_curr_dir, tmp, ft_strlen(tmp));
	}
	else
	{
		if (no_links)
		{
			ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
			if (!(getcwd(g_curr_dir, MAXDIR)))
				err_exit("42sh", "getcwd() error", NULL, NOERROR);
		}
		set_env("OLDPWD", get_env("PWD", ENV), ENV);
		set_env("PWD", g_curr_dir, ENV);
	}
	free(tmp);
	return (ret);
}
