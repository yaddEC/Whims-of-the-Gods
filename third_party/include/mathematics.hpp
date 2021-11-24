#pragma once 
#include <cmath>
template<typename A>
inline float norm(A Vec)
{
return sqrt((Vec.x*Vec.x)+(Vec.y*Vec.y));
}

template<typename A, typename B>
bool collCirclex2(A posCircle1, int radiusCircle1, B posCircle2,int radiusCircle2)
{
    A centerCenterVector = {posCircle1.x - posCircle2.x, posCircle1.y - posCircle2.y};
    float normCenterCenterVector = norm(centerCenterVector);
    if (normCenterCenterVector <= radiusCircle1 + radiusCircle2)
    {
        return true;
    }
    return false;
}

template<typename A>
A vector(A a, A b)
{
    A res;
    res.x=b.x-a.x;
    res.y=b.y-a.y;
    return res;
}



