/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:55:34 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/03 17:29:06 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/App.h"
#include "includes/Utils.h"
#include "includes/Validator.h"

void	*start_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->id % 2 == 0)
		philosopher_sleep(philosopher->data.time_to_eat - 10);
	while (get_philosopher_state(philosopher) != DEAD)
	{
		philosopher_eat(philosopher);
		if (get_philosopher_eat_count(philosopher) == 3)
			break ;
		philosopher_sleep_after_eating(philosopher);
		print_philosopher_state(philosopher, THINKING_MSG);
		set_philosopher_state(philosopher, THINKING);
	}
	return (NULL);
}

// sets up philosophers and mutexes
static bool	setup_app(t_app *app)
{
	if (!create_philosophers(app))
		return (false);
	if (!create_forks(app))
		return (false);
	init_philosophers(app);
	init_forks(app);
	return (true);
}

static int	start_threads(t_app *app)
{
	int			i;
	u_int64_t	start_time;

	i = 0;
	start_time = get_time();
	while (i < app->number_of_philosophers)
	{
		app->philosophers[i].data.start_time = start_time;
		if (pthread_create(&app->philosophers[i].pth, NULL, &start_routine,
				&app->philosophers[i]) != 0)
			return (cleanup_app(app), false);
		i++;
	}
	return (1);
}

static void	wait_for_threads(t_app *app)
{
	int				i;
	t_philosopher	*philos;

	i = 0;
	philos = app->philosophers;
	while (i < app->number_of_philosophers)
	{
		if (pthread_join(philos[i].pth, NULL) != 0)
		{
			cleanup_app(app);
			exit(1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_app app;

	init_app(&app);
	if (!parse_arguments(argc, argv, &app))
		return (1);
	if (!setup_app(&app))
		return (1);
	if (!start_threads(&app))
		return (1);
	wait_for_threads(&app);
	cleanup_app(&app);
	print_app(&app);

	return (0);
}