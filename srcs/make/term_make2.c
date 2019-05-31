/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_make2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:56:18 by filip             #+#    #+#             */
/*   Updated: 2019/05/31 22:23:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_putstr_cord(char *str)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		(g_term.x_cur)++;
		str++;
		if (g_term.x_cur >= g_term.ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			g_term.x_cur = 0;
			if (g_term.y_cur >= g_term.ws_row - 1)
				(g_term.y_start)--;
			else
				(g_term.y_cur)++;
		}
	}
}

void	reset_term(void)
{
	char	*rmkx_mode;

	if ((rmkx_mode = tigetstr("rmkx")) != (char*)-1)
		ft_putstr_fd(rmkx_mode, STDIN_FILENO);
}

void	get_bin_path(void)
{
	if (ft_getenv("PWD"))
		g_term.history_path = ft_strjoin(ft_getenv("PWD"), "/.history");
}