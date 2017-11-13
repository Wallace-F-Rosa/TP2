all: main.exe

main.exe: Dinheiro.o Produto.o GerenciadorProdutos.o main.o 
	g++  main.o Dinheiro.o Produto.o GerenciadorProdutos.o -o main.exe

GerenciadorProdutos.o: GerenciadorProdutos.h GerenciadorProdutos.cpp
	g++ -c GerenciadorProdutos.cpp 

Produto.o: Produto.h Produto.cpp
	g++ -c Produto.cpp 

Dinheiro.o: Dinheiro.h Dinheiro.cpp
	g++ -c Dinheiro.cpp  
	
main.o: main.cpp Dinheiro.h Produto.h GerenciadorProdutos.h
	g++ -c main.cpp 