#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include "util.h"
#include "logradouro.h"
#include "palavra.h"
#include "consulta.h"

int main(int argc, char **argv) {
	// Se um arquivo for passado como argumento, redireciona stdin para esse arquivo.
	// Mantém compatibilidade com execução via redirecionamento: ./bin/tp3.out < arquivo.txt
	if (argc > 1 && argv[1] != NULL) {
		FILE *entradaArquivo = std::freopen(argv[1], "r", stdin);
		// Se falhar, permanece lendo do stdin sem imprimir mensagens para não poluir a saída.
		(void)entradaArquivo;
	}
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	Tabela_Logradouros tabela;
	Arvore_Palavras indice;

	std::string linha;
	// Ler N
	if (!std::getline(std::cin, linha)) {
		return 0;
	}
	Normalizar_Linha(linha);
	while (Linha_Vazia_ou_Espacos(linha)) {
		if (!std::getline(std::cin, linha)) return 0;
		Normalizar_Linha(linha);
	}
	int N = 0;
	{
		std::stringstream ss(linha);
		ss >> N;
	}

	// Ler N endereços
	const int MAX_CAMPOS = 16;
	std::string campos[MAX_CAMPOS];
	for (int i = 0; i < N; ++i) {
		if (!std::getline(std::cin, linha)) {
			return 0;
		}
		Normalizar_Linha(linha);
		if (Linha_Vazia_ou_Espacos(linha)) {
			--i;
			continue;
		}
		int qtde = 0;
		Dividir_Por_PontoEVirgula(linha, campos, MAX_CAMPOS, qtde);
		if (qtde < 10) {
			// linha inválida, ignorar
			continue;
		}
		// Campos: 0 IdEnd; 1 IdLog; 2 TipoLog; 3 Log; 4 Num; 5 Bairro; 6 Regiao; 7 CEP; 8 Lat; 9 Long
		int idLog = 0;
		try {
			idLog = std::stoi(campos[1]);
		} catch (...) {
			continue;
		}
		std::string nomeLog = campos[3];
		double lat = 0.0, lon = 0.0;
		try {
			lat = std::stod(campos[8]);
			lon = std::stod(campos[9]);
		} catch (...) {
			lat = 0.0; lon = 0.0;
		}
		Converter_Maiusculo(nomeLog);
		bool novo = tabela.Inserir_ou_Acumulador(idLog, nomeLog, lat, lon);
		if (novo) {
			// alimentar índice de palavras só na primeira ocorrência do IdLog
			const int MAX_PAL = 64;
			std::string palavras[MAX_PAL];
			int q = 0;
			Dividir_Por_Espaco(nomeLog, palavras, MAX_PAL, q);
			for (int k = 0; k < q; ++k) {
				if (!palavras[k].empty()) {
					indice.Inserir(palavras[k], idLog);
				}
			}
		}
	}

	// Ler linha "M R"
	int M = 0, R = 0;
	while (true) {
		if (!std::getline(std::cin, linha)) {
			return 0;
		}
		Normalizar_Linha(linha);
		if (Linha_Vazia_ou_Espacos(linha)) continue;
		std::stringstream ss(linha);
		if ((ss >> M >> R)) break;
	}

	// Ordenar todas as listas do índice (para interseção eficiente)
	indice.Ordenar_Todas_Listas();

	std::cout << M << "\n";

	Motor_Consultas motor(&tabela, &indice);
	// Processar M consultas
	for (int i = 0; i < M; ++i) {
		if (!std::getline(std::cin, linha)) {
			break;
		}
		Normalizar_Linha(linha);
		if (Linha_Vazia_ou_Espacos(linha)) {
			--i;
			continue;
		}
		int qtde = 0;
		Dividir_Por_PontoEVirgula(linha, campos, MAX_CAMPOS, qtde);
		if (qtde < 4) {
			std::cout << "0;0\n";
			continue;
		}
		int idConsulta = 0;
		try {
			idConsulta = std::stoi(campos[0]);
		} catch (...) {
			idConsulta = 0;
		}
		std::string termos = campos[1];
		double latO = 0.0, lonO = 0.0;
		try {
			latO = std::stod(campos[2]);
			lonO = std::stod(campos[3]);
		} catch (...) {
			latO = 0.0; lonO = 0.0;
		}
		motor.Processar_Consulta(idConsulta, termos, latO, lonO, R, std::cout);
	}

	std::cout << "\n";
	return 0;
}


