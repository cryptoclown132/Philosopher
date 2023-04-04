/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:10:14 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/16 14:02:29 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_rule *rules, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < rules->philo_amount)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
		{
			ft_error("Failed to join the thread!");
			return (0);
		}
	}
	return (1);
}

int	destroy_mutexes(t_rule *rules)
{
	int	i;

	i = -1;
	while (++i < rules->philo_amount)
	{
		if (pthread_mutex_destroy(&rules->fork[i]) != 0)
		{
			ft_error("Failed to destroy the mutex!");
			return (0);
		}
	}
	if (pthread_mutex_destroy(&rules->death_action) != 0)
	{
		ft_error("Failed to destroy the mutex!");
		return (0);
	}
	return (1);
}

int	end_routine(t_rule *rules, t_philosopher *philo)
{
	if (join_threads(rules, philo) == 0)
		return (0);
	if (destroy_mutexes(rules) == 0)
		return (0);
	return (1);
}

int	routine(t_rule *rules)
{
	int				i;
	t_philosopher	*p;

	rules->time_start = get_time();
	p = rules->philo;
	i = -1;
	while (++i < rules->philo_amount)
	{
		if (pthread_create(&rules->philo[i].thread_id, NULL, eat, &p[i]) != 0)
		{
			ft_error("Failed to create the thread!");
			return (0);
		}
	}
	check_meal_death(rules);
	i = end_routine(rules, p);
	return (i);
}
