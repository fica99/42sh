/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:22:06 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 21:20:04 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void				lex_rewind_end_spases(char *str, size_t *pos)
{
	if (!str || !pos)
		return ;
	while (str[*pos - 1] == ' ')
		(*pos)--;
}

t_lex_tkn			*lex_get_next_tkn(char **str, size_t pos)
{
	size_t				start_pos;
	t_lex_tkn_type		type;
	t_lex_tkn			*token;
	short				is_word;
	t_lex_prefix_prop	prefix_prop;

	if (!str || !(*str))
		return (NULL);
	lex_preprocessing(*str, &pos, &prefix_prop);
	start_pos = pos;
	while (1)
	{
		is_word = (pos - start_pos > 0) ? 1 : 0;
		type = lex_check_type(str, is_word, &pos);
		if (type == T_ERR || type == T_CTRL_C)
			return (NULL);
		if (type != T_WORD)
			break ;
	}
	if (!(token = lex_new_tkn()))
		return (NULL);
	token->type = (type == T_NULL) ? T_WORD : type;
	token->class = lex_check_class(token->type, prefix_prop);
	lex_fill_value_pos(token, *str, start_pos, pos);
	return (token);
}

void				lex_fill_value_pos(t_lex_tkn *token, char *str,
	size_t start_pos, size_t pos)
{
	if (!token || !str)
		return ;
	token->start_pos = start_pos;
	token->end_pos = pos;
	lex_parse_tkn_value(token, str);
}
