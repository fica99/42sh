/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 17:13:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(int argc, char **argv)
{
	short	i;
	short	j;
	char	**envp;

	if (argc == 2)
	{
		if ((i = get_count_var(argv[1])) >= 0)
		{
			if (!(envp = (char**)malloc(sizeof(char *) * double_arr_len(env_cp))))
				print_error("Malloc() error", 5);
			j = -1;
			while (env_cp[++j])
			{
				if (j == i)
				{
					ft_memdel((void**)&(env_cp[j]));
					continue;
				}
				envp[j] = env_cp[j];
			}
			envp[j] = NULL;
			free(env_cp);
			env_cp = envp;
		}
		else
			print_error("No env", 11);
	}
	else if (argc > 2)
		print_error("Too many arguments", 8);
	else
		print_environ();
}
