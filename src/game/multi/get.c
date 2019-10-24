/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:59:10 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 11:07:17 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"
#include "client.h"

char		*parse_packet(t_win *wn, char *msg)
{
	(void)wn;
	char	*ret;
	int		len;

	len = 0;
	if (msg[1] == 1)
	{
		len = (msg[2] << 8);
		len += (unsigned char)msg[3];
		ret = malloc(sizeof(char) * len + 1);
		ft_memcpy(ret, &msg[4], len);
		ret[len] = 0;
	}
	else
		return (NULL);
	return (ret);
}

char		*get_msg_client(t_win *wn)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1024);
	recv(((t_client *)wn->client)->sockfd, buff, 1024, 0);
//	ft_putstrindec(buff, ft_strlen(buff + 4) + 4);
	buff = parse_packet(wn, buff);
	ft_putstrindec(buff, ft_strlen(buff));
	return (buff);
}

char		*get_msg_server(t_win *wn, int user)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1024);
	recv(((t_server *)wn->serv)->user[user].socket, buff, 1024, 0);
	buff = parse_packet(wn, buff);
	ft_putstrindec(buff, ft_strlen(buff));
	return (buff);
}
