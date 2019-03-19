/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 18:48:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	echo(int argc, char **argv, char **env)
{
	unsigned short	i;
	uint8_t			j;

	i = 1;
	j = 0;
	env = NULL;
	if (argc == 1)
	{
		ft_putchar('\n');
		return (1);
	}
	echo_find_flags(argv, &i, &j);
	while (argv[i])
	{
		ft_putstr(argv[i++]);
		if (argc != i)
			ft_putchar(' ');
	}
	if (!j)
		ft_putchar('\n');
	return (1);
}

void	echo_find_flags(char **argv, unsigned short *i, uint8_t *j)
{
	uint8_t	k;

	while (argv[*i] && argv[*i][0] == '-')
	{
		k = 0;
		while (argv[*i][++k])
		{
			if (argv[*i][k] == 'n')
				*j = 1;
			else if (argv[*i][k] == 'e' || argv[*i][k] == 'E')
				continue ;
			else
			{
				*j = 0;
				return ;
			}
		}
		(*i)++;
	}
}
