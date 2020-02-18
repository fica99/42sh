/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_var_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 20:33:09 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/18 21:15:10 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static long long	calc_check_var_inc(t_calc_tkns *s_tokens, size_t index)
{
	t_calc_tkntype	type;

	type = s_tokens->tokens[index + 1].type;
	if (type == CALC_INC || type == CALC_DEC)
		return (1);
	return (0);
}

static long long	calc_var_next(long long result, t_calc_tkns *s_tokens,
	size_t *index, t_calc_err *error)
{
	t_calc_tkntype	type;
	t_calc_var		*var;

	type = s_tokens->tokens[*index].type;
	if (type == CALC_VAR)
	{
		var = (t_calc_var *)s_tokens->tokens[*index].value;
		result = calc(var->value, error);
		if (error->status)
			return (0);
		*index += (calc_check_var_inc(s_tokens, *index)) ? 2 : 1;
		return (result);
	}
	return (result = calc_unary(s_tokens, index, error));
}

long long			calc_var(t_calc_tkns *s_tokens, size_t *index,
													t_calc_err *error)
{
	long long		result;

	result = 0;
	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (error->status)
		return (0);
	result = calc_var_next(result, s_tokens, index, error);
	return (result);
}

long long			calc_var_inc(t_calc_tkns *s_tokens, size_t *index,
														t_calc_err *error)
{
	long long		result;
	size_t			cur_index;

	result = 0;
	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (error->status)
		return (0);
	cur_index = *index;
	result = calc_add_sub(s_tokens, index, error);
	if (calc_check_var_inc(s_tokens, cur_index))
		return (result);
	return (result);
}

t_calc_tkns			*calc_prefix(char *str, t_calc_tkns *s_tokens, size_t *pos)
{
	size_t	i;
	char	temp;
	char	*value;

	if (!str || !s_tokens || !pos)
		return (s_tokens);
	(*pos)++;
	str += *pos;
	if (!(i = calc_var_is_valid(str)))
		return (calc_del_tkns(s_tokens));
	temp = str[i];
	str[i] = '\0';
	if (!(value = get_var(str, ALL_VARS)))
		return (calc_del_tkns(s_tokens));
	s_tokens = calc_get_arr_tkns(value, s_tokens, s_tokens->size);
	s_tokens->size--;
	str[i] = temp;
	*pos += i;
	return (s_tokens);
}
