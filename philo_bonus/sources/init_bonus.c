/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:33:35 by cmilagro          #+#    #+#             */
/*   Updated: 2022/06/27 22:56:01 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <signal.h>

static void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	philo = table->philo;
	i = -1;
	while (++i < table->philo_numb)
	{
		philo[i].name = i;
		philo[i].table = table;
		philo[i].count_eat = 0;
	}
}

static void	init_sema(t_table *table)
{
	sem_unlink("!forks");
	sem_unlink("!writing");
	sem_unlink("!perm");
	table->forks = sem_open("!forks", O_CREAT, S_IRWXU, table->philo_numb);
	table->writing = sem_open("!writing", O_CREAT, S_IRWXU, 1);
	table->perm_to_eat = sem_open("!perm", O_CREAT, S_IRWXU, 1);
}

int	init_table(t_table *table, char **argv)
{
	table->philo_numb = ft_atoi(argv[1]);
	if (!table->philo_numb || table->philo_numb < 0)
		terminate(ERR_OF_ARG);
	table->t_t_d = ft_atoi(argv[2]);
	if (!table->t_t_d || table->t_t_d < 0)
		terminate(ERR_OF_ARG);
	table->t_t_e = ft_atoi(argv[3]);
	if (!table->t_t_e || table->t_t_e < 0)
		terminate(ERR_OF_ARG);
	table->t_t_s = ft_atoi(argv[4]);
	if (!table->t_t_s || table->t_t_s < 0)
		terminate(ERR_OF_ARG);
	if (!argv[5])
		table->n_e_p_m_e = -1;
	else
		table->n_e_p_m_e = ft_atoi(argv[5]);
	if (!table->n_e_p_m_e && table->n_e_p_m_e < 0)
		terminate(ERR_OF_ARG);
	table->is_any_died = 0;
	init_sema(table);
	init_philo(table);
	return (0);
}

static void	philo_exit(t_table *table)
{
	int	i;
	int	ret;

	i = 0;
	while (i < table->philo_numb)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < table->philo_numb)
				kill(table->philo[i].pid, 15);
			break ;
		}
		i++;
	}
	sem_close(table->forks);
	sem_close(table->writing);
	sem_close(table->perm_to_eat);
	sem_unlink("!forks");
	sem_unlink("!writing");
	sem_unlink("!perm");
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
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			terminate(ERR_OF_PROCC);
		if (philos[i].pid == 0)
			philo_life(&philos[i]);
		usleep(200);
	}
	philo_exit(table);
	return (0);
}
