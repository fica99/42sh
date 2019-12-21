/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:00:21 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:00:23 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	remove_slashes(void)
{
	char	**tmp;
	int		i;

	i = -1;
	if ((tmp = ft_strsplit(g_curr_dir, '/')) == 0)
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
	*g_curr_dir = '/';
	while (tmp[++i])
		path_add(tmp[i]);
	ft_free_dar(tmp);
}

static int		try_cdpath(char *path, char **cdpath, t_flag no_links)
{
	int		i;
	char	*tmp;
	int		ret;

	ret = -1;
	i = -1;
	while (cdpath[++i])
	{
		if (!ft_strcmp(cdpath[i], ".."))
			continue ;
		if (!(tmp = ft_pathjoin(cdpath[i], path)))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
		if (!(ret = change_wdir(tmp, no_links)))
		{
			if (no_links)
				ft_putln(tmp);
			else
				ft_putln(g_curr_dir);
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (ret);
}

int				cdpath_handle(char *path, t_flag no_links)
{
	char	*var_val;
	char	**cdpath;
	int		ret;

	if (!ft_strncmp(path, ".", 1) || !ft_strncmp(path, "..", 2))
		return (-1);
	if (!(var_val = get_env("CDPATH", ALL_ENV)))
		return (-1);
	if (!(cdpath = ft_strsplit(var_val, ':')))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	ret = try_cdpath(path, cdpath, no_links);
	ft_free_dar(cdpath);
	return (ret);
}
