#include <editor.h>

static int select_len(t_point **select)
{  
    int i;

    i = 0;
    while (select[i] != NULL)
        i++;
    return (i);
}

t_point **addtmptoselection(t_point **tmp, t_point **select)
{
    t_point **ret;
    int     i;
    int     j;

    i = select_len(tmp);
    j = select_len(select);
    ret = malloc(sizeof(t_point *) * (i + j + 1)); // need secure
    memcpy(ret, tmp, i * sizeof(t_point *));
    memcpy(&ret[i], select, j * sizeof(t_point *));
    ret[i + j] = NULL;
    free(tmp);
    free(select);
    return (ret);
}

t_point *find_center(t_point **lst)
{
    t_point *center;
    t_point **curr;
    int     i;

    i = 0;
    center = malloc(sizeof(t_point));
    curr = lst;
    while (curr[i] != NULL && lst != NULL)
    {
        if (center == NULL || !i)
        {
            center->x = curr[i]->x;
            center->y = curr[i]->y;
            center->z = curr[i]->z;
        }
        else
        {
            center->x += curr[i]->x;
            center->y += curr[i]->y;
            center->z += curr[i]->z;
        }
        i++;
    }
    center->x /= i;
    center->y /= i;
    center->z /= i;
    if (center == NULL)
    {
        free(center);
        return (NULL);
    }
    return (center);
}
