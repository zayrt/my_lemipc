/*
** make_map.c for make_map in /home/zellou_i/rendu/PSU_2013_lemipc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sun Mar 30 17:29:50 2014 ilyas zelloufi
** Last update Sun Mar 30 19:23:08 2014 ilyas zelloufi
*/

#include	"lemipc.h"

void		init_create_map(t_game *game)
{
  if ((game->msg_id = msgget(game->key, IPC_CREAT | SHM_R | SHM_W)) == -1)
    my_exit("Msgget() fail.\n");
  if ((game->sem_id = semget(game->key, 1, IPC_CREAT | SHM_R | SHM_W)) == -1)
    my_exit("Shmget() fail.\n");
  if (semctl(game->sem_id, 0, SETVAL, 1) == -1)
    my_exit("Shmctl() fail.\n");
  printf("ipcrm shm %d ; ipcrm sem %d ; ipcrm msg %d key -> %d\n",
	 game->shm_id, game->sem_id, game->msg_id, game->key);
  lock_ipc(game);
  game->shm_id = shmget(game->key, HEIGHT * WIDTH, IPC_CREAT | SHM_R | SHM_W);
  if (game->shm_id == -1)
    my_exit("Shmget() fail.\n");
}

void		create_map(t_game *game)
{
  int		i;
  int		j;
  void		*addr;

  i = 0;
  init_create_map(game);
  if ((addr = shmat(game->shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    my_exit("Shmat() fail.\n");
  if ((game->map = malloc(sizeof(char *) * HEIGHT)) == NULL)
    my_exit("Malloc() fail.\n");
  while (i < HEIGHT)
    {
      j = 0;
      game->map[i] = addr + i * WIDTH;
      while (j < WIDTH)
	game->map[i][j++] = FREE;
      game->map[i][j] = '\0';
      ++i;
    }
  unlock_ipc(game);
}

void		get_map(t_game *game)
{
  int		i;
  void		*addr;

  i = 0;
  if ((game->msg_id = msgget(game->key, SHM_R | SHM_W)) == -1)
    my_exit("Msgget() fail.\n");
  if ((game->sem_id = semget(game->key, 1, SHM_R | SHM_W)) == -1)
    my_exit("Semget() fail.\n");
   printf("ipcrm shm %d ; ipcrm sem %d ; ipcrm msg %d key %d\n",
	  game->shm_id, game->sem_id, game->msg_id, game->key);
   lock_ipc(game);
   if ((addr = shmat(game->shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
     my_exit("Shmat() fail.\n");
   if ((game->map = malloc(sizeof(char *) * HEIGHT)) == NULL)
     my_exit("Malloc() fail.\n");
   while (i < HEIGHT)
     {
       if ((game->map[i] = malloc(sizeof(char) * WIDTH)) == NULL)
	 my_exit("Malloc() fail.\n");
       game->map[i++] = addr + (i * WIDTH);
     }
 unlock_ipc(game);
}
