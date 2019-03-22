/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/15 16:58:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*check_name(char *name)
{
	char	*file;
	char	*file_name;

	if (!(file = ft_strrchr(name, '/')))
		file_name = ft_strdup(name);
	else
		file_name = ft_strdup(file + 1);
	return (file_name);
}

void	check_err(char *name, char *path)
{
	if (errno == EACCES)
	{
		ft_putstr(path);
		ft_putstr(":\nft_ls: ");
		perror(name);
	}
	else
	{
		ft_putstr("ft_ls: ");
		perror(path);
	}
}

void	data_init(struct dirent *file, t_dir *list, t_dir **d, t_dir **head)
{
	(*d)->mode = DTTOIF(file->d_type);
	(*d)->name = ft_strdup(file->d_name);
	(*d)->path = check_path(list->path, file->d_name);
	(*d)->len = file->d_namlen;
	(*d)->level = (list->level) + 1;
	if (is_flags(list->flags, 't') || is_flags(list->flags, 'u')
		|| is_flags(list->flags, 'S') || is_flags(list->flags, 'g')
		|| is_flags(list->flags, 'l'))
		if (!(get_data(d)))
			delete_from_list(d, head);
}

char	get_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('?');
}

void	cheak_usr(mode_t mode, char *str)
{
	if ((S_IRWXU & mode) != S_IRWXU)
	{
		if ((S_IRUSR & mode) != S_IRUSR)
			str[0] = '-';
		if ((S_IWUSR & mode) != S_IWUSR)
			str[1] = '-';
		if ((S_IXUSR & mode) != S_IXUSR)
			str[2] = '-';
	}
}
