/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 16:56:08 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_setenv(int argc, char **argv)
{
	ushort	j;
	char	*value;

	value = NULL;
	j = 0;
	if (argc == 1)
		print_environ();
	else
	{
		while (argv[++j])
		{
			if (!(value = ft_strchr(argv[j], '=')))
			{
				print_error("No such file or directory", 9);
				continue ;
			}
			else
			{
				*value = '\0';
				set_env(argv[j], ++value);
			}
		}
	}
}
