/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:21:43 by filip             #+#    #+#             */
/*   Updated: 2019/07/01 16:23:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_history(t_history *history)
{
	char	**buf;

	buf = history->history_buff;
	ft_memdel((void**)&(history->history_path));
	free_double_arr(buf);
}

char	*get_history_file_path(void)
{
	if (ft_getenv("PWD"))
		return (ft_strjoin(ft_getenv("PWD"), "/.history"));
	return (NULL);
}
