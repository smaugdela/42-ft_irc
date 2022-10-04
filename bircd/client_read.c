
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_read(t_env *e, int cs)
{
  int	r;
  int	i;

  r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);	// Recoit le donnees entrante sur le socket "cs" et les ecrit dans "buf_read" (similaire a un read);
  if (r <= 0)
    {
      close(cs);						// Si rien n'a ete recu, ferme le socket.
      clean_fd(&e->fds[cs]);
      printf("client #%d gone away\n", cs);
    }
  else
    {
      i = 0;
      while (i < e->maxfd)					// Boucle sur tous les fd...
	{
	  if ((e->fds[i].type == FD_CLIENT) &&	// ... et si c'est un autre client...
	      (i != cs))
	    send(i, e->fds[cs].buf_read, r, 0);	// ... il lui emet le message recu ci-dessus.
	  i++;
	}
    }
}
