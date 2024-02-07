/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:55:34 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/08 00:27:18 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/App.h"
#include "includes/Utils.h"
#include "includes/Validator.h"

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

	i = -1;
	start_time = get_time();
	while (++i < app->number_of_philosophers)
	{
		app->philosophers[i].data.start_time = start_time;
		update_philosopher_last_eaten_time(&app->philosophers[i], start_time);
		if (pthread_create(&app->philosophers[i].pth, NULL,
				&philosopher_routine, &app->philosophers[i]) != 0)
			return (cleanup_app(app), false);
	}
	if (pthread_create(&app->monitor_pth, NULL, &monitor_routine, app) != 0)
		return (cleanup_app(app), false);
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
	if (pthread_join(app->monitor_pth, NULL) != 0)
	{
		cleanup_app(app);
		exit(1);
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