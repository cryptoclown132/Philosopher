/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:26:42 by jkroger           #+#    #+#             */
/*   Updated: 2023/01/16 14:01:56 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h> 
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philosopher
{	
	int				id;
	int				eat_x;
	int				l_fork;
	int				r_fork;
	long			lastmeal_time;
	pthread_t		thread_id;
	struct s_rule	*rules;
}t_philosopher;

typedef struct s_rule
{
	int				all_ate;
	int				philo_amount;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meal_amount;
	pthread_mutex_t	fork[1000];
	pthread_mutex_t	death_action;
	t_philosopher	philo[1000];
	long			time_start;
	int				dead;
}t_rule;

int		mod_atoi(const char *str);
void	check_meal_death(t_rule *rules);
void	ft_error(char *err_msg);
int		init(t_rule *rules);
void	print_habit(t_rule r, int id, int action);
void	*eat(void *philosopher);
int		routine(t_rule *rules);
long	get_time(void);

#endif
