/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_to_voidptr.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:26:07 by naali             #+#    #+#             */
/*   Updated: 2019/11/06 12:04:57 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CPY_TO_VOIDPTR_H
# define	CPY_TO_VOIDPTR_H

# include <stdlib.h>
# include <string.h>

# define	STCPY_ERROR		-1
# define	STCPY_SUCCESS	0

typedef struct			s_cmd
{
	unsigned int	id;
	size_t			len;
}						t_cmd;

short		get_type_size(int flg, void *cmd);
char		*ft_memcat(char *s1, char *s2, size_t len1, size_t len2);

/*
** N'importe quel type vers une string
** (ATTENTION cast en void*)
** dst = chaine de destination
** src = adresse du type a copier CASTER en void*
** len = taille de la memoire a copier
** retourne STCPY_ERROR en cas d'erreur sinon STCPY_SUCCESS.
** (ATTENTION malloc sur dst a FREE si necessaire).
*/
int			voidptr_to_string(char **dst, void *src, size_t len);

/*
** Fonction de retranscription GENERIC
** Retourne un ptr sur la copie (void*)
** en cas d'erreur retourne NULL.
** (ATTENTION ==> malloc fait sur le ptr retourner a free si necessaire)
*/
void		*string_to_voidptr(char *s, size_t len);

/*
** Fonction a appeler pour les transformations
** des INFORMATIONS TEXT (chat ou commande console)
*/
char		*cmd_format(char id, char client_id, short len, void *info);

/*
** Fonction a appeler pour les transformations
** de COORDONNEES (position Joueur...)
*/
char		*pos_player_to_tab(t_joueur *j, t_client *c);

/*
** Fonction pour l'envoi de COORDONNEES
** sans utilisation de structure joueur
*/
char		*pos_to_tab(t_client *c, float x, float y, float z);

#endif
