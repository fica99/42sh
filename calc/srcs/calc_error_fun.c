/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_error_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:54:52 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/18 21:08:50 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

long long	calc_error(t_calc_err *error, t_calc_err_type type)
{
	if (!error)
		return (0);
	error->type = type;
	error->status = 1;
	return (0);
}
