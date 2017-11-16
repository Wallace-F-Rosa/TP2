#include <iostream>


using namespace std;

#include "GerenciadorProdutos.h"

int main()
{
    int max;
    cout <<" Digite a quantidade máxima de produtos a ser armazenada : ";
    cin >> max;

    GerenciadorProdutos g(max);

    int opcao = 0;
    cout << "===================================="<<endl;
    cout << "|                                  |"<<endl;
    cout << "|  Menu Principal:                 |"<<endl;
    cout << "|  1- Cadastrar produto            |"<<endl;
    cout << "|  2- Listar produtos              |"<<endl;
    cout << "|  3- Remover produto              |"<<endl;
    cout << "|  4- Remover todos os produtos    |"<<endl;
    cout << "|  5- Consultar produto com codigo |"<<endl;
    cout << "|  6- Sair                         |"<<endl;
    cout << "|                                  |"<<endl;
    cout << "===================================="<<endl;
    cin >> opcao;
    
    while(opcao != 6)
    {

        if(opcao == 1)
        {
            Produto p;
            g.leProdutoDoTeclado(p);
            g.armazenaProduto(p);
        }
        else if(opcao == 2)
        {
            //cout << g <<endl;
            g.listarProdutos();
        }
        else if(opcao == 3)
        {
            int codigo;
            cout << "Informe o codigo do produto que deseja remover:";
            cin >> codigo;
            g.removeProduto(codigo);
        }
        else if(opcao == 4)
        {
            g.removeTodosProdutos();
        }
        else if(opcao == 5)
        {
            int codigo;
            cout << "Informe o codigo do produto para consulta :";
            cin >> codigo;
            cout << g.getProduto(codigo);
        }
        else if(opcao == 6)
        {
            break;
        }
        else
        {
            cerr<<"Opcao invalida!"<<endl;
        }
        

        cout << endl << endl;
        cout << "===================================="<<endl;
        cout << "|                                  |"<<endl;
        cout << "|  Menu Principal:                 |"<<endl;
        cout << "|  1- Cadastrar produto            |"<<endl;
        cout << "|  2- Listar produtos              |"<<endl;
        cout << "|  3- Remover produto              |"<<endl;
        cout << "|  4- Remover todos os produtos    |"<<endl;
        cout << "|  5- Consultar produto com codigo |"<<endl;
        cout << "|  6- Sair                         |"<<endl;
        cout << "|                                  |"<<endl;
        cout << "===================================="<<endl;
        cin >> opcao;
    }

    return 0;
    
}
