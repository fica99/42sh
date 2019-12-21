/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara- <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:43:53 by olegmulko         #+#    #+#             */
/*   Updated: 2019/12/21 18:16:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ac_conversion_scrolling(int opt_rows, t_rl_cord *cord, t_autocom *ac)
{
	int		offset;

	ac->opts_print = ac->opts_size;
	ac->scrolling = 0;
	ac->delta_y = cord->y_cur - cord->y_start;
	offset = (cord->ws_row - 1) - (cord->y_cur + opt_rows);
	if (offset < 0)
	{
		if ((ac->scrolling = cord->y_cur - (offset * -1) + 1) < 0)
		{
			cord->y_start = 0;
			cord->y_cur = cord->y_start + ac->delta_y;
			ac->opts_print = ac->cols * (cord->ws_row - ac->delta_y - 2);
			ac->rows = ac_get_rows(ac->opts_print, ac->cols);
		}
		else
		{
			cord->y_start -= (offset * -1);
			cord->y_cur = cord->y_start + ac->delta_y;
		}
	}
	ac->fixed_opts_print = ac->opts_print;
}

void	ac_get_rows_cols_count(char **options, t_rl_cord *cord, t_autocom *ac)
{
	int	rows;
	int	cols;

	if (!options || !cord)
		return ;
	ac->max_len = ac_get_max_word_len(options);
	ac->opts_size = ft_darlen(options);
	cols = cord->ws_col / (ac->max_len + 1);
	rows = ac_get_rows(ac->opts_size, cols);
	ac->cols = cols;
	ac->rows = rows;
}

int		ac_get_max_word_len(char **list)
{
	int	i;
	int	max;
	int	len;

	if (!list)
		return (0);
	max = 0;
	i = 0;
	while (list[i])
	{
		len = ft_strlen(list[i++]);
		if (len > max)
			max = len;
	}
	return (max);
}

int		ac_get_rows(int count_options, int cols)
{
	int	rows;

	rows = 1;
	while (cols * rows < count_options)
		rows++;
	return (rows);
}

void	ac_set_null_params(t_autocom *ac)
{
	ac->index = -1;
	ac->first = 0;
	ac->start = NULL;
	ft_memdel((void **)&ac->path);
	ac->path = NULL;
	ft_free_dar(ac->options);
	ac->options = NULL;
	ac->scrolling = 0;
	ac->cols = 0;
	ac->rows = 0;
	ac->max_len = 0;
	ac->opts_size = 0;
	ac->opts_print = 0;
	ac->index_print = 0;
	ac->fixed_opts_print = 0;
	ac->prog = 0;
}
