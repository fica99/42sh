/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:29:46 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/01 16:29:47 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	*ft_realloc(void *buf, size_t old, size_t new_size)
{
	unsigned char	*new_buf;

	if (!(new_buf = (unsigned char *)ft_memalloc(new_size)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	if (buf)
		ft_memcpy(new_buf, buf, old);
	return (new_buf);
}
