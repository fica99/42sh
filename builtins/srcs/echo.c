/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_echo(int argc, char **argv, char **env_cp)
{
	unsigned short	i;

	(void)env_cp;
	i = 0;
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argc != i)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}
