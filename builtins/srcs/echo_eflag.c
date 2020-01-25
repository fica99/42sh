/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_eflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:33:58 by jijerde           #+#    #+#             */
/*   Updated: 2020/01/18 04:29:16 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		ft_isoct(char c)
{
	if ('0' <= c && c <= '7')
		return (1);
	return (0);
}

int		ft_ishex(char c)
{
	if (('0' <= c && c <= '9') || ('A' <= c && c <= 'F')
	|| ('a' <= c && c <= 'f'))
		return (1);
	return (0);
}

int		ft_hex(char c)
{
	if (c == 'A' || c == 'a')
		return (10);
	if (c == 'B' || c == 'b')
		return (11);
	if (c == 'C' || c == 'c')
		return (12);
	if (c == 'D' || c == 'd')
		return (13);
	if (c == 'E' || c == 'e')
		return (14);
	if (c == 'F' || c == 'f')
		return (15);
	return (c - '0');
}

int		ft_hexout(char **argv, int i, int j)
{
	int hex;

	hex = 0;
	if (argv[i][j + 1] && ft_ishex(argv[i][j + 2]))
	{
		j++;
		hex = hex * 16 + ft_hex(argv[i][j++]);
		hex = hex * 16 + ft_hex(argv[i][j]);
		ft_putchar_fd((char)hex, STDOUT_FILENO);
	}
	else if (ft_ishex(argv[i][j + 1]))
	{
		j++;
		hex = hex * 16 + ft_hex(argv[i][j]);
		ft_putchar_fd((char)hex, STDOUT_FILENO);
	}
	else
	{
		ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(argv[i][j], STDOUT_FILENO);
	}
	return (j);
}

int		ft_eflag(int i, char **argv, int argc, int *flags)
{
	int				j;

	while (argv[i] && (j = -1))
	{
		while (argv[i][++j])
		{
			if (argv[i][j] == '\\' && argv[i][j + 1] == '\\' && argv[i][j + 2])
			{
				j += 2;
				if (ft_common_escape(argv, i, j))
					;
				else if (argv[i][j] == '0' || argv[i][j] == 'x')
					j = echo_one_escape(argv, i, j);
				else if (argv[i][j] == 'c' && (flags[0] = 1))
					return (argc);
				else
					echo_slashes(argv, i, j);
			}
			else
				echo_text(argv, i, j);
		}
		(argc != (i + 1)) ? ft_putchar_fd(' ', STDOUT_FILENO) : 0;
		i++;
	}
	return (i);
}
