/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:44:46 by filip             #+#    #+#             */
/*   Updated: 2019/05/31 20:45:08 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOUR_H
# define COLOUR_H

# define STANDART(fd) ft_putstr_fd("\033[0m", fd)
# define RED(fd) ft_putstr_fd("\033[0;31m", fd)
# define GREEN(fd) ft_putstr_fd("\033[0;32m", fd)
# define YELLOW(fd) ft_putstr_fd("\033[0;33m", fd)
# define BLUE(fd) ft_putstr_fd("\033[0;34m", fd)
# define PURPLE(fd) ft_putstr_fd("\033[0;35m", fd)
# define CYAN(fd) ft_putstr_fd("\033[0;36m", fd)

#endif
