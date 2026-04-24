#ifndef PALAVRA_H
#define PALAVRA_H

#include <string>

class Lista_Inteiros {
public:
	Lista_Inteiros();
	~Lista_Inteiros();
	Lista_Inteiros(const Lista_Inteiros &outro);
	Lista_Inteiros& operator=(const Lista_Inteiros &outro);

	void Adicionar_Sem_Duplicata(int valor);
	void Ordenar();
	int Tamanho() const;
	const int* Dados() const;

private:
	int *dados;
	int tamanho;
	int capacidade;
	void Garantir_Capacidade(int novaCap);
};

struct No_AVL {
	std::string chave;
	Lista_Inteiros lista;
	int altura;
	No_AVL *esq;
	No_AVL *dir;
	No_AVL(const std::string &c);
};

class Arvore_Palavras {
public:
	Arvore_Palavras();
	~Arvore_Palavras();

	void Inserir(const std::string &palavra, int idLog);
	const Lista_Inteiros* Buscar(const std::string &palavra) const;
	void Ordenar_Todas_Listas();

private:
	No_AVL *raiz;

	static int Altura(No_AVL *n);
	static int Fator_Balanceamento(No_AVL *n);
	static void Atualizar_Altura(No_AVL *n);
	static No_AVL* Rotacao_Direita(No_AVL *y);
	static No_AVL* Rotacao_Esquerda(No_AVL *x);
	static No_AVL* Inserir_Interno(No_AVL *no, const std::string &chave, int idLog);
	static No_AVL* Buscar_Interno(No_AVL *no, const std::string &chave);
	static void Ordenar_Listas_Interno(No_AVL *no);
	static void Destruir(No_AVL *no);
};

#endif


