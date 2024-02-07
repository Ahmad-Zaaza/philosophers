/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:17:59 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/08 00:34:39 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/App.h"

/**
1. Picking up the right fork
2. Picking up the left fork
3. Set state to eating
4. Update last eaten timestamp
5. sleep for eating
6. drop right fork
7. drop left fork
*/

void	drop_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

int	pickup_fork(t_philosopher *philosopher, pthread_mutex_t *fork)
{
	if (did_philosopher_die(philosopher)
		|| get_philosopher_state(philosopher) == DEAD)
		return (0);
	pthread_mutex_lock(fork);
	print_philosopher_state(philosopher, PICKED_UP_FORK_MSG);
	return (1);
}

int	philosopher_eat(t_philosopher *philosopher)
{
	if (!pickup_fork(philosopher, philosopher->right_fork))
		return (0);
	if (!pickup_fork(philosopher, philosopher->left_fork))
	{
		drop_fork(philosopher->right_fork);
		return (0);
	}
	set_philosopher_state(philosopher, EATING);
	print_philosopher_state(philosopher, EATING_MSG);
	update_philosopher_last_eaten_time(philosopher, get_time());
	philosopher_sleep(philosopher->data.time_to_eat);
	drop_fork(philosopher->right_fork);
	drop_fork(philosopher->left_fork);
	increment_philosopher_eat_count(philosopher);
	return (1);
}
