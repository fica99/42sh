/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/06/13 15:17:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_my_hash_table(void)
{
	free_hash_table(g_term.hash_table, g_term.hash_table_size);
	ft_memdel((void**)&(g_term.hash_table));
	g_term.hash_table_size = 0;
}

void	free_hash_table(t_hash **table, unsigned short len)
{
	short	i;
	t_hash	*next;
	t_hash	*copy;

	i = -1;
	while (++i < len)
	{
		next = table[i];
		while (next)
		{
			ft_memdel((void**)&(next->name));
			ft_memdel((void**)&(next->path));
			copy = next;
			next = next->next;
			ft_memdel((void**)&(copy));
		}
	}
}
