/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:18:56 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/29 23:47:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*ft_readline(char *prompt, t_rl_mode mode)
{
	(void)mode;
	if (prompt)
		ft_strcpy(g_rl.prompt, prompt);
	else
		rl_standart_prompt(g_rl.prompt);
	return (NULL);
}

void	init_readline(void)
{
	rl_save_attr(&g_rl.canon_mode);
	rl_init_terminfo();
	rl_init_rl_struct(&g_rl);
}

void	free_readline(void)
{
	rl_free_rl_struct(&g_rl);
	reset_shell_mode();
	rl_set_attr(&g_rl.canon_mode);
}

void	rl_err(char *name, char *str, char *err)
{
	ft_putstr_fd(name, STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	if (err)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_set_attr(&g_rl.canon_mode);
	exit(EXIT_FAILURE);
}
