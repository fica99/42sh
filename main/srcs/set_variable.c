/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 21:45:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/05 15:58:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

static char		*join_name_value(char *name, char *value)
{
	char *name1;
	char *name2;

	if (!(name1 = ft_strjoin(name, "=")))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if (!value)
		return (name1);
	if (!(name2 = ft_strjoin(name1, value)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memdel((void**)&name1);
	return (name2);
}

short			get_index_var(char *arr, char **vars)
{
	short	i;
	short	len;

	if (arr && *arr)
	{
		i = -1;
		len = ft_strlen(arr);
		while (vars[++i])
			if (!ft_strncmp(vars[i], arr, len) && vars[i][len] == '=')
				return (i);
	}
	return (-1);
}

static void		setvar(char *name, char *value, t_vars *vars)
{
	short	j;
	char	**vars_cp;

	if ((j = get_index_var(name, vars->vars)) >= 0)
	{
		ft_memdel((void**)&vars->vars[j]);
		vars->vars[j] = join_name_value(name, value);
	}
	else
	{
		if (++vars->cur_size >= vars->malloc_size)
		{
			vars->malloc_size *= 2;
			if (!(vars_cp = ft_darnew(vars->malloc_size)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			j = -1;
			while (vars->vars[++j])
				vars_cp[j] = vars->vars[j];
			vars_cp[j] = join_name_value(name, value);
			ft_free_dar(vars->vars);
			vars->vars = vars_cp;
		}
		else
			vars->vars[vars->cur_size - 1] = join_name_value(name, value);
	}
}

void			set_var(char *name, char *value, t_vars_type type)
{
	if (type == ENV)
		setvar(name, value, &g_environ);
	else if (type == VARS)
		setvar(name, value, &g_vars);
	else
	{
		if (get_var(name, ENV))
			set_var(name, value, ENV);
		else
			set_var(name, value, VARS);
	}
}
