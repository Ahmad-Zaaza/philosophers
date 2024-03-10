/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:55:34 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/19 23:06:12 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo_Bonus.h"

static bool	setup_app(t_app *app)
{
	app->stopped_simulation = 0;
	app->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (app->print_sem == SEM_FAILED)
		return (false);
	app->print_sem = sem_open("/forks", O_CREAT, 0644, 1);
	if (app->print_sem == SEM_FAILED)
		return (false);
	pthread_mutex_init(&app->stopped_simulation_mutex, NULL);
	return (setup_semaphores(app));
}

static void	start_routine(t_app *app, unsigned short index)
{
	char	*sem_name;

	app->philosopher = philosopher_value(app, index);
	sem_name = get_philo_sem_name(index);
	if (!sem_name)
		exit(1);
	sem_unlink(sem_name);
	app->philosopher.philo_sem = sem_open(sem_name, O_CREAT, 0644, 1);
	ft_free_ptr(sem_name);
	if (app->philosopher.philo_sem == SEM_FAILED)
		exit(1);
	if (pthread_create(&app->monitor_pth, NULL, &monitor_routine, app) != 0)
		exit(2);
	if (pthread_join(app->monitor_pth, NULL) != 0)
	{
		cleanup_app(app);
		exit(1);
	}
}

static int	start_child_processes(t_app *app)
{
	unsigned short	i;
	u_int64_t		start_time;
	pid_t			pid;

	i = -1;
	start_time = get_time();
	while (++i < app->number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
		{
			app->philosopher.data.start_time = start_time;
			start_routine(app, i);
		}
	}
	pid = waitpid(0, NULL, 0);
	while (pid != -1 || errno != ECHILD)
	{
		pid = waitpid(-1, NULL, 0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_app app;

	if (!parse_arguments(argc, argv, &app))
		return (1);
	if (!setup_app(&app))
		return (1);
	if (!start_child_processes(&app))
		return (1);
	cleanup_app(&app);
	print_app(&app);

	return (0);
}