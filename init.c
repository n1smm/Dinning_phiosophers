/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:08:51 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 17:58:09 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	fork_assign(t_fork *forks, t_philo *philo, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->nbr_philos;
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->is_full = false;
		philo->meal_counter = 0;
		philo->table = table;
		safe_mutex(&philo->philo_mtx, INIT);
		fork_assign(table->forks, philo, i);
		i++;
	}
}

void	init(t_table *table)
{
	int	i;

	i = 0;
	table->forks = safe_malloc(sizeof(t_fork) * (size_t)table->nbr_philos);
	table->philos = safe_malloc(sizeof(t_philo) * (size_t)table->nbr_philos);
	table->threads_ready = false;
	table->is_dead = false;
	table->time_out = table->t_die / 100 / table->nbr_philos;
	table->dinner_finished = false;
	safe_mutex(&table->table_mtx, INIT);
	safe_mutex(&table->write_mtx, INIT);
	safe_mutex(&table->time_mtx, INIT);
	safe_mutex(&table->monitor_mtx, INIT);
	while (i < table->nbr_philos)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i + 1;
		table->forks[i].taken = false;
		i++;
	}
	philo_init(table);
}
