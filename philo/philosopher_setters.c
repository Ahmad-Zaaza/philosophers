/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:50:09 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 17:00:43 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

t_philosopher	philosopher_value(t_app *app, unsigned short index)
{
	t_philosopher	philosopher;

	philosopher.id = index + 1;
	philosopher.state = THINKING;
	philosopher.eat_count = 0;
	philosopher.left_fork = NULL;
	philosopher.right_fork = NULL;
	philosopher.last_eaten_at = get_time();
	philosopher.data.print_mutex = &app->print_mutex;
	philosopher.data.stopped_simulation_mutex = &app->stopped_simulation_mutex;
	philosopher.data.stopped_simulation = &app->stopped_simulation;
	philosopher.data.full_philo_count = &app->full_philo_count;
	philosopher.data.full_philo_count_mutex = &app->full_philo_count_mutex;
	philosopher.args = app->args;
	pthread_mutex_init(&philosopher.state_mutex, NULL);
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
	pthread_mutex_lock(philosopher->data.print_mutex);
	printf("%llu %d %s\n", get_time() - philosopher->data.start_time,
		philosopher->id, message);
	pthread_mutex_unlock(philosopher->data.print_mutex);
}
void	increment_philosopher_eat_count(t_philosopher *philosopher)
{
	philosopher->eat_count++;
	if (philosopher->eat_count == philosopher->args.number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(philosopher->data.full_philo_count_mutex);
		*(philosopher->data.full_philo_count) += 1;
		pthread_mutex_unlock(philosopher->data.full_philo_count_mutex);
	}
}

void	update_philosopher_last_eaten_time(t_philosopher *philosopher,
		u_int64_t time)
{
	philosopher->last_eaten_at = time;
}
