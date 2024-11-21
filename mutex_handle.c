/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:09:37 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 17:06:37 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	read_bool(t_mtx *mutex, bool *value)
{
	bool	yaa_noo;

	safe_mutex(mutex, LOCK);
	yaa_noo = *value;
	safe_mutex(mutex, UNLOCK);
	return (yaa_noo);
}

void	change_bool(t_mtx *mutex, bool *input, bool desire)
{
	safe_mutex(mutex, LOCK);
	*input = desire;
	safe_mutex(mutex, UNLOCK);
}

long	read_long(t_mtx *mutex, long *value)
{
	long	very_long_number;

	safe_mutex(mutex, LOCK);
	very_long_number = *value;
	safe_mutex(mutex, UNLOCK);
	return (very_long_number);
}

void	change_long(t_mtx *mutex, long *input, long desire)
{
	safe_mutex(mutex, LOCK);
	*input = desire;
	safe_mutex(mutex, UNLOCK);
}

bool	dinner_is_finished(t_mtx *mutex, t_philo *philo)
{
	bool	outcome;

	safe_mutex(mutex, LOCK);
	if (philo->table->dinner_finished)
		outcome = true;
	else
		outcome = false;
	safe_mutex(mutex, UNLOCK);
	return (outcome);
}
