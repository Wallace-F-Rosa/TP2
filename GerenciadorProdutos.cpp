
#include "GerenciadorProdutos.h"



GerenciadorProdutos::GerenciadorProdutos(int MaxProdutos)
{
    (*this).MaxProdutos = MaxProdutos;
    Lista = new Produto[(*this).MaxProdutos];
    ProdutosCadastrados = 0;

    //construtor chamado, devemos carregar dados anteriormente salvos, se existirem
    ifstream fin;
    //abre o arquivo de entrada em "modo binário"
    fin.open("dados.dat",ios::binary);

    //checa se o arquivo está aberto
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
            fin.read(reinterpret_cast<char*>(&ProdutosCadastrados),sizeof(int));
            
            //se o usuário solicitar um numero maximo de produtos menor do que o que já estava armazenado
            if(ProdutosCadastrados > MaxProdutos)
            {
                char opcao;
                while(true)
                {
                    //perguntamos ao usuário se ele quer carregar todos os produtos armazenados ou somente a quantidade informada
                    cout << "Ha "<<ProdutosCadastrados << " produtos armazenados mas foi solicitado um numero maximo de "<<MaxProdutos << " produto(s)" <<endl;
                    cout << "Deseja carregar todos os produtos ou continuar com "<<MaxProdutos << " prouduto(s)?(os produtos excedentes serão excluidos)"<<endl;
                    cout << "(s = sim/ n = nao)"<<endl;
                    cin >> opcao;
                    if(opcao == 's')
                    {
                        break;
                    }
                    else if(opcao == 'n')
                    {
                        break;
                    }
                    else
                        cerr << "Opcao inválida!" <<endl;
                }
                //efetuamos a opcao informada
                if(opcao == 'n')
                    ProdutosCadastrados = MaxProdutos;
                else
                {
                    //se o usuário quiser carregar todos os produtos anteriormente armazenados, perguntamos se ele deseja carregar mais produtos
                    MaxProdutos = ProdutosCadastrados;
                    cout << "Deseja aumentar a quantidade de produtos armazenados?(Se sim informe o numero de produtos a aumentar, se nao digite um numero menor ou igual a zero) : "<<endl;
                    int max;
                    cin >> max;
                    if(max > 0)
                       MaxProdutos += max;

                    (*this).MaxProdutos = MaxProdutos;
                    delete [] Lista;
                    Lista = new Produto[(*this).MaxProdutos];
                }
            }
            //entrada de dados
            for(int i = 0; i < ProdutosCadastrados;i++)
            {
                //criamos variaveis para os dados anteriormente salvos
                int codigo;
                char * nome = new char[50];
                Dinheiro precoC;
                double margemL;
                Dinheiro impostoM;

                //carregamos os dados propriamente ditos
                fin.read(reinterpret_cast<char*>(&codigo),sizeof(int));
                fin.read(reinterpret_cast<char*>(nome),sizeof(char)*50);
                fin.read(reinterpret_cast<char*>(&precoC),sizeof(Dinheiro));
                fin.read(reinterpret_cast<char*>(&margemL),sizeof(double));
                fin.read(reinterpret_cast<char*>(&impostoM),sizeof(Dinheiro));

                //criamos o produto referente aos dados armazenados
                Produto p(codigo,nome,precoC,margemL,impostoM);
                
                //armazenamos o produto no vetor
                Lista[i] = p;

                delete [] nome;
            }
            clog << ProdutosCadastrados << " produtos foram carregados."<<endl;    
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
    //construtor de cópia
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
    //destrutor chamado, deve-se salvar os produtos cadastrados
    
    ofstream fout;
    //abre o arquivo em "modo binário"
    fout.open("dados.dat",ios::binary);

    //checa se o arquivo esta aberto
    if(!fout.is_open())
    {
        cerr << "Erro ao abrir arquivo de armazenamento dados.dat!"<<endl;
    }
    else
    {
        //se sim, inicia o armazenamento dos dados
        clog << "Armazenando os produtos cadastrados no arquivo dados.dat..."<<endl;

        //armazena-se a quantidade de produtos cadastrados
        fout.write(reinterpret_cast<char*>(&ProdutosCadastrados),sizeof(int));

        //armazena os produtos em si
        for(int i = 0; i < ProdutosCadastrados;i++)
        {   
            //quebrando os dados do produto em variaveis
            int codigo = Lista[i].getCodigo();
            char * nome = new char[50];
            strcpy(nome,Lista[i].getNome());
            Dinheiro precoC = Lista[i].getPrecoCusto();
            double margemL = Lista[i].getMargemLucro();
            Dinheiro impostoM = Lista[i].getImpostoMunicipal();
            
            //armazenando os dados do produto no arquivo
            fout.write(reinterpret_cast<char*>(&codigo),sizeof(int));
            fout.write(reinterpret_cast<char*>(nome),sizeof(char)*50);
            fout.write(reinterpret_cast<char*>(&precoC),sizeof(Dinheiro));
            fout.write(reinterpret_cast<char*>(&margemL),sizeof(double));
            fout.write(reinterpret_cast<char*>(&impostoM),sizeof(Dinheiro));

            //libera memória para novo nome
            delete [] nome;
        }
        clog << "Produtos cadastrados : "<<ProdutosCadastrados <<endl;
        clog << "Dados Armazenados com sucesso!"<<endl;
    }
    //dados armazenados, fecha o arquivo e limpa a memória
    cout << "Obrigado por usar o sistema! Volte sempre (~*w*)~"<<endl;
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
        if((Lista[i].getCodigo() ==-1 && p.getCodigo() != -1) ||  (Lista[i].getCodigo() > p.getCodigo()))
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
    ProdutosCadastrados = 0;
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

