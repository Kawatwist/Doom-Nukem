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
		len = (ft_strlen(msg)) + 3;
	}
	ret = ft_strjoin(";ill", user);						// i = index ll = len;
	ret[1] = 1;
	ret[2] = (len >> 8) & 0xFF;
	ret[3] = len & 0xFF;
	ret = ft_memjoinfree(ret, " : ", 4 + ulen, 3);
	ret = ft_memjoinfree(ret, &msg[4], 7 + ulen, ft_strlen(&msg[4]));
	ret = ft_memjoinfree(ret, ";\0", len + 4, 2);
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
	msg = add_user(msg, ((t_client *)wn->client)->username);
	send(((t_client *)wn->client)->sockfd, msg, i, 0);
}

void		send_msg_from_server(t_win *wn, char *msg, int	user)
{
	int	i;

	i = 0;
	if (((t_server *)wn->serv)->username == NULL)
	{
		((t_server *)wn->serv)->username = malloc(sizeof(char) * 8);
		getlogin_r(((t_server *)wn->serv)->username, 8);
	}
	i = ft_strlen(msg) + ft_strlen(((t_server *)wn->serv)->username)  + 3;
	msg = add_user(msg, ((t_server *)wn->serv)->username);
	send(((t_server *)wn->serv)->user[user].socket, msg, i, 0);
}
