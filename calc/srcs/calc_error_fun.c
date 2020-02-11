/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_error_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:54:52 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/11 17:07:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_err	*calc_new_error(void)
{
	t_calc_err	*new_error;

	if (!(new_error = (t_calc_err *)malloc(sizeof(t_calc_err))))
		return (NULL);
	new_error->type = 0;
	new_error->status = 0;
	return (new_error);
}

long long	calc_error(t_calc_err *error, t_calc_err_type type)
{
	if (!error)
		return (0);
	error->type = type;
	error->status = 1;
	return (0);
}
