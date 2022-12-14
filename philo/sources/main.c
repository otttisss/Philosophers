/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:33:15 by cmilagro          #+#    #+#             */
/*   Updated: 2022/06/27 22:48:09 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include "errors.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		ret;

	if (argc != 5 && argc != 6)
		return (print_error(ERR_OF_ARG));
	ret = init_table(&table, argv);
	if (ret)
		return (print_error(ERR_OF_ARG));
	if (launch(&table))
		return (print_error(ERR_OF_MUTEX));
	return (0);
}
