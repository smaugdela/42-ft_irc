
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bircd.h"

void			srv_accept(t_env *e, int s)
{
  int					cs;
  struct sockaddr_in	csin;
  socklen_t				csin_len;

  csin_len = sizeof(csin);
  cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");	// Cree un nouveau socket pour la premiere requete de connexion entrante sur le socket "s" (en ecoute).
  printf("New client #%d from %s:%d\n", cs,
	 inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
  clean_fd(&e->fds[cs]);					// Restaure a zero la structure t_fd associe au nouveau fd du socket cree.
  e->fds[cs].type = FD_CLIENT;				// Attribue un type client a la struct t_fd du nouveau socket.
  e->fds[cs].fct_read = client_read;		// Attribue la fonction "handler" pour la lecture du nouveau socket.
  e->fds[cs].fct_write = client_write;		// Attribue la fonction "handler" pour l'ecriture du nouveau socket.
}
