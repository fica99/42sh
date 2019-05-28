/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 20:32:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_hash_table(void)
{
	short	i;
	t_hash	**table;
	t_hash	*next;
	t_hash	*copy;

	i = -1;
	table = g_term.hash_table;
	while (++i < g_term.hash_table_size)
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
	g_term.hash_table_size = 0;
	g_term.hash_table = NULL;
}

void	print_hash_table(void)
{
	short	i;
	t_hash	**table;
	t_hash	*hash;

	i = -1;
	table = g_term.hash_table;
	while (++i < g_term.hash_table_size)
	{
		hash = table[i];
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
