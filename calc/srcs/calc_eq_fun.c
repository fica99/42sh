/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_eq_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:10:48 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/21 16:00:41 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static long long	calc_eq_diff_next(long long result, t_calc_tkns *s_tokens,
	size_t *index, t_calc_err *error)
{
	t_calc_tkntype	oper;

	while (1)
	{
		oper = s_tokens->tokens[*index].type;
		if (oper == CALC_EQ || oper == CALC_DIFF)
			(*index)++;
		if (oper == CALC_EQ)
			result = result == calc_log(s_tokens, index, error);
		else if (oper == CALC_DIFF)
			result = result != calc_log(s_tokens, index, error);
		else
			break ;
		if (error->status)
			return (0);
	}
	return (result);
}

t_calc_tkn			*calc_get_eq_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;

	if (!str)
		return (NULL);
	type = (*str == '=') ? CALC_EQ : CALC_DIFF;
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + 2;
	return (token);
}

long long			calc_eq_diff(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error)
{
	long long	result;

	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	result = calc_log(s_tokens, index, error);
	if (error->status)
		return (0);
	result = calc_eq_diff_next(result, s_tokens, index, error);
	return (result);
}
