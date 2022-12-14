/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:03:30 by cmilagro          #+#    #+#             */
/*   Updated: 2022/06/27 22:42:16 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include "philo_bonus.h"

static void	*death_checker(void *inp)
{
	t_table	*table;
	t_philo	*me;

	me = (t_philo *)inp;
	table = (t_table *)me->table;
	while (!table->is_any_died)
	{
		sem_wait(table->perm_to_eat);
		if ((int)(timestamp() - me->last_eat) >= table->t_t_d)
		{
			say(table->f_timestamp, me->name, DEAD, table->writing);
			table->is_any_died = 1;
			sem_wait(table->writing);
			exit(1);
		}
		sem_post(table->perm_to_eat);
		usleep(1200);
		if ((table->n_e_p_m_e != -1) && (me->count_eat >= table->n_e_p_m_e))
			break ;
	}
	return (NULL);
}

static void	philo_sleep(t_table *table, int time)
{
	long long	t;

	t = timestamp();
	while (!table->is_any_died)
	{
		if ((int)(timestamp() - t) >= time)
			break ;
		usleep(50);
	}
}

static void	eat(t_table *table, t_philo *me)
{
	if (!table->is_any_died)
	{
		sem_wait(table->forks);
		say(table->f_timestamp, me->name, TAKEN, table->writing);
		sem_wait(table->forks);
		say(table->f_timestamp, me->name, TAKEN, table->writing);
		sem_wait(table->perm_to_eat);
		say(table->f_timestamp, me->name, EATING, table->writing);
		me->last_eat = timestamp();
		sem_post(table->perm_to_eat);
		philo_sleep(table, table->t_t_e);
		sem_post(table->forks);
		sem_post(table->forks);
		me->count_eat++;
	}
}

void	philo_life(void *inp1)
{
	t_table	*table;
	t_philo	*me;

	me = (t_philo *)inp1;
	table = me->table;
	me->last_eat = timestamp();
	pthread_create(&me->death_check, NULL, death_checker, me);
	if (me->name % 2 == 1)
		usleep(15000);
	while (!table->is_any_died)
	{
		eat(table, me);
		if ((table->n_e_p_m_e != -1) && (me->count_eat >= table->n_e_p_m_e))
			break ;
		say(table->f_timestamp, me->name, SLEEPING, table->writing);
		philo_sleep(table, table->t_t_s);
		say(table->f_timestamp, me->name, THINKING, table->writing);
	}
	pthread_join(me->death_check, NULL);
	exit(0);
}

void	say(long long int start, int name, char *s, sem_t *writing)
{
	sem_wait(writing);
	printf("%d %d %s\n", (int)(timestamp() - start), name + 1, s);
	sem_post(writing);
}
