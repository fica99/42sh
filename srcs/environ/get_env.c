/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:46:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 20:00:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_getenv(char *arr, char **env)
{
	short	j;

	if (arr && *arr)
	{
		if ((j = get_count_env(arr, env)) != -1)
			return (env[j] + ft_strlen(arr) + 1);
	}
	return (NULL);
}

short	get_count_env(char *arr, char **env)
{
	short	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], arr, ft_strlen(arr)))
			return (i);
	}
	return (-1);
}
