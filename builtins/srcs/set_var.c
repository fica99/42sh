/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 22:31:41 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 15:11:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	set_var(int ac, char **av)
{
	char *name;
	char *value;

	(void)ac;
	while (*++av)
	{
		if (!(name = ft_strdup(*av)))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
		if (!(value = ft_strchr(name, '=')))
		{
			free(name);
			return (1);
		}
		*value = 0;
		++value;
		if (get_env(name, ENV))
			set_env(name, value, ENV);
		else
			set_env(name, value, SET_ENV);
		free(name);
		av++;
	}
	return (0);
}
