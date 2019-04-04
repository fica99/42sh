/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:19:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/04 18:20:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**copy_double_arr(char **arr)
{
	short	i;
	char	**arr1;

	if (!(arr1 = (char**)malloc(sizeof(char*) * (double_arr_len(arr) + 1))))
	{
		print_error("minishell", "malloc() error", NULL, ENOMEM);
		exit(1);
	}
	i = -1;
	while (arr[++i])
	{
		if (!(arr1[i] = ft_strdup(arr[i])))
		{
			print_error("minishell", "malloc() error", NULL, ENOMEM);
			exit(1);
		}
	}
	arr1[i] = NULL;
	return (arr1);
}

char			*strjoin_realloc(char *str, char *new_str)
{
	char	*arr;

	arr = str;
	if (!(str = ft_strjoin(arr, new_str)))
	{
		print_error("minishell", "malloc() error", NULL, ENOMEM);
		exit(1);
	}
	ft_memdel((void**)&arr);
	return (str);
}
void			free_double_arr(char **arr)
{
	short	i;

	i = -1;
	while (arr[++i])
		ft_memdel((void**)&(arr[i]));
	free(arr);
	arr = NULL;
}

pid_t	make_process(void)
{
	pid_t	p;

	p = fork();
	if (p < 0)
	{
		print_error("minishell", "fork() error", NULL, ENOMEM);//EAGAIN, ENOMEM
		exit(1);
	}
	return (p);
}

char	*join_env(char *name, char *new_value)
{
	char *name1;
	char *name2;

	if (!(name1 = ft_strjoin(name, "=")))
		print_error("setenv", "malloc() error", NULL, ENOMEM);
	if (!(name2 = ft_strjoin(name1, new_value)))
		print_error("setenv", "malloc() error", NULL, ENOMEM);
	ft_memdel((void**)&name1);
	return(name2);
}
