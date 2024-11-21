/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:51:25 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/06 17:59:09 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc >= 7)
		error_exit(RED "Wrong number of arguments!" GREEN "\nUse"
			" this format [nbr. of philos] [time_die] [time_eat]"
			" [time_sleep] (optional)[nbr. meals]" RESET,
			false);
	parsing(&table, argv);
	init(&table);
	dinner_init(&table);
	cleanup(&table);
}
