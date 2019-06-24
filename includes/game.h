/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:23:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/24 11:22:11 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "doom.h"

typedef struct	s_pointmap
{
	double		x;
	double		y;
	double		z;
}				t_pointmap;

typedef struct		s_entity
{
	void			*text;
	t_pointmap		*pos;
	struct s_entity	*next;
}					t_entity;

typedef struct		s_weapon
{
	int				id;
	int				dmg;
	int				ammo;
	int				range;
	int				status;
	void			*text;
	struct s_weapon	*next;
}					t_weapon;

// Ajout des variables: t_inventaire *inv, unsigned int vie, unsigned int energie
typedef struct		s_joueur
{
	t_weapon		*weapon;
	t_entity		*entity;
	int				rawx;
	int				rawy;
	int				rawz;
	double			x;
	double			y;
	double			z;
	float			sensi;
}					t_joueur;

#endif
