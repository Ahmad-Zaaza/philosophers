/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:20:26 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/01/26 22:48:28 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/App.h"

t_philosopher	*create_philosopher(int index, t_app *app)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->index = index;
	philosopher->time_to_eat = app->time_to_eat;
	philosopher->time_to_die = app->time_to_die;
	philosopher->time_to_sleep = app->time_to_sleep;
	philosopher->number_of_times_each_philosopher_must_eat = app->number_of_times_each_philosopher_must_eat;
	philosopher->next = NULL;
	philosopher->prev = NULL;
	return (philosopher);
}

void	lst_addback(t_app *app, t_philosopher *philosopher)
{
	t_philosopher	*philosophers;

	philosophers = app->philosophers;
	if (!app->philosophers)
	{
		philosopher->next = philosopher;
		philosopher->prev = philosopher;
		app->philosophers = philosopher;
	}
	else
	{
		philosopher->next = app->philosophers->next;
		philosopher->prev = app->philosophers;
		app->philosophers->next = philosopher;
	}
}
