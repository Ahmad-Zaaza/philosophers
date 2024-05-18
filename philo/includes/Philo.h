/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:27 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/05/18 17:00:43 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PICKED_UP_FORK_MSG "has taken a fork"
# define EATING_MSG "is eating"
# define THINKING_MSG "is thinking"
# define SLEEPING_MSG "is sleeping"
# define DEAD_MSG "died"

typedef enum philosopher_state
{
	SLEEPING = 0,
	EATING = 1,
	THINKING = 2,
	DEAD = 3,
}						t_philosopher_state;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	pthread_mutex_t		used_mutex;
	int					is_being_used;
	int					last_used_by;
}						t_fork;

typedef struct s_philosopher_data
{
	u_int64_t			start_time;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*stopped_simulation_mutex;
	int					*stopped_simulation;
	pthread_mutex_t		*full_philo_count_mutex;
	int					*full_philo_count;
}						t_philosopher_data;
typedef struct s_app_args
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
}						t_app_args;

typedef struct s_philosopher
{
	int					id;
	pthread_t			pth;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		state_mutex;
	int					eat_count;
	u_int64_t			last_eaten_at;
	t_philosopher_data	data;
	t_app_args			args;
	t_philosopher_state	state;

}						t_philosopher;

typedef struct s_app
{
	t_app_args			args;
	int					full_philo_count;
	int					stopped_simulation;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		full_philo_count_mutex;
	pthread_mutex_t		stopped_simulation_mutex;
	t_fork				**forks;
	// pthread_t			monitor_pth;
	t_philosopher		*philosophers;
}						t_app;

int						ft_usleep(size_t milliseconds);

bool					parse_arguments(int argc, char **argv,
							t_app_args *args);

/* UTILS */

int						ft_atoi(char *str, int *err);
int						ft_isdigit(int c);
int						ft_isdigit(int c);
void					ft_putstr_fd(char *str, int fd);
void					ft_free_ptr(void *ptr);
void					print_app(t_app *app);
void					ft_print(pthread_mutex_t *print_mutex, char *msg);
/* ERRORS */

void					print_usage_msg(void);
void					print_error(char *msg, char *details);

/* ROUTINES */
void					*philosopher_routine(void *arg);
// void					*monitor_routine(void *arg);

int						philosopher_eat(t_philosopher *philosopher);
void					philosopher_sleep_after_eating(t_philosopher *philosopher);
void					philosopher_sleep(u_int64_t time_in_ms);
u_int64_t				get_time(void);

bool					init_philosophers(t_app *app);
bool					init_forks(t_app *app);

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

int						get_stopped_simulation(t_philosopher *philosopher);
t_philosopher_state		get_philosopher_state(t_philosopher *philosopher);
int						get_full_philo_count(t_philosopher *philosopher);
int						get_philosopher_eat_count(t_philosopher *philosopher);
int						philo_died_or_stopped_sim(t_philosopher *philo);
#endif