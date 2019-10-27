/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:03:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/27 21:25:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ac_get_word(char *is_command, char *line, short pos)
{
	char	*command;
	short	start;
	char	*copy;

	start = pos;
	while (start > 0)
	{
		if (ft_strchr(" \t\n;|", line[--start]))
		{
			++start;
			break ;
		}
	}
	command = NULL;
	if (start >= 0 && start < pos && ft_isalnum(line[start]))
	{
		if (!(command = ft_strtrim(copy = ft_strsub(line, start, pos))))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
		ft_strdel(&copy);
	}
	else
		--start;
	*is_command = ac_is_command(line, start, pos);
	return (command);
}

char	ac_is_command(char *line, short start, short pos)
{
	while (start > 0 && start < pos && !ft_strchr(";|", line[start]))
		if (ft_strchr(" \t\n", line[start--]))
			return (FALSE);
	return (TRUE);
}

void	ac_print_params(char **arr, short win_width)
{
	int	max_len;
	int	i;
	int	len;
	int	width;

	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
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
			width = (max_len + 1);
		}
		ft_putstr_fd(arr[i], STDOUT_FILENO);
		while (len++ <= max_len)
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
