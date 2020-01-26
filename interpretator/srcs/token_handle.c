/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:50:39 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 17:57:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

t_lex_tkn	**find_token(t_lex_tkn **list, int class)
{
	while ((*list)->type != T_END && (*list)->class != (t_lex_tkn_class)class)
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
