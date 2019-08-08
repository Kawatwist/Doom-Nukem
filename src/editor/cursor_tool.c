#include <editor.h>

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
