/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:22:06 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/10 22:40:06 by ggrimes          ###   ########.fr       */
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

static int			lex_is_value(t_lex_tkn_type type)
{
	if (type == T_WORD || type == T_IO_NUMBER)
		return (1);
	return (0);
}

static void			rewind_end_spases(char *str, size_t *pos)
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
		rewind_spases(*str, &pos);
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
	if (lex_is_value(token->type))
	{
		rewind_end_spases(str, &pos);
		len = pos - start_pos;
		token->value = ft_strsub(str, start_pos, len);
	}
}
