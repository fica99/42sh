/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:53:55 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/09 14:03:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

void			ft_unsetvar(char *arr, t_vars *vars)
{
	int		j;
	char	*copy;

	if ((j = get_index_var(arr, vars->vars)) < 0)
		return ;
	copy = vars->vars[j];
	while (j < vars->cur_size)
	{
		vars->vars[j] = vars->vars[j + 1];
		j++;
	}
	--vars->cur_size;
	ft_memdel((void**)&copy);
}

void			unset_var(char *name, t_vars_type type)
{
	if (type == ENV)
		ft_unsetvar(name, &g_environ);
	else if (type == VARS)
		ft_unsetvar(name, &g_vars);
	else if (type == ALL_VARS)
	{
		ft_unsetvar(name, &g_environ);
		ft_unsetvar(name, &g_vars);
	}
}
