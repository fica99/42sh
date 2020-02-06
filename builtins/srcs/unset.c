/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:03:34 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 15:53:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	unset(int ac, char **av, char **environ)
{
	(void)ac;
	(void)environ;
	if (av && *av)
	{
		while (*++av)
			unset_var(*av, ALL_VARS);
	}
	return (0);
}
