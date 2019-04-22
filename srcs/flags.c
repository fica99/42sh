/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:30:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/12 18:33:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	add_flag(uint8_t flags, char flag, uint8_t i)
{
	if (i == 1)
	{
		if (flag == 'n')
			return (flags | 1);
	}
	return (0);
}

uint8_t	is_flags(uint8_t flags, char flag)
{
	if (flag == 'n' && (flags & 1) == 1)
		return (1);
	return (0);
}

uint8_t	find_flags(char **argv, unsigned short *i, uint8_t (fun)(char s))
{
	uint8_t	k;
	uint8_t	flags;

	flags = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		k = 0;
		while (argv[*i][++k])
		{
			if (fun(argv[*i][k]))
				flags = add_flag(flags, argv[*i][k], 1);
			else
				return (flags);
		}
		(*i)++;
	}
	return (flags);
}