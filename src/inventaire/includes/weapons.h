/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:29:44 by naali             #+#    #+#             */
/*   Updated: 2019/06/27 20:33:25 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WEAPONS_H
# define	WEAPONS_H

# define CAC 2
# define RANGE 4
# define ZONE 8

# include "inventaire.h"

typedef struct		s_joueurs		t_joueurs;
typedef struct		s_weapons		t_weapons;

struct				s_weapons
{
	unsigned int	id;
	char			*name;
	int				type;// Arme CaC, Range ou Zone
	unsigned int	dmg[3];// En tableau pour la RNG
	int				munition;
	int				max_ammo;
	int				entityammo;// Position de l'arme
	void			(*shoot)(t_weapons *weapon/* , t_foes ou t_player *ennemi */);// Fonction de tire
	void			(*reload)(t_weapons *weapon, int max);// Fonction de recharge de l'arme
	t_weapons		*previous;// Boucle
	t_weapons		*next;// Boucle
};

/* ARME */
t_weapons		*new_weapon(char *name, int type, int max_ammo);

#endif
