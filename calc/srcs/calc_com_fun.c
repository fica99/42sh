/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_com_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:58:53 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/21 16:00:28 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static t_calc_tkntype	calc_com_type(char *str)
{
	if (!str)
		return (0);
	else if (!ft_strncmp(str, "<=", 2))
		return (CALC_LESSOREQ);
	else if (!ft_strncmp(str, ">=", 2))
		return (CALC_MOREOREQ);
	else if (*str == '<')
		return (CALC_LESS);
	else if (*str == '>')
		return (CALC_MORE);
	else
		return (0);
}

static long long		calc_com_next(long long result, t_calc_tkns *s_tokens,
	size_t *index, t_calc_err *error)
{
	t_calc_tkntype	oper;

	while (1)
	{
		oper = s_tokens->tokens[*index].type;
		if (oper == CALC_LESSOREQ || oper == CALC_MOREOREQ
			|| oper == CALC_LESS || oper == CALC_MORE)
			(*index)++;
		if (oper == CALC_LESSOREQ)
			result = result <= calc_eq_diff(s_tokens, index, error);
		else if (oper == CALC_MOREOREQ)
			result = result >= calc_eq_diff(s_tokens, index, error);
		else if (oper == CALC_LESS)
			result = result < calc_eq_diff(s_tokens, index, error);
		else if (oper == CALC_MORE)
			result = result > calc_eq_diff(s_tokens, index, error);
		else
			break ;
		if (error->status)
			return (0);
	}
	return (result);
}

t_calc_tkn				*calc_get_com_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;
	size_t			len;

	if (!str)
		return (NULL);
	len = (!ft_strncmp(str, "<=", 2)
		|| !ft_strncmp(str, ">=", 2)) ? 2 : 1;
	type = calc_com_type(str);
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + len;
	return (token);
}

long long				calc_com(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error)
{
	long long	result;

	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	result = calc_eq_diff(s_tokens, index, error);
	if (error->status)
		return (0);
	result = calc_com_next(result, s_tokens, index, error);
	return (result);
}
