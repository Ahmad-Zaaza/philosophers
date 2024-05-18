/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:33:10 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 17:00:43 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"
#include <stdio.h>

t_philosopher_state	get_philosopher_state(t_philosopher *philosopher)
{
	t_philosopher_state	state;

	pthread_mutex_lock(&philosopher->state_mutex);
	state = philosopher->state;
	pthread_mutex_unlock(&philosopher->state_mutex);
	return (state);
}

int	get_stopped_simulation(t_philosopher *philosopher)
{
	int	stopped_simulation;

	pthread_mutex_lock(philosopher->data.stopped_simulation_mutex);
	stopped_simulation = *philosopher->data.stopped_simulation;
	pthread_mutex_unlock(philosopher->data.stopped_simulation_mutex);
	return (stopped_simulation);
}

int	get_full_philo_count(t_philosopher *philosopher)
{
	int	full_philo_count;

	pthread_mutex_lock(philosopher->data.full_philo_count_mutex);
	full_philo_count = *philosopher->data.full_philo_count;
	pthread_mutex_unlock(philosopher->data.full_philo_count_mutex);
	return (full_philo_count);
}

int	philo_died_or_stopped_sim(t_philosopher *philo)
{
	int	is_dead;

	is_dead = false;
	pthread_mutex_lock(philo->data.stopped_simulation_mutex);
	if (*philo->data.stopped_simulation)
		is_dead = true;
	else if ((int)(get_time()
			- philo->last_eaten_at) >= philo->args.time_to_die)
	{
		print_philosopher_state(philo, DEAD_MSG);
		set_philosopher_state(philo, DEAD);
		is_dead = true;
	}
	else if (get_full_philo_count(philo) == philo->args.number_of_philosophers)
		is_dead = true;
	*philo->data.stopped_simulation = is_dead;
	pthread_mutex_unlock(philo->data.stopped_simulation_mutex);
	return (is_dead);
}
