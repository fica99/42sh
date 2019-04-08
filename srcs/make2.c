/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/08 15:52:19 by aashara-         ###   ########.fr       */
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
		else if (*new_arr == 27)
			new_arr += 2;
		new_arr++;
	}
	return (arr);
}

void	get_cord(void)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, &size) < 0)
	{
		print_error("minishell", "ioctl() error", NULL, 0);
		exit(-1);
	}
	cord.x = 0;
	cord.y = 0;
	cord.ws_col = size.ws_col;
}
