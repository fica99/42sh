/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/11/05 16:52:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

// void	rl_standart_prompt(char *prompt, char **env)
// {
// 	char	host[FT_HOST_NAME_MAX];
// 	char	*home;
// 	char	*pwd;
// 	short	len_home;

// 	gethostname(host, FT_HOST_NAME_MAX);
// 	ft_strcpy(prompt, CYAN);
// 	ft_strcat(prompt, ft_getenv("USER", env));
// 	ft_strcat(prompt, RED);
// 	ft_strcat(prompt, "@");
// 	ft_strcat(prompt, GREEN);
// 	ft_strcat(prompt, host);
// 	ft_strcat(prompt, RED);
// 	ft_strcat(prompt, ":");
// 	ft_strcat(prompt, YELLOW);
// 	home = ft_getenv("HOME", env);
// 	pwd = ft_getenv("PWD", env);
// 	if (!ft_strncmp(pwd, home, (len_home = ft_strlen(home))))
// 		ft_strcat(ft_strcat(prompt, "~"), pwd + len_home);
// 	else
// 		ft_strcat(prompt, pwd);
// 	ft_strcat(prompt, "\n");
// 	ft_strcat(prompt, PURPLE);
// 	ft_strcat(prompt, "$> ");
// 	ft_strcat(prompt, STANDART);
// }

// void	write_prompt(char *str)
// {
// 	short	i;
// 	short	j;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		j = i;
// 		if (str[i] == '\\')
// 		{
// 			if ((j = prompt_user_host(str, i)) == i)
// 				if ((j = prompt_dir_history(str, i)) == i)
// 					if ((j = prompt_colour_name(str, i)) == i)
// 						j = prompt_time(str, i);
// 		}
// 		if (j == i)
// 			ft_putchar_fd(str[i], STDOUT_FILENO);
// 		else
// 			i = j;
// 	}
// }

// short	prompt_user_host(char *str, short i)
// {
// 	char	hostname[FT_HOST_NAME_MAX];
// 	char	*stop;

// 	if (!ft_strncmp(str + i, "\\u", 2))
// 		ft_putstr_fd(ft_getenv("USER"), STDOUT_FILENO);
// 	else if (!ft_strncmp(str + i, "\\h", 2) ||
// 	!ft_strncmp(str + i, "\\H", 2))
// 	{
// 		gethostname(hostname, FT_HOST_NAME_MAX);
// 		if (!ft_strncmp(str + i, "\\h", 2) && (stop = ft_strchr(hostname, '.')))
// 			*stop = '\0';
// 		ft_putstr_fd(hostname, STDOUT_FILENO);
// 	}
// 	else
// 		i--;
// 	return (++i);
// }

// short	prompt_dir_history(char *str, short i)
// {
// 	char	*path;

// 	if (!ft_strncmp(str + i, "\\W", 2) || !ft_strncmp(str + i, "\\w", 2))
// 	{
// 		path = get_path();
// 		ft_putstr_fd(path, STDOUT_FILENO);
// 		ft_memdel((void**)&path);
// 	}
// 	else if (!ft_strncmp(str + i, "\\$", 2))
// 	{
// 		path = ft_getenv("USER");
// 		(path && !ft_strcmp(path, "root")) ? ft_putchar_fd('#', STDOUT_FILENO)
// 		: ft_putchar_fd('$', STDOUT_FILENO);
// 	}
// 	else if (!ft_strncmp(str + i, "\\!", 2) || !ft_strncmp(str + i, "\\#", 2))
// 		ft_putnbr_fd(g_history.hist_len, STDOUT_FILENO);
// 	else
// 		i--;
// 	i++;
// 	return (i);
// }

// short	prompt_time(char *str, short i)
// {
// 	time_t		t;
// 	short		j;
// 	struct tm	*info;

// 	time(&t);
// 	if (t == -1)
// 		err_exit(g_argv[0], "time() error", NULL, EFAULT);
// 	info = localtime(&t);
// 	if ((j = check_time_flags(str, i, info)) != i)
// 		return (j);
// 	return (i);
// }

