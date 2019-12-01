/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_error_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:54:52 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/01 22:07:59 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_err	*calc_new_error(void)
{
	t_calc_err  *new_error;

	if (!(new_error = (t_calc_err *)malloc(sizeof(t_calc_err))))
		return (NULL);
	new_error->type = 0;
	new_error->status = 0;
	return new_error;
}

int			calc_error(t_calc_err *error, t_calc_err_type type)
{
	if (!error)
		return (0);
	error->type = type;
	error->status = 1;
	calc_print_error(error);
	return (0);
}
