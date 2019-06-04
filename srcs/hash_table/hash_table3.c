/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/06/04 20:09:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_my_table(void)
{
	free_hash_table(g_term.hash_table, g_term.hash_table_size);
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

void	print_hash_table(t_hash **table, unsigned short len)
{
	short	i;
	t_hash	**table_copy;
	t_hash	*hash;

	i = -1;
	table_copy = table;
	while (++i < len)
	{
		hash = table_copy[i];
		while (hash)
		{
			ft_putstr_fd(hash->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(hash->path, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			hash = hash->next;
		}
	}
}
