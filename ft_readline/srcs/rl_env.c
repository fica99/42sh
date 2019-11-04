/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:42:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/31 17:14:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*rl_getenv(char *arr, char **env)
{
	short	j;

	if (arr && *arr)
		if ((j = rl_get_count_env(arr, env)) != -1)
			return (ft_strchr(env[j], '=') + 1);
	return (NULL);
}

short	rl_get_count_env(char *arr, char **env)
{
	short	i;
	short	len;

	if (arr && *arr)
	{
		i = -1;
		len = ft_strlen(arr);
		while (env[++i])
			if (!ft_strncmp(env[i], arr, len))
				return (i);
	}
	return (-1);
}
