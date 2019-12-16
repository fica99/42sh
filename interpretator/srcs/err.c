/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:49:47 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/28 07:49:48 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int syntax_err(t_lex_tkn *token)
{
	ft_putstr("42sh: ");
	ft_putstr("syntax error near unexpected token: ");
	if (token->value)
		ft_putstr(token->value);
	else
	{
		if (token->type == T_END)
			ft_putstr("EOL");
		else if (token->type == T_PIPE)
			ft_putstr("PIPE");
		else if (token->class == C_REDIR)
			ft_putstr("REDIRECT");
	}
	ft_putchar('\n');
	return (-1);
}

void	file_err(char *s1, char *s2, char *s3, t_job *j)
{
	char *buf;
	size_t len;

	if (!s1 || !s2 || !s3)
		return ;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(buf = (char *)ft_memalloc(len + 1)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	ft_strcat(buf, s1);
	ft_strcat(buf, s2);
	ft_strcat(buf, s3);
	while (j->next)
		j = j->next;
	j->err_message = buf;
	j->unactive = 1;
}
