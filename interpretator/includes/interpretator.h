/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:58:11 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/22 15:55:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include "../lex/includes/lex.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define DEF_HEREDOC_SIZE 10

# define INT_LEN 10
# define HEREDOC_FILE "/tmp/.42sh_heredoc"
# define INIT_AGGR_FD -5

typedef	int		(*t_redirect_func)(t_lex_tkn **, t_process *, int);

typedef	struct	s_her_vars
{
	char		**buf;
	size_t		buf_size;
	size_t		i;
	char		*tmp;
	char		**tmpb;

}				t_her_vars;

typedef struct	s_open_files
{
	int			*fd;
	size_t		size;
}				t_open_files;

int				make_ast(t_lex_tkn **list, t_ast **root);
void			clean_tree(t_ast *ast);
void			cls_redir(int **red);
t_lex_tkn		**set_ass_words(t_lex_tkn **list, t_process *curr_proc);
char			*ft_stricut(char *str, int i);
char			*substitution(char *str);
void			exec_jobs(t_job *j);
int				l_redir(t_lex_tkn **list, t_process *curr_proc, int io_number);
int				here_doc(t_lex_tkn **list, t_process *curr, int io_number);
int				l_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number);
int				ft_open(char *fname, int fl);
int				g_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number);
void			add_redir(t_process *curr_proc, int fd0, int fd1);
void			file_err(char *s1, char *s2, char *s3, t_job *j);
int				g_redir(t_lex_tkn **list, t_process *curr_proc, int io_number);
void			ft_free_proc(t_process *p);
int				get_token_ind(t_lex_tkn **token_list, t_lex_tkn *token);
t_job			*job_new(t_lex_tkn **sep);
void			ft_free_jobs(t_job *j);
void			close_fds(t_job *first_job);
t_process		*add_process(t_job *first_job);
int				syntax_err(t_lex_tkn *token);
t_lex_tkn		**find_token(t_lex_tkn **list, int type);
void			parse(t_ast *root);
char			**ft_strtok(char *s);
char			*ft_strccut(char *str, char c);
char			*ft_stricut(char *str, int i);
t_lex_tkn		**split_list(t_lex_tkn **token);
t_lex_tkn		**find_token(t_lex_tkn **list, int type);
void			word_list(t_lex_tkn **redir, t_process *cur_proc);

/*
**  spec_symb.c
*/
char			*spec_symbols(char *args);
char			*tilda_expr(char *args);
char			*dollar_expr(char *args);

/*
**	expansions_validation.c
*/
void			*expansions(char *s);
int				check_bracket(char *s);

/*
**	expansions_implementation.c
*/

char			*exp_implement(char *s);

#endif
