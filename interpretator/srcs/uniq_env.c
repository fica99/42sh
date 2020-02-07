/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniq_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:39:00 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 14:17:08 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char		**find_env(char **shell_env, char *e)
{
	char *name;
	char *tmp;

	if (!(tmp = ft_strchr(e, '=')))
		return (NULL);
	if (!(name = ft_strsub(e, 0, tmp - e)))
		return (NULL);
	while (*shell_env)
	{
		if (!(ft_strncmp(name, *shell_env, ft_strchr(*shell_env, '=')
		- *shell_env)))
		{
			free(name);
			return (shell_env);
		}
		shell_env++;
	}
	free(name);
	return (NULL);
}

static void		merge_env(char **shell_env, char **ue, int se_len)
{
	char **tmp;

	while (*ue)
	{
		if ((tmp = find_env(shell_env, *ue)))
		{
			free(*tmp);
			*tmp = ft_strdup(*ue);
		}
		else
			shell_env[se_len++] = ft_strdup(*ue);
		ue++;
	}
}

static char		**get_uniq_env(char **ue)
{
	char	**shell_env;
	int		se_len;
	int		ue_len;

	shell_env = ft_dardup(g_environ.vars);
	if (!ue)
		return (shell_env);
	se_len = ft_darlen(shell_env);
	ue_len = ft_darlen(ue);
	shell_env = ft_realloc(shell_env, sizeof(char *) * (se_len + 1),
	sizeof(char *) * (ue_len + se_len + 1));
	merge_env(shell_env, ue, se_len);
	return (shell_env);
}

void			set_uniq_env(t_process *p)
{
	char **tmp;

	tmp = p->environment;
	p->environment = get_uniq_env(p->environment);
	ft_free_dar(tmp);
}
