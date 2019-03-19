/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 21:36:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if(is_flags(flags, 'E'))
			ft_putstr_ecr(argv[i++]);
		else
			ft_putstr(argv[i++]);
		if (argc != i)
			ft_putchar(' ');
	}
	if (!(is_flags(flags, 'n')))
		ft_putchar('\n');
	return (1);
}

uint8_t	echo_find_flags(char **argv, unsigned short *i)
{
	uint8_t	k;
	uint8_t	flags;

	flags = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		k = 0;
		while (argv[*i][++k])
		{
			if (!(add_flag(flags, argv[*i][k])))
				return (flags);
			else
				flags = add_flag(flags, argv[*i][k]);
		}
		(*i)++;
	}
	return (flags);
}

void	ft_putstr_ecr(char *arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (check_symbol(arr[i]))
			if (!(arr[++i]))
				break;
		ft_putchar(arr[i]);	
	}
}
