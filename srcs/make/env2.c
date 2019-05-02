/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:35:55 by filip             #+#    #+#             */
/*   Updated: 2019/04/30 16:02:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "42sh.h"

char			*check_path(void)
{
	char	*path;

	path = ft_strrchr(ft_getenv("PWD"), '/');
	ft_isprint(*(path + 1)) == 1 ? path = path + 1 : path;
	!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")) ? path = "~" : path;
	return (path);
}