/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:03:07 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 17:15:35 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(char *err_msg, bool success)
{
	printf("%s\n", err_msg);
	if (!success)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	debug(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		printf("philo id: %ld\t", table->philos[i].philo_id);
		printf("philo first fork: %ld\t", table->philos[i].first_fork->fork_id);
		printf("philo second fork: %ld\n",
			table->philos[i].second_fork->fork_id);
		i++;
	}
}

long	elapsed_time_f(t_table *table)
{
	long	elapsed_time;

	elapsed_time = get_time() - table->start;
	return (elapsed_time);
}

long	get_time(void)
{
	struct timeval	current_time;
	long			time_mili;

	gettimeofday(&current_time, NULL);
	time_mili = (current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3);
	return (time_mili);
}
