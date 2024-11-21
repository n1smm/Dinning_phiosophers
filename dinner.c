/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:12:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 18:01:43 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	long	threshold;
	long	elapsed_time;

	if ((philo->table->nbr_meals != 0
			&& philo->table->nbr_meals == philo->meal_counter)
		|| dinner_is_finished(&philo->table->monitor_mtx, philo))
		return ;
	threshold = (philo->table->t_die / 10) * 5;
	elapsed_time = elapsed_time_f(philo->table) - read_long(&philo->philo_mtx,
			&philo->last_meal_time);
	writing(philo, THINK);
	if ((philo->meal_counter % 2) && !(philo->philo_id % 2)
		&& philo->meal_counter != 0)
		usleep(3000);
	if (!(philo->meal_counter % 2) && (philo->philo_id % 2)
		&& philo->meal_counter != 0)
		usleep(3000);
}

static void	eating(t_philo *philo)
{
	if ((philo->table->nbr_meals != 0
			&& philo->table->nbr_meals == philo->meal_counter)
		|| dinner_is_finished(&philo->table->monitor_mtx, philo))
		return ;
	safe_mutex(&philo->first_fork->fork, LOCK);
	writing(philo, LEFT_FORK);
	safe_mutex(&philo->second_fork->fork, LOCK);
	writing(philo, RIGHT_FORK);
	change_long(&philo->table->monitor_mtx, &philo->meal_counter,
		philo->meal_counter + 1);
	change_long(&philo->philo_mtx, &philo->last_meal_time,
		elapsed_time_f(philo->table));
	writing(philo, EAT);
	usleep(philo->table->t_eat * 1e3);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}

static char	*dinner_start(t_philo *philo)
{
	while (!read_bool(&philo->table->table_mtx, &philo->table->threads_ready))
		usleep(1);
	desync(philo);
	change_long(&philo->philo_mtx, &philo->last_meal_time, 0);
	change_long(&philo->philo_mtx, &philo->meal_counter, 0);
	if (philo->table->nbr_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	return ("let there be death!");
}

static void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!dinner_start(philo))
		return (NULL);
	while (!dinner_is_finished(&philo->table->monitor_mtx, philo))
	{
		if ((philo->table->nbr_meals != 0
				&& philo->table->nbr_meals == philo->meal_counter)
			|| dinner_is_finished(&philo->table->monitor_mtx, philo))
			return (NULL);
		eating(philo);
		if ((philo->table->nbr_meals != 0
				&& philo->table->nbr_meals == philo->meal_counter)
			|| dinner_is_finished(&philo->table->monitor_mtx, philo))
			return (NULL);
		usleep(philo->table->t_sleep * 1e3);
		writing(philo, SLEEP);
		if ((philo->table->nbr_meals != 0
				&& philo->table->nbr_meals == philo->meal_counter)
			|| dinner_is_finished(&philo->table->monitor_mtx, philo))
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		safe_thread(&table->philos[i].thread_phil, dinner_sim,
			&table->philos[i], CREATE);
		safe_thread(&table->philos[i].thread_mon, monitor_check,
			&table->philos[i], CREATE);
		i++;
	}
	table->start = get_time();
	change_bool(&table->table_mtx, &table->threads_ready, true);
	i = 0;
	while (i < table->nbr_philos)
		pthread_join(table->philos[i++].thread_phil, NULL);
	i = 0;
	change_bool(&table->monitor_mtx, &table->dinner_finished, true);
	while (i < table->nbr_philos)
		pthread_join(table->philos[i++].thread_mon, NULL);
	if (table->is_dead)
		printf("%-10ld %-10ld died\n", table->death_time, table->dead_philo);
}
