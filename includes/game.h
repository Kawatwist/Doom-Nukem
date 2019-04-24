/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:23:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/22 11:17:17 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "doom.h"

typedef struct	s_joueur
{
	double		posx;
	double		posy;
	double		viewx;
	double		viewy;
	int			rawx;
	int			rawy;
	float		sensi;
}				t_joueur;
#endif
