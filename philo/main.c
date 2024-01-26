/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:55:34 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/01/26 22:53:53 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/App.h"
#include "includes/Utils.h"
#include "includes/Validator.h"
#include <pthread.h>
#include <sys/time.h>

static void	init_app(t_app *app)
{
	app->number_of_philosophers = -1;
	app->time_to_eat = -1;
	app->time_to_die = -1;
	app->time_to_sleep = -1;
	app->number_of_times_each_philosopher_must_eat = -1;
}

void	*start_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	printf("%d is sleeping\n", philosopher->index + 1);
	usleep(philosopher->time_to_sleep * 1000);
	return (NULL);
}

static bool	create_philosophers(t_app *app)
{
	int				i;
	t_philosopher	*philosopher;

	i = 0;
	while (i < app->number_of_philosophers)
	{
		philosopher = create_philosopher(i, app);
		if (!philosopher)
		{
			free_philosophers(app);
			exit(2);
		}
		lst_addback(app, philosopher);
		if (pthread_create(&philosopher->pth, NULL, &start_routine,
				philosopher) != 0)
			return (free_philosophers(app), false);
		i++;
	}
	return (true);
}

static void	wait_for_threads(t_app *app)
{
	int				i;
	t_philosopher	*tmp_philo;

	i = 0;
	tmp_philo = app->philosophers;
	while (i < app->number_of_philosophers)
	{
		if (pthread_join(tmp_philo->pth, NULL) != 0)
		{
			free_philosophers(app);
			exit(1);
		}
		tmp_philo = tmp_philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_app app;

	init_app(&app);
	if (!parse_arguments(argc, argv, &app))
		return (1);
	if (!create_philosophers(&app))
		return (1);
	wait_for_threads(&app);
	free_philosophers(&app);
	print_app(&app);

	return (0);
}