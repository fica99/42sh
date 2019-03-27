/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:19:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 18:27:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**copy_double_arr(char **arr)
{
	unsigned short	i;
	char			**arr1;

	if (!(arr1 = (char **)malloc(sizeof(char*) * (double_arr_len(arr) + 1))))
		print_error("minishell", "malloc() error", NULL, 12);
	i = 0;
	while (arr[i])
	{
		if (!(arr1[i] = ft_strdup(arr[i])))
			print_error("minishell", "malloc() error", NULL, 12);
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

char	*join_env(char *name, char *new_value)
{
	char *name1;
	char *name2;
	
	if (!(name1 = ft_strjoin(name, "=")))
		print_error("setenv", "malloc() error", NULL, 12);
	if (!(name2 = ft_strjoin(name1, new_value)))
		print_error("setenv", "malloc() error", NULL, 12);
	return(name2);
}