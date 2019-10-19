/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:57:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_node		*init_node(t_node *left, t_token *token, t_node *right)
{
	t_node	*node;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
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

char		tk_type(t_token *token, t_token_type type)
{
	if (!token)
		return (FALSE);
	if (token->type == type)
		return (TRUE);
	return (FALSE);
}

char		tk_class(t_token *token, t_token_class class)
{
	if (!token)
		return (FALSE);
	if (token->class == class)
		return (TRUE);
	return (FALSE);
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
