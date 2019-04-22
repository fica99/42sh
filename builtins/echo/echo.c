/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/20 14:05:08 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(int argc, char **argv)
{
	unsigned short	i;

	i = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
		if (argc != i)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}