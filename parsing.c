/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:22:15 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 18:01:22 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline bool	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (true);
	return (false);
}

static inline bool	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

long	ft_atol(char *number)
{
	long	result;
	int		i;

	i = 0;
	result = 0;
	while (is_space(number[i]))
		i++;
	if (number[i] == '+')
		i++;
	if (number[i] == '-')
		error_exit(RED "Arg is a negative number" RESET, false);
	if (!is_digit(number[i]))
		error_exit(RED "Arg is not a number" RESET, false);
	while (is_digit(number[i]))
		result = result * 10 + (number[i++] - 48);
	if (result > INT_MAX || number[i] != 0)
		error_exit(RED "Invalid number" RESET, false);
	return (result);
}

void	parsing(t_table *table, char **argv)
{
	table->nbr_philos = ft_atol(argv[1]);
	table->t_die = ft_atol(argv[2]);
	table->t_eat = ft_atol(argv[3]);
	table->t_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->nbr_meals = ft_atol(argv[5]);
	else
		table->nbr_meals = 0;
	if (table->t_die < 60 || table->t_sleep < 60 || table->t_eat < 60)
		error_exit(RED "Time is less then 60 milliseconds" RESET, false);
}
