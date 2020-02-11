/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:17:29 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/11 15:32:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char		*n_pathcat(char *p, char *p2, DIR *dr)
{
	char *ret;

	ret = ft_pathjoin(p, p2);
	closedir(dr);
	return (ret);
}

static char		*locate(char *fname, char **path)
{
	DIR				*dr;
	struct dirent	*dirent;

	if (!path)
		return (ft_strdup(fname));
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
				return (n_pathcat(*path, dirent->d_name, dr));
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

	if (!environ)
	{
		if (!(path_var = get_var("PATH", ALL_VARS)))
			return (NULL);
	}
	else
	{
		if (!(path_var = ft_getvar("PATH", environ)))
			return (NULL);
	}
	if (!(paths = ft_strsplit(path_var, ':')))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	res = locate(filename, paths);
	ft_free_dar(paths);
	return (res);
}
