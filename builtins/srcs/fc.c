/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:01:57 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/06 17:03:08 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_readline.h"

static void	fc_check_first_last(t_fc *fc)
{
	int		size;

	size = get_hist_size();
	if (!fc->first)
	{
		if (fc->flag_l)
			fc->first = "-16";
		else
			fc->first = "-1";
	}
	if (!fc->last)
		fc->last = "-1";
	if ((fc->first_i = ft_atoi(fc->first)) <= 0)
		fc->first_i += size;
	if ((fc->last_i = ft_atoi(fc->last)) <= 0)
		fc->last_i += size;
	if (fc->first_i > size)
		fc->first_i = size - 1;
	if (fc->last_i > size)
		fc->last_i = size - 1;
}

static void	fc_init_struct(t_fc *fc)
{
	if (!(fc->editor = get_var("FCEDIT", VARS)))
		if (!(fc->editor = get_var("EDITOR", VARS)))
			fc->editor = "vi";
	fc->first = NULL;
	fc->last = NULL;
	fc->flag_l = FALSE;
	fc->flag_r = FALSE;
	fc->first_i = 0;
	fc->last_i = 0;
	fc->flag_n = FALSE;
}

int			fc(int argc, char **argv, char **environ)
{
	t_fc	fc;

	fc_init_struct(&fc);
	if (!fc_parse_args(&fc, argc, argv))
	{
		ft_putendl(FC_USAGE);
		return (EXIT_FAILURE);
	}
	fc_check_first_last(&fc);
	fc_exec(&fc, environ);
	return (EXIT_SUCCESS);
}
