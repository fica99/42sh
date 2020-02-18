/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_asig_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:22:50 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:01:54 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int		lex_is_an_sep(char c)
{
	if (c == ' ' || c == ';')
		return (1);
	return (0);
}

static t_lex_fr	lex_an_quotes(char **str, size_t *pos)
{
	t_lex_fr	qr;

	if ((*str)[*pos] == '"')
		qr = lex_quotes(str, pos, '"');
	else if ((*str)[*pos] == '\'')
		qr = lex_quotes(str, pos, '\'');
	else
		qr = FR_ERR;
	return (qr);
}

char			*lex_an_cut_quotes(t_lex_tkn *token, const char *str)
{
	size_t	pos;
	size_t	i;
	char	*new_str;

	if (!(new_str = ft_strnew((token->end_pos) - (token->start_pos))))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	i = 0;
	pos = token->start_pos;
	while (pos < token->end_pos)
	{
		if (str[pos] != '"' && str[pos] != '\'' && str[pos] != '`')
			new_str[i++] = str[pos];
		pos++;
	}
	return (new_str);
}

t_lex_fr		lex_is_asig_name(char **str, short is_word, size_t *pos)
{
	size_t		i;

	if (!str || !*str)
		return (FR_ERR);
	i = *pos;
	while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
		i++;
	if ((*str)[i++] != '=')
		return (FR_FALSE);
	if ((*str)[i] == '"' || (*str)[i] == '\'')
		lex_an_quotes(str, &i);
	else
		while ((*str)[i] && !lex_is_an_sep((*str)[i]))
			i++;
	if (!is_word)
		(*pos) = i;
	return (FR_TRUE);
}

t_lex_tkn_type	lex_asig_name(short is_word, t_lex_fr fr)
{
	if (fr == FR_ERR)
		return (T_ERR);
	else if (fr == FR_CTRL_C)
		return (T_CTRL_D);
	else if (fr == FR_CTRL_D)
		return (T_CTRL_C);
	if (is_word)
		return (T_NULL);
	return (T_ASSIGNMENT_WORD);
}
