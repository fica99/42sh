/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:52:38 by filip             #+#    #+#             */
/*   Updated: 2019/08/30 19:38:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define LOOP 1
# define PARSER_ERROR (1 << 1)
# define THREAD_FLAG 1
# define EXPR_FLAG 2

typedef struct	s_node
{
	void	*left;
	t_token	*token;
	void	*right;
}				t_node;

typedef struct	s_string
{
	char	*str;
	short	index;
}				t_string;

t_node		*init_node(void *left, t_token *token, void *right);
void		*free_ast(t_node **ast);
t_node		*parser(char *str);
t_node		*statement_list(t_string *str);
t_node		*statement(t_string *str);
t_node		*thread_statement(t_string *str);
t_node		*pipe_ast(t_string *str);
t_node		*expr(t_string *str);
char		g_parser_flags;
#endif
