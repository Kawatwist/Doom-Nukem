/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:23:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/11 19:06:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

typedef struct s_joueur
{
	double		posx;
	double		posy;
	double		viewx;
	double		viewy;
	int			rawx;
	int			rawy;
	float		sensi;
}				t_joueur;
