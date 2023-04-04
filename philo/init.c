/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:29:33 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/16 14:01:33 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_rule *rules)
{
	int	i;

	i = -1;
	while (++i < rules->philo_amount)
	{
		if (pthread_mutex_init(&rules->fork[i], NULL) != 0)
		{
			ft_error("Could not initialize mutex!");
			return (0);
		}
	}
	if (pthread_mutex_init(&rules->death_action, NULL) != 0)
	{
		ft_error("Could not initialize mutex!");
		return (0);
	}
	return (1);
}

static void	init_philo(t_rule *rules)
{
	int	i;

	i = -1;
	while (++i < rules->philo_amount)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].eat_x = 0;
		rules->philo[i].lastmeal_time = rules->time_start;
		rules->philo[i].rules = rules;
		if (i == 0)
		{
			rules->philo[i].l_fork = i;
			rules->philo[i].r_fork = (rules->philo_amount - 1);
		}
		else
		{
			rules->philo[i].l_fork = i;
			rules->philo[i].r_fork = i - 1;
		}
	}
}

int	init(t_rule *rules)
{
	if (init_mutexes(rules) == 0)
		return (0);
	init_philo(rules);
	return (1);
}
