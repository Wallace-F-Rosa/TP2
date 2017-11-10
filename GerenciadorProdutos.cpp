
#include "GerenciadorProdutos.h"

GerenciadorProdutos::GerenciadorProdutos(int MaxProdutos)
{
    (*this).MaxProdutos = MaxProdutos;
    Lista = new Produto[MaxProdutos];
    ProdutosCadastrados = 0;
}

GerenciadorProdutos::~GerenciadorProdutos()
{
    delete [] Lista;
}

void GerenciadorProdutos::armazenaProduto(Produto &p)
{
    if(ProdutosCadastrados + 1 > MaxProdutos) return;

    Produto aux;
    ProdutosCadastrados++;
    for(int i = 0; i < ProdutosCadastrados; i++)
    {
        if(Lista[i].getCodigo() > p.getCodigo())
        {
            aux = Lista[i];
            Lista[i] = p;
            p = aux;
        }
    }   
}

void GerenciadorProdutos::removeTodosProdutos()
{
    delete [] Lista;
    Lista = new Produto[MaxProdutos];
}

Produto GerenciadorProdutos::getProduto(int codigo) const
{
    for(int i = 0; i < ProdutosCadastrados;i++)
    {
        if(codigo == Lista[i].getCodigo())
            return Lista[i];
    }

    return Produto();
}

int GerenciadorProdutos::getNumProdutosCadastrados() const
{
    return ProdutosCadastrados; 
}

