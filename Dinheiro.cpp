#include "Dinheiro.h"

Dinheiro::Dinheiro(unsigned int reais, unsigned int centavos)
{
    (*this).reais = reais;
    (*this).centavos = reais;
}

Dinheiro::Dinheiro()
{
    reais = 0;
    centavos = 0;
}

Dinheiro::~Dinheiro()
{

}

unsigned Dinheio::getReais()
{
    return reais;
}

unsigned Dinheio::getCentavos()
{
    return centavos;
}

void Dinheio::setCentavos(unsigned int centavos)
{
    (*this).centavos = centavos;
}

void Dinheio::setReais(unsigned int reais)
{
    (*this).reais = reais;
}