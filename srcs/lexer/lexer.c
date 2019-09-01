/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 19:40:00 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/30 19:45:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*check_token_type(t_token *token, int type)
{
	if (!token)
		return (NULL);
	if (token->type == type)
		return (SOMETHING);
	return (NULL);
}

char		*check_token_class(t_token *token, int class)
{
	if (!token)
		return (NULL);
	if (token->class == class)
		return (SOMETHING);
	return (NULL);
}

void		free_token(t_token **token)
{
	if (token && *token)
	{
		ft_memdel((void**)&((*token)->lexeme));
		ft_memdel((void**)token);
		*token = NULL;
	}
}
