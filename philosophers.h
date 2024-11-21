/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:47:03 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 18:09:58 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BOLD "\033[1m"

/* # define B_RED BOLD RED */
/* # define B_GREEN BOLD GREEN */
/* # define B_YELLOW BOLD YELLOW */
/* # define B_BLUE BOLD BLUE */
/* # define B_MAGENTA BOLD MAGENTA */
/* # define B_CYAN BOLD CYAN */
/* # define B_WHITE BOLD WHITE */

typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_trx;

typedef struct s_table	t_table;

typedef enum e_operation
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_operation;

typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	LEFT_FORK,
	RIGHT_FORK,
	DIE
}						t_action;

typedef struct s_fork
{
	t_mtx				fork;
	long				fork_id;
	bool				taken;
}						t_fork;

typedef struct s_philo
{
	long				philo_id;
	long				meal_counter;
	long				last_meal_time;
	bool				is_full;
	bool				is_dead;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_mtx				philo_mtx;
	t_trx				thread_phil;
	t_trx				thread_mon;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				nbr_philos;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				start;
	long				time_out;
	long				nbr_meals;
	long				death_time;
	long				death_meals;
	long				dead_philo;
	bool				is_dead;
	bool				threads_ready;
	bool				dinner_finished;
	t_mtx				table_mtx;
	t_mtx				write_mtx;
	t_mtx				time_mtx;
	t_mtx				monitor_mtx;
	t_philo				*philos;
	t_fork				*forks;
}						t_table;

/* utils_main */
void					error_exit(char *err_msg, bool success);
long					get_time(void);
long					elapsed_time_f(t_table *table);
/* parsing */
void					parsing(t_table *table, char **argv);
/* init */
void					init(t_table *table);
/* safe functions */
void					*safe_malloc(size_t size);
void					safe_thread(t_trx *thread, void *(*function)(void *),
							void *data, t_operation operation);
void					safe_mutex(t_mtx *mutex, t_operation operation);
/* dinner */
void					dinner_init(t_table *table);
void					thinking(t_philo *philo);
/* utils_dinner */
void					writing(t_philo *philo, t_action action);
void					desync(t_philo *philo);
/* debug */
void					debug(t_table *table);
/* mutex handle */
bool					read_bool(t_mtx *mutex, bool *value);
void					change_bool(t_mtx *mutex, bool *input, bool desire);
long					read_long(t_mtx *mutex, long *value);
void					change_long(t_mtx *mutex, long *input, long desire);
bool					dinner_is_finished(t_mtx *mutex, t_philo *philo);
/* monitor and one philo */
void					*monitor_check(void *data);
t_philo					one_philo(t_philo *philo);
/* clean_up */
void					cleanup(t_table *table);

#endif
