#include "palavra.h"
#include "util.h"

Lista_Inteiros::Lista_Inteiros() {
	dados = NULL;
	tamanho = 0;
	capacidade = 0;
}

Lista_Inteiros::~Lista_Inteiros() {
	delete [] dados;
}

Lista_Inteiros::Lista_Inteiros(const Lista_Inteiros &outro) {
	tamanho = outro.tamanho;
	capacidade = outro.capacidade;
	if (capacidade > 0) {
		dados = new int[capacidade];
		for (int i = 0; i < tamanho; ++i) dados[i] = outro.dados[i];
	} else {
		dados = NULL;
	}
}

Lista_Inteiros& Lista_Inteiros::operator=(const Lista_Inteiros &outro) {
	if (this == &outro) return *this;
	delete [] dados;
	tamanho = outro.tamanho;
	capacidade = outro.capacidade;
	if (capacidade > 0) {
		dados = new int[capacidade];
		for (int i = 0; i < tamanho; ++i) dados[i] = outro.dados[i];
	} else {
		dados = NULL;
	}
	return *this;
}

void Lista_Inteiros::Garantir_Capacidade(int novaCap) {
	if (novaCap <= capacidade) return;
	int nova = capacidade == 0 ? 4 : capacidade * 2;
	while (nova < novaCap) nova *= 2;
	int *novo = new int[nova];
	for (int i = 0; i < tamanho; ++i) novo[i] = dados[i];
	delete [] dados;
	dados = novo;
	capacidade = nova;
}

void Lista_Inteiros::Adicionar_Sem_Duplicata(int valor) {
	for (int i = 0; i < tamanho; ++i) {
		if (dados[i] == valor) return;
	}
	Garantir_Capacidade(tamanho + 1);
	dados[tamanho++] = valor;
}

void Lista_Inteiros::Ordenar() {
	if (tamanho > 1) {
		Ordenar_Inteiros(dados, tamanho);
	}
}

int Lista_Inteiros::Tamanho() const {
	return tamanho;
}

const int* Lista_Inteiros::Dados() const {
	return dados;
}

No_AVL::No_AVL(const std::string &c) : chave(c), lista(), altura(1), esq(NULL), dir(NULL) {}

Arvore_Palavras::Arvore_Palavras() {
	raiz = NULL;
}

Arvore_Palavras::~Arvore_Palavras() {
	Destruir(raiz);
}

int Arvore_Palavras::Altura(No_AVL *n) {
	return n ? n->altura : 0;
}

int Arvore_Palavras::Fator_Balanceamento(No_AVL *n) {
	return n ? Altura(n->esq) - Altura(n->dir) : 0;
}

void Arvore_Palavras::Atualizar_Altura(No_AVL *n) {
	if (n) {
		int ae = Altura(n->esq);
		int ad = Altura(n->dir);
		n->altura = (ae > ad ? ae : ad) + 1;
	}
}

No_AVL* Arvore_Palavras::Rotacao_Direita(No_AVL *y) {
	No_AVL *x = y->esq;
	No_AVL *T2 = x->dir;
	x->dir = y;
	y->esq = T2;
	Atualizar_Altura(y);
	Atualizar_Altura(x);
	return x;
}

No_AVL* Arvore_Palavras::Rotacao_Esquerda(No_AVL *x) {
	No_AVL *y = x->dir;
	No_AVL *T2 = y->esq;
	y->esq = x;
	x->dir = T2;
	Atualizar_Altura(x);
	Atualizar_Altura(y);
	return y;
}

No_AVL* Arvore_Palavras::Inserir_Interno(No_AVL *no, const std::string &chave, int idLog) {
	if (!no) {
		No_AVL *novo = new No_AVL(chave);
		novo->lista.Adicionar_Sem_Duplicata(idLog);
		return novo;
	}
	if (chave < no->chave) {
		no->esq = Inserir_Interno(no->esq, chave, idLog);
	} else if (chave > no->chave) {
		no->dir = Inserir_Interno(no->dir, chave, idLog);
	} else {
		no->lista.Adicionar_Sem_Duplicata(idLog);
		return no;
	}
	Atualizar_Altura(no);
	int fb = Fator_Balanceamento(no);
	if (fb > 1 && chave < no->esq->chave) {
		return Rotacao_Direita(no);
	}
	if (fb < -1 && chave > no->dir->chave) {
		return Rotacao_Esquerda(no);
	}
	if (fb > 1 && chave > no->esq->chave) {
		no->esq = Rotacao_Esquerda(no->esq);
		return Rotacao_Direita(no);
	}
	if (fb < -1 && chave < no->dir->chave) {
		no->dir = Rotacao_Direita(no->dir);
		return Rotacao_Esquerda(no);
	}
	return no;
}

void Arvore_Palavras::Inserir(const std::string &palavra, int idLog) {
	raiz = Inserir_Interno(raiz, palavra, idLog);
}

No_AVL* Arvore_Palavras::Buscar_Interno(No_AVL *no, const std::string &chave) {
	if (!no) return NULL;
	if (chave < no->chave) return Buscar_Interno(no->esq, chave);
	if (chave > no->chave) return Buscar_Interno(no->dir, chave);
	return no;
}

const Lista_Inteiros* Arvore_Palavras::Buscar(const std::string &palavra) const {
	No_AVL *no = Buscar_Interno(raiz, palavra);
	if (!no) return NULL;
	return &no->lista;
}

void Arvore_Palavras::Ordenar_Listas_Interno(No_AVL *no) {
	if (!no) return;
	Ordenar_Listas_Interno(no->esq);
	no->lista.Ordenar();
	Ordenar_Listas_Interno(no->dir);
}

void Arvore_Palavras::Ordenar_Todas_Listas() {
	Ordenar_Listas_Interno(raiz);
}

void Arvore_Palavras::Destruir(No_AVL *no) {
	if (!no) return;
	Destruir(no->esq);
	Destruir(no->dir);
	delete no;
}


