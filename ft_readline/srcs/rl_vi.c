/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_vi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:07:43 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 19:00:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_open_editor(char **env)
{
	char	**argv;
	char	*command;

	if (!(argv = ft_darnew(2)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (!(command = ft_getenv("VISUAL", env)))
		if (!(command = ft_getenv("EDITOR", env)))
			command = "vi";
	if (!(argv[1] = ft_strdup(RL_VIFILE)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (!(argv[0] = ft_strdup(command)))
		rl_err("42sh", "malloc() error", ENOMEM);
	find_command(argv);
	ft_free_dar(argv);
}
