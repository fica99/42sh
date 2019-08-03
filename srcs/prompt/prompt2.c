/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:34:35 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/03 01:05:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_shell.h"

short	prompt_colour(char *str, short i)
{
	char	colour[20];
	short	j;

	j = 0;
	if (*(str + i + 1) == 'e')
	{
		colour[0] = '\033';
		j = 1;
		while (*(str + i + j + 1) != 'm')
		{
			colour[j] = *(str + i + j + 1);
			j++;
		}
		colour[j] = '\0';
		ft_putstr_fd(colour, STDIN_FILENO);
	}
	return (i + j);
}

short	prompt_dir_history(char *str, short i, short history_len)
{
	char	*path;

	if (!ft_strncmp(str + i, "\\W", 2))
	{
		path = get_folder();
		ft_putstr_fd(path, STDIN_FILENO);
		ft_memdel((void**)&path);
	}
	else if (!ft_strncmp(str + i, "\\w", 2))
	{
		path = get_path();
		ft_putstr_fd(path, STDIN_FILENO);
		ft_memdel((void**)&path);
	}
	else if (!ft_strncmp(str + i, "\\$", 2))
	{
		(ft_getenv("USER") && !ft_strcmp(ft_getenv("USER"),"root")) ?
		ft_putchar_fd('#', STDIN_FILENO) : ft_putchar_fd('$', STDIN_FILENO);
	}
	else if (!ft_strncmp(str + i, "\\!", 2) || !ft_strncmp(str + i, "\\#", 2))
		ft_putnbr_fd(history_len, STDIN_FILENO);
	else
		i--;
	i++;
	return (i);
}
