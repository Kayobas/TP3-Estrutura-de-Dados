#include "logradouro.h"
#include <cstring>

Tabela_Logradouros::Tabela_Logradouros() {
	capacidade = 1024;
	tamanho = 0;
	tabela = new Entrada[capacidade];
	for (int i = 0; i < capacidade; ++i) {
		tabela[i].id = -1;
		tabela[i].ocupado = false;
	}
}

Tabela_Logradouros::~Tabela_Logradouros() {
	delete [] tabela;
}

unsigned int Tabela_Logradouros::Hash(int chave) const {
	// Multiplicative hashing
	unsigned int x = static_cast<unsigned int>(chave);
	return (x * 2654435761u) % static_cast<unsigned int>(capacidade);
}

int Tabela_Logradouros::Encontrar_Posicao(int chave) const {
	unsigned int idx = Hash(chave);
	for (int i = 0; i < capacidade; ++i) {
		int pos = static_cast<int>((idx + i) % static_cast<unsigned int>(capacidade));
		if (!tabela[pos].ocupado) return -1;
		if (tabela[pos].id == chave) return pos;
	}
	return -1;
}

int Tabela_Logradouros::Encontrar_Posicao_Insercao(int chave) const {
	unsigned int idx = Hash(chave);
	for (int i = 0; i < capacidade; ++i) {
		int pos = static_cast<int>((idx + i) % static_cast<unsigned int>(capacidade));
		if (!tabela[pos].ocupado || tabela[pos].id == chave) return pos;
	}
	return -1;
}

void Tabela_Logradouros::Redimensionar() {
	int capacidade_antiga = capacidade;
	Entrada *antiga = tabela;
	capacidade = capacidade * 2;
	tabela = new Entrada[capacidade];
	for (int i = 0; i < capacidade; ++i) {
		tabela[i].id = -1;
		tabela[i].ocupado = false;
	}
	for (int i = 0; i < capacidade_antiga; ++i) {
		if (antiga[i].ocupado) {
			int id = antiga[i].id;
			unsigned int idx = Hash(id);
			for (int j = 0; j < capacidade; ++j) {
				int pos = static_cast<int>((idx + j) % static_cast<unsigned int>(capacidade));
				if (!tabela[pos].ocupado) {
					tabela[pos] = antiga[i];
					break;
				}
			}
		}
	}
	delete [] antiga;
}

bool Tabela_Logradouros::Inserir_ou_Acumulador(int idLog, const std::string &nome, double lat, double lon) {
	if ((tamanho + 1) * 10 >= capacidade * 7) {
		Redimensionar();
	}
	int pos = Encontrar_Posicao(idLog);
	if (pos >= 0) {
		// Existe: acumular
		tabela[pos].dado.somaLat += lat;
		tabela[pos].dado.somaLong += lon;
		tabela[pos].dado.quantidade += 1;
		return false;
	}
	// Inserir novo
	int posIns = Encontrar_Posicao_Insercao(idLog);
	if (posIns < 0) return false; // não deve ocorrer
	tabela[posIns].id = idLog;
	tabela[posIns].ocupado = true;
	tabela[posIns].dado.idLog = idLog;
	tabela[posIns].dado.nome = nome;
	tabela[posIns].dado.somaLat = lat;
	tabela[posIns].dado.somaLong = lon;
	tabela[posIns].dado.quantidade = 1;
	tamanho += 1;
	return true;
}

bool Tabela_Logradouros::Obter_Centro(int idLog, double &latMed, double &lonMed) const {
	int pos = Encontrar_Posicao(idLog);
	if (pos < 0) return false;
	const Logradouro &L = tabela[pos].dado;
	if (L.quantidade <= 0) return false;
	latMed = L.somaLat / static_cast<double>(L.quantidade);
	lonMed = L.somaLong / static_cast<double>(L.quantidade);
	return true;
}

const std::string* Tabela_Logradouros::Obter_Nome(int idLog) const {
	int pos = Encontrar_Posicao(idLog);
	if (pos < 0) return NULL;
	return &tabela[pos].dado.nome;
}


