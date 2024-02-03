/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:33:10 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/03 11:57:40 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/App.h"

t_philosopher_state	get_philosopher_state(t_philosopher *philosopher)
{
	t_philosopher_state	state;

	pthread_mutex_lock(&philosopher->state_mutex);
	state = philosopher->state;
	pthread_mutex_unlock(&philosopher->state_mutex);
	return (state);
}

int	get_philosopher_eat_count(t_philosopher *philosopher)
{
	int	eat_count;

	pthread_mutex_lock(&philosopher->eat_count_mutex);
	eat_count = philosopher->eat_count;
	pthread_mutex_unlock(&philosopher->eat_count_mutex);
	return (eat_count);
}
