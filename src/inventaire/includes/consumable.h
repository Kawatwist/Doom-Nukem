/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consumable.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:26:35 by naali             #+#    #+#             */
/*   Updated: 2019/06/28 15:55:08 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CONSUMABLE_H
# define	CONSUMABLE_H

# include "inventaire.h"

typedef struct		s_joueurs		t_joueurs;
typedef struct		s_consumable	t_consumable;

struct				s_consumable
{
	unsigned int	id;
	char			name[15];
	int				type;// Consommable vie ou energie (pour le moment)
	int				used;// Valeur du soin de vie ou bouclier
	unsigned int	qty;
	void			(*use)(t_joueurs *p, t_consumable *c);// Fonction d'utilisation -> add_life ou add_energy
	t_consumable	*previous;// Boucle
	t_consumable	*next;// Boucle
};

/* CONSOMABLE */
t_consumable		*new_conso(char *name, unsigned int qty, t_consumable **start);
void				pushback_conso(t_consumable **start, t_consumable *node);
void				destroy_conso_list(t_consumable **start);
int					conso_list_len(t_consumable **start);

#endif
