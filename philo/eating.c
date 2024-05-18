/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:17:59 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 16:53:47 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo.h"

/**
1. Picking up the right fork
2. Picking up the left fork
3. Set state to eating
4. Update last eaten timestamp
5. sleep for eating
6. drop right fork
7. drop left fork
*/

static void	update_forks(t_philosopher *philo, bool is_being_used)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->used_mutex);
		pthread_mutex_lock(&philo->left_fork->used_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->used_mutex);
		pthread_mutex_lock(&philo->right_fork->used_mutex);
	}
	philo->right_fork->is_being_used = is_being_used;
	philo->left_fork->is_being_used = is_being_used;
	philo->right_fork->last_used_by = philo->id;
	philo->left_fork->last_used_by = philo->id;
	pthread_mutex_unlock(&philo->right_fork->used_mutex);
	pthread_mutex_unlock(&philo->left_fork->used_mutex);
}

static void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	update_forks(philo, false);
}

static void	pickup_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
	}
	update_forks(philo, true);
}

static bool	is_both_forks_free(t_philosopher *philo)
{
	int	both_free;

	both_free = true;
	if (philo->args.number_of_philosophers == 1)
		return (false);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->used_mutex);
		pthread_mutex_lock(&philo->left_fork->used_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->used_mutex);
		pthread_mutex_lock(&philo->right_fork->used_mutex);
	}
	if (philo->left_fork->is_being_used || philo->right_fork->is_being_used
		|| philo->left_fork->last_used_by == philo->id
		|| philo->right_fork->last_used_by == philo->id)
		both_free = false;
	pthread_mutex_unlock(&philo->left_fork->used_mutex);
	pthread_mutex_unlock(&philo->right_fork->used_mutex);
	return (both_free);
}

int	philosopher_eat(t_philosopher *philosopher)
{
	if (philo_died_or_stopped_sim(philosopher)
		|| !is_both_forks_free(philosopher))
		return (false);
	pickup_forks(philosopher);
	if (philo_died_or_stopped_sim(philosopher))
		return (drop_forks(philosopher), false);
	print_philosopher_state(philosopher, PICKED_UP_FORK_MSG);
	print_philosopher_state(philosopher, PICKED_UP_FORK_MSG);
	set_philosopher_state(philosopher, EATING);
	print_philosopher_state(philosopher, EATING_MSG);
	update_philosopher_last_eaten_time(philosopher, get_time());
	philosopher_sleep(philosopher->args.time_to_eat);
	drop_forks(philosopher);
	increment_philosopher_eat_count(philosopher);
	return (true);
}
// printf("Philo no: %d, is eating\n", philosopher->id);
