/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:06:12 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/16 13:46:33 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	get_right_time(int time, t_rule *rules)
{
	long	i;

	i = get_time();
	while (rules->dead == -1)
	{
		if (get_time() - i >= time)
			break ;
		usleep(50);
	}
}

void	philo_eat(t_rule *rules, t_philosopher *philo)
{	
	pthread_mutex_lock(&rules->fork[philo->l_fork]);
	pthread_mutex_lock(&rules->death_action);
	print_habit(*rules, philo->id, 0);
	pthread_mutex_unlock(&rules->death_action);
	if (rules->philo_amount == 1)
	{
		usleep((rules->time_die + 2) * 1000);
		pthread_mutex_unlock(&rules->fork[philo->l_fork]);
		return ;
	}
	pthread_mutex_lock(&rules->fork[philo->r_fork]);
	pthread_mutex_lock(&rules->death_action);
	print_habit(*rules, philo->id, 0);
	pthread_mutex_unlock(&rules->death_action);
	pthread_mutex_lock(&rules->death_action);
	print_habit(*rules, philo->id, 1);
	philo->lastmeal_time = get_time();
	pthread_mutex_unlock(&rules->death_action);
	get_right_time(rules->time_eat, rules);
	philo->eat_x += 1;
	pthread_mutex_unlock(&rules->fork[philo->l_fork]);
	pthread_mutex_unlock(&rules->fork[philo->r_fork]);
}

void	*eat(void *philosopher)
{
	t_philosopher	*philo;
	t_rule			*rules;

	philo = (t_philosopher *)philosopher;
	rules = philo->rules;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (philo->rules->dead == -1)
	{
		philo_eat(philo->rules, philo);
		if (philo->rules->all_ate)
			break ;
		pthread_mutex_lock(&rules->death_action);
		print_habit(*rules, philo->id, 2);
		pthread_mutex_unlock(&rules->death_action);
		get_right_time(philo->rules->time_sleep, philo->rules);
		pthread_mutex_lock(&rules->death_action);
		print_habit(*rules, philo->id, 3);
		pthread_mutex_unlock(&rules->death_action);
	}
	return (philosopher);
}
