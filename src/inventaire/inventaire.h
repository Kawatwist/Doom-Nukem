/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:27:59 by naali             #+#    #+#             */
/*   Updated: 2019/06/24 11:26:06 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		INVENTAIRE_H
# define	INVENTAIRE_H

typedef struct		s_consumable
{
	unsigned int		id;
	char				name[15];
	int					type;// Consommable vie ou energie (pour le moment)
	int					used;// Valeur du soin de vie ou bouclier
	unsigned int		qty;
	void				(*use)(t_joueurs *p, int used);// Fonction d'utilisation -> add_life ou add_energy
}					t_consumable;

typedef struct		s_weapons
{
	unsigned int		id;
	char				name[20];
	int					type;// Arme CaC, Range ou Zone
	int					dmg[3];// En tableau pour la RNG
	int					munition;
	int					entityammo;// A quoi correspond cette variable ???????? --> Voir LOMASSE
	void				(*shoot)(t_weapon *weapon/* , t_target *ennemi */);// Fonction de tire
	void				(*reload)(t_weapon *weapon, int max);// Fonction de recharge de l'arme
	struct s_weapons	*previous;// Boucle
	struct s_weapons	*next;// Boucle
}					t_weapons;

typedef struct		s_inventaire
{
	t_consumable		*conso;
	t_weapons			*weapo;
	// item utilisable pour les crafts;
}					t_inventaire;

typedef struct		s_joueurs
{
	t_inventaire	*inv;
	unsigned int	vie;
	unsigned int	energie;
//	t_weapons		*weapon;
	t_entity		*entity;
	int				rawx;
	int				rawy;
	int				rawz;
	double			x;
	double			y;
	double			z;
	float			sensi;
}					t_joueurs;

/* CONSOMABLE */
t_consumable		*new_conso(char *name, unsigned int qty);
void				pushback_conso(t_consumable **start, t_consumable *node);
void				destroy_conso_list(t_consumable **start);

/* ARME */

#endif
