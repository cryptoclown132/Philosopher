/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:38:16 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/12 13:38:30 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meal_death(t_rule *rules)
{
	int	i;

	while (!(rules->all_ate))
	{
		i = -1;
		while (++i < rules->philo_amount)
		{
			pthread_mutex_lock(&rules->death_action);
			if ((get_time() - rules->philo[i].lastmeal_time) > rules->time_die)
			{
				rules->dead = 1;
				print_habit(*rules, rules->philo[i].id, 4);
			}
			pthread_mutex_unlock(&rules->death_action);
			if (rules->dead == 1)
				return ;
		}
		i = 0;
		while (i < rules->philo_amount
			&& rules->philo[i].eat_x >= rules->meal_amount
			&& rules->meal_amount != -1)
			i++;
		if (i == rules->philo_amount)
			rules->all_ate = 1;
	}
}
