/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:38:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/20 22:50:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void		rl_autocom_word_split(char *word, char **file)
{
	int		i;

	if (!word || !*word)
		return ;
	i = ft_strlen(word);
	while (i >= 0 && word[i] != '/')
		--i;
	if (i < 0)
		++i;
	if (word[i] == '/')
		word[i++] = '\0';
	if (!(*file = ft_strdup(word + i)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (i == 0)
		ft_strclr(word);
}

static void		rl_autocom_check_files(char **files, char *file)
{
	short	len;
	short	i;
	short	j;

	i = -1;
	len = ft_strlen(file);
	while (files[++i])
	{
		if (ft_strncmp(files[i], file, len))
		{
			j = i;
			ft_strdel(&files[j]);
			while (files[j + 1])
			{
				files[j] = files[j + 1];
				++j;
			}
			files[j] = NULL;
			--i;
		}
	}
}

static char		**rl_autocom_path(char *word)
{
	char	*file;
	char	**content;
	char	*pwd;
	char	*full_path;

	file = NULL;
	content = NULL;
	rl_autocom_word_split(word, &file);
	if (!(pwd = get_env("PWD", ENV)))
		rl_err("42sh", "pwd error", NOERROR);
	if (!(full_path = ft_strnew(ft_strlen(pwd) + ft_strlen(word) + 1)))
		rl_err("42sh", "malloc() error", ENOMEM);
	full_path = ft_strcat(full_path, pwd);
	if (*word)
		full_path = ft_strcat(ft_strcat(full_path, "/"), word);
	if (!access(full_path, 4) && ft_file_type(full_path) == 'd')
	{
		if (!(content = ft_dir_content(full_path, 0)))
			rl_err("42sh", "malloc() error", ENOMEM);
		rl_autocom_check_files(content, file);
	}
	ft_strdel(&full_path);
	ft_strcpy(word, file);
	ft_strdel(&file);
	return (content);
}

void			rl_k_tab(t_readline *rl)
{
	t_rl_autocom_parse	autocom;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_autocom_parse(&autocom, rl);
	if (autocom.is_env == TRUE)
		autocom.res = get_env_names_dar(autocom.to_find, ALL_ENV);
	else if (autocom.is_path == TRUE)
		autocom.res = rl_autocom_path(autocom.to_find);
	rl_autocom_print(&autocom, rl);
	ft_strdel(&autocom.to_find);
	ft_free_dar(autocom.res);
}
