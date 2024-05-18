/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:41:21 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 16:55:31 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

void	philosopher_think(t_philosopher *philo)
{
	if (philo_died_or_stopped_sim(philo) || philo->state == THINKING)
		return ;
	print_philosopher_state(philo, THINKING_MSG);
	set_philosopher_state(philo, THINKING);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (true)
	{
		if (philo_died_or_stopped_sim(philosopher))
			return (NULL);
		if (philosopher_eat(philosopher))
			philosopher_sleep_after_eating(philosopher);
		philosopher_think(philosopher);
	}
	return (NULL);
}
