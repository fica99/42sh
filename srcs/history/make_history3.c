/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:25:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/31 18:04:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    free_history(void)
{
   char    	**buf;
	t_history	*history;

	buf = g_term.history->history_buff;
	history = g_term.history;
	free_double_arr(buf);
    ft_memdel((void**)&history);
}