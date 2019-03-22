/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:59:43 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 16:42:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_prt_cols	get_print_prm_c(t_dir *request, ushort ws_col)
{
	t_prt_cols	pprm;

	pprm.max = 0;
	pprm.cnt_elems = 0;
	while (request)
	{
		if (request->len > pprm.max)
			pprm.max = request->len;
		pprm.cnt_elems++;
		request = request->next;
	}
	get_cols_rows(&pprm, ws_col);
	return (pprm);
}

void		print_cols(t_dir *request, ushort ws_col, ushort flags, uint8_t j)
{
	t_prt_cols	pprm;
	u_int16_t	i;
	char		buf[BUFFOUT];

	if (!request)
		exit(-1);
	j = 1;
	flags = 0;
	i = 0;
	pprm = get_print_prm_c(request, ws_col);
	pprm.cur_row = 0;
	while (++pprm.cur_row <= pprm.rows && request)
	{
		print_line(request, pprm, buf, &i);
		request = request->next;
	}
	write(1, buf, i);
}

void		print_line(t_dir *request, t_prt_cols pprm, char *buf, u_int16_t *i)
{
	u_int16_t j;

	pprm.cur_col = 0;
	while (++pprm.cur_col <= pprm.cols && request)
	{
		j = 0;
		while (request->name[j])
		{
			*i = check_buf(buf, *i);
			buf[(*i)++] = request->name[j++];
		}
		while (j++ <= pprm.max && pprm.cur_col != pprm.cols)
		{
			*i = check_buf(buf, *i);
			buf[(*i)++] = ' ';
		}
		request = next_elem(request, pprm);
	}
	*i = check_buf(buf, *i);
	buf[(*i)++] = '\n';
}

u_int8_t	check_buf(char *buf, u_int8_t i)
{
	if (i == (u_int8_t)BUFFOUT)
	{
		write(1, buf, i);
		return (0);
	}
	return (i);
}
