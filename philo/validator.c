/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:21:22 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 12:31:13 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Philo.h"

/*

ACCEPTED ARGUMENTS

number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]

*/

static bool	get_value_of(char *arg, char *type, int *ptr)
{
	int	err;
	int	count;

	err = false;
	count = ft_atoi(arg, &err);
	if (err)
		return (print_error(type, "Cannot handle argument"), false);
	if (count < 0)
		return (print_error(type, "can only be positive"), false);
	*ptr = count;
	return (true);
}

bool	parse_arguments(int argc, char **argv, t_app_args *args)
{
	if (argc < 5 || argc > 6)
		return (print_usage_msg(), false);
	if (!get_value_of(argv[1], "number_of_philosophers",
			&args->number_of_philosophers))
		return (false);
	if (!get_value_of(argv[2], "time_to_die", &args->time_to_die))
		return (false);
	if (!get_value_of(argv[3], "time_to_eat", &args->time_to_eat))
		return (false);
	if (!get_value_of(argv[4], "time_to_sleep", &args->time_to_sleep))
		return (false);
	if (argc == 6)
		if (!get_value_of(argv[5], "number_of_times_each_philosopher_must_eat",
				&args->number_of_times_each_philosopher_must_eat))
			return (false);
	if (args->number_of_philosophers > 200)
	{
		print_error("number_of_philosophers",
			"number_of_philosophers cannot be more than 200");
		return (false);
	}
	return (true);
}
