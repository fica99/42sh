/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_asig_name2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 20:57:41 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 22:30:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void	lex_an_cut_quotes(t_lex_tkn *token, const char *str)
{
	size_t	pos;
	size_t	i;
	char	*new_str;

	lex_rewind_end_spases((char *)str, &token->end_pos);
	if (!(new_str = ft_strnew((token->end_pos) - (token->start_pos))))
		return ;
	i = 0;
	pos = token->start_pos;
	while (pos < token->end_pos)
	{
		if (str[pos] != '"' && str[pos] != '\'' && str[pos] != '`')
			new_str[i++] = str[pos];
		pos++;
	}
	token->value = new_str;
}
