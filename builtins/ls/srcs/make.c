/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:07:47 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 20:25:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*ft_list(ushort flags)
{
	t_dir	*list;

	if (!(list = (t_dir *)malloc(sizeof(t_dir))))
	{
		perror("ft_ls");
		exit(-1);
	}
	list->f_names = NULL;
	list->next = NULL;
	list->pre = NULL;
	list->flags = flags;
	list->size = 0;
	list->gid = 0;
	list->uid = 0;
	list->total = 0;
	list->time_mod = 0;
	list->a_time = 0;
	list->nlink = 0;
	list->name = NULL;
	list->path = NULL;
	list->mode = 0;
	list->len = 0;
	list->level = 1;
	list->st_rdev = 0;
	return (list);
}

t_dir	*swap_list(t_dir *cur, t_dir *next)
{
	next->pre = cur->pre;
	cur->next = next->next;
	next->next = cur;
	cur->pre = next;
	if (cur->next)
		(cur->next)->pre = cur;
	return (next);
}

t_dir	*next_elem(t_dir *request, t_prt_cols pprm)
{
	ushort	i;

	i = 0;
	while (++i <= pprm.rows && request)
		request = request->next;
	return (request);
}

void	print_usage(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-@RSadfglrtu] [file ...]\n");
	exit(-1);
}

uint8_t	get_bit(int nlink)
{
	uint8_t	bit;

	bit = 1;
	if (!nlink)
		return (bit);
	while (nlink /= 10)
		bit++;
	return (bit);
}
