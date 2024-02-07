/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:41:21 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/08 00:33:46 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/App.h"
#include "includes/Utils.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->id % 2 == 0)
		philosopher_sleep(philosopher->data.time_to_eat - 10);
	while (get_philosopher_state(philosopher) != DEAD)
	{
		if (!philosopher_eat(philosopher))
			break ;
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
		if (did_philosopher_die(&philosophers[i])
			|| get_stopped_simulation(&philosophers[i]))
		{
			kill_all_threads(app);
			print_philosopher_state(&philosophers[i], DEAD_MSG);
			break ;
		}
		i = -1;
		ft_usleep(1);
	}
	return (NULL);
}
