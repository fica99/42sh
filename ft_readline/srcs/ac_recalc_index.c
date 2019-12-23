/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_recalc_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:52:35 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 18:52:36 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

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
