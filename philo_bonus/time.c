/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 10:03:19 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/15 23:20:45 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo_Bonus.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		print_error("Error: failed to call gettimeofday", "");
		return (0);
	}
	return ((tv.tv_usec / 1000) + (tv.tv_sec * (u_int64_t)1000));
}
