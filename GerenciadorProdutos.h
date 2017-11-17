#ifndef GERENCIADORPRODUTOS_H
#define GERENCIADORPRODUTOS_H

#include "Produto.h"
#include <fstream>


class GerenciadorProdutos
{
    private:
        int MaxProdutos;
        int ProdutosCadastrados;
        Produto * Lista;
        
    public:
        GerenciadorProdutos(int MaxProdutos);
        GerenciadorProdutos(GerenciadorProdutos & g);
        ~GerenciadorProdutos();
        void armazenaProduto(Produto &p);
        void removeProduto(int codigo);
        void removeTodosProdutos();
        Produto getProduto(int codigo) const;
        Produto getIesimoProduto(int i) const;
        int getNumProdutosCadastrados() const;
        void leProdutoDoTeclado(Produto &p);
        void listarProdutos() const;

        friend int pesquisaBinaria(Produto * p, int inicio, int fim, int chave);

};

#endif