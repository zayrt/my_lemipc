/*
** lemipc.h for lemipic in /home/zellou_i/rendu/PSU_2013_lemipc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Wed Mar 26 18:43:19 2014 ilyas zelloufi
** Last update Thu Apr  3 12:55:27 2014 ilyas zelloufi
*/

#ifndef LEMIPC_H__
# define LEMIPC_H__

# include	<stdio.h>
# include	<sys/types.h>
# include	<sys/ipc.h>
# include	<stdlib.h>
# include	<sys/shm.h>
# include	<sys/sem.h>
# include	<unistd.h>
# include	<string.h>
# include	<sys/msg.h>

# define HEIGHT	5
# define WIDTH	5
# define TIME	100000
# define FREE	'o'
# define TRUE	1
# define FALSE	0

typedef struct	s_player
{
  int		x;
  int		y;
  int		dead;
  char		team;
}		t_player;

typedef struct	s_msg
{
  long		type;
  char		str[1];
}		t_msg;

typedef struct	s_game
{
  char		**map;
  int		shm_id;
  int		sem_id;
  int		msg_id;
  key_t		key;
  t_player	p;
}		t_game;

int		first_player(t_game *);
int		other_player(t_game *);
void		show_map(char **map);
void		create_map(t_game *game);
void		get_map(t_game *game);
void		add_player(t_game *game);
int		check_free_place(t_game *game);
void		nb_player(char **map, int *count_team1, int *count_team2);
int		check_win_team(char **map);
void		unlock_ipc(t_game *);
void		lock_ipc(t_game *);
int		my_ia(t_game *);
void		my_exit(char *);
void		move_player(t_game *);

#endif /* !LEMIPC_H__ */
