/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:50:06 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/05 14:15:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

static void	set_variables(t_vars *vars, char **data, short malloc_size)
{
	short	i;

	vars->malloc_size = malloc_size;
	if (!(vars->vars = ft_darnew(malloc_size)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	i = 0;
	if (data)
	{
		while (data[i])
		{
			if (!(vars->vars[i] = ft_strdup(data[i])))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			++i;
		}
	}
	vars->cur_size = i;
}

void		init_cwd(void)
{
	if (!(g_cur_wd = (char *)ft_memalloc(PATH_MAX)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	if (!getcwd(g_cur_wd, PATH_MAX))
		err_exit("42sh", "getcwd() error", NULL, NOERROR);
	set_var("PWD", g_cur_wd, ENV);
}

void		init_variables(char **data, t_vars_type type)
{
	short		len;
	short		counter;

	len = ft_darlen(data);
	counter = 1;
	while (len >= counter * VAR_DEF_MALLOC_SIZE)
		counter++;
	if (type == ENV)
		set_variables(&g_environ, data, counter * VAR_DEF_MALLOC_SIZE);
	else
		set_variables(&g_vars, data, counter * VAR_DEF_MALLOC_SIZE);
}
