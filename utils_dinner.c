/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:09:47 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 18:06:47 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

static void	correct_writing(t_philo *philo, t_action action, long elapsed_time)
{
	if (action == EAT)
		printf("%-10ld "
			"%-10ld is eating\n",
			elapsed_time, philo->philo_id);
	if (action == SLEEP)
		printf("%-10ld "
			"%-10ld is sleeping\n",
			elapsed_time, philo->philo_id);
	if (action == THINK)
		printf("%-10ld "
			"%-10ld is thinking\n",
			elapsed_time, philo->philo_id);
	if (action == DIE)
		printf("%-10ld "
			"%-10ld died\n",
			elapsed_time, philo->philo_id);
	if (action == LEFT_FORK)
		printf("%-10ld "
			"%-10ld has taken a fork\n",
			elapsed_time, philo->philo_id);
	if (action == RIGHT_FORK)
		printf("%-10ld "
			"%-10ld has taken a fork\n",
			elapsed_time, philo->philo_id);
}

/*static void	writing_fork(t_philo *philo, */
/* t_action action, long elapsed_time) */
/* { */
/* 	if (action == LEFT_FORK) */
/* 		printf(B_GREEN"timestamp: %10ld " */
/* 			"philo_id:%-10ld action: left fork \t"RESET, */
/* 			elapsed_time, philo->philo_id); */
/* 	if (action == RIGHT_FORK) */
/* 		printf(B_GREEN"timestamp: %10ld " */
/* 			"philo_id:%-10ld action: right fork \t"RESET, */
/* 			elapsed_time, philo->philo_id); */
/* } */

/* static void	debug_writing(t_philo *philo, */
/* t_action action, long elapsed_time) */
/* { */
/* 	if (action == EAT) */
/* 		printf(B_GREEN"timestamp: %10ld " */
/* 			"philo_id:%-10ld action: eating \t"RESET, */
/* 			elapsed_time, philo->philo_id); */
/* 	if (action == SLEEP) */
/* 		printf(B_GREEN"timestamp: %10ld " */
/* 			"philo_id:%-10ld action: sleeping \t"RESET, */
/* 			elapsed_time, philo->philo_id); */
/* 	if (action == THINK) */
/* 		printf(B_GREEN"timestamp: %10ld " */
/* 			"philo_id:%-10ld action: thinking \t"RESET, */
/* 			elapsed_time, philo->philo_id); */
/* 	if (action == DIE) */
/* 		printf(B_RED"timestamp: %10ld " */
/* 			"philo_id:%-10ld action: died \t"RESET, */
/* 			elapsed_time, philo->philo_id); */
/* 	writing_fork(philo, action, elapsed_time); */
/* 	printf("meal counter: %-10ld last meal time: %-10ld philo id:" */
/* 		"%-10ld left fork id: %-10ld right fork id: %-10ld\n", */
/* 		philo->meal_counter, philo->last_meal_time, */
/* 		philo->philo_id, philo->first_fork->fork_id, */
/* 		philo->second_fork->fork_id); */
/* } */

void	writing(t_philo *philo, t_action action)
{
	long	elapsed_time;

	if (dinner_is_finished(&philo->table->monitor_mtx, philo))
		return ;
	elapsed_time = elapsed_time_f(philo->table);
	safe_mutex(&philo->table->monitor_mtx, LOCK);
	correct_writing(philo, action, elapsed_time);
	safe_mutex(&philo->table->monitor_mtx, UNLOCK);
}

void	desync(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(3e4);
}
