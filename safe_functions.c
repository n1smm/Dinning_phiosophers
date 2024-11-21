/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:20:51 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 18:00:44 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	*safe_malloc(size_t size)
{
	void			*allocated;
	unsigned int	i;

	i = 0;
	allocated = malloc(size);
	if (!allocated)
		error_exit(RED "Allocation failed" RESET, false);
	while (i < size)
	{
		*(unsigned char *)(allocated + i) = 0;
		i++;
	}
	return (allocated);
}

static void	error_handling(int mutex_error)
{
	if (mutex_error == EINVAL)
		error_exit(RED "EINVAL:" CYAN " Invalid argument" RESET, false);
	else if (mutex_error == EAGAIN)
		error_exit(RED "EBUSY:" CYAN " Resource temporarily"
			" unavailable" RESET,
			false);
	else if (mutex_error == EDEADLK)
		error_exit(RED "EDEADLK:" CYAN " Resource deadlock" RESET, false);
	else if (mutex_error == EPERM)
		error_exit(RED "EPERM:" CYAN " Operation not permitted" RESET,
			false);
	else if (mutex_error == EINTR)
		error_exit(RED "EINTR:" CYAN " Interrupted function call" RESET,
			false);
	else if (mutex_error == ESRCH)
		error_exit(RED "ESRCH:" CYAN " No such process" RESET, false);
}

void	safe_thread(t_trx *thread, void *(*function)(void *), void *data,
		t_operation operation)
{
	int	thread_error;

	thread_error = 0;
	if (operation == CREATE)
		thread_error = pthread_create(thread, NULL, function, data);
	else if (operation == DETACH)
		thread_error = pthread_detach(*thread);
	else if (operation == JOIN)
		thread_error = pthread_join(*thread, NULL);
	error_handling(thread_error);
	if (thread_error)
		error_exit(RED "wrong operation for thread" RESET, false);
}

void	safe_mutex(t_mtx *mutex, t_operation operation)
{
	int	mutex_error;

	mutex_error = 0;
	if (operation == INIT)
		mutex_error = pthread_mutex_init(mutex, NULL);
	else if (operation == DESTROY)
		mutex_error = pthread_mutex_destroy(mutex);
	else if (operation == LOCK)
		mutex_error = pthread_mutex_lock(mutex);
	else if (operation == UNLOCK)
		mutex_error = pthread_mutex_unlock(mutex);
	error_handling(mutex_error);
	if (mutex_error)
		error_exit(RED "wrong operation for mutex" RESET, false);
}
