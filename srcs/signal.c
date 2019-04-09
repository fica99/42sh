/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/09 16:57:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signalling(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGFPE, signal_handler);
}

void	signal_handler(int sign)
{
	char	*arr;

	if (sign == SIGINT)
	{
		ft_putchar('\n');
		return ;
	}
	if (sign == SIGSEGV)
		arr = "Segmentation fault (core dumped)\n";
	if (sign == SIGABRT)
		arr = "Aborted\n";
	if (sign == SIGFPE)
		arr = "Floating point exception (core dumped)\n";
	if (sign == SIGTERM)
		arr = "Killed\n";
	if (sign == SIGWINCH)
	{
		get_cord();
		return;
	}
	print_error(arr, NULL, NULL, 0);
	exit(1);
}
