#ifndef LOGRADOURO_H
#define LOGRADOURO_H

#include <string>

struct Logradouro {
	int idLog;
	std::string nome;
	double somaLat;
	double somaLong;
	int quantidade;
};

class Tabela_Logradouros {
public:
	Tabela_Logradouros();
	~Tabela_Logradouros();

	// Retorna true se for um logradouro novo (primeira inserção do idLog)
	bool Inserir_ou_Acumulador(int idLog, const std::string &nome, double lat, double lon);
	bool Obter_Centro(int idLog, double &latMed, double &lonMed) const;
	const std::string* Obter_Nome(int idLog) const;

private:
	struct Entrada {
		int id;
		Logradouro dado;
		bool ocupado;
	};

	Entrada *tabela;
	int capacidade;
	int tamanho;

	unsigned int Hash(int chave) const;
	void Redimensionar();
	int Encontrar_Posicao(int chave) const;
	int Encontrar_Posicao_Insercao(int chave) const;
};

#endif


