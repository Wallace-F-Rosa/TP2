#ifndef PRODUTO_H
#define PRODUTO_H

#include "Dinheiro.h"
#include <cstring>
#include <iostream>

class Produto
{
    private:
    int Codigo;
    char * Nome;
    Dinheiro PrecoCusto;
    double MargemLucro;
    Dinheiro ImpostoMunicipal;
    
    public:
    Produto(int Codigo, char * Nome, Dinheiro PrecoCusto, double MargemLucro, Dinheiro ImpostoMunicipal);
    Produto();
    ~Produto();
    Produto(Produto &p);
    Dinheiro getPrecoCusto() const;
    Dinheiro getPrecoVenda() const;
    int getCodigo() const;
    const char * getNome() const;
    double getMargemLucro() const;
    Produto & operator=(const Produto p2);
    friend ostream & operator<<(ostream & os, const Produto & p);
};

#endif