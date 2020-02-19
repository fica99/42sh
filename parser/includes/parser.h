/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:40:17 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/19 21:07:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lex.h"
# include "error.h"
# define COMPLETION 255
# define RULES_NUM 17
# define DEF_ARGS_SIZE 10
# define DEF_REDIR_SIZE 10
# define DEF_VARLIST_SIZE 10

typedef struct			s_ast
{
	t_lex_tkn			**token;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef	struct			s_redir_list
{
	t_lex_tkn			**rd_token;
	struct s_redir_list	*next;
}						t_redir_list;

typedef struct			s_process
{
	struct s_process	*next;
	char				**args;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					error;
	int					exit_status;
	int					**fd_list;
	t_redir_list		*r;
	char				**environment;
	int					inpipe;
	int					outpipe;
	size_t				redir_size;
	size_t				args_size;
}						t_process;

typedef struct			s_job
{
	struct s_job		*next;
	int					separator;
	int					num;
	int					execution;
	char				**command;
	t_process			*first_process;
	pid_t				pgid;
	struct termios		*tmodes;
}						t_job;

typedef struct			s_ass_vars
{
	char				**varlist;
	int					i;
	int					size;
	t_process			*p;

}						t_ass_vars;

typedef struct			s_cycle_list
{
	char				*name;
	struct s_cycle_list	*next;
}						t_cycle_list;

struct termios			g_shell_tmodes;
t_job					*g_first_job;
t_job					*g_last_job;

void					parse_calc(t_lex_tkn **tkn);
/*
**						make_ast.c
*/
int						make_ast(t_lex_tkn ***list, t_ast **root);
void					clean_tree(t_ast *ast);
/*
**						errors.c
*/
int						syntax_err(t_lex_tkn *token);
/*
**						parse.c
*/
void					parse(t_ast *root);
/*
**						add_process.c
*/
int						max_job(void);
t_process				*add_process(t_job *j);
t_job					*job_new(t_lex_tkn **sep);
/*
**						word_list.c
*/
void					h_ass_words(t_lex_tkn **list, t_process *p);
void					word_list(t_lex_tkn **list, t_process *cur_proc);

/*
**						alias_handle.c
*/
char					*ft_getalias(char *name, char **varlist);
t_lex_tkn				**alias_handle(t_lex_tkn **list);
/*
**						alias_add_to_cycle.c
*/
void					free_cycle_list(t_cycle_list *l);
void					add_to_cycle_list(char *alias, t_cycle_list **l);

#endif
