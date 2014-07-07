/*
** algo.c for algo in /home/zellou_i/rendu/PSU_2013_lemipc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Fri Mar 28 21:41:40 2014 ilyas zelloufi
** Last update Sun Mar 30 18:48:01 2014 ilyas zelloufi
*/

#include	"lemipc.h"

void		nb_player(char **map, int *count_team1, int *count_team2)
{
  int		i;
  int		j;

  i = 0;
  *count_team1 = 0;
  *count_team2 = 0;
  while (i < HEIGHT)
    {
      j = 0;
      while (j < WIDTH)
	{
	  if (map[i][j] == '1')
	    *count_team1 += 1;
	  if (map[i][j] == '2')
	    *count_team2 += 1;
	  ++j;
	}
      ++i;
    }
}

int		check_win_team(char **map)
{
  int		nb_team1;
  int		nb_team2;

  nb_player(map, &nb_team1, &nb_team2);
  if (nb_team1 == 0)
    return (2);
  if (nb_team2 == 0)
    return (1);
  return (FALSE);
}

int		check_around(char **map, int x, int y, char ennemy)
{
  int		nb_ennemy;

  nb_ennemy = 0;
  if (x - 1 >= 0 && x - 1 < WIDTH && map[y][x - 1] == ennemy)
    nb_ennemy += 1;
  if (x + 1 < WIDTH && x + 1 >= 0 && map[y][x + 1] == ennemy)
    nb_ennemy += 1;
  if (y - 1 < HEIGHT && y - 1 >= 0 && map[y - 1][x] == ennemy)
    nb_ennemy += 1;
  if (y + 1 < HEIGHT && y + 1 >= 0 && map[y + 1][x] == ennemy)
    nb_ennemy += 1;
  if (y + 1 < HEIGHT && y + 1 >= 0 && x + 1 < WIDTH && x + 1 >= 0
      && map[y + 1][x + 1] == ennemy)
    nb_ennemy += 1;
  if (y + 1 < HEIGHT && y + 1 >= 0 && x - 1 < WIDTH && x - 1 >= 0
      && map[y + 1][x - 1] == ennemy)
    nb_ennemy += 1;
  if (y - 1 < HEIGHT && y - 1 >= 0 && x + 1 < WIDTH && x + 1 >= 0
      && map[y - 1][x + 1] == ennemy)
    nb_ennemy += 1;
  if (y - 1 < HEIGHT && y - 1 >= 0 && x - 1 < WIDTH && x - 1 >= 0
      && map[y - 1][x - 1] == ennemy)
    nb_ennemy += 1;
  return (nb_ennemy);
}

int		isDie(t_game *game)
{
  int		nb_ennemy;
  char		ennemy;

  ennemy = (game->p.team == '1') ? '2' : '1';
  nb_ennemy = check_around(game->map, game->p.x, game->p.y,  ennemy);
  if (nb_ennemy < 2)
    return (FALSE);
  return (TRUE);
}

int		my_ia(t_game *game)
{
  lock_ipc(game);
  if (isDie(game))
    {
      show_map(game->map);
      puts("Hi, je suis mort.");
      game->map[game->p.y][game->p.x] = FREE;
      unlock_ipc(game);
      game->p.dead = TRUE;
      return (0);
    }
  move_player(game);
  usleep(TIME);
  unlock_ipc(game);
  return (0);
}
