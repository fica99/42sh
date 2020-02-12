/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 22:31:41 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 16:17:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	set_variable(int ac, char **av, char **environ)
{
	char *name;
	char *value;

	(void)environ;
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
		if (get_var(name, ENV) || !ft_strcmp("PATH", name))
			set_var(name, value, ENV);
		else
			set_var(name, value, VARS);
		free(name);
	}
	return (0);
}
