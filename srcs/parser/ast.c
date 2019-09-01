/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:35:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/30 20:16:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_node		*expr(t_string *str)
{
	t_node	*node;
	t_token	*token;

	token = get_next_token(str);
	if (check_token_type(token, FT_ERROR) || !check_token_type(token, EXPRESS))
	{
		if (check_token_type(token, FT_ERROR))
			g_parser_flags |= PARSER_ERROR;
		free_token(&token);
		return (NULL);
	}
	node = init_node(NULL, token, NULL);
	return (node);
}
