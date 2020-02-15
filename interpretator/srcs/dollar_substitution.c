/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:26:01 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/15 13:39:06 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char    *strcutcopy(char *dest, char *copy, int i, int n)
{
    char *new;
    int copylen;
    if (!dest || !copy)
        return (NULL);
    copylen = ft_strlen(copy);
    if (!(new = (char *)malloc(ft_strlen(dest) + copylen + 1 - n)))
        err_exit("42sh", "malloc() error", NULL, ENOMEM);
    ft_memcpy(new, dest, dest + i - dest);
    ft_memcpy(&new[i], copy, copylen);
    ft_memcpy(&new[i + copylen], &dest[i + n], ft_strlen(&dest[i + n]));
    return (new);
}

char	*dollar_expr(char *line, int pos)
{
	char	*var;
	int		i;
	char	*replace;
	int		pos_save;

	i = 0;
	pos_save = pos;
	if (!(var = ft_strnew(LINE_MAX)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	pos++;
	while (line[pos] && isvalidparameter(line[pos]))
	{
		var[i++] = line[pos++];
	}
	replace = get_var(var, ALL_VARS);
	ft_memdel((void**)&var);
	return (strcutcopy(line, replace, pos_save, i));
}

char	*dollar_substitution(char *line, int pos)
{
	char	*for_return;
	
	if (line[pos + 1] == '{')
		;
    else
    {
		for_return = dollar_expr(line, pos);
    }
}

