/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:55:47 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 16:55:28 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

// Improved version of sleep function
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

void	philosopher_sleep(u_int64_t time_in_ms)
{
	ft_usleep(time_in_ms);
}

void	philosopher_sleep_after_eating(t_philosopher *philosopher)
{
	if (philo_died_or_stopped_sim(philosopher)
		|| get_philosopher_state(philosopher) == SLEEPING)
		return ;
	print_philosopher_state(philosopher, SLEEPING_MSG);
	set_philosopher_state(philosopher, SLEEPING);
	philosopher_sleep(philosopher->args.time_to_sleep);
}
