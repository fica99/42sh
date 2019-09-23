/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   templates.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:03:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/23 23:10:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_temp	*set_templates(void)
{
	t_temp	*temp;
	t_temp	*head;

	head = init_temp_struct(ft_strdup(K_LFT), );
	temp = head;
	temp->next = init_temp_struct(ft_strdup(K_RGHT), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(K_HOME), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(K_END), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(K_DEL), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(K_UP), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(K_DOWN), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(SHIFT_LFT), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(SHIFT_RGHT), );
	temp = temp->next;
	temp->next = set_esc_templates();
	return (head);
}

t_temp	*set_esc_templates(void)
{
	t_temp	*head;
	t_temp	*temp;
	char	*str;

	head = init_temp_struct(ft_strdup(CTRL_UP), );
	temp = head;
	temp->next = init_temp_struct(ft_strdup(CTRL_DOWN), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(CTRL_RIGHT), );
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(CTRL_LEFT), );
	temp = temp->next;
	str = ft_strnew(1);
	*str = TAB;
	temp->next = init_temp_struct(ft_strdup(str), );
	temp = temp->next;
	temp->next = set_other_templates(str);
	ft_strdel(&str);
	return (head);
}

t_temp	*set_other_templates(char *str)
{
	t_temp	*head;
	t_temp	*temp;

	*str = CTRL_R;
	head = init_temp_struct(ft_strdup(str), );
	temp = head;
	*str = BCSP;
	temp->next = init_temp_struct(ft_strdup(str), );
	temp = temp->next;
	*str = CTRL_H;
	temp->next = init_temp_struct(ft_strdup(str), );
	temp = temp->next;
	*str = CTRL_D;
	temp->next = init_temp_struct(ft_strdup(str), );
	temp = temp->next;
	*str = CTRL_C;
	temp->next = init_temp_struct(ft_strdup(str), );
	temp = temp->next;
	*str = CTRL_X;
	temp->next = init_temp_struct(ft_strdup(str), );
	temp = temp->next;
	*str = CTRL_V;
	temp->next = init_temp_struct(ft_strdup(str), );
	return (head);
}

t_temp	*init_temp_struct(char *template, void (*handler)())
{
	t_temp	*temp;

	if (!(temp = (t_temp*)malloc(sizeof(t_temp))))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	temp->template = template;
	temp->handler = handler;
	temp->next = NULL;
	return (temp);
}
