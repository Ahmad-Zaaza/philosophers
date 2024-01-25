/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:21:22 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/01/26 00:57:07 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Error.h"
#include "./includes/Validator.h"
#include "includes/Utils.h"

/*

ACCEPTED ARGUMENTS

number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]

*/

static bool	get_no_of_philosophers(t_app *app, char *arg)
{
	int	err;
	int	count;

	err = 0;
	count = ft_atoi(arg, &err);
	if (err)
		return (print_error("Error in number of philosophers"), false);
	if (count < 1)
		return (print_error("Number of philosophers can atleast be 1"), false);
	app->number_of_philosophers = count;
	return (true);
}
static bool	get_time_to_die(t_app *app, char *arg)
{
	int	err;
	int	count;

	err = 0;
	count = ft_atoi(arg, &err);
	if (err)
		return (print_error("Error in time_to_die"), false);
	if (count < 0)
		return (print_error("time_to_die can only be positive"), false);
	app->time_to_die = count;
	return (true);
}

static bool	get_time_to_eat(t_app *app, char *arg)
{
	int	err;
	int	count;

	err = 0;
	count = ft_atoi(arg, &err);
	if (err)
		return (print_error("Error in time_to_eat"), false);
	if (count < 0)
		return (print_error("time_to_eat can only be positive"), false);
	app->time_to_eat = count;
	return (true);
}

static bool	get_time_to_sleep(t_app *app, char *arg)
{
	int	err;
	int	count;

	err = 0;
	count = ft_atoi(arg, &err);
	if (err)
		return (print_error("Error in time_to_sleep"), false);
	if (count < 0)
		return (print_error("time_to_sleep can only be positive"), false);
	app->time_to_sleep = count;
	return (true);
}

bool	parse_arguments(int argc, char **argv, t_app *app)
{
	if (argc < 4 || argc > 5)
		return (print_usage_msg(), false);
	if (!get_no_of_philosophers(app, argv[1]))
		return (print_usage_msg(), false);
	if (!get_time_to_die(app, argv[2]))
		return (print_usage_msg(), false);
	if (!get_time_to_eat(app, argv[3]))
		return (print_usage_msg(), false);
	if (!get_time_to_sleep(app, argv[4]))
		return (print_usage_msg(), false);
	return (true);
}
