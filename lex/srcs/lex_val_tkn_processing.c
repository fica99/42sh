/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_val_tkn_processing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:35:34 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 21:29:59 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static char		*lex_clip_tkn_value(t_lex_tkn *token,
	const char *str, size_t left_clip, size_t right_clip)
{
	size_t		len;
	char		*new_str;

	if (!token)
		return (NULL);
	if (token->start_pos + left_clip + right_clip > token->end_pos)
	{
		return (ft_strsub(str, token->start_pos,
			token->end_pos - token->start_pos));
	}
	len = token->end_pos - right_clip - (token->start_pos + left_clip);
	if (!(new_str = ft_strsub(str, token->start_pos
		+ left_clip, len)))
		return (NULL);
	return (new_str);
}

static size_t	lex_end_spases_size(const char *str, size_t pos)
{
	size_t		i;

	if (!str || !pos)
		return (0);
	i = 0;
	while (str[pos - 1] == ' ')
	{
		i++;
		pos--;
	}
	return (i);
}

void			lex_cut_tkn_value(t_lex_tkn *token, const char *str)
{
	char	*tkn_value;
	size_t	es_size;

	es_size = lex_end_spases_size(str, token->end_pos);
	if (token->type == T_ASSIGNMENT_WORD)
		tkn_value = lex_an_cut_quotes(token, str);
	else
		tkn_value = lex_clip_tkn_value(token, str, 0, es_size + 0);
	token->value = tkn_value;
}
