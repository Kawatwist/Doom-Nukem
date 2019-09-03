/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:27:59 by naali             #+#    #+#             */
/*   Updated: 2019/07/09 14:11:51 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		INVENTAIRE_H
# define	INVENTAIRE_H

# include "doom.h"
# include "consumable.h"
# include "weapons.h"
# include "components.h"

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
	SDL_Texture		*inv_txt;
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

/* INIT */
void		inventaire_init_weapons(t_inventaire *inv);
void		init_inventaire_texture(t_win *win);
void		print_inventory(t_win *wn, t_joueurs *j, int selected);
void		print_text_with_ariel_font(t_win *wn, char *s, \
										SDL_Color color, SDL_Rect position);

/* Print ON Render */
int			print_weapo_list(t_win *wn, t_joueurs *j, int *selected);
void		print_conso_list(t_win *wn, t_joueurs *j, int selected, int pos);
void		print_items_name(t_win *wn, char *name, int pos, int isselected);
void		choose_item_color(SDL_Color *color, int isselected);
void		print_items_qty(t_win *wn, char *qty, int pos, int isselected);// Use ft_itoa(qty)

#endif