// short	check_time_flags(char *str, short i, struct tm *info)
// {
// 	char	buffer[LINE_MAX];

// 	buffer[0] = '\0';
// 	if (!ft_strncmp(str + i, "\\A", 2))
// 		strftime(buffer, LINE_MAX, "%H:%M", info);
// 	else if (!ft_strncmp(str + i, "\\t", 2))
// 		strftime(buffer, LINE_MAX, "%H:%M:%S", info);
// 	else if (!ft_strncmp(str + i, "\\T", 2))
// 		strftime(buffer, LINE_MAX, "%I:%M:%S", info);
// 	else if (!ft_strncmp(str + i, "\\@", 2))
// 		strftime(buffer, LINE_MAX, "%I:%M", info);
// 	else if (!ft_strncmp(str + i, "\\d", 2))
// 		strftime(buffer, LINE_MAX, "%a %b %d", info);
// 	else if (!ft_strncmp(str + i, "\\D{", 3))
// 		i = time_format_flag(str, i, info);
// 	else
// 		i--;
// 	i++;
// 	ft_putstr_fd(buffer, STDOUT_FILENO);
// 	return (i);
// }

// short	prompt_colour_name(char *str, short i)
// {
// 	char	colour[LINE_MAX];
// 	short	j;

// 	if (!ft_strncmp(str, "\\e", 2))
// 	{
// 		j = 1;
// 		colour[0] = '\033';
// 		while (*(str + i + j + 1) != 'm')
// 		{
// 			colour[j] = *(str + i + j + 1);
// 			j++;
// 		}
// 		colour[j] = '\0';
// 		ft_putstr_fd(colour, STDOUT_FILENO);
// 		i += j;
// 	}
// 	else if (!ft_strncmp(str + i, "\\s", 2))
// 	{
// 		ft_putstr_fd(g_argv[0], STDOUT_FILENO);
// 		i++;
// 	}
// 	return (i);
// }

// short	time_format_flag(char *str, short i, struct tm *info)
// {
// 	char	buffer[LINE_MAX];
// 	char	format[LINE_MAX];
// 	short	j;

// 	str = ft_strchr(str + i, '{') + 1;
// 	j = 0;
// 	while (*(str + j) != '\0' && *(str + j) != '}')
// 	{
// 		format[j] = *(str + j);
// 		j++;
// 	}
// 	format[j] = '\0';
// 	strftime(buffer, LINE_MAX, format, info);
// 	ft_putstr_fd(buffer, STDOUT_FILENO);
// 	i += j + TIME_BRACKETS;
// 	return (i);
// }

// char		*get_path(void)
// {
// 	char	*path;
// 	char	*pwd;
// 	char	*home;

// 	path = NULL;
// 	pwd = ft_getenv("PWD");
// 	home = ft_getenv("HOME");
// 	if (home && pwd)
// 	{
// 		if (!ft_strncmp(pwd, home, ft_strlen(home)))
// 		{
// 			if (!(path = ft_strjoin("~", pwd + ft_strlen(home))))
// 				err_exit("42sh", "malloc() error", NULL, ENOMEM);
// 		}
// 		else
// 		{
// 			if (!(path = ft_strdup(pwd)))
// 				err_exit("42sh", "malloc() error", NULL, ENOMEM);
// 		}
// 	}
// 	return (path);
// }

// char		*get_cur_dir(void)
// {
// 	char	*path;
// 	char	*pwd;
// 	char	*home;
// 	char	*folder;

// 	path = NULL;
// 	pwd = ft_getenv("PWD");
// 	home = ft_getenv("HOME");
// 	if (home && pwd)
// 	{
// 		if (*(folder = ft_strrchr(pwd, '/') + 1) == '\0')
// 			folder--;
// 		if (!(path = ft_strdup(folder)))
// 			err_exit("42sh", "malloc() error", NULL, ENOMEM);
// 		if (!ft_strcmp(pwd, home))
// 		{
// 			ft_strclr(path);
// 			ft_strcat(path, "~");
// 		}
// 	}
// 	return (path);
// }
