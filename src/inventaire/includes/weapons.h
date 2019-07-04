/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:29:44 by naali             #+#    #+#             */
/*   Updated: 2019/07/04 16:25:43 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WEAPONS_H
# define	WEAPONS_H

# define CAC 2
# define RANGE 4
# define ZONE 8

# include "inventaire.h"

/* typedef struct		s_joueurs		t_joueurs; */
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
	void			(*shoot)(/* t_weapons *weapon *//* , t_foes ou t_player *ennemi */);// Fonction de tire
	void			(*reload)(/* t_weapons *weapon, int max */);// Fonction de recharge de l'arme
	t_weapons		*previous;// Boucle
	t_weapons		*next;// Boucle
};

/* INIT */
void			init_names_n_dmg(char ***names, unsigned int (*dmg)[12][3]);
void			free_tab_names(char ***n);

/* SHOT & RELOAD */
void			cac_shot();
void			range_shot();
void			area_shot();

void			cac_reload();
void			range_reload();
void			area_reload();

void			select_shot_reload(t_weapons *w, int type);

/* ARME */
t_weapons		*new_weapon(char *name, int type, int max_ammo);
void			pushback_weapons(t_weapons **start, t_weapons *node);
void			destroy_weapo_list(t_weapons **start);
int				weapo_list_len(t_weapons **start);
void			destroy_one_weapo(t_weapons **start, unsigned int id);
t_weapons		*get_weapo_by_id(t_weapons **start, unsigned int id);
void			weapo_swap_elem(t_weapons **start, \
								unsigned int id1, unsigned int id2);

#endif
