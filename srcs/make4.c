/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:48:56 by filip             #+#    #+#             */
/*   Updated: 2019/04/27 15:41:39 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
