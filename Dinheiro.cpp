#include "Dinheiro.h"
#include <iostream>

using namespace std;

//Métodos básicos da classe Dinheiro
Dinheiro::Dinheiro(unsigned int Reais, unsigned int Centavos)
{
    if(Reais < 0)
    {
        Reais = 0;
    }
    (*this).Reais = Reais;
    (*this).Centavos = Centavos;
}

Dinheiro::Dinheiro()
{
    Reais = 0;
    Centavos = 0;
}

Dinheiro::~Dinheiro()
{

}

/*Dinheiro::Dinheiro(Dinheiro & d)
{
    (*this).Reais = d.Reais;
    (*this).Centavos = d.Centavos;
}*/

unsigned Dinheiro::getReais() const
{
    return Reais;
}

unsigned Dinheiro::getCentavos() const
{
    return Centavos;
}

void Dinheiro::setCentavos(unsigned int Centavos)
{
    (*this).Centavos = Centavos;
}

void Dinheiro::setReais(unsigned int Reais)
{
    (*this).Reais = Reais;
}


//sobrecarga de operadores
Dinheiro & Dinheiro::operator=(const Dinheiro d2)
{
    //se tentar realizar uma autorreferencia, não podemos deixar
    if (this == &d2) return *this;

    (*this).Reais = d2.Reais; // atribui os reais recebidos
    (*this).Centavos = d2.Centavos; // atribui os centavos recebidos

    return *this;
}

Dinheiro & Dinheiro::operator+=(const Dinheiro d2)
{
    //converte para realizar a soma
    Centavos = (Centavos + d2.Centavos) % 100; // soma-se os centavos. se excerder 100 temos mais 1 real, somente o restante permanece
    Reais = Reais + d2.Centavos + (Centavos + d2.Centavos) / 100; // soma-se os reais e os reais obtidos na soma dos centavos

    return *this; 
}

Dinheiro & Dinheiro::operator-=(const Dinheiro d2)
{
    //se o dinheiro recebido para subtração for maior que o que temos, este ficará negativo
    if((Reais*100 + Centavos) < (d2.Reais*100 + d2.Centavos))
    {
        //Logo, já devolvemos R$ 0,00
        Centavos = 0; 
        Reais = 0;
        return *this;
    }
    
    //senão, convertemos os valores para centavos e realizamos a subtração
    long long subtracao = (Reais*100 + Centavos) - (d2.Reais*100 + d2.Centavos);
    Reais = subtracao/100; // converte os centavos para reais
    Centavos = subtracao%100;//atribui o restante dos centavos 
    return *this;
}

Dinheiro Dinheiro::operator+(const Dinheiro d2) const
{
    //realiza a soma dos centavos
    int centavos = (Centavos + d2.Centavos) % 100;//%100 para receber somente centavos
    int reais = Reais + d2.Centavos + (Centavos + d2.Centavos) / 100;//soma-se os reais e os reais adquiridos ao somar os centavos
    Dinheiro dSoma(reais,centavos); // cria o dinheiro da soma
    return dSoma;
}

Dinheiro Dinheiro::operator-(const Dinheiro d2) const
{
     //se o dinheiro recebido para subtração for maior que o que temos, este ficará negativo
    if((Reais*100 + Centavos) < (d2.Reais*100 + d2.Centavos))
    {
        //Logo, já devolvemos R$ 0,00
        Dinheiro dSub(0,0);
        return dSub;
    }
    //senão, convertemos os valores para centavos e realizamos a subtração
    long long subtracao = (Reais*100 + Centavos) - (d2.Reais*100 + d2.Centavos);
    Dinheiro dSub(subtracao/100,subtracao%100);//desfaz a conversão para somente centavos
    return dSub;
}

Dinheiro Dinheiro::operator*(const double c) const
{
    //se a constante de multiplicação é negativa
    if( c < 0.0)
    {
        //já devolvemos R$ 0,00
        Dinheiro dSub(0,0);
        return dSub;
    }
    //senão, realizamos a multiplicação normal
    int mult =(int)((Reais*100 + Centavos) * c);//converte para centavos e multiplica

    Dinheiro dSub(mult/100,mult%100);//desfaz a conversão
    return dSub;
}

ostream & operator<<(ostream & os, const Dinheiro & d)
{
    //sobrecarga do operador << utilizando a classe ostream
    
    os << "R$" << d.getReais() << ","<<d.getCentavos();//retornamos uma saída com o formato desejado
    return os;
}
/*
int main()
{
    Dinheiro d(10,10);
    Dinheiro d2(10,10);
    cout << d <<endl;
    Dinheiro soma = d + d2;
    cout << soma << endl;
    Dinheiro sub = d - d2;
    cout << sub << endl;
    Dinheiro mult = d * 2;
    cout << mult << endl;
    d += d2;
    cout << d <<endl;
    d-= d2*3;
    cout << d << endl;
    return 0;
}*/

