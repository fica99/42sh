/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cols2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:11:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 14:17:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_cols_rows(t_prt_cols *pprm, ushort ws_col)
{
	pprm->cols = pprm->cnt_elems;
	pprm->rows = 1;
	if (pprm->max >= ws_col)
	{
		pprm->cols = 1;
		pprm->rows = pprm->cnt_elems;
		return ;
	}
	while (((pprm->max + 1) * pprm->cnt_elems) / pprm->rows > ws_col)
		(pprm->rows)++;
	pprm->cols = (pprm->cnt_elems % pprm->rows == 0) ?
	pprm->cnt_elems / pprm->rows
	: (pprm->cnt_elems / pprm->rows) + 1;
	while (pprm->cols * (pprm->max + 1) > ws_col)
	{
		pprm->cols = (pprm->cnt_elems % (++(pprm->rows)) == 0)
		? pprm->cnt_elems / pprm->rows : (pprm->cnt_elems / pprm->rows) + 1;
	}
}
