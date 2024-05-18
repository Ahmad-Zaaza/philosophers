/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:55:34 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 14:46:28 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo.h"

static void	wait_for_threads(t_app *app)
{
	int				i;
	t_philosopher	*philos;

	i = 0;
	philos = app->philosophers;
	while (i < app->args.number_of_philosophers)
	{
		if (pthread_join(philos[i].pth, NULL) != 0)
		{
			cleanup_app(app);
			exit(1);
		}
		i++;
	}
	// if (pthread_join(app->monitor_pth, NULL) != 0)
	// {
	// 	cleanup_app(app);
	// 	exit(1);
	// }
}

static int	start_threads(t_app *app)
{
	int			i;
	u_int64_t	start_time;

	i = -1;
	start_time = get_time();
	while (++i < app->args.number_of_philosophers)
	{
		app->philosophers[i].data.start_time = start_time;
		app->philosophers[i].last_eaten_at = start_time;
		if (pthread_create(&app->philosophers[i].pth, NULL,
				&philosopher_routine, &app->philosophers[i]) != 0)
			return (cleanup_app(app), false);
	}
	return (1);
}

static bool	setup_app(t_app *app)
{
	app->stopped_simulation = 0;
	app->full_philo_count = 0;
	app->philosophers = NULL;
	app->forks = NULL;
	pthread_mutex_init(&app->print_mutex, NULL);
	pthread_mutex_init(&app->stopped_simulation_mutex, NULL);
	pthread_mutex_init(&app->full_philo_count_mutex, NULL);
	if (!init_forks(app))
		return (false);
	if (!init_philosophers(app))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_app app;
	t_app_args args;

	if (!parse_arguments(argc, argv, &args))
		return (1);
	app.args = args;
	if (!setup_app(&app))
		return (1);
	if (!start_threads(&app))
		return (1);
	wait_for_threads(&app);
	cleanup_app(&app);
	return (0);
}