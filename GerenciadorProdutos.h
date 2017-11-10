#ifndef GERENCIADORPRODUTOS_H
#define GERENCIADORPRODUTOS_H

#include "Produto.h"

class GerenciadorProdutos
{
    private:
        int MaxProdutos;
        int ProdutosCadastrados;
        Produto * Lista;
        
    public:
        GerenciadorProdutos(int MaxProdutos);
        ~GerenciadorProdutos();
        void armazenaProduto(Produto &p);
        void removeProduto(int codigo);
        void removeTodosProdutos();
        Produto getProduto(int codigo) const;
        Produto getIesimoProduto(int i) const;
        int getNumProdutosCadastrados() const;
};

#endif