/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:56:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/01 16:50:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned short	double_arr_len(char **arr)
{
	unsigned short	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
