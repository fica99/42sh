/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:52:38 by filip             #+#    #+#             */
/*   Updated: 2019/09/02 20:06:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PARSER_ERROR (1 << 1)
# define THREAD_FLAG 1
# define EXPR_FLAG 2

typedef struct	s_node
{
	struct s_node	*left;
	t_token			*token;
	struct s_node	*right;
}				t_node;

t_node		*init_node(t_node *left, t_token *token, t_node *right);
void		free_ast(t_node **ast);
t_node		*parser(char *str);
t_node		*statement_list(t_string *str);
t_node		*statement(t_string *str);
t_node		*thread_statement(t_string *str);
t_node		*pipe_ast(t_string *str);
t_node		*expr(t_string *str);
char		*check_token_type(t_token *token, token_type type);
char		*check_token_class(t_token *token, token_class class);
void		free_token(t_token **token);
char		g_parser_flags;
#endif
