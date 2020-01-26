/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keywords.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:49:36 by jijerde           #+#    #+#             */
/*   Updated: 2020/01/26 15:10:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char		*type_error(char *arg)
{
	ft_error("42sh", "type", "not found", arg);
	return (NULL);
}

static void	push_keyw(t_keyw *keyw, char *name)
{
	while (keyw->next)
		keyw = keyw->next;
	if (!(keyw->next = ft_memalloc(sizeof(t_keyw))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	keyw = keyw->next;
	if (!(keyw->data = ft_strdup(name)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	keyw->next = NULL;
}

void		fill_keyw(t_keyw *keyw)
{
	if (!(keyw->data = ft_strdup("!")))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	keyw->next = NULL;
	push_keyw(keyw, "{");
	push_keyw(keyw, "}");
	push_keyw(keyw, "case");
	push_keyw(keyw, "do");
	push_keyw(keyw, "done");
	push_keyw(keyw, "elif");
	push_keyw(keyw, "else");
	push_keyw(keyw, "esac");
	push_keyw(keyw, "fi");
	push_keyw(keyw, "for");
	push_keyw(keyw, "if");
	push_keyw(keyw, "in");
	push_keyw(keyw, "then");
	push_keyw(keyw, "until");
	push_keyw(keyw, "while");
}

void		free_keyw(t_keyw *keyw)
{
	t_keyw *tmp;

	free(keyw->data);
	keyw = keyw->next;
	while (keyw)
	{
		tmp = keyw->next;
		free(keyw->data);
		free(keyw);
		keyw = tmp;
	}
}
