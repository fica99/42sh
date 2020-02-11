/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:50:01 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/11 21:43:39 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

long long		calc(char *str, t_calc_err **error)
{
	t_calc_tkns	*s_tokens;
	long long	res;

	if (!str || !error)
		return (0);
	if (!*error)
		*error = calc_new_error();
	if (!(s_tokens = calc_get_arr_tkns(str, NULL, 0)))
		return (calc_error(*error, CALC_ERR_LX));
	res = calc_exp(s_tokens, 0, *error);
	return (res);
}

long long		calc_exp(t_calc_tkns *s_tokens, size_t index, t_calc_err *error)
{
	long long	result;

	if (!s_tokens || !calc_check_index(s_tokens, index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (s_tokens->tokens[index].type == CALC_END)
		return (0);
	result = calc_add_sub(s_tokens, &index, error);
	if (error->status)
		return (0);
	if (s_tokens->tokens[index].type != CALC_END)
	{
		if (s_tokens->tokens[index].type == CALC_RPARENT)
			return (calc_error(error, CALC_ERR_PARENT));
		return (calc_error(error, CALC_ERR_SYNTAX));
	}
	calc_del_tkns(s_tokens);
	return (result);
}
