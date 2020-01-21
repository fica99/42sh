/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:38:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/21 19:25:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void		rl_autocom_delete_copy(char **res)
{
	size_t	i;
	size_t	j;

	if (!res)
		return ;
	i = 0;
	while (res[i])
	{
		if (res[i + 1] && !ft_strcmp(res[i], res[i + 1]))
		{
			j = i;
			ft_strdel(&res[i]);
			while (res[j + 1])
			{
				res[j] = res[j + 1];
				++j;
			}
			res[j] = NULL;
			--i;
		}
		++i;
	}
}

void			rl_k_tab(t_readline *rl)
{
	t_rl_autocom_parse	autocom;
	size_t				len;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_autocom_parse(&autocom, rl);
	if (autocom.is_env == TRUE)
		autocom.res = get_env_names_dar(autocom.to_find, ALL_ENV);
	else if (autocom.is_path == TRUE)
		autocom.res = rl_autocom_path(autocom.to_find);
	else if (autocom.is_bin == TRUE)
		autocom.res = rl_autocom_bin(autocom.to_find);
	len = ft_darlen(autocom.res);
	ft_dar_quick_sort(autocom.res, len);
	rl_autocom_delete_copy(autocom.res);
	rl_autocom_print(&autocom, rl);
	ft_strdel(&autocom.to_find);
	ft_free_dar(autocom.res);
}
