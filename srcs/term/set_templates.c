/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_templates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:36:05 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 18:25:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_temp	*set_templates(void)
{
	t_temp	*temp;
	t_temp	*head;

	head = init_temp_struct(ft_strdup(K_LFT), &key_left);
	temp = head;
	temp->next = init_temp_struct(ft_strdup(K_RGHT), &key_right);
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(K_HOME), &key_home);
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(K_END), &key_end);
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

	head = init_temp_struct(ft_strdup(CTRL_UP), &ctrl_up);
	temp = head;
	temp->next = init_temp_struct(ft_strdup(CTRL_DOWN), ctrl_down);
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(CTRL_RIGHT), &ctrl_right);
	temp = temp->next;
	temp->next = init_temp_struct(ft_strdup(CTRL_LEFT), &ctrl_left);
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
