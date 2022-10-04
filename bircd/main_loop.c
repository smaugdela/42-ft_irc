
#include "bircd.h"

void	main_loop(t_env *e)
{
  while (1)
    {
      init_fd(e);	// Initialise les listes "fd_read" et "fd_write" necessaire pour "select";
      do_select(e);	// Lance "select" pour identifier les fds actifs.
      check_fd(e);	// Traite chacun des fds actifs en ecriture et/ou lecture avec les fonctions configures dans fct_read et fct_write du "env".
    }
}
