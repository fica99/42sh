/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_make2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:56:18 by filip             #+#    #+#             */
/*   Updated: 2019/06/02 15:10:58 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_putstr_cord(char *str, t_cord *cord)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		(cord->x_cur)++;
		str++;
		if (cord->x_cur >= cord->ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
	}
}

void	reset_term(void)
{
	char	*rmkx_mode;

	if ((rmkx_mode = tigetstr("rmkx")) != (char*)-1)
		ft_putstr_fd(rmkx_mode, STDIN_FILENO);
}

char	*get_bin_path(void)
{
	if (ft_getenv("PWD"))
		return (ft_strjoin(ft_getenv("PWD"), "/.history"));
	return (NULL);
}