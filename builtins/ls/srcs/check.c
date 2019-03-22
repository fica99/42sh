/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/15 16:56:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR		*check_open(char *path, char *name)
{
	DIR	*folder;

	if (!(folder = opendir(path)))
	{
		check_err(name, path);
		return (NULL);
	}
	return (folder);
}

void	check_close(int nb)
{
	if (nb == -1)
	{
		perror("ft_ls");
		exit(-1);
	}
}

uint8_t	double_arr_len(char **d_names)
{
	uint8_t	i;

	i = 0;
	if (!(d_names))
		return (i);
	while (d_names[i])
		i++;
	return (i);
}

void	free_all_list(t_dir *request)
{
	t_dir	*file;

	if (!request)
		return ;
	while (request)
	{
		file = request;
		request = request->next;
		free_list(&file);
	}
}

t_dir	*make_dir_list(t_dir **head, t_dir *dir)
{
	t_dir	*direct;

	direct = *head;
	while (direct->next && get_type(direct->next->mode) == 'd')
		direct = direct->next;
	if (!(direct->next))
	{
		dir = NULL;
		*head = NULL;
	}
	else
	{
		dir = direct;
		direct->next = NULL;
	}
	return (dir);
}
