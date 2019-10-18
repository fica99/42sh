/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggr_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:21:55 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

void	aggr_fd_op(t_node *ast)
{
	int		left_fd;
	int		right_fd;
	int		back_fd;

	left_fd = INIT_AGGR_FD;
	right_fd = INIT_AGGR_FD;
	if (tk_class(ast->token, C_CLOSE))
	{
		get_aggr_fd(ast->token->lexeme, &left_fd, &right_fd);
		if (left_fd < -1 || left_fd > 2 || (right_fd > 2 &&
		!ft_strchr(ast->token->lexeme, '-')))
		{
			err(g_argv[0], NULL, NULL, EBADF);
			return ;
		}
		back_fd = copy_fd(right_fd, left_fd);
		exec_redir_command(ast, C_CLOSE);
		restore_fd(back_fd, left_fd);
	}
}

void	get_aggr_fd(char *str, int *left_fd, int *right_fd)
{
	short	i;
	char	*nb;
	short	j;

	i = 0;
	j = 0;
	if (!(nb = ft_strnew(10)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	while (str[i] && ft_isdigit(str[i]))
		nb[j++] = str[i++];
	*left_fd = ft_atoi(nb);
	if (*nb == '\0')
		*left_fd = 1;
	ft_strclr(nb);
	i += 2;
	j = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		nb[j++] = str[i++];
	*right_fd = ft_atoi(nb);
	if (*nb == '\0')
		if (!(*right_fd = open("/dev/null", O_WRONLY)))
			err_exit(g_argv[0], "open() error", "/dev/null", NOERROR);
	ft_memdel((void**)&nb);
}
