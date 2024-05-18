/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:12:38 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 16:35:14 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

static void	free_forks(t_fork **forks)
{
	int	i;

	i = -1;
	while (forks[++i])
		ft_free_ptr(forks[i]);
	ft_free_ptr(forks);
}

bool	init_philosophers(t_app *app)
{
	int	i;

	app->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* app->args.number_of_philosophers);
	if (!app->philosophers)
		return (false);
	memset(app->philosophers, 0, sizeof(t_philosopher)
		* (app->args.number_of_philosophers));
	i = 0;
	while (i < app->args.number_of_philosophers)
	{
		app->philosophers[i] = philosopher_value(app, i);
		app->philosophers[i].left_fork = app->forks[i];
		app->philosophers[i].right_fork = app->forks[(i + 1)
			* (!(i == app->args.number_of_philosophers - 1))];
		i++;
	}
	return (true);
}

bool	init_forks(t_app *app)
{
	int	i;

	app->forks = (t_fork **)malloc(sizeof(t_fork *)
			* (app->args.number_of_philosophers + 1));
	if (!app->forks)
		return (false);
	memset(app->forks, 0, sizeof(t_fork *) * (app->args.number_of_philosophers
			+ 1));
	i = -1;
	while (++i < app->args.number_of_philosophers)
	{
		app->forks[i] = malloc(sizeof(t_fork));
		if (!app->forks[i])
			return (free_forks(app->forks), false);
		app->forks[i]->is_being_used = 0;
		app->forks[i]->last_used_by = -1;
		pthread_mutex_init(&(app->forks[i]->mutex), NULL);
		pthread_mutex_init(&(app->forks[i]->used_mutex), NULL);
	}
	app->forks[i] = NULL;
	return (true);
}

void	cleanup_app(t_app *app)
{
	int	i;

	i = -1;
	while (++i < app->args.number_of_philosophers)
	{
		pthread_mutex_destroy(&app->philosophers[i].state_mutex);
	}
	pthread_mutex_destroy(&app->print_mutex);
	pthread_mutex_destroy(&app->full_philo_count_mutex);
	pthread_mutex_destroy(&app->stopped_simulation_mutex);
	ft_free_ptr(app->philosophers);
	free_forks(app->forks);
}
