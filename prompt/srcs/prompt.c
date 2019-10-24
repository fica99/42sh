/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/10/24 22:58:44 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	standart_prompt(void)
{
	char	*folder;
	char	host[FT_HOST_NAME_MAX];

	gethostname(host, FT_HOST_NAME_MAX);
	ft_strcpy(g_prompt, CYAN);
	ft_strcat(g_prompt, ft_getenv("USER"));
	ft_strcat(g_prompt, RED);
	ft_strcat(g_prompt, "@");
	ft_strcat(g_prompt, GREEN);
	ft_strcat(g_prompt, host);
	ft_strcat(g_prompt, RED);
	ft_strcat(g_prompt, ":");
	ft_strcat(g_prompt, YELLOW);
	folder = get_path();
	ft_strcat(g_prompt, folder);
	ft_memdel((void**)&folder);
	ft_strcat(g_prompt, "\n");
	ft_strcat(g_prompt, PURPLE);
	ft_strcat(g_prompt, "$> ");
	ft_strcat(g_prompt, STANDART);
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
