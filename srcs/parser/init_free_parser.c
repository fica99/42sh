/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:57:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/04 20:52:31 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_node		*init_node(t_node *left, t_token *token, t_node *right)
{
	t_node	*node;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	node->left = left;
	node->token = token;
	node->right = right;
	return (node);
}

void		free_ast(t_node **ast)
{
	if (ast && *ast)
	{
		free_ast(&((*ast)->left));
		free_ast(&((*ast)->right));
		free_token(&((*ast)->token));
		ft_memdel((void**)ast);
		*ast = NULL;
	}
}

char		*check_token_type(t_token *token, token_type type)
{
	if (!token)
		return (NULL);
	if (token->type == type)
		return (SOMETHING);
	return (NULL);
}

char		*check_token_class(t_token *token, token_class class)
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
