/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/12 20:33:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_buf_print(char *buf, char *c, uint8_t *n)
{
	int len;

	*n = *n;
	if (ft_isprint(*c))
	{
		len = cord.x_cur - cord.prompt;
		buf = ft_stradd(buf, c, len);
		ft_putstr(buf + len);
		cord.x_cur += ft_strlen(c);
		len = ft_strlen(buf + len);
		while (--len)
			ft_putstr(LEFT);
	}
	/*if (*c == '\t'))
	{
		while (!(autocom(&buf, (*n) * NORMAL_LINE)))
			buf = strnew_realloc_buf(buf, n);
	}*/
	check_key(c, buf);
	return (buf);
}

char	*reading(char *buf)
{
	char			c[LINE_MAX + 1];
	uint8_t			n;
	uint8_t			nb;


	n = 1;
	cord.x_cur = cord.prompt;
	while (RUNNING)
	{
		set_input_mode();
		nb = read(STDIN_FILENO, &c, LINE_MAX);
		c[nb] = '\0';
		signalling();
		reset_input_mode();
		if (g_flags & SHELL_SIG)
		{
			ft_strclr(buf);
			g_flags &= ~SHELL_SIG;
			continue;
		}
		if ((ft_strchr(c, '\n')))
			break;
		while (ft_strlen(buf) + ft_strlen(c) >= NORMAL_LINE * n)
			buf = strnew_realloc_buf(buf, &n);
		buf = make_buf_print(buf , c, &n);
	}
	ft_putchar('\n');
	return (buf);
}

char	*read_prompt()
{
	char	*str;

	if (!(str = ft_strnew(NORMAL_LINE)))
		print_error("minishell", "malloc() error", NULL, 0);
	return (reading(str));
}