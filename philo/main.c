/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:55:34 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/01/26 00:59:24 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/App.h"
#include "includes/Utils.h"
#include "includes/Validator.h"

static void	init_app(t_app *app)
{
	app->number_of_philosophers = -1;
	app->time_to_eat = -1;
	app->time_to_die = -1;
	app->time_to_sleep = -1;
	app->number_of_times_each_philosopher_must_eat = -1;
}

int	main(int argc, char **argv)
{
	t_app app;
	init_app(&app);
	if (!parse_arguments(argc, argv, &app))
		return (1);
	print_app(&app);
	return (0);
}