/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/29 19:51:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	int		status;
	ushort	i;

	i = 0;
	while (RUNNING)
	{
		signal(SIGINT, stop_program);
		print_message();
		make_new_process(++i, &status);
		if (WEXITSTATUS(status) == 100)
			break ;
		if (WEXITSTATUS(status) != 100 && status != -123)
			i = 0;
	}
}

void	make_new_process(ushort i, int *status)
{
	pid_t	p;

	if (i == 1)
	{
		p = make_process();
		if (p)
			waitpid(p, status, 0);
		else
			read_prompt();
	}
	else
		*status = -123;
}

void	read_prompt(void)
{
	char	buf[PROMPT_LEN + 1];
	char	*arr;
	char	*arr1;
	uint8_t	nb;

	arr = NULL;
	while ((nb = read(0, buf, PROMPT_LEN)) > 0)
	{
		buf[nb] = '\0';
		if (!arr)
		{
			if (!(arr = ft_strdup(buf)))
				print_error("minishell", "malloc() error", NULL, ENOMEM);
		}
		else
		{
			if (!(arr1 = ft_strjoin(arr, buf)))
				print_error("minishell", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
			arr = arr1;
		}
		if ((arr1 = check_new_line(arr)) != NULL)
			break;
	}
	parse_string(arr1);
}

void	exec_command(char **args)
{
	if (ft_strncmp(args[0], "ls", 2) == 0)
		execve("/bin/ls", args, env_cp);
	else
		execve("/bin/pwd", args, env_cp);
}

void	find_command(char **args)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)\
		cd(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		echo(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		env(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "setenv", 6) == 0)
		ft_setenv(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "unsetenv", 8) == 0)
		ft_unsetenv(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		exit(100);
	else if (!(ft_strncmp(args[0],"ls", 2)) || !(ft_strncmp(args[0],"pwd", 3)))
		exec_command(args);
	else
		print_error("minishell", "command not found", args[0], 0);
}