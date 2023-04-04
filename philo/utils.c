/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:42:08 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/16 14:00:46 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_convert(const char *str, int i)
{
	long	res;

	res = 0;
	while (str[i])
	{
		if ((str[i] - '0' <= 9 && str[i] - '0' >= 0))
		{
			res = res * 10 + str[i] - '0';
			i++;
		}
		else
			return (-2);
	}
	return (res);
}

int	mod_atoi(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
	i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-2);
		i++;
	}
	return (ft_convert(str, i));
}

long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_habit(t_rule r, int id, int action)
{
	if (r.dead == -1 || action == 4)
	{
		if (action == 0)
			printf("%lims %i has taken a fork\n",
				(get_time() - r.time_start), id);
		else if (action == 1)
			printf("%lims %i is eating\n", (get_time() - r.time_start), id);
		else if (action == 2)
			printf("%lims %i is sleeping\n", (get_time() - r.time_start), id);
		else if (action == 3)
			printf("%lims %i is thinking\n", (get_time() - r.time_start), id);
		else if (action == 4)
			printf("%lims %i died\n", (get_time() - r.time_start), id);
	}
}
