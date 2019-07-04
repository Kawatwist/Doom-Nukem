/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:27:59 by naali             #+#    #+#             */
/*   Updated: 2019/07/04 16:27:06 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		INVENTAIRE_H
# define	INVENTAIRE_H

# include "consumable.h"
# include "weapons.h"

/* typedef struct		s_joueurs		t_joueurs; */
//typedef struct		s_weapons		t_weapons;
//typedef struct		s_consumable	t_consumable;

typedef struct		s_inventaire
{
	t_consumable		*conso;
	t_weapons			*weapo;
	char				**weap_name;
	unsigned int		weap_dmg[12][3];
	// item utilisable pour les crafts a ajouter;
}					t_inventaire;

struct				s_joueurs
{
	t_inventaire	*inv;
	char			*name;
	unsigned int	vie;
	unsigned int	energie;
//	t_weapons		*weapon;
//	t_entity		*entity;
	int				rawx;
	int				rawy;
	int				rawz;
	double			x;
	double			y;
	double			z;
	float			sensi;
};

void			inventaire_init_weapons(t_inventaire *inv);

#endif
