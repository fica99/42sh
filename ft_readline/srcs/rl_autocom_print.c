/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_autocom_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:45:32 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/21 19:30:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static short	rl_words_len(char **arr)
{
	short	i;
	short	len;
	short	max_word_len;

	i = -1;
	max_word_len = 0;
	while (arr[++i])
	{
		if (max_word_len < (len = ft_strlen(arr[i])))
			max_word_len = len;
	}
	return (max_word_len);
}

static void		rl_autocom_print_arr(t_rl_autocom_print *autocom)
{
	short	j;
	short	i;
	short	row;

	j = 0;
	row = 1;
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putchar('\n');
	while (j < autocom->arr_len)
	{
		i = -1;
		while (autocom->arr[j][++i])
			ft_putchar(autocom->arr[j][i]);
		while (++i <= autocom->max_word)
			ft_putchar(' ');
		j += autocom->rows;
		if (row < autocom->rows && j >= autocom->arr_len)
		{
			j = ++row;
			ft_putchar('\n');
		}
	}
	ft_putchar('\n');
}

static void		rl_autocom_print_params(t_rl_autocom_print *autocom,
										char **res, t_readline *rl)
{
	autocom->arr = res;
	autocom->arr_len = ft_darlen(res);
	autocom->max_word = rl_words_len(res) + 2;
	autocom->cols = rl->cord.ws_col / autocom->max_word;
	autocom->rows = autocom->arr_len / autocom->cols;
	if (autocom->arr_len % autocom->cols != 0)
		++autocom->rows;
}

void			rl_autocom_print(t_rl_autocom_parse *parse, t_readline *rl)
{
	t_rl_autocom_print	autocom;
	short				pos;
	short				len;

	if (!parse->res || !*parse->res)
		return ;
	rl_autocom_print_params(&autocom, parse->res, rl);
	if (autocom.arr_len > 1)
	{
		pos = rl->cord.pos;
		rl_go_to_cord(rl->cord.x_end, rl->cord.y_end);
		rl_autocom_print_arr(&autocom);
		rl_write_prompt(rl->prompt, rl->history);
		rl_start_cord_data(&rl->cord);
	}
	else
	{
		len = ft_strlen(parse->to_find);
		if (parse->is_env)
			++len;
		ft_stradd(rl->line.buffer, parse->res[0] + len, rl->cord.pos);
		pos = ft_strlen(parse->res[0] + len);
	}
	rl_disable_line(rl);
	rl_go_right(pos, &rl->cord);
}
