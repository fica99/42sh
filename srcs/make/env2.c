/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:35:55 by filip             #+#    #+#             */
/*   Updated: 2019/05/18 00:51:12 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "42sh.h"

char			*check_path(void)
{
	char	*path;

	path = NULL;
	if (ft_getenv("PATH") && ft_getenv("PWD") && ft_getenv("HOME"))
	{
		path = ft_strrchr(ft_getenv("PWD"), '/');
		ft_isprint(*(path + 1)) == 1 ? path = path + 1 : path;
		!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")) ? path = "~" : path;
	}
	return (path);
}