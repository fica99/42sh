/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 22:19:26 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 19:09:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_get_hist_size(t_rl_history *history)
{
	history->histfilesize = ft_atoi(get_env("HISTFILESIZE", SET_ENV));
	history->histsize = ft_atoi(get_env("HISTSIZE", SET_ENV));
}

void	rl_check_history_size(t_rl_history *history)
{
	size_t	histsize;

	histsize = history->histsize;
	rl_get_hist_size(history);
	if (histsize != history->histsize)
	{
		rl_free_history(history);
		rl_init_history(history);
	}
}
