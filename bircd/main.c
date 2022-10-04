
#include "bircd.h"

int	main(int ac, char **av)
{
  t_env	e;

  init_env(&e);				// Initialise la structure "env".
  get_opt(&e, ac, av);		// Recupere le port donne en parametre du programme, et le note dans l'env.
  srv_create(&e, e.port);	// Lance un socket en ecoute sur le port indique en parametre du programme (e.port).
  main_loop(&e);
  return (0);
}
