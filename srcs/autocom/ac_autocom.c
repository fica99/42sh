/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_autocom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:12:50 by ggrimes           #+#    #+#             */
/*   Updated: 2019/07/06 21:51:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	autocomplite(t_buff *buff, t_cord *cord)
{
	static t_autocom	ac;

	if (!buff && !cord)
		return (ac_set_null_params(&ac));
	if (ac.options != NULL)
	{
		ac_index_tracking(&ac);
		ac_opts_tracking(&ac);
		ac_complement_line(buff, cord, &ac);
		get_cur_cord(cord);
		ac_print_options(&ac, cord);
		return ;
	}
	if (!(ac.options = ac_parse_cmd_line(buff->buffer, &ac)))
		return (ac_set_null_params(&ac));
	get_cur_cord(cord);
	ac_get_rows_cols_count(ac.options, cord, &ac);
	ac_conversion_scrolling(ac.rows + 1, cord, &ac);
	ac_print_options(&ac, cord);
	return ;
}

void	ac_complement_line(t_buff *buffer, t_cord *cord, t_autocom *ac)
{
	char	*arg;
	short	i;

	CHECKV(ac->options);
	if (ac->prog)
		arg = ft_strdup(ac->options[ac->index]);
	else
		arg = ft_strjoin(ac->path, ac->options[ac->index]);
	CHECKV(arg);
	i = ac->start - buffer->buffer;
	while (ft_strlen(arg) + ft_strlen(buffer->buffer) >=
			(unsigned)buffer->malloc_len)
		buffer->buffer = ft_strdup_realloc(buffer->buffer,
				buffer->malloc_len += NORMAL_LINE);
	ac->start = buffer->buffer + i;
	CHECKV(ac_rewrite_str(ac->start, arg));
	go_left(cord->pos, cord);
	ac_clear_options();
	ft_putstr_cord(buffer->buffer + cord->pos, cord);
	ft_memdel((void **)&arg);
}

int		ac_rewrite_str(char *dest, char *src)
{
	int	i;

	if (!dest || !src)
		return (0);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (1);
}
