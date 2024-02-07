/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:12:38 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/08 00:29:22 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/App.h"
#include "includes/Utils.h"

void	init_app(t_app *app)
{
	app->number_of_philosophers = -1;
	app->time_to_eat = -1;
	app->time_to_die = -1;
	app->time_to_sleep = -1;
	app->stopped_simulation = 0;
	app->number_of_times_each_philosopher_must_eat = -1;
	app->philosophers = NULL;
	app->forks = NULL;
	pthread_mutex_init(&app->print_mutex, NULL);
	pthread_mutex_init(&app->stopped_simulation_mutex, NULL);
}

bool	create_philosophers(t_app *app)
{
	app->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* app->number_of_philosophers);
	if (!app->philosophers)
		return (false);
	return (true);
}

bool	create_forks(t_app *app)
{
	app->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* app->number_of_philosophers);
	if (!app->forks)
		return (false);
	return (true);
}

void	init_philosophers(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->number_of_philosophers)
	{
		app->philosophers[i] = philosopher_value(app, i);
		i++;
	}
}

void	init_forks(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->number_of_philosophers)
		pthread_mutex_init(&app->forks[i++], NULL);
	i = 0;
	while (i < app->number_of_philosophers)
	{
		app->philosophers[i].left_fork = &app->forks[i];
		app->philosophers[i].right_fork = &app->forks[i + 1
			% app->number_of_philosophers];
		i++;
	}
}

void	cleanup_app(t_app *app)
{
	ft_free_ptr(app->philosophers);
	ft_free_ptr(app->forks);
}