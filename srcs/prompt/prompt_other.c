/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:34:35 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:55:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

short	prompt_dir_history(char *str, short i)
{
	char	*path;

	if (!ft_strncmp(str + i, "\\W", 2) || !ft_strncmp(str + i, "\\w", 2))
	{
		path = get_path();
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_memdel((void**)&path);
	}
	else if (!ft_strncmp(str + i, "\\$", 2))
	{
		path = ft_getenv("USER");
		(path && !ft_strcmp(path, "root")) ? ft_putchar_fd('#', STDOUT_FILENO)
		: ft_putchar_fd('$', STDOUT_FILENO);
	}
	else if (!ft_strncmp(str + i, "\\!", 2) || !ft_strncmp(str + i, "\\#", 2))
		ft_putnbr_fd(g_history.hist_len, STDOUT_FILENO);
	else
		i--;
	i++;
	return (i);
}

short	prompt_time(char *str, short i)
{
	time_t		t;
	short		j;
	struct tm	*info;

	time(&t);
	if (t == -1)
		err_exit(g_argv[0], "time() error", NULL, EFAULT);
	info = localtime(&t);
	if ((j = check_time_flags(str, i, info)) != i)
		return (j);
	return (i);
}

short	check_time_flags(char *str, short i, struct tm *info)
{
	char	buffer[LINE_MAX];

	buffer[0] = '\0';
	if (!ft_strncmp(str + i, "\\A", 2))
		strftime(buffer, LINE_MAX, "%H:%M", info);
	else if (!ft_strncmp(str + i, "\\t", 2))
		strftime(buffer, LINE_MAX, "%H:%M:%S", info);
	else if (!ft_strncmp(str + i, "\\T", 2))
		strftime(buffer, LINE_MAX, "%I:%M:%S", info);
	else if (!ft_strncmp(str + i, "\\@", 2))
		strftime(buffer, LINE_MAX, "%I:%M", info);
	else if (!ft_strncmp(str + i, "\\d", 2))
		strftime(buffer, LINE_MAX, "%a %b %d", info);
	else if (!ft_strncmp(str + i, "\\D{", 3))
		i = time_format_flag(str, i, info);
	else
		i--;
	i++;
	ft_putstr_fd(buffer, STDOUT_FILENO);
	return (i);
}

short	prompt_colour_name(char *str, short i)
{
	char	colour[LINE_MAX];
	short	j;

	if (!ft_strncmp(str, "\\e", 2))
	{
		j = 1;
		colour[0] = '\033';
		while (*(str + i + j + 1) != 'm')
		{
			colour[j] = *(str + i + j + 1);
			j++;
		}
		colour[j] = '\0';
		ft_putstr_fd(colour, STDOUT_FILENO);
		i += j;
	}
	else if (!ft_strncmp(str + i, "\\s", 2))
	{
		ft_putstr_fd(g_argv[0], STDOUT_FILENO);
		i++;
	}
	return (i);
}


short	time_format_flag(char *str, short i, struct tm *info)
{
	char	buffer[LINE_MAX];
	char	format[LINE_MAX];
	short	j;

	str = ft_strchr(str + i, '{') + 1;
	j = 0;
	while (*(str + j) != '\0' && *(str + j) != '}')
	{
		format[j] = *(str + j);
		j++;
	}
	format[j] = '\0';
	strftime(buffer, LINE_MAX, format, info);
	ft_putstr_fd(buffer, STDOUT_FILENO);
	i += j + TIME_BRACKETS;
	return (i);
}
