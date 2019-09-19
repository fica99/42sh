/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/09/19 21:35:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	term_prompt(short history_len, char *name)
{
	char	*prompt;

	if ((prompt = ft_getenv("PS1")))
		write_prompt(prompt, history_len, name);
	else
		standart_prompt();
}

void	standart_prompt(void)
{
	char	hostname[FT_HOST_NAME_MAX];
	char	*folder;

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
	ft_putchar_fd(' ', STDIN_FILENO);
	YELLOW(STDIN_FILENO);
	folder = get_folder();
	ft_putstr_fd(folder, STDIN_FILENO);
	ft_memdel((void**)&folder);
	RED(STDIN_FILENO);
	ft_putchar_fd(']', STDIN_FILENO);
	PURPLE(STDIN_FILENO);
	ft_putstr_fd(" $> ", STDIN_FILENO);
	STANDART(STDIN_FILENO);
}

void	write_prompt(char *str, short history_len, char *name)
{
	short	i;
	short	j;

	i = -1;
	while (str[++i])
	{
		j = i;
		if (str[i] == '\\')
		{
			j = prompt_user_host(str, i);
			if (j == i)
				j = prompt_time(str, i);
			if (j == i)
				j = prompt_dir_history(str, i, history_len);
			if (j == i)
				j = prompt_colour_name(str, i, name);
		}
		if (j == i)
			ft_putchar_fd(str[i], STDIN_FILENO);
		else
			i = j;
	}
}

short	prompt_user_host(char *str, short i)
{
	char	hostname[FT_HOST_NAME_MAX];
	short	j;

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
		if (!ft_strncmp(str + i, "\\H", 2))
			ft_putstr_fd(hostname, STDIN_FILENO);
		else
		{
			j = 0;
			while (hostname[j] && hostname[j] != '.')
				ft_putchar_fd(hostname[j++], STDIN_FILENO);
		}
		i++;
	}
	return (i);
}

short	prompt_dir_history(char *str, short i, short history_len)
{
	char	*path;

	if (!ft_strncmp(str + i, "\\W", 2))
	{
		path = get_folder();
		ft_putstr_fd(path, STDIN_FILENO);
		ft_memdel((void**)&path);
	}
	else if (!ft_strncmp(str + i, "\\w", 2))
	{
		path = get_path();
		ft_putstr_fd(path, STDIN_FILENO);
		ft_memdel((void**)&path);
	}
	else if (!ft_strncmp(str + i, "\\$", 2))
	{
		(ft_getenv("USER") && !ft_strcmp(ft_getenv("USER"), "root")) ?
		ft_putchar_fd('#', STDIN_FILENO) : ft_putchar_fd('$', STDIN_FILENO);
	}
	else if (!ft_strncmp(str + i, "\\!", 2) || !ft_strncmp(str + i, "\\#", 2))
		ft_putnbr_fd(history_len, STDIN_FILENO);
	else
		i--;
	i++;
	return (i);
}
