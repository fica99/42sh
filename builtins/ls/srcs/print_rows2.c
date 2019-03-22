/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:25:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/15 14:38:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_label_attr(t_dir *request, char *buf, t_attr *attr)
{
	acl_t	tmp;

	if (get_type(request->mode) != 'b' && get_type(request->mode) != 'c')
	{
		attr->size_list = listxattr(request->path, attr->list, NAME_SATTR,
						(get_type(request->mode) == 'l') ? XATTR_NOFOLLOW : 0);
		tmp = acl_get_link_np(request->path, ACL_TYPE_EXTENDED);
		if (attr->size_list)
			buf[0] = '@';
		else if (tmp)
		{
			buf[0] = '+';
			acl_free(tmp);
		}
		else
			buf[0] = ' ';
	}
	else
		buf[0] = ' ';
	buf[1] = ' ';
	return (2);
}

int		print_number(long int num, long int max, char *buf, uint8_t j)
{
	long int	bit;
	int			i;

	i = 0;
	bit = get_bit(num);
	while (i + bit < max)
		buf[i++] = ' ';
	max = (j) ? max + 2 : max;
	putnum(num, i + bit - 1, buf);
	if (j)
		buf[i++ + bit] = ',';
	buf[i + bit] = ' ';
	return ((int)max + 1);
}

void	putnum(long int n, int i, char *buf)
{
	if (n >= 10)
		putnum(n / 10, i - 1, buf);
	buf[i] = n % 10 + '0';
}

int		putuid(char *uid, ushort max, char *buf)
{
	int i;

	i = 0;
	while (uid[i])
	{
		buf[i] = uid[i];
		i++;
	}
	while (i < max + 2)
		buf[i++] = ' ';
	return (i);
}

int		putgid(char *gid, ushort max, char *buf)
{
	int i;

	i = 0;
	while (gid[i])
	{
		buf[i] = gid[i];
		i++;
	}
	while (i < max + 2)
		buf[i++] = ' ';
	return (i);
}
