/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/10/30 17:46:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_standart_prompt(char *prompt, char **env)
{
	char	host[FT_HOST_NAME_MAX];
	char	*home;
	char	*pwd;
	short	len_home;

	gethostname(host, FT_HOST_NAME_MAX);
	ft_strcpy(prompt, CYAN);
	ft_strcat(prompt, ft_getenv("USER", env));
	ft_strcat(prompt, RED);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, GREEN);
	ft_strcat(prompt, host);
	ft_strcat(prompt, RED);
	ft_strcat(prompt, ":");
	ft_strcat(prompt, YELLOW);
	home = ft_getenv("HOME", env);
	pwd = ft_getenv("PWD", env);
	if (!ft_strncmp(pwd, home, (len_home = ft_strlen(home))))
		ft_strcat(ft_strcat(prompt, "~"), pwd + len_home);
	else
		ft_strcat(prompt, pwd);
	ft_strcat(prompt, "\n");
	ft_strcat(prompt, PURPLE);
	ft_strcat(prompt, "$> ");
	ft_strcat(prompt, STANDART);
}
