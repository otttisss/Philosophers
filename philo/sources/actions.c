/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:03:30 by cmilagro          #+#    #+#             */
/*   Updated: 2022/06/27 22:46:30 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	philo_sleep(int time_sleep, t_table *table)
{
	int		start;

	start = timestamp();
	while (!(table->is_any_died))
	{
		if ((int)diff_time(start, timestamp()) >= time_sleep)
			break ;
		usleep(50);
	}
}

void	eat(t_table *table, t_philo *me)
{
	pthread_mutex_lock(&table->forks[me->left_f]);
	say(table->f_timestamp, me->name, TAKEN, table);
	if (me->right_f == -1)
	{
		table->is_any_died = 1;
		printf("%lld %d died\n", diff_time(table->f_timestamp, \
		timestamp()), me->name + 1);
		return ;
	}
	pthread_mutex_lock(&table->forks[me->right_f]);
	say(table->f_timestamp, me->name, TAKEN, table);
	me->last_eat = timestamp();
	pthread_mutex_lock(&table->perm_to_eat);
	say(table->f_timestamp, me->name, EATING, table);
	me->count_eat++;
	pthread_mutex_unlock(&table->perm_to_eat);
	philo_sleep(table->t_t_e, table);
	pthread_mutex_unlock(&table->forks[me->left_f]);
	pthread_mutex_unlock(&table->forks[me->right_f]);
}

void	*philo_life(void *inp1)
{
	t_table	*table;
	t_philo	*me;

	me = (t_philo *)inp1;
	table = (t_table *)me->table;
	if (me->name % 2 == 1)
		usleep(15000);
	while (!(table->is_any_died) && (table->all_ate != 1))
	{
		eat(table, me);
		if (table->all_ate == 1)
			break ;
		say(table->f_timestamp, me->name, SLEEPING, table);
		philo_sleep(table->t_t_s, table);
		say(table->f_timestamp, me->name, THINKING, table);
	}
	return (NULL);
}

int	philo_exit(t_table *table, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < table->philo_numb)
		pthread_join(philos[i].thread_id, NULL);
	while (++i < table->philo_numb)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->perm_to_eat);
	pthread_mutex_destroy(&table->on_air);
	return (0);
}

void	say(long long int start, int name, char *s, t_table *table)
{
	long long int	t2;

	t2 = timestamp();
	pthread_mutex_lock(&table->on_air);
	if (!table->is_any_died)
		printf("%lld %d %s\n", diff_time(start, t2), name + 1, s);
	pthread_mutex_unlock(&table->on_air);
}
