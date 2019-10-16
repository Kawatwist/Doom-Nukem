#include "editor.h"

t_point     normalize(t_point src)
{
    float        l;

   	l = sqrtf(src.x * src.x + src.y * src.y + src.z * src.z);
   	src.x /= l;
   	src.y /= l;
   	src.z /= l;
   	return (src);
}