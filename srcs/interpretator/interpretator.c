/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/29 22:04:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	make_command(char *buff, t_term *term)
{
	char	**args;
	short	i;

	if (!buff || !(*buff) || !(args = ft_strsplit(buff, ' ')))
		return ;
	i = -1;
	while (args[++i])
		args[i] = spec_symbols(args[i]);
	find_command(args, term);
	ft_free_dar(args);
}

char	*spec_symbols(char *args)
{
	char	*path;
	char	*arr;

	if (*args == '~')
	{
		if ((path = ft_getenv("HOME")))
		{
			arr = args;
			if (!(args = ft_strjoin(path, arr + 1)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
		}
	}
	if (*args == '$' && args + 1)
	{
		if ((path = ft_getenv(args + 1)))
		{
			arr = args;
			if (!(args = ft_strdup(path)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
		}
	}
	return (args);
}

void	interpret_ast(t_node *ast, t_term *term)
{
	if (ast)
	{
		if (token_type(ast->token, SEP))
		{
			interpret_ast(ast->left, term);
			interpret_ast(ast->right, term);
			return ;
		}
		if (token_type(ast->token, PIPE))
			pipe_op(ast, term);
		if (token_class(ast->token, REDIR))
			redir_op(ast, term);
		if (token_type(ast->token, EXPR))
			make_command(ast->token->lexeme, term);
	}
}


void	pipe_op(t_node *ast, t_term *term)
{
	int	pipes[2];
	int	pid[2];

	if (pipe(pipes) != 0)
		print_error("42sh", "pipe() error", NULL, NOERROR);
	if ((pid[0] = make_process()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		interpret_ast(ast->left, term);
		exit(0);
	}
	if ((pid[1] = make_process()) == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		interpret_ast(ast->right, term);
		exit(0);
	}
	close(pipes[0]);
	close(pipes[1]);
}
