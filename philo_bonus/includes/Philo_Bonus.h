/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_Bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:27 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/19 23:04:18 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <pthread.h>
# include <semaphore.h>
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
	IDLE = 4,
	FULL = 5,
}						t_philosopher_state;

typedef struct s_philosopher_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	u_int64_t			start_time;
	int					time_to_sleep;
	sem_t				*print_sem;
	sem_t				*forks_sem;
	int					*stopped_simulation;
	int					number_of_times_each_philosopher_must_eat;
}						t_philosopher_data;

typedef struct s_philosopher
{
	int					id;
	pthread_t			pth;
	int					eat_count;
	u_int64_t			last_eaten_at;
	t_philosopher_data	data;
	t_philosopher_state	state;
	sem_t				*philo_sem;

}						t_philosopher;

typedef struct s_app
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					stopped_simulation;
	sem_t				*print_sem;
	sem_t				*forks_sem;
	pthread_mutex_t		stopped_simulation_mutex;
	pthread_t			monitor_pth;
	int					number_of_times_each_philosopher_must_eat;
	t_philosopher		philosopher;
}						t_app;

int						ft_usleep(size_t milliseconds);

bool					parse_arguments(int argc, char **argv, t_app *app);

/* UTILS */

int						ft_atoi(char *str, int *err);
int						ft_isdigit(int c);
int						ft_isdigit(int c);
void					ft_putstr_fd(char *str, int fd);
void					ft_free_ptr(void *ptr);
void					print_app(t_app *app);
void					ft_print(pthread_mutex_t *print_mutex, char *msg);
size_t					ft_strlen(const char *s);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_itoa(int n);
/* ERRORS */

void					print_usage_msg(void);
void					print_error(char *msg, char *details);

/* ROUTINES */
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);

int						philosopher_eat(t_philosopher *philosopher);
void					philosopher_sleep_after_eating(t_philosopher *philosopher);
void					philosopher_sleep(u_int64_t time_in_ms);
u_int64_t				get_time(void);

bool					setup_semaphores(t_app *app);

void					cleanup_app(t_app *app);

/**

PHILOSOPHER
*/

t_philosopher			philosopher_value(t_app *app, unsigned short index);
char					*get_philo_sem_name(unsigned int id);
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