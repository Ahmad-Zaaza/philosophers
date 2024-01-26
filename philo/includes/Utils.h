/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:25 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/01/26 22:41:05 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "./App.h"

int		ft_atoi(char *str, int *err);
int		ft_isdigit(int c);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *str, int fd);
void	free_philosophers(t_app *app);
void	print_app(t_app *app);

#endif