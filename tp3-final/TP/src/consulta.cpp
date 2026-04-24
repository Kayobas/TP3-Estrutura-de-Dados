#include "consulta.h"

Motor_Consultas::Motor_Consultas(Tabela_Logradouros *t, Arvore_Palavras *i) {
	tabela = t;
	indice = i;
}

Lista_Inteiros Motor_Consultas::Intersectar_Listas(const Lista_Inteiros* const* listas, int qtdeListas) {
	Lista_Inteiros resultado;
	if (qtdeListas <= 0) return resultado;
	// Escolher a menor lista como base
	int idxMenor = 0;
	int tamMenor = listas[0]->Tamanho();
	for (int i = 1; i < qtdeListas; ++i) {
		int t = listas[i]->Tamanho();
		if (t < tamMenor) {
			tamMenor = t;
			idxMenor = i;
		}
	}
	const Lista_Inteiros *base = listas[idxMenor];
	const int *dadosBase = base->Dados();
	int tamBase = base->Tamanho();

	for (int b = 0; b < tamBase; ++b) {
		int candidato = dadosBase[b];
		bool presente = true;
		for (int j = 0; j < qtdeListas; ++j) {
			if (j == idxMenor) continue;
			// busca binária em listas[j]
			const int *dados = listas[j]->Dados();
			int tam = listas[j]->Tamanho();
			int esq = 0, dir = tam - 1;
			bool achou = false;
			while (esq <= dir) {
				int m = (esq + dir) / 2;
				if (dados[m] == candidato) {
					achou = true;
					break;
				} else if (dados[m] < candidato) {
					esq = m + 1;
				} else {
					dir = m - 1;
				}
			}
			if (!achou) {
				presente = false;
				break;
			}
		}
		if (presente) {
			resultado.Adicionar_Sem_Duplicata(candidato);
		}
	}
	return resultado;
}

void Motor_Consultas::Processar_Consulta(int idConsulta, const std::string &consulta, double latOrigem, double lonOrigem, int maxRespostas, std::ostream &saida) {
	// separar palavras da consulta
	const int MAX_PALAVRAS = 64;
	std::string palavras[MAX_PALAVRAS];
	int qPalavras = 0;
	std::string consultaMaius = consulta;
	Converter_Maiusculo(consultaMaius);
	Dividir_Por_Espaco(consultaMaius, palavras, MAX_PALAVRAS, qPalavras);

	// obter listas de cada palavra
	const Lista_Inteiros* listas[MAX_PALAVRAS];
	int qListas = 0;
	for (int i = 0; i < qPalavras; ++i) {
		const Lista_Inteiros *lst = indice->Buscar(palavras[i]);
		if (lst == NULL) {
			// nenhuma ocorrência -> zero resultados
			saida << idConsulta << ";" << 0 << "\n";
			return;
		}
		listas[qListas++] = lst;
	}

	// interseção
	Lista_Inteiros inter = Intersectar_Listas(listas, qListas);
	int totalCandidatos = inter.Tamanho();

	if (totalCandidatos == 0) {
		saida << idConsulta << ";" << 0 << "\n";
		return;
	}

	// calcular distâncias
	int limite = totalCandidatos < maxRespostas ? totalCandidatos : maxRespostas;
	Resultado_Distancia *resultados = new Resultado_Distancia[totalCandidatos];
	const int *ids = inter.Dados();
	for (int i = 0; i < totalCandidatos; ++i) {
		int idLog = ids[i];
		double lat, lon;
		if (!tabela->Obter_Centro(idLog, lat, lon)) {
			lat = 0.0; lon = 0.0;
		}
		resultados[i].idLog = idLog;
		resultados[i].distancia = Calcular_Distancia_Euclidiana(latOrigem, lonOrigem, lat, lon);
	}

	// ordenar por distância (e id como desempate)
	Ordenar_Resultados(resultados, totalCandidatos);

	saida << idConsulta << ";" << limite << "\n";
	for (int i = 0; i < limite; ++i) {
		const std::string *nome = tabela->Obter_Nome(resultados[i].idLog);
		if (nome) {
			saida << resultados[i].idLog << ";" << *nome << "\n";
		} else {
			saida << resultados[i].idLog << ";" << "" << "\n";
		}
	}

	delete [] resultados;
}


