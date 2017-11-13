
#include "Produto.h"


using namespace std;

//Métodos básicos da classe Produto

Produto::Produto(int Codigo,char * Nome, Dinheiro PrecoCusto, double MargemLucro, Dinheiro ImpostoMunicipal)
{
    //construtor inicia o objeto com os parâmetros recebidos
    (*this).Codigo = Codigo;
    (*this).Nome = new char[ strlen(Nome)];
    strcpy((*this).Nome,Nome);
    (*this).PrecoCusto = PrecoCusto;
    (*this).MargemLucro = MargemLucro;
    (*this).ImpostoMunicipal = ImpostoMunicipal;
}

Produto::Produto()
{
    //cout << "Construtor sem parametro" <<endl;
    //chama-se o construtor com parametros já criado
    char * nome = new char[50];
    strcpy(nome," ");
    Dinheiro impostoMunicipal(0,0);
    Dinheiro precoCusto(0,0);

    (*this).Codigo = -1;
    (*this).Nome = new char[ strlen(nome)];
    strcpy((*this).Nome,nome);
    (*this).PrecoCusto = impostoMunicipal;
    (*this).MargemLucro = 0;
    (*this).ImpostoMunicipal = ImpostoMunicipal;
}

Produto::~Produto()
{
    delete [] Nome;
}

Produto::Produto(Produto &p)
{
    (*this).Codigo = p.Codigo;
    (*this).Nome = new char[ strlen(p.Nome)];
    strcpy((*this).Nome,p.Nome);
    (*this).PrecoCusto = p.PrecoCusto;
    (*this).MargemLucro = p.MargemLucro;
    (*this).ImpostoMunicipal = p.ImpostoMunicipal;
}

Dinheiro Produto::getPrecoCusto() const
{
    return PrecoCusto;
}

Dinheiro Produto::getImpostoMunicipal() const
{
    return ImpostoMunicipal;
}

Dinheiro Produto::getPrecoVenda() const
{
    //como a margem de lucro é dada em porcentagem %
    //devemos multipĺicar PrecoCusto por (1+margemLucro) para acrescentar
    //o valor da margem de lucro no dinheiro retornado
    Dinheiro PrecoVenda(PrecoCusto * (1+(MargemLucro/100)));
    return PrecoVenda;
}

const char * Produto::getNome() const
{
    return Nome;
}

double Produto::getMargemLucro() const
{
    return MargemLucro;
}

int Produto::getCodigo() const
{
    return Codigo;
}

Produto leProdutoDoTeclado()
{
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
    cin >> centavos >> aux >> reais;
    impostoMunicipal.setCentavos(centavos);
    impostoMunicipal.setReais(reais);

    //cria o produto com os valores obtidos do teclado
    Produto p(codigo,nome,precoCusto,margemLucro,impostoMunicipal);

    return p; // retorna os produtos
}


//sobrecarga de operadores
ostream & operator<<(ostream & os,const Produto & p)
{
    os << "Codigo: " << p.getCodigo()<<endl;
    os << "Nome: "<<p.getNome()<<endl;
    os<< "Preco de custo: " << p.getPrecoCusto() <<endl;
    os<< "Margem de lucro (%) : " <<p.getMargemLucro() <<endl;
    os<<"Imposto municipal : "<<p.getImpostoMunicipal() <<endl;
    os<< "Preco de venda : " <<p.getPrecoVenda()<<endl;
    os<<endl;
    os<<"---------------------------------------------"<<endl;
    return os; 
}

Produto & Produto::operator=(const Produto p2)
{
    if(this == &p2) return *this;

    (*this).Codigo = p2.Codigo;
    (*this).Nome = new char[strlen(p2.Nome)];
    strcpy(Nome,p2.Nome);
    (*this).PrecoCusto = p2.PrecoCusto;
    (*this).MargemLucro = p2.MargemLucro;
    (*this).ImpostoMunicipal = p2.ImpostoMunicipal;

    return *this;
}
