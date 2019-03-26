/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:29:20 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 19:25:50 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *name, char *new_value)
{
	short	j;
	char	*name1;

	if ((j = get_count_var(name)) >= 0)
	{
		free(env_cp[j]);
		name1 = ft_strjoin(name, "=");
		env_cp[j] = ft_strjoin(name1, new_value);
	}
}

short	get_count_var(char *arr)
{
	uint8_t	i;

	i = 0;
	while (env_cp[i])
	{
		if (ft_strncmp(env_cp[i], arr, ft_strlen(arr)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_var(char *arr)
{
	if (get_count_var(arr) == -1)
		return (NULL);
	else
		return (&(env_cp[get_count_var(arr)][ft_strlen(arr) + 1]));
}
