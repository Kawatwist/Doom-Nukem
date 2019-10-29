/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_to_voidptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:27:36 by naali             #+#    #+#             */
/*   Updated: 2019/10/29 13:02:11 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpy_to_voidptr.h"

/***********************************************/
/* ATTENTION MEMCPY A TRANSFORMER EN FT_MEMCPY */
/***********************************************/

int		voidptr_to_string(char **dst, void *src, size_t len)
{
	if (dst != NULL && src != NULL)
	{
		*dst = NULL;
		if ((*dst = (char*)malloc(len)) == NULL)
			return (STCPY_ERROR);
		/*ft_*/memcpy((void*)(*dst), src, len);
	}
	else
		return (STCPY_ERROR);
	return (STCPY_SUCCESS);
}

void		*string_to_voidptr(char *s, size_t len)
{
	void	*ret;

	ret = NULL;
	if ((s == NULL) || ((ret = malloc(len)) == NULL))
		return (NULL);
	/*ft_*/memcpy(ret, (void*)s, len);
	return (ret);
}

/***************************************/
/* Test de formatage de commande DEBUT */
/***************************************/

char		*ft_memcat(char *s1, char *s2, size_t len1, size_t len2)
{
	char			*ret;
	unsigned int	i;

	if ((ret = malloc(sizeof(char) * (len1 + len2 + 2))) == NULL)
		return (NULL);
	i = -1;
	while (++i < len1)
		ret[i] = s1[i];
	i = -1;
	while (++i < len2)
		ret[i + len1] = s2[i];
	return (ret);
}

char		*cmd_format(char id, short len, void *info)
{
	char			*ret;
	char			tmp[4];
	unsigned int	sz_max;

	ret = NULL;
	if (id < 0 || len == 0 || info == NULL)
		return (ret);
	sz_max = 6 + len;
	tmp[0] = ';';
	tmp[1] = id;
	tmp[2] = (len >> 8) & 0xFF;
	tmp[3] = len & 0xFF;
	ret = ft_memcat(tmp, info, 4, len);
	ret[sz_max - 2] = ';';
	ret[sz_max - 1] = '\0';
	free(info);
	info = NULL;
	return (ret);
}

/*************************************/
/* Test de formatage de commande FIN */
/*************************************/

/*********************/
/* 2eme Main de test */
/*********************/
/*
#include <string.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	short	size;
	char	*info;

	size = 0;
	info = NULL;
	if (ac < 2)
		return (0);
	info = strdup(av[1]);
	size = (short)strlen(info);
	info = cmd_format(1, size, info);
	if (size > 0)
		printf("id = |%d|\nlen = |%d|\nstr = |%s|\n",					\
			info[1], ((short)(info[2]) << 8) + (short)(info[3]), &info[4]);
	free(info);
	info = NULL;
	return (0);
}
*/
/*********************/

/***************************************/
/* MAIN d'exemple avec MEMCPY + STRUCT */
/** Pointeur retourner n'est pas FREE **/
/*********** dans l'exemple ************/
/***************************************/

/*
int		main()
{
	int		i = 42;
	float	f = 54687451323545468745.465687f;
	double	d = 534568.54648687864654132135478;
	char	*src = "salut les ami(e)s";
	char	*dst;

	if (voidptr_to_string(&dst, (void*)(&i), sizeof(i)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr int = %d\n\n", *(int*)string_to_voidptr(dst, sizeof(i)));

	free(dst);
	dst = NULL;

	if (voidptr_to_string(&dst, (void*)(&f), sizeof(f)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr float = %.3f\n\n", *(float*)string_to_voidptr(dst, sizeof(f)));

	free(dst);
	dst = NULL;

	if (voidptr_to_string(&dst, (void*)(&d), sizeof(d)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr double = %.40f\n\n", *(double*)string_to_voidptr(dst, sizeof(d)));

	free(dst);
	dst = NULL;

	if (voidptr_to_string(&dst, (void*)(src), strlen(src)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr string = |%s|\n\n", (char*)string_to_voidptr(dst, strlen(src)));
	return (STCPY_SUCCESS);
}
*/
