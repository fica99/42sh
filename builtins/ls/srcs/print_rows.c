/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 23:06:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/15 14:23:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_rows(t_dir *request, ushort ws_cols, ushort flags, uint8_t g)
{
	char		buf[BUFFOUT];
	t_prt_rows	pprm;
	int			i;

	ws_cols = 0;
	i = 0;
	pprm = get_print_prm_r(request);
	if (g)
	{
		ft_putstr("total ");
		ft_putnbr(pprm.total);
		ft_putchar('\n');
	}
	while (request)
	{
		if (i + SIZELINE >= BUFFOUT)
		{
			write(1, buf, i);
			i = 0;
		}
		i += print_line_rows(request, flags, pprm, buf + i);
		request = request->next;
	}
	write(1, buf, i);
}

t_prt_rows	get_print_prm_r(t_dir *request)
{
	t_prt_rows	pprm;

	pprm.total = 0;
	pprm.max_nlink = 1;
	pprm.max_size = 1;
	pprm.max_uid = 0;
	pprm.max_gid = 0;
	pprm.max_gid = 0;
	pprm.max_minor = 0;
	pprm.cur_time = time(NULL);
	while (request)
	{
		get_data_max(&pprm, request);
		request = request->next;
	}
	return (pprm);
}

int			print_line_rows(t_dir *request, ushort flags, t_prt_rows pprm,
			char *buf)
{
	int		i;
	t_attr	attr;

	i = 0;
	buf[i++] = get_type(request->mode);
	i += print_mode_bits(request->mode, buf + i);
	i += print_label_attr(request, buf + i, &attr);
	i += print_number((long int)request->nlink,
			(long int)pprm.max_nlink, buf + i, 0);
	i += print_gu_ids(request, pprm, flags, buf + i);
	if (get_type(request->mode) == 'b' || get_type(request->mode) == 'c')
	{
		i += print_number(major(request->st_rdev), pprm.max_major, buf + i, 1);
		i += print_number(minor(request->st_rdev), pprm.max_minor, buf + i, 0);
	}
	else
		i += print_number((long int)request->size,
				(long int)pprm.max_size, buf + i, 0);
	i += print_time(request->time_mod, pprm.cur_time, buf + i);
	i += print_name(request, buf + i);
	i += print_attr_full(request, flags, buf + i, attr);
	return (i);
}

int			print_mode_bits(mode_t mode, char *buf)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		buf[i++] = 'r';
		buf[i++] = 'w';
		buf[i++] = 'x';
	}
	cheak_usr(mode, buf);
	cheak_grp(mode, buf);
	cheak_oth(mode, buf);
	return (9);
}

int			print_name(t_dir *request, char *buf)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (request->name[j])
		buf[i++] = request->name[j++];
	if (get_type(request->mode) == 'l')
		i += print_link(request, buf + i);
	buf[i++] = '\n';
	return (i);
}
