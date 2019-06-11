/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_make2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:56:18 by filip             #+#    #+#             */
/*   Updated: 2019/06/11 18:08:23 by aashara-         ###   ########.fr       */
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

char	*get_history_file_path(void)
{
	if (ft_getenv("PWD"))
		return (ft_strjoin(ft_getenv("PWD"), "/.history"));
	return (NULL);
}

t_cord	*init_cord(void)
{
	t_cord	*cord;

	if (!(cord = (t_cord*)malloc(sizeof(t_cord))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	get_win_size(cord);
	return (cord);
}

t_buff	*init_buff(void)
{
	t_buff	*buff;

	if (!(buff = (t_buff*)malloc(sizeof(t_buff))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	buff->buffer = NULL;
	buff->malloc_len = 0;
	buff->save_buff = NULL;
	buff->save_malloc_len = 0;
	return (buff);
}
