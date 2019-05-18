/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/18 17:12:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	set_env(int argc, char **argv, char **env_cp)
{
	short	j;
	char	*value;

	(void)env_cp;
	value = NULL;
	j = 0;
	if (argc == 1)
		print_environ();
	else
	{
		while (argv[++j])
		{
			if (!(value = ft_strchr(argv[j], '=')))
				continue ;
			else
			{
				*value = '\0';
				ft_setenv(argv[j], ++value);
			}
		}
	}
}
