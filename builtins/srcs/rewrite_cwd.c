/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_cwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:47:52 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 15:06:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	path_back(void)
{
	int i;

	i = ft_strlen(g_cur_wd) - 1;
	while (g_cur_wd[i] != '/')
		--i;
	if (!i)
		i++;
	ft_bzero(&g_cur_wd[i], ft_strlen(&g_cur_wd[i]));
}

void		path_add(char *tmp)
{
	int len;

	len = ft_strlen(g_cur_wd) - 1;
	if (g_cur_wd[len] != '/')
		g_cur_wd[len + 1] = '/';
	ft_strcat(g_cur_wd, tmp);
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
		ft_bzero(g_cur_wd, ft_strlen(g_cur_wd));
		ft_memcpy(g_cur_wd, path, ft_strlen(path));
		remove_slashes();
	}
	else
		rewrite_global(ft_strsplit(path, '/'));
}

int			change_wdir(char *path, t_flag no_links,
char **environ)
{
	char	*tmp;
	int		ret;

	if (!(tmp = ft_strdup(g_cur_wd)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	rewrite_cwd(path);
	if ((ret = chdir(g_cur_wd)) < 0)
	{
		ft_bzero(g_cur_wd, ft_strlen(g_cur_wd));
		ft_memcpy(g_cur_wd, tmp, ft_strlen(tmp));
	}
	else
	{
		if (no_links)
		{
			ft_bzero(g_cur_wd, ft_strlen(g_cur_wd));
			if (!(getcwd(g_cur_wd, PATH_MAX)))
				err_exit("42sh", "getcwd() error", NULL, NOERROR);
		}
		set_var("OLDPWD", ft_getvar("PWD", environ), ENV);
		set_var("PWD", g_cur_wd, ENV);
	}
	free(tmp);
	return (ret);
}
