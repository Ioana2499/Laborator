#ifndef M_H
#define M_H
#include <iostream>
class M
{
    int* Obiect, * grad;
    int n,coef;
    public:
    M();
    friend std::ostream & operator<<(std::ostream&, const M&);
    friend std::istream & operator>>(std::istream&, M&);
    int operator[](const int); //operatorul de indexare
};
#endif // M_H
