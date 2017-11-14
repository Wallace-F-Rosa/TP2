
#include "GerenciadorProdutos.h"



GerenciadorProdutos::GerenciadorProdutos(int MaxProdutos)
{
    (*this).MaxProdutos = MaxProdutos;
    Lista = new Produto[MaxProdutos];
    ProdutosCadastrados = 0;

    ifstream fin;
    fin.open("dados.dat",ios::binary);

    if(fin.is_open())
    {
        //arquivo de banco de dados existe
        clog<<"Arquivo de banco de dados existente: dados.dat"<<endl;
        clog<<"Buscando produtos já cadastrados..."<<endl;
        fin.seekg(0,ios::end);
        int tamArquivo = fin.tellg();

        fin.seekg(0,ios::beg);
        //se houver produtos devemos buscá-los no arquivo
        if(tamArquivo > 0)
        {
            Produto p;
            fin.read(reinterpret_cast<char*>(&MaxProdutos),sizeof(int));
            cout << "Total de produtos : " << MaxProdutos << endl;
            fin.read(reinterpret_cast<char*>(Lista),sizeof(p)*MaxProdutos);
        }
        else
        {
            clog<<"Arquivo sem produtos!"<<endl;
        }
    }
    else
    {
        clog<<"Arquivo de armazenamento dados.dat não existe."<<endl;
        clog<<"Dados cadastrados serão armazenados ao finalizar o programa."<<endl;
    }
    fin.close();
}

GerenciadorProdutos::GerenciadorProdutos(GerenciadorProdutos &g)
{
    Lista = new Produto[g.MaxProdutos];
    MaxProdutos = g.MaxProdutos;
    ProdutosCadastrados = g.ProdutosCadastrados;
    for(int i = 0; i < g.MaxProdutos;i++)
    {
        Lista[i] = g.Lista[i];
    }
}

GerenciadorProdutos::~GerenciadorProdutos()
{
    ofstream fout;
    fout.open("dados.dat",ios::binary);

    if(!fout.is_open())
    {
        cerr << "Erro ao abrir arquivo de armazenamento dados.dat!"<<endl;
    }
    else
    {
        //clog << "Armazenando os produtos cadastrados no arquivo dados.dat..."<<endl;

        fout.write(reinterpret_cast<char*>(&MaxProdutos),sizeof(int));
       
        Produto p;
        cout << "OK" << endl;
        cout << p << endl;
        fout.write(reinterpret_cast<char*>(Lista),sizeof(p)*MaxProdutos);
        
        //clog << "Dados Armazenados com sucesso"<<endl;
    }
    //cout << "Obrigado por usar o sistema! Volte sempre (~*w*)~"<<endl;
    fout.close();
    delete [] Lista;
}

void GerenciadorProdutos::armazenaProduto(Produto &p)
{
    if(ProdutosCadastrados + 1 > MaxProdutos) return;
    
    Produto aux;
    ProdutosCadastrados++;
    //implementar busca binária
    //retorna a posição do vetor onde colocar o elemento
    //retorna -1 se o elemento já existir
    for(int i = 0; i < ProdutosCadastrados; i++)
    {
        if(Lista[i].getCodigo() == p.getCodigo())
        {
            cerr<<"Produto já cadastrado!"<<endl;
            return;
        }
        //substitui o produto na posição devida e da um "backspace" no resto da lista para mantê-la ordenada
        if(Lista[i].getCodigo() ==-1 ||  (Lista[i].getCodigo() > p.getCodigo()))
        {
            aux = Lista[i];
            Lista[i] = p;
            p = aux;
        }
    }   
}

void GerenciadorProdutos::removeProduto(int codigo)
{
    if(codigo <= 0)
    { 
        //tetar remover produto com código inválido
        cerr << "Produto inexistente!"<<endl;
        return;
    }
    int i;
    Produto aux; // Produto vazio
    for( i = 0; i < ProdutosCadastrados;i++) // procura o produto
    {
        if(codigo == Lista[i].getCodigo())
        {
            Lista[i] = aux; //apaga o produto colocando um produto vazio no lugar
            break;
        }
    }
    //reordena o resto da lista para mante-la em ordem crescente
    for(; i < ProdutosCadastrados-1;i++)
    {
        aux = Lista[i];
        Lista[i] = Lista[i+1];
        Lista[i+1] = aux;
    }
        
    ProdutosCadastrados--;
}

void GerenciadorProdutos::removeTodosProdutos()
{
    delete [] Lista;
    Lista = new Produto[MaxProdutos];
}

Produto GerenciadorProdutos::getProduto(int codigo) const
{
    cout<<endl;
    for(int i = 0; i < ProdutosCadastrados;i++)
    {
        if(codigo == Lista[i].getCodigo())
            return Lista[i];
    }

    Produto p;
    return p;
}

Produto GerenciadorProdutos::getIesimoProduto(int i) const
{
    if(i >= ProdutosCadastrados)
    { 
        //mensagem de erro ao informar uma posição inválida, negativa ou maior que o tamanho do vetor
        cerr << "O "<<i<<"-esimo produto nao existe" <<endl;
        Produto p;
        return p;
    }

    for(int j = 0; j < ProdutosCadastrados; j++)
    {
        if(j == i)
            return Lista[j];
    }
}

int GerenciadorProdutos::getNumProdutosCadastrados() const
{
    return ProdutosCadastrados; 
}

void GerenciadorProdutos::leProdutoDoTeclado(Produto &p)
{
    cout<<endl;
    //le um produto a patir de valores digitados no teclado e o retorna
    int codigo;
    char * nome = new char[50];
    Dinheiro precoCusto;
    double margemLucro;
    Dinheiro impostoMunicipal;
    unsigned int centavos, reais;

    char aux;

    cout << "Digite o codigo do produto : ";
    cin >> codigo;

    cout << "Digite o nome do produto : ";
    cin.ignore();
    cin.getline(nome,49);
            
    cout << "Digite o preco do produto, separando os centavos com virgula( Ex : 1,00) : ";
    cin >> reais >> aux >> centavos;
    precoCusto.setCentavos(centavos);
    precoCusto.setReais(reais);

    cout << "Digite a margem de lucro do produto (%) : "<<endl;
    cin >> margemLucro;

    cout << "Digite o valor do imposto municipal( Ex : 1,00) : ";
    cin >> reais >> aux >>centavos ;
    impostoMunicipal.setCentavos(centavos);
    impostoMunicipal.setReais(reais);

    //cria o produto com os valores obtidos do teclado
    Produto p1(codigo,nome,precoCusto,margemLucro,impostoMunicipal);

    p = p1;

}

void GerenciadorProdutos::listarProdutos() const
{
    cout<<endl;
    if(ProdutosCadastrados == 0)
    {
        cout << "Nao ha produtos cadastrados!"<<endl;
        return;
    }
    for(int i = 0; i < ProdutosCadastrados; i++)
    {
        cout << Lista[i] <<endl;
    }
}

