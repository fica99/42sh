/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/12 16:53:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(int argc, char **argv)
{
	short	i;
	short	j;
	char	**envp;

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
			free(env_cp);
			env_cp = envp;
		}
	}
}

char	**copy_new_arr(short i)
{
	char	**envp;
	short	j;

	if (!(envp = (char**)malloc(sizeof(char *) * (double_arr_len(env_cp)))))
		print_error("unsetenv", "malloc() error", NULL, ENOMEM);
	j = -1;
	while (env_cp[++j])
	{
		if (j >= i)
		{
			if (j == i)
				ft_memdel((void**)&(env_cp[j]));
			envp[j] = env_cp[j + 1];
		}
		else
			envp[j] = env_cp[j];
	}
	return (envp);
}
