/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_bins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:19:27 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/27 22:34:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ac_get_bin(char *command)
{
	static size_t	i;
	t_hash			*hash;
	int				len;
	char			*data;

	len = ft_strlen(command);
	while (i < g_bin_table.size)
	{
		hash = g_bin_table.table[i];
		while (hash)
		{
			if ((data = ft_strrchr((char*)hash->data, '/')))
			{
				if (!ft_strncmp(command, ++data, len))
				{
					++i;
					return (data);
				}
			}
			hash = hash->next;
		}
		++i;
	}
	i = 0;
	return (NULL);
}

void	ac_bins(char *command, t_line *line)
{
	char	*bin[g_bin_table.size];
	int		i;
	t_cord	*cord;

	i = 0;
	while ((bin[i] = ac_get_bin(command)))
		++i;
	if (i == 1)
		print_symb(bin[0] + ft_strlen(command), line);
	else if (i > 1)
	{
		cord = line->cord;
		cord->pos -= (cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
		cord->ws_col));
		go_to_cord(cord->x_end, cord->y_end, STDIN_FILENO);
		ac_print_params(bin, cord->ws_col);
		ft_putchar_fd(NEW_LINE, STDIN_FILENO);
		ft_readline("");
	}
}
