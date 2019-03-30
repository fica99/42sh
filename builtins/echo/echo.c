/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/30 20:18:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	flag_n(char s)
{
	if (s == 'n')
		return (1);
	return (0);
}

void	echo(int argc, char **argv)
{
	unsigned short	i;
	uint8_t			flags;

	i = 1;
	flags = find_flags(argv, &i, flag_n);
	while (argv[i])
	{
		ft_putstr(argv[i++]);
		if (argc != i)
			ft_putchar(' ');
	}
	if (!(is_flags(flags, 'n')) || argc == 1)
		ft_putchar('\n');
}