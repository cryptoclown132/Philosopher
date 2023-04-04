/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:28:56 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/12 18:40:12 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_values(int argc, char **argv, t_rule *rules)
{
	rules->philo_amount = mod_atoi(argv[1]);
	rules->time_die = mod_atoi(argv[2]);
	rules->time_eat = mod_atoi(argv[3]);
	rules->time_sleep = mod_atoi(argv[4]);
	rules->meal_amount = -1;
	rules->dead = -1;
	if (argc == 6)
		rules->meal_amount = mod_atoi(argv[5]);
	rules->time_start = get_time();
	if (rules->philo_amount == -2 || rules->time_die == -2
		|| rules->time_eat == -2 || rules->time_sleep == -2
		|| rules->meal_amount == -2 || rules->philo_amount == 0
		|| rules->meal_amount == 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_rule	rules;

	if (argc < 5 || argc > 6)
	{
		ft_error("Wrong number of arguments must be 4 or 5 arguments!");
		return (0);
	}
	if (get_values(argc, argv, &rules) == 1)
	{
		ft_error("Arguments have wrong input!");
		return (1);
	}
	if (!init(&rules))
		return (0);
	if (!routine(&rules))
		return (0);
	return (1);
}
