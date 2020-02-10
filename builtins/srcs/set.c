/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:05:59 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/10 18:29:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**check_set_flags(char **av, t_flag *o_opt)
{
	int i;
	int j;

	j = 1;
	i = 0;
	while (av[j] && av[j][0] == '-')
	{
		if (av[j][i + 1] == 0 || av[j][i + 1] == '-')
			return (&av[j]);
		while (av[j][++i])
		{
			if (av[j][i] == 'o')
				*o_opt = 1;
			else
				return (NULL);
		}
		j++;
		i = 0;
	}
	return (&av[j]);
}

int		set_readline(char **args)
{
	if (!*args)
	{
		ft_putstr("required argument\n");
		ft_putstr("set: usage: set [-o]\n");
	}
	else if (args[1])
	{
		ft_putstr("required argument\n");
		ft_putstr("set: usage: set [-o]\n");
	}
	else if (ft_strcmp(*args, "VI") && ft_strcmp(*args, "readline"))
		ft_putstr("invalid mode\n");
	else
	{
		setvar("READMODE", "VI", &g_vars);
		return (0);
	}
	return (1);
}

int		set(int ac, char **args, char **environ)
{
	t_flag o_opt;

	(void)ac;
	o_opt = 0;
	if (!(args = check_set_flags(args, &o_opt)))
	{
		err("42sh", "set", NULL, "invalid option");
		ft_putstr("set: usage: set [-o]\n");
		return (1);
	}
	if (o_opt)
		return (set_readline(args));
	ft_putdar(environ);
	ft_putdar(g_vars.vars);
	return (0);
}
