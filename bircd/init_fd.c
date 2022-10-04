
#include <string.h>
# include <sys/select.h>
#include "bircd.h"

void	init_fd(t_env *e)
{
  int	i;

  i = 0;
  e->max = 0;				// Initialise le nombre maximum de fds actifs.
  FD_ZERO(&e->fd_read);		// Vide l'ensemble des fds en lecture (si il y en a).
  FD_ZERO(&e->fd_write);	// Vide l'ensemble des fds en ecriture (si il y en a).
  while (i < e->maxfd)		// Boucle jusqu'au nombre limite de fds disponibles (selon getrlimit).
    {
      if (e->fds[i].type != FD_FREE)	// Si le fd n'est pas 0...
	{
	  FD_SET(i, &e->fd_read);			// ... il est ajoute a l'ensemble des fds en lecture.
	  if (strlen(e->fds[i].buf_write) > 0)	// Et si son buffer n'est pas vide...
	    {
	      FD_SET(i, &e->fd_write);			// ... il est ajoute a l'ensemble des fds en ecriture.
	    }
	  e->max = MAX(e->max, i);			// On garde en memoire la valeur du plus grand fd actif.
	}
      i++;
    }
}
