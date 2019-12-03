/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:01:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/03 20:01:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	fc_print_usage(void)
{
	ft_putstr(FC_USAGE1);
	ft_putstr(" or ");
	ft_putendl(FC_USAGE2);
}

void	fc_check_flags(int flags, char *editor, int argc, char **argv)
{
	char	*first;
	char	*last;

	first = NULL;
	last = NULL;
	if (flags & FC_FLAG_ERROR)
	{
		fc_print_usage();
		return ;
	}
	if (!editor && !(editor = get_env("FCEDIT", ENV))
	&& !(editor = get_env("FCEDIT", ENV)))
		editor = "vi";
	if (optind < argc)
		first = argv[optind++];
	if (optind < argc)
		last = argv[optind];
//	fc_write2file(first, last, flags);
}

void	fc(int argc, char **argv)
{
	int 	opt;
	int		flags;
	char	*editor;

	editor = NULL;
	flags = 0;
	while((opt = getopt(argc, argv, "e:nlrs")) != -1)
	{
		if (opt == 'e')
			editor = optarg;
		else if (opt == 'n')
			flags |= FC_FLAG_N;
		else if (opt == 'l')
			flags |= FC_FLAG_L;
		else if (opt == 'r')
			flags |= FC_FLAG_R;
			else if (opt == 's')
			flags |= FC_FLAG_S;
		else
			flags |= FC_FLAG_ERROR;
	}
	fc_check_flags(flags, editor, argc, argv);
	optind = 1;
}
