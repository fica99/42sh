/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_add_to_cycle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 06:04:51 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/11 15:44:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void				free_cycle_list(t_cycle_list *l)
{
	if (!l)
		return ;
	free_cycle_list(l->next);
	free(l);
}

static t_cycle_list	*c_list_new(char *alias)
{
	t_cycle_list *new;

	new = (t_cycle_list *)ft_memalloc(sizeof(t_cycle_list));
	new->name = alias;
	return (new);
}

void				add_to_cycle_list(char *alias, t_cycle_list **l)
{
	static t_cycle_list *last;

	if (!*l)
	{
		*l = c_list_new(alias);
		last = *l;
		return ;
	}
	last->next = c_list_new(alias);
	last = last->next;
}
