#include <iostream>

using namespace std;

#include "GerenciadorProdutos.h"

int main()
{
    Dinheiro mTeste(0,0);
    Dinheiro iTeste(0,0);
    Produto teste(1,"teste",mTeste,5,iTeste);
    cout << teste <<endl;
    return 0;
}