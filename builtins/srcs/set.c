/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:05:59 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 15:44:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	set(int ac, char **args)
{
	(void)ac;
	(void)args;
	ft_putdar(g_environ.vars);
	ft_putdar(g_vars.vars);
	return (0);
}
