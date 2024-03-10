/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:12:38 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/19 23:06:12 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo_Bonus.h"

// bool	create_philosophers(t_app *app)
// {
// 	app->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
// 			* app->number_of_philosophers);
// 	if (!app->philosophers)
// 		return (false);
// 	return (true);
// }

bool	setup_semaphores(t_app *app)
{
	sem_unlink("/print");
	sem_unlink("/forks");
	app->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (app->print_sem == SEM_FAILED)
		return (false);
	app->print_sem = sem_open("/forks", O_CREAT, 0644, 1);
	if (app->print_sem == SEM_FAILED)
		return (false);
	return (true);
}

// void	init_philosophers(t_app *app)
// {
// 	int	i;

// 	i = 0;
// 	while (i < app->number_of_philosophers)
// 	{
// 		app->philosophers[i] = philosopher_value(app, i);
// 		i++;
// 	}
// }
