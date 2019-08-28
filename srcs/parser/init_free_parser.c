/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:57:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/28 17:58:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_node		*init_node(void *left, t_token *token, void *right)
{
	t_node	*node;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	node->left = left;
	node->token = token;
	node->right = right;
	return (node);
}

void		*free_ast(t_node **ast)
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
