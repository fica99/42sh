/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:29:20 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/12 16:51:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *name, char *new_value)
{
	short	j;
	char	**envp;

	if ((j = get_count_var(name)) >= 0)
	{
		free(env_cp[j]);
		env_cp[j]= join_env(name, new_value);
	}
	else
	{
		if (!(envp = (char**)malloc(sizeof(char*) * (double_arr_len(env_cp) + 2))))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		while(env_cp[++j])
			envp[j] = env_cp[j];
		envp[j] = join_env(name, new_value);
		envp[++j] = NULL;
		free(env_cp);
		env_cp = envp;
	}
}

short	get_count_var(char *arr)
{
	uint8_t	i;

	i = 0;
	while (env_cp[i])
	{
		if (ft_strncmp(env_cp[i], arr, ft_strlen(arr)) == 0
				&& env_cp[i][ft_strlen(arr)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char *arr)
{
	if (get_count_var(arr) == -1)
		return (NULL);
	else
		return (&(env_cp[get_count_var(arr)][ft_strlen(arr) + 1]));
}
