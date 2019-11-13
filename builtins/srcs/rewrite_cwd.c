/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:47:52 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/07 18:47:54 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	path_back(void)
{
	int i;

	i = ft_strlen(g_curr_dir) - 1;
	while (g_curr_dir[i] != '/')
		--i;
	if (!i)
		i++;
	ft_bzero(&g_curr_dir[i], ft_strlen(&g_curr_dir[i]));
}

void	path_add(char *tmp)
{
	int len;

	len = ft_strlen(g_curr_dir) - 1;
	if (g_curr_dir[len] != '/')
		g_curr_dir[len + 1] = '/';
	ft_strcat(g_curr_dir, tmp);
}

void	rewrite_global(char **split_path)
{
	char **tmp;

	if (!split_path)
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
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

void	remove_slashes(void)
{
	char	**tmp;
	int		i;

	i = -1;
	if ((tmp = ft_strsplit(g_curr_dir, '/')) == 0)
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
	*g_curr_dir = '/';
	while (tmp[++i])
		path_add(tmp[i]);
	ft_free_dar(tmp);
}

void	rewrite_cwd(char *path, t_flag no_links)
{
	if (no_links || access(g_curr_dir, F_OK))
		getwd(g_curr_dir);
	if (*path == '/')
	{
		ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
		ft_memcpy(g_curr_dir, path, ft_strlen(path));
		remove_slashes();
	}
	else
		rewrite_global(ft_strsplit(path, '/'));
}

int	change_wdir(char *path, t_flag no_links)
{
	char *tmp;

	if (!(tmp = ft_strdup(g_curr_dir)))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	rewrite_cwd(path, no_links);
	if ((chdir(g_curr_dir)) < 0)
	{
		ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
		ft_memcpy(g_curr_dir, tmp, ft_strlen(tmp));
		return (-1);
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", g_env.env));
	ft_setenv("PWD", g_curr_dir);
	free(tmp);
	return (0);
}
