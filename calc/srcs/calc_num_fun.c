/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_num_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:48:32 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/11 21:48:26 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static long long	calc_unary_next(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error)
{
	long long		result;

	(*index)++;
	result = calc_number(s_tokens, index, error);
	if (error->status)
		return (0);
	return (result * -1);
}

t_calc_tkn			*calc_get_number_tkn(char *str, size_t pos)
{
	size_t		i;
	char		*value;
	t_calc_tkn	*token;

	if (!str)
		return (NULL);
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!(value = ft_strsub(str, 0, i)))
		return (NULL);
	if (!(token = calc_newtkn((void *)value, CALC_NUMBER)))
	{
		ft_memdel((void **)&value);
		return (NULL);
	}
	token->start_pos = pos;
	token->end_pos = pos + i;
	return (token);
}

long long			calc_number(t_calc_tkns *s_tokens, size_t *index,
														t_calc_err *error)
{
	long long	result;

	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (s_tokens->tokens[*index].type == CALC_NUMBER)
	{
		result = calc_ll_atoi((char *)s_tokens->tokens[*index].value);
		(*index)++;
		return (result);
	}
	else
		return (calc_error(error, CALC_ERR_SYNTAX));
}

long long			calc_unary(t_calc_tkns *s_tokens, size_t *index,
														t_calc_err *error)
{
	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (s_tokens->tokens[*index].type == CALC_MINUS)
		return (calc_unary_next(s_tokens, index, error));
	else if (s_tokens->tokens[*index].type == CALC_NUMBER)
		return (calc_number(s_tokens, index, error));
	else
		return (calc_error(error, CALC_ERR_SYNTAX));
}
