/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_log_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:21:02 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/04 20:21:55 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static int	calc_log_or(int result, t_calc_tkns *s_tokens, size_t *index, t_calc_err *error)
{
	int		next_result;

	next_result = calc_parent(s_tokens, index, error);
	if (error->status)
		return (0);
	return (result || next_result);
}

static int	calc_log_next(int result, t_calc_tkns *s_tokens, size_t *index, t_calc_err *error)
{
	t_calc_tkntype	oper;

	while (1)
	{
		oper = s_tokens->tokens[*index].type;
		if (oper == CALC_AND || oper == CALC_OR)
			(*index)++;
		if (oper == CALC_AND)
			result = result && calc_parent(s_tokens, index, error);
		else if (oper == CALC_OR)
			result = calc_log_or(result, s_tokens, index, error);
		else
			break ;
		if (error->status)
			return (0);
	}
	return (result);
}

t_calc_tkn	*calc_get_log_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;

	if (!str)
		return (NULL);
	type = (*str == '&') ? CALC_AND : CALC_OR;
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + 2;
	return (token);
}

int			calc_log(t_calc_tkns *s_tokens, size_t *index, t_calc_err *error)
{
	int		result;

	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	result = calc_parent(s_tokens, index, error);
	if (error->status)
		return (0);
	result = calc_log_next(result, s_tokens, index, error);
	return result;
}
