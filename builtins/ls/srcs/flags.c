/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:26:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/12 16:32:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

ushort	read_flags(char **argv, uint8_t *i)
{
	ushort		flags;
	uint8_t		j;

	flags = 0;
	while (argv[*i] && argv[*i][0] == '-' && ft_strlen(argv[*i]) != 1)
	{
		j = 0;
		while (argv[*i][++j])
			flags = add_flag(flags, argv[*i][j]);
		(*i)++;
	}
	return (flags);
}

ushort	add_flag(ushort flags, char flag)
{
	if (flag == 'a')
		return (flags | 1);
	if (flag == 'l')
		return (flags | 2);
	if (flag == 'r')
		return (flags | 4);
	if (flag == 't')
		return (flags | 8);
	if (flag == 'R')
		return (flags | 16);
	if (flag == 'u')
		return (flags | 32);
	if (flag == 'f')
		return (flags | 64);
	if (flag == 'g')
		return (flags | 128);
	if (flag == 'd')
		return (flags | 256);
	if (flag == 'S')
		return (flags | 512);
	if (flag == 1)
		return (flags | 1024);
	return (add_flag2(flags, flag));
}

ushort	add_flag2(ushort flags, char flag)
{
	if (flag == '@')
		return (flags | 4096);
	if (flag == 'G')
	{
		ft_putstr("\033[32;1m");
		return (flags | 8192);
	}
	print_usage(flag);
	return (0);
}

ushort	is_flags(ushort flags, char flag)
{
	if (flag == 'a' && (flags & 1) == 1)
		return (1);
	if (flag == 'l' && (flags & 2) == 2)
		return (1);
	if (flag == 'r' && (flags & 4) == 4)
		return (1);
	if (flag == 't' && (flags & 8) == 8)
		return (1);
	if (flag == 'R' && (flags & 16) == 16)
		return (1);
	if (flag == 'u' && (flags & 32) == 32)
		return (1);
	if (flag == 'f' && (flags & 64) == 64)
		return (1);
	if (flag == 'g' && (flags & 128) == 128)
		return (1);
	if (flag == 'd' && (flags & 256) == 256)
		return (1);
	if (flag == 'S' && (flags & 512) == 512)
		return (1);
	if (flag == 1 && (flags & 1024) == 1024)
		return (1);
	return (is_flags2(flags, flag));
}

ushort	is_flags2(ushort flags, char flag)
{
	if (flag == '@' && (flags & 4096) == 4096)
		return (1);
	if (flag == 'G' && (flags & 8192) == 8192)
		return (1);
	return (0);
}
