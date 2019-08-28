/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:35:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/29 13:36:25 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_node		*expr(t_string *str)
{
	t_node	*node;
	t_token	*token;

	token = get_next_token(str);
	if (token_type(token, ERROR) || !token_type(token, EXPR))
	{
		if (token_type(token, ERROR))
			g_parser_flags |= PARSER_ERROR;
		free_token(&token);
		return (NULL);
	}
	node = init_node(NULL, token, NULL);
	return (node);
}

