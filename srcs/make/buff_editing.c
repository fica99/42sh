/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:25:22 by filip             #+#    #+#             */
/*   Updated: 2019/05/18 17:15:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		**copy_double_arr(char **arr)
{
	short	i;
	char	**arr1;

	if (!arr)
		return (NULL);
	if (!(arr1 = (char**)malloc(sizeof(char*) * (double_arr_len(arr) + 1))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (arr[++i])
		if (!(arr1[i] = ft_strdup(arr[i])))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
	arr1[i] = NULL;
	return (arr1);
}

char		*strnew_realloc_buf(char *str, short len)
{
	char	*arr;

	arr = str;
	if (!(str = ft_strnew(len)))
	{
		reset_input_mode();
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	str = ft_strcat(str, arr);
	ft_memdel((void**)&arr);
	return (str);
}

char		*ft_strdel_el(char *buf, size_t i)
{
	char	*str;

	if (i >= ft_strlen(buf))
		return (buf);
	str = NULL;
	if (buf + i + 1)
	{
		if (!(str = ft_strdup(buf + i + 1)))
		{
			reset_input_mode();
			ft_putchar_fd('\n', STDERR_FILENO);
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		}
	}
	*(buf + i) = '\0';
	buf = ft_strcat(buf, str);
	ft_memdel((void**)&str);
	return (buf);
}

char		*ft_stradd(char *buf, char *s, size_t i)
{
	char	*str;

	if (i >= ft_strlen(buf))
		return (ft_strcat(buf, s));
	if (!(str = ft_strdup(buf + i)))
	{
		reset_input_mode();
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	*(buf + i) = '\0';
	buf = ft_strcat(ft_strcat(buf, s), str);
	ft_memdel((void**)&str);
	return (buf);
}
