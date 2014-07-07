/*
** init_game.c for init_game in /home/zellou_i/rendu/PSU_2013_lemipc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Fri Mar 28 11:42:02 2014 ilyas zelloufi
** Last update Sun Mar 30 17:04:30 2014 ilyas zelloufi
*/

#include	"lemipc.h"

void		show_map(char **map)
{
  int		i;
  int		j;

  i = 0;
  while (i < HEIGHT)
    {
      j = 0;
      while (j < WIDTH)
	printf("%c", map[i][j++]);
      printf("\n");
      ++i;
    }
  printf("\n\n");
}

int		check_free_place(t_game *game)
{
  int		i;
  int		j;

  i = 0;
  while (i < HEIGHT)
    {
      j = 0;
      while (j < WIDTH)
	{
	  if (game->map[i][j] == FREE)
	    return (TRUE);
	  ++j;
	}
      ++i;
    }
  return (FALSE);
}

void		unlock_ipc(t_game *game)
{
  struct sembuf	sbuf;

  sbuf.sem_num = 0;
  sbuf.sem_op = 1;
  sbuf.sem_flg = 0;
  if (semop(game->sem_id, &sbuf, 1) == -1)
    my_exit("Semop() fail\n");
}

void		lock_ipc(t_game *game)
{
  struct sembuf	sbuf;

  sbuf.sem_num = 0;
  sbuf.sem_op = -1;
  sbuf.sem_flg = 0;
  if (semop(game->sem_id, &sbuf, 1) == -1)
    my_exit("Semop() fail\n");
}

void		my_exit(char *str)
{
  perror(str);
  exit (EXIT_FAILURE);
}
