/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_sym_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:42:52 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/09 21:43:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*ft_del_sym_str(char *str, char *delsym)
{
	char	*buffer;
	char	*newstr;
	int		i;
	int		j;

	if (!str || !delsym)
		return (NULL);
	if (!(buffer = ft_strnew(ft_strlen(str))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && ft_is_str_contain(delsym, str[i]))
		i++;
	while (str[i])
	{
		if (!ft_is_str_contain(delsym, str[i]))
			buffer[j++] = str[i];
		i++;
	}
	buffer[j] = '\0';
	newstr = ft_strdup(buffer);
	ft_memdel((void **)&buffer);
	return (newstr);
}
