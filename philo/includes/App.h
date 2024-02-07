/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:35:56 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/05 21:08:48 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PICKED_UP_FORK_MSG "has picked up a fork"
# define EATING_MSG "is eating"
# define THINKING_MSG "is thinking"
# define SLEEPING_MSG "is sleeping"
# define DEAD_MSG "is dead"

typedef enum philosopher_state
{
	SLEEPING = 0,
	EATING = 1,
	THINKING = 2,
	DEAD = 3,
}						t_philosopher_state;

typedef struct s_philosopher_data
{
	int					time_to_die;
	int					time_to_eat;
	u_int64_t			start_time;
	int					time_to_sleep;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*stopped_simulation_mutex;
	int					*stopped_simulation;
	int					number_of_times_each_philosopher_must_eat;
}						t_philosopher_data;

typedef struct s_philosopher
{
	int					id;
	pthread_t			pth;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		state_mutex;
	pthread_mutex_t		eat_count_mutex;
	pthread_mutex_t		last_eaten_mutex;
	int					eat_count;
	u_int64_t			last_eaten_at;
	t_philosopher_data	data;
	t_philosopher_state	state;

}						t_philosopher;

typedef struct s_app
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					stopped_simulation;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stopped_simulation_mutex;
	pthread_mutex_t		*forks;
	pthread_t			monitor_pth;
	int					number_of_times_each_philosopher_must_eat;
	t_philosopher		*philosophers;
}						t_app;

int						ft_usleep(size_t milliseconds);

/* ROUTINES */
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);

int						philosopher_eat(t_philosopher *philosopher);
void					philosopher_sleep_after_eating(t_philosopher *philosopher);
void					philosopher_sleep(u_int64_t time_in_ms);
u_int64_t				get_time(void);

void					init_app(t_app *app);
void					init_philosophers(t_app *app);
void					init_forks(t_app *app);

bool					create_philosophers(t_app *app);
bool					create_forks(t_app *app);

void					cleanup_app(t_app *app);

/**

PHILOSOPHER
*/

t_philosopher			philosopher_value(t_app *app, unsigned short index);
void					set_philosopher_state(t_philosopher *philosopher,
							t_philosopher_state state);
void					print_philosopher_state(t_philosopher *philosopher,
							char *message);
void					increment_philosopher_eat_count(t_philosopher *philosopher);

void					update_philosopher_last_eaten_time(t_philosopher *philosopher,
							u_int64_t time);

void					update_stopped_simulation(t_philosopher *philosopher);
int						get_stopped_simulation(t_philosopher *philosopher);
t_philosopher_state		get_philosopher_state(t_philosopher *philosopher);
int						get_philosopher_eat_count(t_philosopher *philosopher);
u_int64_t				get_philosopher_last_eaten(t_philosopher *philosopher);
int						did_philosopher_die(t_philosopher *philosopher);

#endif