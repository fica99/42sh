/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:35:55 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 20:03:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*check_path(void)
{
	char	*path;

	path = NULL;
	if (ft_getenv("PWD") && ft_getenv("HOME"))
	{
		path = ft_strrchr(ft_getenv("PWD"), '/');
		ft_isprint(*(path + 1)) == 1 ? path = path + 1 : path;
		!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")) ? path = "~" : path;
	}
	return (path);
}
