/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/07/31 00:10:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_my_hash_table(t_hash **hash_table, unsigned short *hash_table_size)
{
	if (hash_table)
	{
		free_hash_table(hash_table, *hash_table_size);
		ft_memdel((void**)&(hash_table));
		*hash_table_size = 0;
	}
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
