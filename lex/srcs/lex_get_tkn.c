/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:22:06 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/20 00:00:09 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void			rewind_spases(char *str, size_t *pos)
{
	if (!str || !pos)
		return ;
	while (str[*pos] == ' ')
		(*pos)++;
}

void				lex_rewind_end_spases(char *str, size_t *pos)
{
	if (!str || !pos)
		return ;
	while (str[*pos - 1] == ' ')
		(*pos)--;
}

t_lex_tkn			*lex_get_next_tkn(char **str, size_t pos)
{
	size_t			start_pos;
	t_lex_tkn_type	type;
	t_lex_tkn		*token;
	short			is_word;

	if (!str || !(*str))
		return (NULL);
	rewind_spases(*str, &pos);
	start_pos = pos;
	while (1)
	{
		is_word = (pos - start_pos > 0) ? 1 : 0;
		type = lex_check_type(str, is_word, &pos);
		if (type == T_ERR)
			return (NULL);
		if (type != T_WORD)
			break ;
	}
	if (!(token = lex_new_tkn()))
		return (NULL);
	token->type = (type == T_NULL) ? T_WORD : type;
	token->class = lex_check_class(token->type);
	lex_fill_value_pos(token, *str, start_pos, pos);
	return (token);
}

void				lex_fill_value_pos(t_lex_tkn *token, char *str,
	size_t start_pos, size_t pos)
{
	size_t	len;

	if (!token || !str)
		return ;
	token->start_pos = start_pos;
	token->end_pos = pos;
	if (token->type == T_CONTROL_SUB)
		lex_fill_control_sub_value(token, str, pos);
	else if (token->type == T_ARITH_OPERS)
		lex_fill_arith_opers_value(token, str, pos);
	else
	{
		lex_rewind_end_spases(str, &pos);
		len = pos - start_pos;
		token->value = ft_strsub(str, start_pos, len);
	}
}
