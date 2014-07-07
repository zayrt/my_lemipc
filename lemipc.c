/*
** main.c for main.c in /home/zellou_i/rendu/PSU_2013_lemipc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Wed Mar 26 13:24:10 2014 ilyas zelloufi
** Last update Sun Mar 30 19:21:13 2014 ilyas zelloufi
*/

#include	"lemipc.h"

void		move_player(t_game *game)
{
  game->map[game->p.y][game->p.x] = FREE;
  game->p.x = random() % WIDTH;
  game->p.y = random() % HEIGHT;
  while (game->map[game->p.y][game->p.x] == '1' ||
	 game->map[game->p.y][game->p.x] == '2')
    {
      game->p.x = random() % WIDTH;
      game->p.y = random() % HEIGHT;
    }
  game->map[game->p.y][game->p.x] = game->p.team;
}

void		add_player(t_game *game)
{
  game->p.dead = FALSE;
  game->p.x = random() % WIDTH;
  game->p.y = random() % HEIGHT;
  while (game->map[game->p.y][game->p.x] == '1' ||
	 game->map[game->p.y][game->p.x] == '2')
    {
      game->p.x = random() % WIDTH;
      game->p.y = random() % HEIGHT;
    }
  game->map[game->p.y][game->p.x] = game->p.team;
}

int		first_player(t_game *game)
{
  char		win_team;
  t_msg		mymsg;

  create_map(game);
  add_player(game);
  if (msgrcv(game->msg_id, &mymsg, 1, 42, 0) == -1)
    my_exit("Msgrcv fail.\n");
  show_map(game->map);
  while ((win_team = check_win_team(game->map)) == FALSE)
    {
      if (msgrcv(game->msg_id, &mymsg, 1, 42, 0) == -1)
	my_exit("Msgrcv fail.\n");
      show_map(game->map);
      if (!game->p.dead)
	my_ia(game);
    }
  if (shmctl(game->shm_id, IPC_RMID, NULL) == -1)
    my_exit ("Shmctl fail.\n");
  if (semctl(game->sem_id, 0, IPC_RMID, 0) == -1)
    my_exit("Semctl fail.\n");
  if (msgctl(game->msg_id, IPC_RMID, NULL) == -1)
    my_exit("Msgctl fail.\n");
  return (win_team);
}

int		other_player(t_game *game)
{
  t_msg		mymsg;

  get_map(game);
  if (check_free_place(game))
    {
      add_player(game);
      mymsg.type = 42;
      while (!game->p.dead && check_win_team(game->map) == FALSE)
	{
	  if (msgsnd(game->msg_id, &mymsg, 1, 0) == -1)
	    my_exit("Msgsn fail.\n");
	  my_ia(game);
	}
      if (msgsnd(game->msg_id, &mymsg, 1, 0) == -1)
	  my_exit("Msgsn fail.\n");
    }
  else
    {
      puts("La map est pleine cesse d'être en pitt");
      return (FALSE);
    }
  return (TRUE);
}
