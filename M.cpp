#include "M.h"
#include <iostream>
#include <math.h>
///suprascrierea operatorului [] pentru a returna coeficientul gradului i
int M::operator[](const int i)
{
    if(i>=0 && i<n) return Obiect[i];
    else return 0;
}
M :: M()
{
    grad = 0;
    coef = NULL;
}
