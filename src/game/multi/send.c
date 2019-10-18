/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:57:48 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 11:06:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"
#include "client.h"

/*
** LISTE D'INDEX:
** 1 = message
** 2 = message retransmit
*/

/*
** Fonction basic de formatage d'instruction
** A REFONDRE
*/
static char	*add_user(char *msg, char *user)
{
	char	*ret;
	int		ulen;
	int		len;

	if (user != NULL)
	{
		ulen = ft_strlen(user);
		len = ulen + (ft_strlen(msg) - 4) + 3;
	}
	else
	{
		ulen = 0;
		len = (ft_strlen(msg));
	}
	ret = (user != NULL) ? ft_strjoin(";ill", user) : ft_strdup(";ill");	// i = index ll = len;
	ret[1] = 1;															// index
	ret[2] = (len >> 8) & 0xFF;											// len 1
	ret[3] = len & 0xFF;												// len 2
	if (user != NULL)
		ret = ft_memjoinfree(ret, " : ", 4 + ulen, 3);					// Separation USER : MESSAGE
	ret = ft_memjoinfree(ret, &msg[(user == NULL ? 0 : 4)], ((user == NULL) ? 4 : 7) + ulen, ft_strlen(&msg[(user == NULL ? 0 : 4)]));	// Ajout du message
	ret = ft_memjoinfree(ret, ";\0", len + 4, 2);	// Fin d'intruction
	//ft_putstrindec(ret, len + 6);  /// PRINTF DANS LIBFT !
	return (ret);
}

void		send_msg_from_client(t_win *wn, char *msg)
{
	int	i;

	i = 0;
	if (((t_client *)wn->client)->username == NULL)
		getlogin_r(((t_client *)wn->client)->username, 8);
	i = ft_strlen(msg) + ft_strlen(((t_client *)wn->client)->username) + 3;
	printf("CLIENT ENVOI DE MESSAGE: %s\n", msg);
	msg = add_user(msg, ((t_client *)wn->client)->username);
	send(((t_client *)wn->client)->sockfd, msg, i, 0);
	printf("socket fd = %d\n", ((t_client *)wn->client)->sockfd);
}

void		send_msg_from_server(t_win *wn, char *msg, int	user)
{
	int	i;

	i = 0;
	printf("SEND FROM SERVER\n");
	if (((t_server *)wn->serv)->username == NULL)
	{
		printf("SET SERVER NAME\n");
		((t_server *)wn->serv)->username = malloc(sizeof(char) * 8);
		getlogin_r(((t_server *)wn->serv)->username, 8);
	}
	printf("SERVER NAME = %s\n", ((t_server *)wn->serv)->username);
	i = ft_strlen(msg) + ft_strlen(((t_server *)wn->serv)->username) + 3;
	msg = add_user(msg, ((t_server *)wn->serv)->username);
	printf("SERVEUR ENVOI DE MESSAGE: %s\n", msg);
	send(((t_server *)wn->serv)->user[user].socket, msg, i, 0);
}

void		resend_msg_from_server(t_win *wn, char *msg, int user)
{
	int	i;

	i = 0;
	i = ft_strlen(msg) + 4;
	msg = add_user(msg, NULL);
	send(((t_server *)wn->serv)->user[user].socket, msg, i, 0);
}
