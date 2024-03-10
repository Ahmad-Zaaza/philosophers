/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:33:10 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/19 22:20:15 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo_Bonus.h"

t_philosopher_state	get_philosopher_state(t_philosopher *philosopher)
{
	t_philosopher_state	state;

	sem_wait(philosopher->philo_sem);
	state = philosopher->state;
	sem_post(philosopher->philo_sem);
	return (state);
}

int	get_philosopher_eat_count(t_philosopher *philosopher)
{
	int	eat_count;

	sem_wait(philosopher->philo_sem);
	eat_count = philosopher->eat_count;
	sem_post(philosopher->philo_sem);
	return (eat_count);
}

int	get_stopped_simulation(t_philosopher *philosopher)
{
	int	stopped_simulation;

	sem_wait(philosopher->philo_sem);
	stopped_simulation = *philosopher->data.stopped_simulation;
	sem_post(philosopher->philo_sem);
	return (stopped_simulation);
}
u_int64_t	get_philosopher_last_eaten(t_philosopher *philosopher)
{
	u_int64_t	last_eaten_at;

	sem_wait(philosopher->philo_sem);
	last_eaten_at = philosopher->last_eaten_at;
	sem_post(philosopher->philo_sem);
	return (last_eaten_at);
}

int	did_philosopher_die(t_philosopher *philosopher)
{
	int	died;

	died = (int)(get_time()
			- get_philosopher_last_eaten(philosopher)) > philosopher->data.time_to_die
		&& get_philosopher_state(philosopher) != EATING;
	if (died)
		set_philosopher_state(philosopher, DEAD);
	return (died);
}

char	*get_philo_sem_name(unsigned int id)
{
	return (ft_strjoin("/philo_", ft_itoa(id)));
}