/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:18:15 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/26 16:17:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_bin_table(t_hash **bin_table, size_t size)
{
	size_t	i;
	t_hash	**table_copy;
	t_hash	*hash;

	i = 0;
	table_copy = bin_table;
	while (i < size)
	{
		hash = table_copy[i++];
		while (hash)
		{
			ft_putstr_fd(ft_strrchr(hash->data, '/') + 1, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(hash->data, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			hash = hash->next;
		}
	}
}

int			hash(int ac, char **av)
{
	(void)ac;
	(void)av;
	print_bin_table(g_bin_table.table, g_bin_table.size);
	return (0);
}
