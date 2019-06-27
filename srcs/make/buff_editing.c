/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:25:22 by filip             #+#    #+#             */
/*   Updated: 2019/06/28 00:35:53 by aashara-         ###   ########.fr       */
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
		go_right(ft_strlen(g_term.line.buffer.buffer) - g_term.line.cord->pos,
		g_term.line.cord);
		reset_input_mode(&g_term.line.savetty);
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	if (arr)
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
			go_right(ft_strlen(g_term.line.buffer.buffer) - g_term.line.cord->pos,
			g_term.line.cord);
			reset_input_mode(&g_term.line.savetty);
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
		go_right(ft_strlen(g_term.line.buffer.buffer) - g_term.line.cord->pos,
		g_term.line.cord);
		reset_input_mode(&g_term.line.savetty);
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	*(buf + i) = '\0';
	buf = ft_strcat(ft_strcat(buf, s), str);
	ft_memdel((void**)&str);
	return (buf);
}

char		*copy_from_buff(char *buffer, char *new_buffer, short start, short end)
{
	short	j;

	j = 0;
	while (start <= end)
		new_buffer[j++] = buffer[start++];
	return (new_buffer);
}
