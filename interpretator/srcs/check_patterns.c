/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:46:57 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/14 00:28:42 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char	**check_patterns(char **args, size_t i, short patterns)
{
	char	**result;
	char	**new_args;
	int		res_len;

	result = NULL;
	if (!patterns || !(result = pattern_matching(args[i])))
		return (args);
	res_len = ft_darlen(result);
	if (!(new_args = ft_darnew(ft_darlen(args) + res_len)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memcpy(new_args, args, i * sizeof(char *));
	ft_memcpy(new_args + i, result, sizeof(char *) * res_len);
	ft_memcpy(new_args + i + res_len, args + i + 1, sizeof(char *) *
										ft_darlen(args + i + 1));
	free(args);
	free(result);
	return (new_args);
}
