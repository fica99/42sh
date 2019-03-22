/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:21:48 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/01 15:26:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*sort_one_list(t_dir *list, uint8_t (fun)(t_dir*))
{
	t_dir	*head;

	if (!list)
		return (NULL);
	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (fun(list))
		{
			list = swap_list(list, (*list).next);
			if ((*list).pre)
			{
				(list->pre)->next = list;
				list = (*list).pre;
			}
			else
				head = list;
			continue ;
		}
		list = (*list).next;
	}
	return (head);
}

uint8_t	list_rev(t_dir *list)
{
	uint8_t	i;

	i = 0;
	if (ft_strcmp((*list).name, (*((*list).next)).name) < 0)
		i = 1;
	return (i);
}

uint8_t	list_time_mod(t_dir *list)
{
	uint8_t	i;

	i = 0;
	if (list->time_mod < (list->next)->time_mod)
		i = 1;
	return (i);
}

uint8_t	list_time_a(t_dir *list)
{
	uint8_t	i;

	i = 0;
	if (list->a_time < (list->next)->a_time)
		i = 1;
	return (i);
}

uint8_t	list_sort(t_dir *list)
{
	uint8_t	i;

	i = 0;
	if (ft_strcmp((*list).name, (*((*list).next)).name) > 0)
		i = 1;
	return (i);
}
