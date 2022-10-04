
#include "bircd.h"

void	check_fd(t_env *e)
{
  int	i;

  i = 0;
  while ((i < e->maxfd) && (e->r > 0))	// Boucle sur les fds potentiellement actifs, tant que le retour de select (e->r) n'indique pas d'erreur, ni de timeout, et qu'il y a encore des fds actifs dans le lot.
    {
      if (FD_ISSET(i, &e->fd_read))		// On appelle la fonction fct_read sur les fds de l'ensemble fd_read.
	e->fds[i].fct_read(e, i);
      if (FD_ISSET(i, &e->fd_write))	// On appelle la fonction fct_write sur les fds de l'ensemble fd_write.
	e->fds[i].fct_write(e, i);
      if (FD_ISSET(i, &e->fd_read) ||	// On decremente le nombre de fds actifs precedement renvoye par select, car on vient de le traiter.
	  FD_ISSET(i, &e->fd_write))
	e->r--;
      i++;
    }
}
