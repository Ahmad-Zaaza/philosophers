/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:50:09 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/19 22:21:11 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo_Bonus.h"

t_philosopher	philosopher_value(t_app *app, unsigned short index)
{
	t_philosopher	philosopher;

	philosopher.id = index + 1;
	philosopher.state = IDLE;
	philosopher.eat_count = 0;
	philosopher.last_eaten_at = get_time();
	philosopher.data.number_of_times_each_philosopher_must_eat = app->number_of_times_each_philosopher_must_eat;
	philosopher.data.time_to_die = app->time_to_die;
	philosopher.data.time_to_sleep = app->time_to_sleep;
	philosopher.data.time_to_eat = app->time_to_eat;
	philosopher.data.number_of_philosophers = app->number_of_philosophers;
	philosopher.data.stopped_simulation = &app->stopped_simulation;
	return (philosopher);
}

void	set_philosopher_state(t_philosopher *philosopher,
		t_philosopher_state state)
{
	sem_wait(philosopher->philo_sem);
	philosopher->state = state;
	sem_post(philosopher->philo_sem);
}
void	print_philosopher_state(t_philosopher *philosopher, char *message)
{
	sem_wait(philosopher->data.print_sem);
	if (!get_stopped_simulation(philosopher))
	{
		printf("[%llu] %d %s\n", get_time() - philosopher->data.start_time,
			philosopher->id, message);
	}
	sem_post(philosopher->data.print_sem);
}
void	increment_philosopher_eat_count(t_philosopher *philosopher)
{
	sem_wait(philosopher->philo_sem);
	philosopher->eat_count++;
	sem_post(philosopher->philo_sem);
}

void	update_philosopher_last_eaten_time(t_philosopher *philosopher,
		u_int64_t time)
{
	sem_wait(philosopher->philo_sem);
	philosopher->last_eaten_at = time;
	sem_post(philosopher->philo_sem);
}

void	update_stopped_simulation(t_philosopher *philosopher)
{
	sem_wait(philosopher->philo_sem);
	*philosopher->data.stopped_simulation = 1;
	sem_post(philosopher->philo_sem);
}
