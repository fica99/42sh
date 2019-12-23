/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_con_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 21:37:00 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/21 16:11:02 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_control_sub(char *str, short is_word, size_t *pos,
	int *err)
{
	size_t	i;
	int		brk;

	if (ft_strncmp(str + *pos, "$(", 2) != 0)
		return (0);
	i = *pos + 2;
	brk = 1;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '(')
			brk++;
		if (str[i] == ')')
			brk--;
		i++;
		if (!brk)
			break ;
	}
	*err = (brk) ? 1 : 0;
	if (!is_word)
		*pos = i;
	return (1);
}

t_lex_tkn_type	lex_control_sub(short is_word, int err)
{
	if (err)
		return (T_ERR);
	if (is_word)
		return (T_NULL);
	return (T_CONTROL_SUB);
}

void			lex_fill_control_sub_value(t_lex_tkn *token,
	char *str, size_t pos)
{
	size_t	start_pos;
	size_t	end_pos;
	size_t	len;

	lex_rewind_end_spases(str, &pos);
	start_pos = token->start_pos + 2;
	end_pos = token->end_pos - 1;
	len = end_pos - start_pos;
	token->value = ft_strsub(str, start_pos, len);
}
