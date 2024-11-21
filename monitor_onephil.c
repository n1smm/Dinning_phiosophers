/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_onephil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:49:18 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 17:51:21 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

/* inline static void	dead_philo(t_philo *philo, long elapsed_time) */
/* { */
/* 	philo->table->is_dead = true; */
/* 	philo->table->death_time = elapsed_time; */
/* 	philo->table->death_meals = philo->meal_counter; */
/* 	philo->table->dead_philo = philo->philo_id; */
/* } */

/* static char	*dying_philo(t_philo *philo, long elapsed_time) */
/* { */
/* 	change_bool(&philo->table->monitor_mtx, */
/* 			&philo->table->dinner_finished, true); */
/* 	safe_mutex(&philo->table->monitor_mtx, LOCK); */
/* 	dead_philo(philo, elapsed_time); */
/* 	safe_mutex(&philo->table->monitor_mtx, UNLOCK); */
/* 	return (NULL); */
/* } */

static char	*dying_philo(t_philo *philo)
{
	writing(philo, DIE);
	change_bool(&philo->table->monitor_mtx, &philo->table->dinner_finished,
		true);
	return (NULL);
}

static void	start_monitor(t_philo *philo, long *threshold)
{
	*threshold = philo->table->t_die - 10;
	while (!read_bool(&philo->table->table_mtx, &philo->table->threads_ready))
		usleep(1);
	desync(philo);
}

void	*monitor_check(void *data)
{
	t_philo	*philo;
	long	threshold;
	long	elapsed_time;

	philo = (t_philo *)data;
	start_monitor(philo, &threshold);
	while (!dinner_is_finished(&philo->table->monitor_mtx, philo))
	{
		if (philo->table->nbr_meals != 0
			&& philo->table->nbr_meals == read_long(&philo->table->monitor_mtx,
				&philo->meal_counter))
			return (NULL);
		if (dinner_is_finished(&philo->table->monitor_mtx, philo))
			return (NULL);
		elapsed_time = elapsed_time_f(philo->table)
			- read_long(&philo->philo_mtx, &philo->last_meal_time);
		if (elapsed_time >= philo->table->t_die
			&& !dinner_is_finished(&philo->table->monitor_mtx, philo))
			return (dying_philo(philo));
		else if (elapsed_time < (philo->table->t_die / 10) * 9)
			usleep((threshold - elapsed_time) * 1e3);
	}
	return (NULL);
}

t_philo	one_philo(t_philo *philo)
{
	if (dinner_is_finished(&philo->table->monitor_mtx, philo))
		return (*philo);
	safe_mutex(&philo->first_fork->fork, LOCK);
	writing(philo, LEFT_FORK);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	usleep(philo->table->t_die * 1e3);
	return (one_philo(philo));
}
