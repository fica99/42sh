/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fname.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:42:38 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/06 17:15:58 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char		*locate(char *fname, char **path)
{
	DIR				*dr;
	struct dirent	*dirent;

	if (!path)
		return (fname);
	while (*path)
	{
		if (!(dr = opendir(*path)))
		{
			path++;
			continue;
		}
		while ((dirent = readdir(dr)))
		{
			if (!(ft_strcmp(dirent->d_name, fname)))
			{
				closedir(dr);
				return (ft_pathjoin(*path, dirent->d_name));
			}
		}
		closedir(dr);
		path++;
	}
	return (NULL);
}

char			*find_in_path(char *filename, char **environ)
{
	char	**paths;
	char	*res;
	char	*path_var;

	if (!(path_var = ft_getvar("PATH", environ)))
		return (NULL);
	if (!(paths = ft_strsplit(path_var, ':')))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	res = locate(filename, paths);
	ft_free_dar(paths);
	return (res);
}

static int		find_path_var(char *name, char **paths)
{
	char	*tmp;

	if (!(tmp = ft_strrchr(name, '/')))
		name = CUR_D;
	else
		ft_bzero(tmp, ft_strlen(tmp));
	while (*paths)
	{
		if (!ft_pathcmp(*paths, name))
			return (0);
		paths++;
	}
	return (-1);
}

int				check_path_var(char *fname, char **environ)
{
	char	*tmp;
	char	**paths;
	char	*path_var;
	int		ret;

	if (!(path_var = ft_getvar("PATH", environ)))
		return (-1);
	if (!(tmp = ft_strdup(fname)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	if (!(paths = ft_strsplit(path_var, ':')))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	ret = find_path_var(tmp, paths);
	free(tmp);
	ft_free_dar(paths);
	return (ret);
}

char			*get_fname(char *arg)
{
	char *fname;

	if (ft_strchr(arg, '/'))
		fname = arg;
	else if (!(fname = (char *)get_hash_data(g_bin_hash_table.table,
	arg, g_bin_hash_table.size)))
	{
		if (!(fname = find_in_path(arg, g_environ.vars)))
			err_exit("42sh", "command not found", arg, NOERROR);
	}
	else
	{
		if (check_path_var(fname, g_environ.vars) < 0)
			err_exit("42sh", "command not found", arg, NOERROR);
	}
	return (fname);
}
