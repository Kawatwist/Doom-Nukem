/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_to_voidptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:27:36 by naali             #+#    #+#             */
/*   Updated: 2019/10/25 15:32:28 by naali            ###   ########.fr       */
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
	if ((ret = malloc(len)) == NULL)
		return (NULL);
	/*ft_*/memcpy(ret, (void*)s, len);
	return (ret);
}

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
