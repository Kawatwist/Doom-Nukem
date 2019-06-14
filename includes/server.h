/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:59:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/14 16:30:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

typedef struct s_user
{
	char				*name;
	struct sockaddr_in	cli_addr;
}				t_user;

typedef struct	s_server
{
	char		*username;
	int			sockfd;
	int			newsockfd;
	int			port;
	int			len;
	struct sockaddr_in serv_addr;
	t_user		user[3];
}				t_server;

#endif
