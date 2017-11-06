#ifndef DINHEIRO_H
#define DINHEIRO_H

class Dinheiro
{
    private:
        unsigned int reais;
        unsigned int centavos;

    public:
        Dinheiro(unsigned int reais,unsigned int centavos);
        Dinheiro();
        ~Dinheio();
        unsigned getReais();
        unsigned getCentavos();
        void setReais(unsigned int reais);
        void setCentavos(unsigned int centavos);
};

#endif