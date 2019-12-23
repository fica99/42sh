/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:50:39 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/28 07:50:40 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_lex_tkn	**find_token(t_lex_tkn **list, int class)
{
	while ((*list)->type != T_END && (*list)->class != class)
		list++;
	return (list);
}

t_lex_tkn	**split_list(t_lex_tkn **token)
{
	if (!*token || (*token)->type == T_END)
		return (token);
	(*token)->type = T_END;
	return (++token);
}
