/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/01 15:49:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signalling(char i)
{
	signal(SIGINT, signal_handler);
//	signal(SIGILL, signal_handler);
//	signal(SIGFPE, signal_handler);
	if (i)
		signal(SIGSEGV, signal_handler);
//	signal(SIGILL, signal_handler);
//	signal(SIGILL, signal_handler);

}

void	signal_handler(int sign)
{

	if (sign == SIGINT)
		ft_putchar('\n');;
	if (sign == SIGSEGV)
	{
		print_error("segmentation fault(core dumped)", NULL, NULL, 0);
		exit(1);
	}
}
