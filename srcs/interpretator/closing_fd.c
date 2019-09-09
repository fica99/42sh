/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:21:55 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/09 20:47:44 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	closing_fd(t_node *ast, t_term *term)
{
	int		left_fd;
	int		right_fd;
	int		back_fd;

	left_fd = -5;
	right_fd = -5;
	if (tk_class(ast->token, C_CLOSE))
	{
		get_close_fd(ast->token->lexeme, &left_fd, &right_fd);
		if (left_fd < -1 || left_fd > 2 || right_fd < 0 ||
		(right_fd > 2 && !ft_strchr(ast->token->lexeme, '-')))
		{
			print_error_withoutexit("42sh", NULL, NULL, EBADF);
			return ;
		}
		back_fd = copy_fd(left_fd, right_fd);
		interpret_ast(ast->left, term);
		restore_fd(back_fd, right_fd);
	}
}

void	get_close_fd(char *str, int *left_fd, int *right_fd)
{
	int		i;
	char	*nb;
	int		j;

	i = -1;
	j = 0;
	if (!(nb = ft_strnew(100)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	while (ft_isdigit(str[++i]))
		nb[j++] = str[i];
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
		if (!(*right_fd = open("/dev/null", 0)))
 			print_error("42sh", "open() error", "/dev/null", 0);
	ft_memdel((void**)&nb);
}
