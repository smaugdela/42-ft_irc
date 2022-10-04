
#include <stdlib.h>
#include <sys/resource.h>
#include "bircd.h"

void		init_env(t_env *e)
{
  int		i;
  struct rlimit	rlp;

  X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");						// Recupere la structure rlp avec getrlimit.
  e->maxfd = rlp.rlim_cur;													// Ecrit la soft limit indique par getrlimit dans l'environnement.
  e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc");	// Malloc un tableau de structure t_fd dans l'environnement (en fonction de maxfd qui vient d'etre recupere).
  i = 0;
  while (i < e->maxfd)			// Boucle qui va initialiser par defaut chaque structure t_fd dans l'env.
    {
      clean_fd(&e->fds[i]);
      i++;
    }
}
