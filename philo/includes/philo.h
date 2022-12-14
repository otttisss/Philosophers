/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:18:51 by cmilagro          #+#    #+#             */
/*   Updated: 2022/06/24 19:25:14 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
# include "errors.h"
# include <stdbool.h>
# include <pthread.h>

# define TAKEN 		"has taken a fork"
# define EATING 	"is eating"
# define THINKING 	"is thinking"
# define SLEEPING 	"is sleeping"

typedef struct s_philo
{
	int				name;
	int				left_f;
	int				right_f;
	int				n_o_e;
	long long int	last_eat;
	int				count_eat;
	struct s_table	*table;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_table
{
	int				all_ate;
	int				philo_numb;
	int				t_t_d;
	int				t_t_e;
	int				t_t_s;
	int				n_e_p_m_e;
	long long int	f_timestamp;
	int				is_any_died;
	pthread_mutex_t	on_air;
	pthread_mutex_t	perm_to_eat;
	pthread_mutex_t	forks[201];
	t_philo			philo[201];
}	t_table;

void			*philo_life(void *inp1);
int				philo_exit(t_table *table, t_philo *philos);
int				init_table(t_table *table, char **tablev);
int				ft_atoi(const char *s);
long long int	timestamp(void);
long long int	diff_time(long long int t1, long long int t2);
void			say(long long int start, int name, char *s, t_table *table);
int				launch(t_table *table);
int				print_error(char *str);

#endif
