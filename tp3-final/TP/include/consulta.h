#ifndef CONSULTA_H
#define CONSULTA_H

#include <string>
#include <iostream>
#include "palavra.h"
#include "logradouro.h"
#include "util.h"

class Motor_Consultas {
public:
	Motor_Consultas(Tabela_Logradouros *tabela, Arvore_Palavras *indice);
	void Processar_Consulta(int idConsulta, const std::string &consulta, double latOrigem, double lonOrigem, int maxRespostas, std::ostream &saida);

private:
	Tabela_Logradouros *tabela;
	Arvore_Palavras *indice;

	Lista_Inteiros Intersectar_Listas(const Lista_Inteiros* const* listas, int qtdeListas);
};

#endif


