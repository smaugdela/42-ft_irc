
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"

void			srv_create(t_env *e, int port)
{
  int					s;
  struct sockaddr_in	sin;
  struct protoent		*pe;
  
  pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");		// Recupere les informations relatives au protocole tcp.
  s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");				// Ouvre un socket pour communiquer avec le protocole souhaite, et renvoie le fd associe.
  sin.sin_family = AF_INET;					// Configure les attributs de la structure "sockaddr_in sin" pour son utilisation par "bind".
  sin.sin_addr.s_addr = INADDR_ANY;			// Idem
  sin.sin_port = htons(port);				// htons sert a rendre compatible le numero de port hote avec le reseau (car l'ordre des bytes n'est pas necessairement le meme).
  X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind");	// Attribue la structure "sin" au socket ouvert "s".
  X(-1, listen(s, 42), "listen");			// Met le socket "s" en attente de connections entrantes, avec une limite de "42" connexion entrante.
  e->fds[s].type = FD_SERV;					// Indique a notre "env" que le socket au fd "s" est un serveur (fd = 1).
  e->fds[s].fct_read = srv_accept;			// Indique a notre "env" quelle fonction le socket au fd "s" utiliser pour accepter les communication entrantes.
}
