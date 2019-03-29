/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:56:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/29 16:47:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_new_line(char *arr)
{
	char	*stop;
	char	*arr1;

	arr1 = NULL;
	if ((stop = ft_strchr(arr, '\n')) != NULL)
	{
		*stop = '\0';
		if (!(arr1 = ft_strdup(arr)))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		ft_memdel((void**)&arr);
	}
	return (arr1);
}

unsigned short	double_arr_len(char **arr)
{
	unsigned short	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
