/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	unset_env(int argc, char **argv, char **env_cp)
{
	short	j;

	(void)env_cp;
	if (argc < 2)
		err(argv[0], NULL, "not enough arguments", NOERROR);
	else
	{
		j = 0;
		while (argv[++j])
		{
			ft_unsetenv(argv[j]);
			if (!ft_strcmp(argv[j], "PATH"))
				g_flags |= TERM_FREE_HASH;
		}
	}
}
