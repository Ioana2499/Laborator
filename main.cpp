#include <iostream>
#include <math.h>
#include "M.h"
using namespace std;
class Polinom
{
    double* coef;
    int grad;
public:
    Polinom(); // constr de initializare
    Polinom(int x); //constr de initializare cu 1 parametru
    ~Polinom();
    Polinom(const Polinom&);
    float valoareInPunct(int);
    void setGrad(int);
    void setCoef(double*m, int);
    double* getCoef();
    int getGrad();
    Polinom operator+(const Polinom&);
    Polinom operator*(const Polinom&);
    Polinom operator-(const Polinom&);
    Polinom& operator=(const Polinom&);
    int operator[](const int);
    void show();
    void eliminare(int);
    void adaugare(float, int);
    friend std::ostream & operator<<(std::ostream&, const Polinom&);
    friend std::istream & operator>>(std::istream&, Polinom&);
   // friend Polinom& operator --(Polinom& y);
};

Polinom::Polinom()
{
    grad = 0;
    coef = NULL;
}
///constructor de initializare cu 1 parametru
Polinom::Polinom(int x)
{
    grad = x;
    coef = NULL;
}
///functie de afisare
void Polinom::show()
{
    for(int i=grad; i>=1; i--)
        if(coef[i])
            std::cout<<coef[i]<<"x^"<<i<<" + ";
    std::cout<<coef[0]<<std::endl;
}
///destructorul care dezaloca vectorul de coeficienti si seteaza gradul la 0
Polinom::~Polinom()
{
    grad = 0;
    delete[] coef;
}
///constructor de copiere
Polinom::Polinom(const Polinom& b)
{
    grad = b.grad;
    coef = new double[grad+1];
    for(int i=0; i<=grad; i++)
        coef[i] = b.coef[i];
}
///suprascrierea operatorului = ce egaleaza gradele si copiaza coeficientii
Polinom& Polinom::operator=(const Polinom &b)
{
    grad = b.grad;
    delete coef;
    coef = new double[grad+1];
    for(int i=0; i<=b.grad; i++)
        coef[i] = b.coef[i];
    return *this;
}
///functie ce returneaza un pointer de tip double ce reprezinta coeficientii polinomului
double* Polinom::getCoef()
{
    return this->coef;
}
///functie ce calculeaza valoarea intr-un punct
float Polinom::valoareInPunct(int val)
{
    float suma = 0;
    for (int i = grad; i >= 0; i--)
    {
        suma = suma + coef[i] * pow(val, i);
    }
    return suma;
}
///functie ce returneaza gradul unui polinom
int Polinom::getGrad()
{
    return this->grad;
}
///suprascrierea operatorului [] pentru a returna coeficientul gradului i
int Polinom::operator[](const int i)
{
    return coef[i];
}
///functie ce supraincarca operatorul +
Polinom Polinom::operator+(const Polinom &b)
{
    ///in polinomul aux voi calcula rezultatul adunarii
    Polinom aux;
    ///in min1 si max1 aflu maximul si minimul dintre gradele operanzilor
    int min1, max1;
    if(b.grad > this->grad)
    {
        max1 = b.grad;
        min1 = grad;
    }
    else
    {
        max1 = grad;
        min1 = b.grad;
    }
    ///setez gradul rezultatului la gradul celui mai mare dintre operanzi si aloc memoria necesara
    aux.grad = max1;
    aux.coef = new double[max1+1];
    for(int i=0; i<=aux.grad; i++)
    {
        aux.coef[i] = 0;
    }
    ///adaug la rezultat suma coeficientilor pentru fiecare grad de gradul minim de ori
    for(int i=0; i<=min1; i++)
    {
        aux.coef[i] = coef[i] + b.coef[i];
    }
    ///in functie de polinomul cu gradul mai mare copiez din acesta in rezultat
    if(grad > b.grad)
        for(int i=min1+1; i<=max1; i++)
        {
            aux.coef[i] = coef[i];
        }
    else
        for(int i=min1+1; i<=max1; i++)
        {
            aux.coef[i] = b.coef[i];
        }

    return aux;
}
///functie ce supraincarca operatorul -
Polinom Polinom::operator-(const Polinom &b)
{
    ///in polinomul aux voi calcula rezultatul scaderii
    Polinom aux;
    ///in min1 si max1 aflu maximul si minimul dintre gradele operanzilor
    int min1, max1;
    if(b.grad > this->grad)
    {
        max1 = b.grad;
        min1 = grad;
    }
    else
    {
        max1 = grad;
        min1 = b.grad;
    }
    ///setez gradul rezultatului la gradul celui mai mare dintre operanzi si aloc memoria necesara
    aux.grad = max1;
    aux.coef = new double[max1+1];
    for(int i=0; i<=aux.grad; i++)
    {
        aux.coef[i] = 0;
    }
    ///adaug la rezultat diferenta coeficientilor pentru fiecare grad de gradul minim de ori
    for(int i=0; i<=min1; i++)
    {
        aux.coef[i] = coef[i] - b.coef[i];
    }
    ///in functie de polinomul cu gradul mai mare copiez din acesta in rezultat
    if(grad > b.grad)
        for(int i=min1+1; i<=max1; i++)
        {
            aux.coef[i] = coef[i];
        }
    else
        for(int i=min1+1; i<=max1; i++)
        {
            aux.coef[i] = b.coef[i];
        }

    return aux;
}
///suprascrierea operatorului * pentru inmultirea a doua polinoame
Polinom Polinom::operator*(const Polinom& b)
{
    ///in polinomul aux voi calcula rezultatul inmultirii
    Polinom aux;
    int i, j;
    ///gradul rezultatului va fi suma gradelor operanzilor
    aux.grad = b.grad + grad;
    aux.coef = new double[aux.grad+1];
    for(i=0; i<=aux.grad; i++)
    {
        aux.coef[i] = 0;
    }
    ///gradului i+j din rezultat i se va adauga rezultatul inmultirii gradului i, respectiv j din polinoamele supuse inmultirii
    for(i=grad; i>=0; i--)
        for(j=b.grad; j>=0; j--)
        {
            aux.coef[i+j] += coef[i] * b.coef[j];
        }

    return aux;
}

///suprascrierea operatorului <<
std::ostream& operator<<(std::ostream &out, const Polinom& b)
{
    ///sunt afisati toti coeficientii
    for(int i=b.grad; i>0; i--)
        if(b.coef[i] != 0)
            out << b.coef[i] << "X^" << i << " + ";
    out << b.coef[0] << std::endl;
    return out;
}
///suprascrierea operatorului >>
std::istream& operator>>(std::istream &in, Polinom& b)
{
    delete[] b.coef;
    in >> b.grad;
    b.coef = new double[b.grad+1];
    for(int i=b.grad; i>=0; i--)
        in >> b.coef[i];
    return in;
}

int main()
{
    Polinom P, Q;
    cin>>P;
    cin >> Q;
    cout << P;
    cout << Q;
    Polinom I = P * Q;
    cout << I;
    I = P + Q;
    cout << I;
    I = P - Q;
    cout<<I;
   /* Obiect v[u];
    cin>>c[1]; cout<<v[1];
    v[2]=v[3]=(v[1]+v[2]);*/
    return 0;
}
