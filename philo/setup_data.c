/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:12:38 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/15 23:18:18 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

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
	memset(app->forks, 0, sizeof(pthread_mutex_t)
		* app->number_of_philosophers);
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

	i = -1;
	while (++i < app->number_of_philosophers)
		pthread_mutex_init(&app->forks[i], NULL);
	i = 0;
	app->philosophers[i].right_fork = &app->forks[0];
	app->philosophers[i].left_fork = &app->forks[app->number_of_philosophers
		- 1];
	while (++i < app->number_of_philosophers)
	{
		app->philosophers[i].right_fork = &app->forks[i];
		app->philosophers[i].left_fork = &app->forks[i - 1];
	}
}

void	cleanup_app(t_app *app)
{
	int	i;

	i = -1;
	while (++i < app->number_of_philosophers)
	{
		pthread_mutex_destroy(&app->philosophers[i].eat_count_mutex);
		pthread_mutex_destroy(&app->philosophers[i].state_mutex);
		pthread_mutex_destroy(&app->philosophers[i].last_eaten_mutex);
		pthread_mutex_destroy(&app->forks[i]);
	}
	pthread_mutex_destroy(&app->print_mutex);
	pthread_mutex_destroy(&app->stopped_simulation_mutex);
	ft_free_ptr(app->philosophers);
	ft_free_ptr(app->forks);
}
