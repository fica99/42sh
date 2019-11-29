/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:58:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:51:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define LRED_OPEN O_RDONLY
# define RRED_OPEN O_RDWR | O_CREAT | O_TRUNC
# define DRRED_OPEN O_RDWR | O_CREAT | O_APPEND
# define PERM_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define INT_LEN 10
# define HEREDOC_FILE "/tmp/.fucking_heredoc"
# define INIT_AGGR_FD -5

typedef struct s_sep_list
{
	int sep;
	int status;
	struct	s_sep_list  *next;
}				t_sep_list;

char		**ft_strtok(char *s);
t_sep_list	*g_sep_list;
char		*ft_strccut(char *str, char c);
char		*ft_stricut(char *str, int i);
t_token		*split_list(t_token *token)
t_token		*find_token(t_token *list, int type);

t_sep_list	*new_sep(t_token *token);
void		add_logical(t_token *token);
t_job		*job_new(void);

int			syntax_err(t_token *token);

#endif