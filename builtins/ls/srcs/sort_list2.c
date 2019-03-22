/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:03:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 15:14:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint8_t	list_size(t_dir *list)
{
	uint8_t	i;

	i = 0;
	if (list->size < (list->next)->size)
		i = 1;
	return (i);
}

t_dir	*sorting(t_dir *request, ushort flags)
{
	if (!request)
		return (NULL);
	if (is_flags(flags, 'r'))
		return (sort_one_list(request, list_rev));
	if (is_flags(flags, 't'))
		return (sort_one_list(request, list_time_mod));
	if (is_flags(flags, 'u'))
		return (sort_one_list(request, list_time_a));
	if (is_flags(flags, 'S'))
		return (sort_one_list(request, list_size));
	if (is_flags(flags, 'f'))
		return (request);
	return (sort_one_list(request, list_sort));
}
