/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:33:35 by cmilagro          #+#    #+#             */
/*   Updated: 2022/06/27 22:44:58 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

static int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_numb)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			printf(ERR_OF_MUTEX);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&table->perm_to_eat, NULL))
	{
		printf(ERR_OF_MUTEX);
		return (1);
	}
	if (pthread_mutex_init(&table->on_air, NULL))
	{
		printf(ERR_OF_MUTEX);
		return (1);
	}
	return (0);
}

static void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_numb)
	{
		table->philo[i].name = i;
		table->philo[i].left_f = i;
		if (table->philo_numb != 1)
			table->philo[i].right_f = (i + 1) % table->philo_numb;
		else
			table->philo[i].right_f = -1;
		table->philo[i].last_eat = 0;
		table->philo[i].count_eat = 0;
		table->philo[i].table = table;
	}
}

int	init_table(t_table *table, char **argv)
{
	table->philo_numb = ft_atoi(argv[1]);
	if (!table->philo_numb || table->philo_numb < 0)
		return (1);
	table->t_t_d = ft_atoi(argv[2]);
	if (!table->t_t_d || table->t_t_d < 0)
		return (1);
	table->t_t_e = ft_atoi(argv[3]);
	if (!table->t_t_e || table->t_t_e < 0)
		return (1);
	table->t_t_s = ft_atoi(argv[4]);
	if (!table->t_t_s || table->t_t_s < 0)
		return (1);
	if (!argv[5])
		table->n_e_p_m_e = -1;
	else
		table->n_e_p_m_e = ft_atoi(argv[5]);
	if (!table->n_e_p_m_e)
		return (1);
	table->is_any_died = 0;
	table->all_ate = 0;
	init_mutex(table);
	init_philo(table);
	return (0);
}

static void	deathchecking(t_table *table, t_philo *philo)
{
	int	i;

	while (!table->all_ate)
	{
		while (++i < table->philo_numb && !(table->is_any_died))
		{
			pthread_mutex_lock(&table->perm_to_eat);
			if (diff_time(philo[i].last_eat, timestamp()) > table->t_t_d)
			{
				printf("%lld %d died\n", diff_time(table->f_timestamp, \
				timestamp()), philo[i].name + 1);
				table->is_any_died = 1;
			}
			pthread_mutex_unlock(&table->perm_to_eat);
			usleep(100);
		}
		if (table->is_any_died == 1)
			break ;
		i = 0;
		while (table->n_e_p_m_e != -1 && i < table->philo_numb
			&& table->philo[i].count_eat >= table->n_e_p_m_e)
			i++;
		if (i == table->philo_numb)
			table->all_ate = 1;
	}
}

int	launch(t_table *table)
{
	int		i;
	t_philo	*philos;

	philos = table->philo;
	i = -1;
	table->f_timestamp = timestamp();
	while (++i < table->philo_numb)
	{
		philos[i].last_eat = timestamp();
		pthread_create(&philos[i].thread_id, NULL, philo_life, &philos[i]);
	}
	deathchecking(table, table->philo);
	philo_exit(table, philos);
	return (0);
}
