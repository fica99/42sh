/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:06:37 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 16:07:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	e_err(char opt)
{
	ft_putstr_fd("42sh: export: -", 2);
	ft_putchar_fd(opt, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("export: usage: export [-p] [name[=value]]", 2);
}

static void	e_print(char const *av)
{
	ft_putstr("export ");
	ft_putstr(av);
	ft_putchar('\n');
}

static char	**e_getopt(char **av, t_flag *print)
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
			if (av[j][i] == 'p')
				*print = 1;
			else
			{
				e_err(av[j][i]);
				return (NULL);
			}
		}
		j++;
		i = 0;
	}
	return (&av[j]);
}

static char	*get_value(char *arg)
{
	char *value;
	char *tmp;

	if (!(tmp = ft_strchr(arg, '=')))
	{
		if (!(tmp = get_var(arg, ALL_VARS)))
		{
			free(arg);
			return (0);
		}
	}
	else
		*tmp++ = 0;
	if (!(value = ft_strdup(tmp)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	return (value);
}

int			export(int ac, char **av, char **environ)
{
	char	*name;
	char	*value;
	t_flag	print;

	(void)ac;
	(void)environ;
	print = 0;
	if (!(av = e_getopt(av, &print)))
		return (2);
	while (*av)
	{
		if (!(name = ft_strdup(*av)))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
		if (!(value = get_value(name)))
			continue ;
		unset_var(name, ALL_VARS);
		set_var(name, value, ENV);
		free(name);
		free(value);
		if (print)
			e_print(*av);
		av++;
	}
	return (0);
}
