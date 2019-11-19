/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_v.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:34:46 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/19 19:55:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_open_editor(t_readline *rl)
{
	char	**argv;
	char	*command_path;
	char	**path;

	if (!(argv = ft_darnew(2)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (!(argv[0] = ft_getenv("VISUAL", rl->env)))
		if (!(argv[0] = ft_getenv("EDITOR", rl->env)))
			argv[0] = "vi";
	if (!(argv[1] = ft_strdup(RL_VIFILE)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (!(argv[0] = ft_strdup(argv[0])))
		rl_err("42sh", "malloc() error", ENOMEM);
	if ((command_path = ft_getenv("PATH", rl->env)))
	{
		if (!(path = ft_strsplit(command_path, ':')))
			rl_err("42sh", "malloc() error", ENOMEM);
		rl_exec_editor(rl, rl_editor_path(argv[0], path), argv);
		ft_free_dar(path);
	}
	ft_free_dar(argv);
}

char	*rl_editor_path(char *editor, char **path)
{
	short	j;
	char	*editor_path;
	char	**content;
	short	i;

	editor_path = NULL;
	i = -1;
	while (path[++i])
	{
		content = ft_dir_content(path[i], 0);
		j = -1;
		while (content[++j])
		{
			if (!ft_strcmp(editor, content[j]))
			{
				ft_strcat(editor_path = ft_strnew(MAX_LINE_SIZE), path[i]);
				ft_strcat(ft_strcat(editor_path, "/"), editor);
				break ;
			}
		}
		ft_free_dar(content);
		if (editor_path)
			break ;
	}
	return (editor_path);
}

void	rl_exec_editor(t_readline *rl, char *command_path, char **argv)
{
	pid_t	p;
	int		status;

	if (!command_path || !(*command_path))
	{
		ft_strdel(&command_path);
		return ;
	}
	rl_set_attr(&rl->canon_mode);
	if ((p = fork()) < 0)
		rl_err("42sh", "fork() error", UNDEFERR);
	if (!p)
		if (execve(command_path, argv, rl->env) < 0)
			rl_err("42sh", "execve() error", UNDEFERR);
	waitpid(p, &status, 0);
	rl_set_non_canon_mode(&rl->non_canon_mode);
	ft_strdel(&command_path);
}
