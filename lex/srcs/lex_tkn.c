/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tkn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:33:58 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/08 21:52:12 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn	*lex_new_tkn(void)
{
	t_lex_tkn	*new_tkn;

	if (!(new_tkn = (t_lex_tkn *)malloc(sizeof(t_lex_tkn))))
		return (NULL);
	new_tkn->value = NULL;
	new_tkn->type = T_NULL;
	new_tkn->class = C_NULL;
	new_tkn->start_pos = 0;
	new_tkn->end_pos = 0;
	return (new_tkn);
}

t_lex_tkn	*lex_del_tkn(t_lex_tkn *token)
{
	if (!token)
		return (NULL);
	if (token->value)
		free(token->value);
	token->value = NULL;
	token->type = T_NULL;
	token->class = C_NULL;
	token->start_pos = 0;
	token->end_pos = 0;
	free(token);
	return (NULL);
}
