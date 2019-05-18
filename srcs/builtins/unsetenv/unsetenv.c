/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/18 17:13:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_unsetenv(int argc, char **argv, char **env_cp)
{
	short	i;
	short	j;
	char	**envp;

	(void)env_cp;
	if (argc < 2)
		print_error_withoutexit("unsetenv", NULL, "not enough arguments", 0);
	else
	{
		j = 0;
		while (argv[++j])
		{
			if ((i = get_count_var(argv[j])) < 0)
				continue;
			envp = copy_new_arr(i);
			free(g_term.env_cp);
			g_term.env_cp = envp;
		}
	}
}

char	**copy_new_arr(short i)
{
	char	**envp;
	short	j;

	if (!(envp = (char**)malloc(sizeof(char *)
					* (double_arr_len(g_term.env_cp)))))
		print_error("unsetenv", "malloc() error", NULL, ENOMEM);
	j = -1;
	while (g_term.env_cp[++j])
	{
		if (j >= i)
		{
			if (j == i)
				ft_memdel((void**)&(g_term.env_cp[j]));
			envp[j] = g_term.env_cp[j + 1];
		}
		else
			envp[j] = g_term.env_cp[j];
	}
	return (envp);
}
