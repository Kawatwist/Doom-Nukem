/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_to_voidptr.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:26:07 by naali             #+#    #+#             */
/*   Updated: 2019/10/25 15:27:00 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CPY_TO_VOIDPTR_H
# define	CPY_TO_VOIDPTR_H

# include <stdlib.h>
# include <string.h>

# define	STCPY_ERROR		-1
# define	STCPY_SUCCESS	0

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

#endif
