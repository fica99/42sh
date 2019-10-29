/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/10/29 23:42:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_standart_prompt(char *prompt)
{
	char	*folder;
	char	host[FT_HOST_NAME_MAX];

	gethostname(host, FT_HOST_NAME_MAX);
	ft_strcpy(prompt, CYAN);
	ft_strcat(prompt, getenv("USER"));
	ft_strcat(prompt, RED);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, GREEN);
	ft_strcat(prompt, host);
	ft_strcat(prompt, RED);
	ft_strcat(prompt, ":");
	ft_strcat(prompt, YELLOW);
	folder = rl_get_path();
	ft_strcat(prompt, folder);
	ft_memdel((void**)&folder);
	ft_strcat(prompt, "\n");
	ft_strcat(prompt, PURPLE);
	ft_strcat(prompt, "$> ");
	ft_strcat(prompt, STANDART);
}

char		*rl_get_path(void)
{
	char	*path;
	char	*pwd;
	char	*home;

	path = NULL;
	pwd = getenv("PWD");
	home = getenv("HOME");
	if (home && pwd)
	{
		if (!ft_strncmp(pwd, home, ft_strlen(home)))
		{
			if (!(path = ft_strjoin("~", pwd + ft_strlen(home))))
				rl_err("42sh", "malloc() error", ENOMEM);
		}
		else
		{
			if (!(path = ft_strdup(pwd)))
				rl_err("42sh", "malloc() error", ENOMEM);
		}
	}
	return (path);
}
