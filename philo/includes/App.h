/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:35:56 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/01/26 22:47:59 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int						index;
	pthread_t				pth;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_times_each_philosopher_must_eat;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
}							t_philosopher;

typedef struct s_app
{
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_times_each_philosopher_must_eat;
	t_philosopher			*philosophers;
}							t_app;

t_philosopher				*create_philosopher(int index, t_app *app);
void						lst_addback(t_app *app, t_philosopher *philosopher);

#endif