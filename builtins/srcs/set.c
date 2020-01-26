/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:05:59 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 15:13:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	set(int ac, char **args)
{
	(void)ac;
	(void)args;
	ft_putdar(g_env.env);
	ft_putdar(g_set_env.env);
	return (0);
}
