/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:33:10 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/15 23:18:18 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

t_philosopher_state	get_philosopher_state(t_philosopher *philosopher)
{
	t_philosopher_state	state;

	pthread_mutex_lock(&philosopher->state_mutex);
	state = philosopher->state;
	pthread_mutex_unlock(&philosopher->state_mutex);
	return (state);
}

int	get_philosopher_eat_count(t_philosopher *philosopher)
{
	int	eat_count;

	pthread_mutex_lock(&philosopher->eat_count_mutex);
	eat_count = philosopher->eat_count;
	pthread_mutex_unlock(&philosopher->eat_count_mutex);
	return (eat_count);
}

int	get_stopped_simulation(t_philosopher *philosopher)
{
	int	stopped_simulation;

	pthread_mutex_lock(philosopher->data.stopped_simulation_mutex);
	stopped_simulation = *philosopher->data.stopped_simulation;
	pthread_mutex_unlock(philosopher->data.stopped_simulation_mutex);
	return (stopped_simulation);
}
u_int64_t	get_philosopher_last_eaten(t_philosopher *philosopher)
{
	u_int64_t	last_eaten_at;

	pthread_mutex_lock(&philosopher->last_eaten_mutex);
	last_eaten_at = philosopher->last_eaten_at;
	pthread_mutex_unlock(&philosopher->last_eaten_mutex);
	return (last_eaten_at);
}

int	did_philosopher_die(t_philosopher *philosopher)
{
	int	died;

	died = (int)(get_time()
			- get_philosopher_last_eaten(philosopher)) > philosopher->data.time_to_die
		&& get_philosopher_state(philosopher) != EATING;
	if (died)
		set_philosopher_state(philosopher, DEAD);
	return (died);
}
