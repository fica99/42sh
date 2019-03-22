/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 15:49:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*print_files(t_dir *head, t_dir *head_files)
{
	if (head_files)
	{
		print(sorting(head_files, head_files->flags));
		if (head)
		{
			head = sorting(head, head->flags);
			head->flags = add_flag(head->flags, 1);
			return (head);
		}
	}
	if (head)
		return (sorting(head, head->flags));
	return (NULL);
}

void	print(t_dir *request)
{
	struct winsize	size;

	if (!request)
		return ;
	if (ioctl(0, TIOCGWINSZ, (char*)&size) < 0)
		exit(-1);
	if (is_flags(request->flags, 'd'))
	{
		(is_flags(request->flags, 'l') || is_flags(request->flags, 'g')) ?
			print_rows(request, size.ws_col, request->flags, 0) :
			print_cols(request, size.ws_col, request->flags, 1);
		exit(0);
	}
	if (get_type(request->mode) != 'd')
	{
		(is_flags(request->flags, 'l') || is_flags(request->flags, 'g'))
		? print_rows(request, size.ws_col, request->flags, 0) :
		print_cols(request, size.ws_col, request->flags, 1);
		free_all_list(request);
		return ;
	}
	print_all_rek(request, size.ws_col, (is_flags(request->flags, 'l') ||
		is_flags(request->flags, 'g')) ? print_rows :
		print_cols, request->flags);
}

void	print_all_rek(t_dir *request, ushort size,
		void (f)(t_dir *, ushort, ushort, uint8_t), ushort flags)
{
	t_dir	*file;

	file = request;
	while (request)
	{
		if ((get_type(request->mode) == 'd' && (ft_strcmp(request->name, "."))
		&& (ft_strcmp(request->name, ".."))) || ((request->level) == 1))
			request->f_names = reading(request);
		if (request->f_names)
		{
			print_path(request, flags);
			flags = add_flag(flags, 1);
			request->f_names = sorting(request->f_names, flags);
			f(request->f_names, size, flags, 1);
			if ((is_flags(flags, 'R') && (ft_strcmp(request->name, "."))
			&& (ft_strcmp(request->name, ".."))) || ((is_flags(flags, 'R')
			&& (request->level) == 1)))
				print_all_rek(request->f_names, size, f, flags);
			else
				free_all_list(request->f_names);
		}
		request = request->next;
	}
	free_all_list(file);
}

void	print_path(t_dir *request, ushort flags)
{
	if (request->next || is_flags(flags, 1))
	{
		if (is_flags(flags, 1))
			ft_putchar('\n');
		ft_putstr(request->path);
		ft_putstr(":\n");
	}
}
