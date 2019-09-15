/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_recalc_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olegmulko <olegmulko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:46:32 by olegmulko         #+#    #+#             */
/*   Updated: 2019/07/06 16:00:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ac_index_tracking(t_autocom *ac)
{
	if (ac->index < ac->opts_size - 1)
		ac->index++;
	else
	{
		ac->index = 0;
		ac->index_print = 0;
		ac->opts_print = ac->fixed_opts_print;
		ac->rows = ac_get_rows(ac->fixed_opts_print, ac->cols);
	}
}

void	ac_opts_tracking(t_autocom *ac)
{
	int	options_dest;

	if (ac->index == ac->opts_print)
	{
		ac->index_print = ac->opts_print;
		if (ac->opts_size - ac->opts_print >= ac->fixed_opts_print)
			ac->opts_print += ac->fixed_opts_print;
		else
		{
			options_dest = ac->opts_size - ac->opts_print;
			ac->opts_print = ac->opts_size;
			ac->rows = ac_get_rows(options_dest, ac->cols);
		}
	}
}
