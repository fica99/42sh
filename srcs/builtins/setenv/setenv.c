/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/02 13:32:45 by filip            ###   ########.fr       */
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
				if (!ft_strcmp(argv[j], "PATH"))
					make_hash_table();
			}
		}
	}
}
