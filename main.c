/*
** main.c for main in /home/zellou_i/rendu/PSU_2013_lemipc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sun Mar 30 19:12:29 2014 ilyas zelloufi
** Last update Tue Apr  8 13:00:19 2014 ilyas zelloufi
*/

#include	"lemipc.h"

void		init_game(t_game *game, char team)
{
  char		*tmp;

  if ((tmp = getcwd(NULL, 0)) == NULL)
    my_exit("Getcwd() fail.\n");
  if ((game->key = ftok(tmp, 0)) == -1)
   my_exit("Ftok() fail.\n");
  free (tmp);
  game->p.team = team;
  game->shm_id = shmget(game->key, HEIGHT * WIDTH, SHM_R | SHM_W);
}

int		main(int ac, char **av)
{
  t_game	game;
  int		ret;

  if (ac != 2 || (strcmp(av[1], "1") != 0 && strcmp(av[1], "2") != 0))
    {
      fprintf(stderr, "[USAGE] %s team number 1 or 2.\n", av[0]);
      return (FALSE);
    }
  else
    {
      init_game(&game, av[1][0]);
      if (game.shm_id == -1)
	{
	  if ((ret = first_player(&game)))
	    {
	      printf("l'equipe %d a gagné !\n", ret);
	      return (TRUE);
	    }
	}
      else
	if (!other_player(&game))
	  return (FALSE);
    }
  return (TRUE);
}
