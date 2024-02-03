/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:50:09 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/03 16:34:57 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/App.h"

t_philosopher	philosopher_value(t_app *app, unsigned short index)
{
	t_philosopher	philosopher;

	philosopher.id = index + 1;
	philosopher.state = THINKING;
	philosopher.eat_count = 0;
	philosopher.left_fork = NULL;
	philosopher.right_fork = NULL;
	philosopher.last_eaten_at = get_time();
	philosopher.data.number_of_times_each_philosopher_must_eat = app->number_of_times_each_philosopher_must_eat;
	philosopher.data.time_to_die = app->time_to_die;
	philosopher.data.time_to_sleep = app->time_to_sleep;
	philosopher.data.time_to_eat = app->time_to_eat;
	philosopher.data.print_mutex = app->print_mutex;
	pthread_mutex_init(&philosopher.state_mutex, NULL);
	pthread_mutex_init(&philosopher.last_eaten_mutex, NULL);
	pthread_mutex_init(&philosopher.eat_count_mutex, NULL);
	return (philosopher);
}

void	set_philosopher_state(t_philosopher *philosopher,
		t_philosopher_state state)
{
	pthread_mutex_lock(&philosopher->state_mutex);
	philosopher->state = state;
	pthread_mutex_unlock(&philosopher->state_mutex);
}
void	print_philosopher_state(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->data.print_mutex);
	printf("[%llu] %d %s\n", get_time() - philosopher->data.start_time,
		philosopher->id, message);
	pthread_mutex_unlock(&philosopher->data.print_mutex);
}
void	increment_philosopher_eat_count(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->eat_count_mutex);
	philosopher->eat_count++;
	pthread_mutex_unlock(&philosopher->eat_count_mutex);
}

void	update_philosopher_last_eaten_time(t_philosopher *philosopher,
		u_int64_t time)
{
	pthread_mutex_lock(&philosopher->last_eaten_mutex);
	philosopher->last_eaten_at = time;
	pthread_mutex_unlock(&philosopher->last_eaten_mutex);
}
