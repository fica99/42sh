/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:22:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	print_history(t_history *history_buff)
{
	short	i;
	char	**history;

	i = -1;
	history = history_buff->history_buff;
	while (history[++i])
	{
		ft_putnbr_fd(i + 1, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(history[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
