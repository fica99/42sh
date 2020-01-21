/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_autocom_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:51:02 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/21 15:52:07 by aashara-         ###   ########.fr       */
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

char			**rl_autocom_path(char *word)
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
