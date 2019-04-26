/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:48:56 by filip             #+#    #+#             */
/*   Updated: 2019/04/27 01:40:46 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(char *name, char *new_value)
{
	short	j;
	char	**envp;

	if ((j = get_count_var(name)) >= 0)
	{
		free(g_term.env_cp[j]);
		g_term.env_cp[j]= join_env(name, new_value);
	}
	else
	{
		if (!(envp = (char**)malloc(sizeof(char*) * (double_arr_len(g_term.env_cp) + 2))))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		while(g_term.env_cp[++j])
			envp[j] = g_term.env_cp[j];
		envp[j] = join_env(name, new_value);
		envp[++j] = NULL;
		free(g_term.env_cp);
		g_term.env_cp = envp;
	}
}

char	*join_env(char *name, char *new_value)
{
	char *name1;
	char *name2;

	if (!(name1 = ft_strjoin(name, "=")))
		print_error("setenv", "malloc() error", NULL, ENOMEM);
	if (!(name2 = ft_strjoin(name1, new_value)))
		print_error("setenv", "malloc() error", NULL, ENOMEM);
	ft_memdel((void**)&name1);
	return(name2);
}
