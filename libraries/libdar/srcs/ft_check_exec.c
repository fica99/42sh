/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:19:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/11 17:19:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

int	ft_check_exc(char *str, char **exc)
{
	int	i;

	if (!str || !exc)
		return (0);
	i = -1;
	while (exc[++i])
		if (!ft_strcmp(exc[i], str))
			return (1);
	return (0);
}
