/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:18:15 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/19 15:18:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

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
