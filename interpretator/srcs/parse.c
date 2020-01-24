/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	parse_ass_words(t_ast *node, t_job *curr)
{
	if ((*node->token)->type == T_ASSIGNMENT_WORD)
		node->token = set_ass_words(node->token, add_process(curr));
	if ((*node->token)->type == T_WORD || (*node->token)->class == C_REDIR)
		word_list(node->token, add_process(curr));
}

void	parse_pipe(t_ast *node, t_job *curr)
{
	if ((*node->token)->class != C_PIPE)
		return (parse_ass_words(node, curr));
	parse_ass_words(node->left, curr);
	if ((*node->right->token)->class == C_PIPE)
		parse_pipe(node->right, curr);
	else
		parse_ass_words(node->right, curr);
}

void	parse_logical(t_ast *root)
{
	if (!root)
		return ;
	if ((*root->token)->class != C_LOG_OPERS)
		return (parse_pipe(root, job_new(NULL)));
	parse_pipe(root->left, job_new(root->token));
	if (root->right && (*root->right->token)->class == C_LOG_OPERS)
		parse_logical(root->right);
	else if (root->right)
		parse_pipe(root->right, job_new(root->token));
}

void	parse(t_ast *root)
{
	if ((*root->token)->type != T_SEP)
		return (parse_logical(root));
	parse_logical(root->left);
	if (root->right && (*root->right->token)->type == T_SEP)
		parse(root->right);
	else
		parse_logical(root->right);
}
