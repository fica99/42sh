/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 09:25:12 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/03 21:33:23 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	*ft_strrev(char *str)
{
	char *start;
	char *finish;
	char *end;
	char c;

	start = str;
	finish = str;
	while (*str)
		str++;
	str--;
	end = str;
	while (start < end)
	{
		c = *start;
		*start = *end;
		*end = c;
		end--;
		start++;
	}
	return (finish);
}

static char	*get_dirpath(char *arg)
{
	int		len;
	char	*argcpy;

	argcpy = ft_memalloc((ft_strlen(arg) + 1));
	argcpy = ft_strcpy(argcpy, arg);
	if (!(ft_strcmp(argcpy, "/")))
		return (argcpy);
	len = (int)ft_strlen(arg) - 1;
	if (argcpy[len] == '/')
		len--;
	while (argcpy[len] && argcpy[len] != '/')
	{
		argcpy[len] = '\0';
		len--;
		if (argcpy[len] == '/' && len != 0)
		{
			argcpy[len] = '\0';
			break ;
		}
	}
	return (argcpy);
}

static char	*get_filename(char *arg)
{
	int		len;
	int		i;
	char	*filename;

	i = 0;
	len = (int)ft_strlen(arg) - 1;
	filename = ft_memalloc(len + 2);
	if (arg[len] == '/')
		len--;
	while (arg[len] && arg[len] != '/')
	{
		filename[i] = arg[len];
		i++;
		len--;
	}
	filename = ft_strrev(filename);
	return (filename);
}

static int	dir_with_filename(char *dirpath, char **argv)
{
	struct dirent	*dp;
	DIR				*di;
	char			*filename;

	if ((di = opendir(dirpath)) == NULL)
		return (1);
	filename = get_filename(argv[2]);
	while ((dp = readdir(di)) != NULL)
	{
		if (!(ft_strcmp(dp->d_name, filename)))
		{
			free(filename);
			closedir(di);
			return (file_was_found(argv));
		}
	}
	free(filename);
	closedir(di);
	return (1);
}

int			works_with_dir(char **argv)
{
	DIR				*di;
	struct dirent	*dp;
	char			*dirpath;

	dirpath = NULL;
	if (!(ft_strcmp(argv[2], "/")))
		return (0);
	(ft_strchr(argv[2], '/')) ? dirpath = get_dirpath(argv[2]) : 0;
	if (dirpath)
		return (dir_with_filename(dirpath, argv));
	else
	{
		if ((di = opendir(".")) == NULL)
			return (1);
		while ((dp = readdir(di)) != NULL)
		{
			if (!(ft_strcmp(dp->d_name, argv[2])))
			{
				closedir(di);
				return (file_was_found(argv));
			}
		}
		closedir(di);
	}
	return (1);
}
