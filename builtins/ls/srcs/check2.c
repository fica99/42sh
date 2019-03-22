/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:02:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/15 16:56:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*check_path(char *path, char *name)
{
	char	*d;
	char	*temp;

	d = NULL;
	if (path[ft_strlen(path) - 1] == '/')
		d = ft_strjoin(path, name);
	else
	{
		d = ft_strjoin(path, "/");
		temp = d;
		d = ft_strjoin(temp, name);
		ft_memdel((void **)&temp);
	}
	return (d);
}

char	**check_dir(int argc, char **argv, uint8_t i)
{
	uint8_t	j;

	j = double_arr_len(argv);
	if (argc - i == 0)
	{
		argv[j + 1] = NULL;
		argv[j] = ".";
	}
	return (argv);
}

t_dir	*check_exist(t_dir *dir, t_dir **head, ushort flags)
{
	if (dir)
	{
		dir->next = ft_list(flags);
		(dir->next)->pre = dir;
		dir = dir->next;
	}
	else
	{
		dir = ft_list(flags);
		*head = dir;
	}
	return (dir);
}

void	delete_from_list(t_dir **dir, t_dir **head)
{
	if ((*dir)->pre)
	{
		*dir = (*dir)->pre;
		free_list(&((*dir)->next));
	}
	else
	{
		free_list(dir);
		*head = *dir;
	}
}

void	free_list(t_dir **request)
{
	if (!request)
		return ;
	ft_memdel((void**)&((*request)->name));
	ft_memdel((void**)&((*request)->path));
	(*request)->f_names = NULL;
	(*request)->next = NULL;
	(*request)->pre = NULL;
	free(*request);
	*request = NULL;
}
