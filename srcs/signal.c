/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/02 11:23:03 by filip            ###   ########.fr       */
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

	if (sign == SIGINT)
		ft_putchar('\n');
	if (sign == SIGSEGV)
		print_error("Segmentation fault (core dumped)\n", NULL, NULL, 0);
	if (sign == SIGABRT)
		print_error("Aborted\n", NULL, NULL, 0);
	if (sign == SIGFPE)
		print_error("Floating point exception (core dumped)", NULL, NULL, 0);
	if (sign == SIGTERM)
		exit(1);
}
