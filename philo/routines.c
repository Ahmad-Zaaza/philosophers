/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:41:21 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/03/10 12:04:31 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->id % 2 == 0)
		philosopher_sleep(philosopher->data.time_to_eat - 10);
	while (get_philosopher_state(philosopher) != DEAD
		&& get_stopped_simulation(philosopher) != 1)
	{
		if (!philosopher_eat(philosopher))
			break ;
		if (get_philosopher_eat_count(philosopher) == philosopher->data.number_of_times_each_philosopher_must_eat)
		{
			set_philosopher_state(philosopher, FULL);
			break ;
		}
		if (get_philosopher_state(philosopher) == DEAD)
			break ;
		philosopher_sleep_after_eating(philosopher);
		if (get_philosopher_state(philosopher) == DEAD)
			break ;
		print_philosopher_state(philosopher, THINKING_MSG);
		set_philosopher_state(philosopher, THINKING);
	}
	return (NULL);
}

static void	kill_all_threads(t_app *app)
{
	int				i;
	t_philosopher	*philosophers;

	i = -1;
	philosophers = app->philosophers;
	while (++i < app->number_of_philosophers)
	{
		set_philosopher_state(&philosophers[i], DEAD);
	}
}

void	*monitor_routine(void *arg)
{
	t_app			*app;
	int				i;
	t_philosopher	*philosophers;

	app = (t_app *)arg;
	philosophers = app->philosophers;
	i = -1;
	while (++i < app->number_of_philosophers)
	{
		if (get_philosopher_state(&philosophers[i]) == FULL)
			continue ;
		if (did_philosopher_die(&philosophers[i]))
		{
			print_philosopher_state(&philosophers[i], DEAD_MSG);
			update_stopped_simulation(&philosophers[i]);
			kill_all_threads(app);
			break ;
		}
		if (i + 1 == app->number_of_philosophers)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}
