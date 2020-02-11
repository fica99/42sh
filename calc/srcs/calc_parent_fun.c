/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_parent_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:14:54 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/11 17:10:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static t_calc_tkntype	calc_parent_type(char *str)
{
	if (!str)
		return (0);
	if (*str == '(')
		return (CALC_LPARENT);
	else if (*str == ')')
		return (CALC_RPARENT);
	else
		return (0);
}

static long long		calc_parent_next(long long result,
					t_calc_tkns *s_tokens, size_t *index, t_calc_err *error)
{
	t_calc_tkntype	oper;

	oper = s_tokens->tokens[*index].type;
	if (oper == CALC_LPARENT)
	{
		(*index)++;
		result = calc_add_sub(s_tokens, index, error);
		if (s_tokens->tokens[*index].type != CALC_RPARENT)
			return (calc_error(error, CALC_ERR_PARENT));
		(*index)++;
		return (result);
	}
	return (result = calc_var(s_tokens, index, error));
}

t_calc_tkn				*calc_get_parent_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;

	if (!str)
		return (NULL);
	type = calc_parent_type(str);
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + 1;
	return (token);
}

long long				calc_parent(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error)
{
	long long	result;

	result = 0;
	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (error->status)
		return (0);
	result = calc_parent_next(result, s_tokens, index, error);
	return (result);
}
