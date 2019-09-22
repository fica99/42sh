/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:52:38 by filip             #+#    #+#             */
/*   Updated: 2019/09/22 16:21:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PARSER_ERROR (1 << 1)
# define THREAD_FLAG 1
# define EXPR_FLAG 2

typedef struct		s_string
{
	char			*str;
	short			index;
}					t_string;

typedef struct		s_node
{
	struct s_node	*left;
	t_token			*token;
	struct s_node	*right;
}					t_node;

/*
**	init_free_parser.c
*/
t_node				*init_node(t_node *left, t_token *token, t_node *right);
void				free_ast(t_node **ast);
char				tk_type(t_token *token, t_token_type type);
char				tk_class(t_token *token, t_token_class class);
void				free_token(t_token **token);
/*
**	ast.c
*/
t_node				*parser(char *str);
t_node				*statement_list(t_string *str);
t_node				*statement(t_string *str);
t_node				*thread_statement(t_string *str);
t_node				*fd_aggr(t_string *str);
/*
**	ast_other.c
*/
t_node				*rredir_statement(t_node *ast, t_string *str);
t_node				*lredir_statement(t_node *ast, t_string *str);
t_node				*pipe_statement(t_node *ast, t_string *str);
t_node				*expr(t_string *str);
char				g_parser_flags;
#endif
