/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/08/01 23:28:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	term_prompt(void)
{
	if (ft_getenv("PS1"))
		write_prompt(ft_getenv("PS1"));
	else
		standart_prompt();
}

void	standart_prompt(void)
{
	char	hostname[FT_HOST_NAME_MAX];

	gethostname(hostname, FT_HOST_NAME_MAX);
	RED(STDIN_FILENO);
	ft_putchar_fd('[', STDERR_FILENO);
	if (ft_getenv("USER"))
	{
		CYAN(STDIN_FILENO);
		ft_putstr_fd(ft_getenv("USER"), STDIN_FILENO);
		RED(STDIN_FILENO);
		ft_putchar_fd('@', STDIN_FILENO);
	}
	GREEN(STDIN_FILENO);
	ft_putstr_fd(hostname, STDIN_FILENO);
	if ((check_path()))
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		YELLOW(STDIN_FILENO);
		ft_putstr_fd(check_path(), STDIN_FILENO);
	}
	RED(STDIN_FILENO);
	ft_putchar_fd(']', STDIN_FILENO);
	PURPLE(STDIN_FILENO);
	ft_putstr_fd(" $> ", STDIN_FILENO);
	STANDART(STDIN_FILENO);
}

void	write_prompt(char *str)
{
	short	i;
	short	j;

	i = -1;
	while (str[++i])
	{
		j = i;
		if (str[i] == '\\')
		{
			j = prompt_user_host_dir(str, i);
			if (j == i)
				j = prompt_time_root(str, i);
		}
		if (j == i)
			j = prompt_colour(str, i);
		if (j == i)
			ft_putchar_fd(str[i], STDIN_FILENO);
		else
			i = j;
	}
}

short	prompt_user_host_dir(char *str, short i)
{
	char	hostname[FT_HOST_NAME_MAX];

	if (!ft_strncmp(str + i, "\\u", 2))
	{
		if (ft_getenv("USER"))
			ft_putstr_fd(ft_getenv("USER"), STDIN_FILENO);
		i++;
	}
	else if (!ft_strncmp(str + i, "\\h", 2) ||
	!ft_strncmp(str + i, "\\H", 2))
	{
		gethostname(hostname, FT_HOST_NAME_MAX);
		ft_putstr_fd(hostname, STDIN_FILENO);
		i++;
	}
	else if (!ft_strncmp(str + i, "\\W", 2))
	{
		if ((check_path()))
			ft_putstr_fd(check_path(), STDIN_FILENO);
		i++;
	}
	return (i);
}

short	prompt_time_root(char *str, short i)
{
	time_t	t;
	short	j;
	char	*str_time;

	if (!ft_strncmp(str + i, "\\$", 2))
	{
		if (ft_getenv("USER") && !ft_strcmp(ft_getenv("USER"),"root"))
			ft_putchar_fd('#', STDIN_FILENO);
		else
			ft_putchar_fd('$', STDIN_FILENO);
		i++;
	}
	else if (!ft_strncmp(str + i, "\\@", 2))
	{
		time(&t);
		if (t == -1)
			print_error("42sh", "time() error", NULL, EFAULT);
		str_time = ctime(&t);
		j = START_TIME;
		while (j != END_TIME)
			ft_putchar_fd(str_time[j++],STDIN_FILENO);
		i++;
	}
	return (i);
}
