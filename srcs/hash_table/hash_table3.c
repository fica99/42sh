/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/05/20 14:14:29 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_hash_table(void)
{
	int		i;
	t_hash	**table;
	t_hash	*next;

	i = -1;
	table = g_term.hash_table;
	while (++i < g_term.hash_table_size)
	{
        while (table[i])
        {
            ft_memdel((void**)&(table[i]->name));
            ft_memdel((void**)&(table[i]->path));
            next = table[i]->next;
            ft_memdel((void**)&(table[i]));
            table[i] = next;
        }
	}
	ft_memdel((void**)g_term.hash_table);
	g_term.hash_table_size = 0;
}