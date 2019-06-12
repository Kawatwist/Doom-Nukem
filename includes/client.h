/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:09:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/12 15:21:48 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>

typedef struct	s_client
{
	int					sockfd;
	int					port;
	int					n;
	struct sockaddr_in	serv_addr;
	struct hostent		*server;
	char				*message;
}				t_client;

#endif
