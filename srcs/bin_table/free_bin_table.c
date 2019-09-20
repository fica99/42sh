/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bin_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/09/26 20:01:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash	**free_bin_table(t_hash **bin_table, size_t *bin_table_size)
{
	if (bin_table)
	{
		bin_table = free_hash_table(bin_table, *bin_table_size,
		FREE_HASH_DATA);
		*bin_table_size = 0;
	}
	return (bin_table);
}
