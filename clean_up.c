/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:40:32 by thiew             #+#    #+#             */
/*   Updated: 2024/08/06 16:28:04 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nbr_philos)
		safe_mutex(&table->forks[i++].fork, DESTROY);
	safe_mutex(&table->table_mtx, DESTROY);
	safe_mutex(&table->write_mtx, DESTROY);
	safe_mutex(&table->monitor_mtx, DESTROY);
	free(table->philos);
	free(table->forks);
}
