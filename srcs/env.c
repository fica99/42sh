/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:28:25 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 19:45:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	get_count_var(char *arr, char **env)
{
	uint8_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arr, ft_strlen(arr)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_var(char *arr, char **env)
{
	return (&(env[get_count_var(arr, env)][ft_strlen(arr) + 1]));
}
