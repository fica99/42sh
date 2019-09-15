/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:21:43 by filip             #+#    #+#             */
/*   Updated: 2019/07/30 01:06:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_history(t_history *history)
{
	char	**buf;

	buf = history->history_buff;
	history->history_index = -1;
	ft_memdel((void**)&(history->history_path));
	ft_free_dar(buf);
}

char	*get_history_file_path(void)
{
	if (ft_getenv("PWD"))
		return (ft_strjoin(ft_getenv("PWD"), HISTORY_FILE));
	return (NULL);
}
