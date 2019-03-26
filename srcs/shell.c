/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 18:57:43 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	pid_t	p;
	int		status;

	while (RUNNING)
	{
		print_message();
		p = fork();
		if (p < 0)
		{
			perror("Fork() error");
			exit(1);
		}
		if (p)
			waitpid(p, &status, 0);
		else
			read_prompt();
		if (WEXITSTATUS(status) == 2)
			break ;
	}
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
			arr = ft_strdup(buf);
		else
		{
			arr1 = ft_strjoin(arr, buf);
			ft_memdel((void**)&arr);
			arr = arr1;
		}
		if ((arr1 = check_new_line(arr)) != NULL)
			break;
	}
	parse_string(arr1);
}

void	find_command(char **args)
{
	if (ft_strncmp(args[0], "ls", 2) == 0)
		execve("/bin/ls", args, env_cp);
	else if (ft_strncmp(args[0], "cd", 2) == 0)\
		cd(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		echo(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		env(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "setenv", 6) == 0)
		ft_setenv(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "unsetenv", 8) == 0)
		ft_unsetenv(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		execve("/bin/pwd", args, env_cp);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		exit(2);
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(args[0]);
		ft_putchar('\n');
	}
}