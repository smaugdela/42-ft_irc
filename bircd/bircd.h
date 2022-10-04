#ifndef BIRCD_H_
# define BIRCD_H_

# include <sys/select.h>

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE	4096

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))		// Appelle la fonction "x_void*" grace a une macro parametrique pour simplifier l'appel.
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))		// Appelle la fonction "x_int" grace a une macro parametrique pour simplifier l'appel.
# define MAX(a,b)	((a > b) ? a : b)									// Macro parametrique de la fonction max (equivalent a un template en C++).

# define USAGE		"Usage: %s port\n"									// Si l'utilisateur lance mal ./bircd, rappelle son fonctionnement.

typedef struct	s_fd
{
  int	type;
  void	(*fct_read)();
  void	(*fct_write)();
  char	buf_read[BUF_SIZE + 1];
  char	buf_write[BUF_SIZE + 1];
}		t_fd;

typedef struct	s_env
{
  t_fd		*fds;
  int		port;
  int		maxfd;
  int		max;
  int		r;
  fd_set	fd_read;
  fd_set	fd_write;
}		t_env;

void	init_env(t_env *e);
void	get_opt(t_env *e, int ac, char **av);
void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	srv_accept(t_env *e, int s);
void	client_read(t_env *e, int cs);
void	client_write(t_env *e, int cs);
void	clean_fd(t_fd *fd);

/*
Les deux fonctions suivantes permettent de proteger un appel de fonction qui peut echouer (comme malloc)
et, si le retour est == err (cad qu'une erreur a bien eu lieu), alors le programme exit et affiche un message indiquant
le fichier, la ligne et le nom de la fonction ayant echouee.
*/
int		x_int(int err, int res, char *str, char *file, int line);		// Permet de proteger les appels de fonction avec un int en retour. A utiliser avec la macro X ci-dessus.
void	*x_void(void *err, void *res, char *str, char *file, int line);	// Permet de proteger les appels de fonction avec un pointeur en retour. A utiliser avec la macro Xv ci-dessus.

void	init_fd(t_env *e);
void	do_select(t_env *e);
void	check_fd(t_env *e);

#endif /* !BIRCD_H_ */
