/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/20 04:20:54 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_ass_words(t_ast *node, t_job *curr)
{
	if ((*node->token)->type == T_ASSIGNMENT_WORD)
		h_ass_words(node->token, add_process(curr));
	else if ((*node->token)->class == C_WORD ||
	(*node->token)->class == C_REDIR)
		word_list(node->token, add_process(curr));
}

static void	parse_pipe(t_ast *node, t_job *curr)
{
	if ((*node->token)->class != C_PIPE)
		return (parse_ass_words(node, curr));
	parse_ass_words(node->left, curr);
	if ((*node->right->token)->class == C_PIPE)
		parse_pipe(node->right, curr);
	else
		parse_ass_words(node->right, curr);
}

static void	parse_logical(t_ast *root, t_lex_tkn **sep)
{
	if (!root)
		return ;
	if ((*root->token)->class != C_LOG_OPERS)
		return (parse_pipe(root, job_new(sep)));
	parse_pipe(root->left, job_new((*root->token)->type == T_AND ? root->token : sep));
	if (root->right && ((*root->right->token)->class == C_LOG_OPERS))
		parse_logical(root->right, root->token);
	else if (root->right)
		parse_pipe(root->right, job_new(root->token));
}

void		parse(t_ast *root)
{
	if ((*root->token)->type != T_SEP)
		return (parse_logical(root, NULL));
	parse_logical(root->left, NULL);
	if (root->right && (*root->right->token)->type == T_SEP)
		parse(root->right);
	else
		parse_logical(root->right, NULL);
}

int			ast_handle(t_lex_tkn ***tokens, t_ast **root, char **line)
{
	int ret;

	ret = make_ast(*tokens, root);
	if (ret == 2)
	{
		clean_tree(*root);
		*root = NULL;
		if (al_p_lo(tokens, line))
			return (1);
		return (ast_handle(tokens, root, line));
	}
	return (ret);
}
