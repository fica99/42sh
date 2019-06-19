/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:22:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/19 15:22:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	print_history(char **history)
{
	short	i;

	i = -1;
	while (history[++i])
	{
		ft_putnbr_fd(i + 1, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(history[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}