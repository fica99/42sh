/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

void	standart_prompt(void)
{
	char	hostname[FT_HOST_NAME_MAX];
	char	*folder;

	gethostname(hostname, FT_HOST_NAME_MAX);
	RED(STDOUT_FILENO);
	CYAN(STDOUT_FILENO);
	ft_putstr_fd(ft_getenv("USER"), STDOUT_FILENO);
	RED(STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	GREEN(STDOUT_FILENO);
	ft_putstr_fd(hostname, STDOUT_FILENO);
	ft_putchar_fd(':', STDOUT_FILENO);
	YELLOW(STDOUT_FILENO);
	folder = get_path();
	ft_putstr_fd(folder, STDOUT_FILENO);
	ft_memdel((void**)&folder);
	RED(STDOUT_FILENO);
	ft_putchar_fd(NEW_LINE, STDOUT_FILENO);
	PURPLE(STDOUT_FILENO);
	ft_putstr_fd("$> ", STDOUT_FILENO);
	STANDART(STDOUT_FILENO);
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
			if ((j = prompt_user_host(str, i)) == i)
				if ((j = prompt_dir_history(str, i)) == i)
					if ((j = prompt_colour_name(str, i)) == i)
						j = prompt_time(str, i);
		}
		if (j == i)
			ft_putchar_fd(str[i], STDOUT_FILENO);
		else
			i = j;
	}
}

short	prompt_user_host(char *str, short i)
{
	char	hostname[FT_HOST_NAME_MAX];
	char	*stop;

	if (!ft_strncmp(str + i, "\\u", 2))
		ft_putstr_fd(ft_getenv("USER"), STDOUT_FILENO);
	else if (!ft_strncmp(str + i, "\\h", 2) ||
	!ft_strncmp(str + i, "\\H", 2))
	{
		gethostname(hostname, FT_HOST_NAME_MAX);
		if (!ft_strncmp(str + i, "\\h", 2) && (stop = ft_strchr(hostname, '.')))
			*stop = '\0';
		ft_putstr_fd(hostname, STDOUT_FILENO);
	}
	else
		i--;
	return (++i);
}
