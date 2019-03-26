/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:19:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 11:03:41 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**copy_double_arr(char **arr)
{
	unsigned short	i;
	char			**arr1;
	
	if (!(arr1 = (char **)malloc(sizeof(char*) * (double_arr_len(arr) + 1))))
		exit(1);
	i = 0;
	while (arr[i])
	{
		arr1[i] = ft_strdup(arr[i]);
		i++;
	}
	arr1[i] = NULL;
	return (arr1);
}

void			free_double_arr(char **arr)
{
	unsigned short	i;

	i = 0;
	while (arr[i])	
	{
		ft_memdel((void**)&(arr[i]));
		i++;
	}
	ft_memdel((void**)arr);
}