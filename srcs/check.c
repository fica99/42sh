/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:56:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/25 21:56:35 by aashara-         ###   ########.fr       */
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
		arr1 = ft_strdup(arr);
		ft_memdel((void**)&arr);
	}
	return (arr1);
}