/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:27:51 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/01/26 01:04:25 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Error.h"
#include "includes/Utils.h"

void	print_usage_msg(void)
{
	ft_putstr_fd("error: wrong usage: use ./philo \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n",
					STDERR_FILENO);
}

void	print_error(char *msg)
{
	ft_putstr_fd("philo error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
