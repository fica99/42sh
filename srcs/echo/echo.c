/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/20 21:01:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint8_t	add_flag(uint8_t flags, char flag, uint8_t i)
{
	if (i == 1)
	{
		if (flag == 'n')
			return (flags | 1);
	}
	return (0);
}

static uint8_t	is_flags(uint8_t flags, char flag)
{
	if (flag == 'n' && (flags & 1) == 1)
		return (1);
	return (0);
}

static uint8_t	echo_find_flags(char **argv, unsigned short *i)
{
	uint8_t	k;
	uint8_t	flags;

	flags = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		k = 0;
		while (argv[*i][++k])
		{
			if (argv[*i][k] == 'n')
				flags = add_flag(flags, argv[*i][k], 1);
			else
				return (flags);
		}
		(*i)++;
	}
	return (flags);
}

uint8_t	echo(int argc, char **argv, char **env)
{
	unsigned short	i;
	uint8_t			flags;

	i = 1;
	env = NULL;
	if (argc == 1)
	{
		ft_putchar('\n');
		return (1);
	}
	flags = echo_find_flags(argv, &i);
	while (argv[i])
	{
		ft_putstr(argv[i++]);
		if (argc != i)
			ft_putchar(' ');
	}
	if (!(is_flags(flags, 'n')))
		ft_putchar('\n');
	return (0);
}
