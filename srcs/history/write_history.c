/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:21:43 by filip             #+#    #+#             */
/*   Updated: 2019/05/29 21:10:11 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    add_to_historybuf(void)
{
	short	len;
	short	len_copy;

	len = double_arr_len(g_term.history);
	if (!check_print_arr(g_term.buffer))
		return ;
	if (len >= HISTORY_SIZE)
	{
		len_copy = len;
		while (--len > 0)
			g_term.history[len - 1] = g_term.history[len];
		g_term.history[len_copy - 1] = g_term.buffer;
	}
	else
	{
		g_term.history[len] = g_term.buffer;
		g_term.history[++len] = NULL;
	}
}

char	check_print_arr(char *arr)
{
	short	i;

	i = -1;
	while (arr[++i])
	{
		if (ft_isprint(arr[i]) && arr[i] != ' ')
			return (1);
	}
	return (0);
}