/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/30 21:09:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	int		status;
	pid_t	p;
	int		i;

	i = 1;
	while (RUNNING)
	{
		signal(SIGINT, stop_program);
		print_message();
		if (i)
			p = make_process();
		if (p)
		{
			waitpid(p, &status, 0);
			i = 1;
		}
		else
			make_new_process(&i);
		if (WEXITSTATUS(status) == 100)
			break ;
	}
}

void	make_new_process(int *status)
{
	char	*arr;

	*status = 0;
	arr = read_prompt();
	parse_string(arr);
}

char	*read_prompt(void)
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
	return (arr1);
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
	if (ft_strncmp(args[0], "cd", 2) == 0)
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