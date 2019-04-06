/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/06 20:03:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat_print(char *arr, char *new_arr)
{
	int	i;

	i = 0;
	while (arr[i] != '\0')
		i++;
	while (*new_arr != '\0')
	{
		if (ft_isprint(*new_arr))
			arr[i] = *new_arr;
		new_arr++;
	}
	return (arr);
}

void	ft_putstr_print(char *arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		if (ft_isprint(arr[i]))
			ft_putchar(arr[i]);
}

t_cord	*get_term(void)
{
	struct winsize	size;
	t_cord			*cord;

	if (ioctl(0, TIOCGWINSZ, &size) < 0)
	{
		print_error("minishell", "ioctl() error", NULL, 0);
		exit(-1);
	}
	if (!(cord = (t_cord*)malloc(sizeof(t_cord))))
	{
		print_error("minishell", "malloc() error", NULL, ENOMEM);
		exit(1);
	}
	cord->x = 0;
	cord->y = 0;
	cord->ws_col = size.ws_col;
	return (cord);
}
