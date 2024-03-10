/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmadzaaza <ahmadzaaza@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:11:05 by ahmadzaaza        #+#    #+#             */
/*   Updated: 2024/02/19 22:19:10 by ahmadzaaza       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Philo_Bonus.h"

int	ft_atoi(char *str, int *err)
{
	long int	result;
	long int	tmp_result;
	int			sign;
	int			i;

	i = 0;
	result = 0;
	sign = 1;
	while (str && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-')
		sign = -1;
	i += (str[i] == '-' || str[i] == '+');
	if (!str || !ft_isdigit(str[i]))
		return (*err = 1, 0);
	while (str && ft_isdigit(str[i]))
	{
		tmp_result = result;
		result = result * 10 + (str[i++] - 48);
		if (result < tmp_result)
			return (*err = 1, -1);
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
		write(fd, &str[i++], 1);
}
void	print_app(t_app *app)
{
	printf("Philosophers: [%d]\n", app->number_of_philosophers);
	printf("time_to_die: [%d]\n", app->time_to_die);
	printf("time_to_eat: [%d]\n", app->time_to_eat);
	printf("time_to_sleep: [%d]\n", app->time_to_sleep);
}
void	ft_print(pthread_mutex_t *print_mutex, char *msg)
{
	pthread_mutex_lock(print_mutex);
	printf("%s\n", msg);
	pthread_mutex_unlock(print_mutex);
}

void	ft_free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		total;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s2 == NULL)
		return (s1);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(total * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	free(s2);
	return (str);
}
