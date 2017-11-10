#include <iostream>
using namespace std;

#ifndef DINHEIRO_H
#define DINHEIRO_H

class Dinheiro
{
    private:
        unsigned int Reais;
        unsigned int Centavos;

    public:
        Dinheiro(unsigned int Reais,unsigned int Centavos);
        Dinheiro();
        ~Dinheiro();
        //Dinheiro(Dinheiro & d);
        unsigned getReais() const;
        unsigned getCentavos() const;
        void setReais(unsigned int Reais);
        void setCentavos(unsigned int Centavos);
        Dinheiro & operator=(const Dinheiro d2);
        Dinheiro & operator+=(const Dinheiro d2);
        Dinheiro & operator-=(const Dinheiro d2);
        Dinheiro operator+(const Dinheiro d2) const;
        Dinheiro operator-(const Dinheiro d2) const;
        Dinheiro operator*(const double c) const;

        friend ostream & operator<<(ostream & os, const Dinheiro & d);
};

#endif