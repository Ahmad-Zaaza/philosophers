/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:55:47 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/15 23:20:45 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo_Bonus.h"

// Improved version of sleep function
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	philosopher_sleep(u_int64_t time_in_ms)
{
	ft_usleep(time_in_ms);
}

void	philosopher_sleep_after_eating(t_philosopher *philosopher)
{
	print_philosopher_state(philosopher, SLEEPING_MSG);
	set_philosopher_state(philosopher, SLEEPING);
	philosopher_sleep(philosopher->data.time_to_sleep);
}
