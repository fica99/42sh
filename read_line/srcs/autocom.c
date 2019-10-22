/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:03:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/22 21:13:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ac_get_word(char *is_command, char *line, short pos)
{
	char	*command;
	short	start;

	start = pos;
	while (--start >= 0)
		if (ft_strchr(" \t\n;|", line[start]))
			break ;
	command = NULL;
	if (start + 1 != pos)
		if (!(command = ft_strsub(line, start + 1, pos)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	*is_command = TRUE;
	while (start >= 0 && !ft_strchr(";|", line[start]))
	{
		if (ft_strchr(" \t\n", line[start]))
		{
			*is_command = FALSE;
			break ;
		}
		--start;
	}
	return (command);
}

void	ac_print_params(char **arr, short win_width)
{
	int	max_len;
	int	i;
	int	len;
	int	width;

	max_len = ac_max_len(arr);
	i = -1;
	width = 0;
	while (arr[++i])
	{
		len = ft_strlen(arr[i]);
		width += (max_len + 1);
		if (width >= win_width)
		{
			ft_putchar_fd(NEW_LINE, STDOUT_FILENO);
			width = 0;
		}
		ft_putstr_fd(arr[i], STDOUT_FILENO);
		while (++len <= max_len)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int		ac_max_len(char **arr)
{
	int	max_len;
	int	i;
	int	len;

	max_len = 0;
	i = -1;
	while (arr[++i])
		if (max_len < (len = ft_strlen(arr[i])))
			max_len = len;
	return (max_len);
}


