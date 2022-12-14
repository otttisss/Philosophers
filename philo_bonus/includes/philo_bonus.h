/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmilagro <cmilagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:18:51 by cmilagro          #+#    #+#             */
/*   Updated: 2022/06/25 19:07:51 by cmilagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
# include "errors_bonus.h"
# include <pthread.h>
# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>

# define TAKEN 		"has taken a fork"
# define EATING 	"is eating"
# define THINKING 	"is thinking"
# define SLEEPING 	"is sleeping"
# define DEAD		"died"

typedef struct s_philo
{
	int				name;
	pid_t			pid;
	long long int	last_eat;
	int				count_eat;
	struct s_table	*table;
	pthread_t		death_check;
}	t_philo;

typedef struct s_table
{
	int				philo_numb;
	int				t_t_d;
	int				t_t_e;
	int				t_t_s;
	int				n_e_p_m_e;
	long long int	f_timestamp;
	int				is_any_died;
	sem_t			*writing;
	sem_t			*perm_to_eat;
	sem_t			*forks;
	t_philo			philo[201];
}	t_table;

void			philo_life(void *inp1);
int				init_table(t_table *table, char **tablev);
int				ft_atoi(const char *s);
long long int	timestamp(void);
long long int	diff_time(long long int t1, long long int t2);
void			say(long long int start, int name, char *s, sem_t *writing);
int				launch(t_table *table);
int				print_error(char *str);
void			terminate(char *s);
int				free_philo(t_table *table, int arg);

#endif
