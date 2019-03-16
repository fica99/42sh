/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:28:25 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/16 20:34:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	get_argc_env(char *arr, char **env)
{
	uint8_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i++], arr, ft_strlen(arr)) == 0)
			return (--i);
	}
	return (0);
}
