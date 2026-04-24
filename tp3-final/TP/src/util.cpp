#include "util.h"
#include <cctype>
#include <sstream>
#include <cmath>

static inline void Trocar_Inteiros(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}

static inline void Trocar_Resultados(Resultado_Distancia &a, Resultado_Distancia &b) {
	Resultado_Distancia t = a;
	a = b;
	b = t;
}

void Converter_Maiusculo(std::string &texto) {
	for (size_t i = 0; i < texto.size(); ++i) {
		unsigned char c = static_cast<unsigned char>(texto[i]);
		texto[i] = static_cast<char>(std::toupper(c));
	}
}

void Dividir_Por_PontoEVirgula(const std::string &linha, std::string campos[], int maxCampos, int &qtde) {
	qtde = 0;
	std::string atual;
	for (size_t i = 0; i <= linha.size(); ++i) {
		if (i == linha.size() || linha[i] == ';') {
			if (qtde < maxCampos) {
				campos[qtde++] = atual;
			}
			atual.clear();
		} else {
			atual.push_back(linha[i]);
		}
	}
}

void Dividir_Por_Espaco(const std::string &linha, std::string palavras[], int maxPalavras, int &qtde) {
	qtde = 0;
	std::string atual;
	for (size_t i = 0; i <= linha.size(); ++i) {
		if (i == linha.size() || linha[i] == ' ') {
			if (!atual.empty()) {
				if (qtde < maxPalavras) {
					palavras[qtde++] = atual;
				}
				atual.clear();
			}
		} else {
			atual.push_back(linha[i]);
		}
	}
}

double Calcular_Distancia_Euclidiana(double x1, double y1, double x2, double y2) {
	double dx = x1 - x2;
	double dy = y1 - y2;
	return std::sqrt(dx * dx + dy * dy);
}

static int Particionar_Inteiros(int *valores, int inicio, int fim) {
	int pivo = valores[fim];
	int i = inicio - 1;
	for (int j = inicio; j < fim; ++j) {
		if (valores[j] <= pivo) {
			++i;
			Trocar_Inteiros(valores[i], valores[j]);
		}
	}
	Trocar_Inteiros(valores[i + 1], valores[fim]);
	return i + 1;
}

void Ordenar_Inteiros(int *valores, int inicio, int fim) {
	if (inicio < fim) {
		int p = Particionar_Inteiros(valores, inicio, fim);
		Ordenar_Inteiros(valores, inicio, p - 1);
		Ordenar_Inteiros(valores, p + 1, fim);
	}
}

void Ordenar_Inteiros(int *valores, int tamanho) {
	if (tamanho > 1) {
		Ordenar_Inteiros(valores, 0, tamanho - 1);
	}
}

static int Comparar_Resultados(const Resultado_Distancia &a, const Resultado_Distancia &b) {
	if (a.distancia < b.distancia) return -1;
	if (a.distancia > b.distancia) return 1;
	if (a.idLog < b.idLog) return -1;
	if (a.idLog > b.idLog) return 1;
	return 0;
}

static int Particionar_Resultados(Resultado_Distancia *itens, int inicio, int fim) {
	Resultado_Distancia pivo = itens[fim];
	int i = inicio - 1;
	for (int j = inicio; j < fim; ++j) {
		if (Comparar_Resultados(itens[j], pivo) <= 0) {
			++i;
			Trocar_Resultados(itens[i], itens[j]);
		}
	}
	Trocar_Resultados(itens[i + 1], itens[fim]);
	return i + 1;
}

void Ordenar_Resultados(Resultado_Distancia *itens, int inicio, int fim) {
	if (inicio < fim) {
		int p = Particionar_Resultados(itens, inicio, fim);
		Ordenar_Resultados(itens, inicio, p - 1);
		Ordenar_Resultados(itens, p + 1, fim);
	}
}

void Ordenar_Resultados(Resultado_Distancia *itens, int tamanho) {
	if (tamanho > 1) {
		Ordenar_Resultados(itens, 0, tamanho - 1);
	}
}

bool Linha_Vazia_ou_Espacos(const std::string &s) {
	for (size_t i = 0; i < s.size(); ++i) {
		if (!std::isspace(static_cast<unsigned char>(s[i]))) return false;
	}
	return true;
}

void Normalizar_Linha(std::string &s) {
	// Remove BOM UTF-8 se presente no início
	if (s.size() >= 3 &&
		static_cast<unsigned char>(s[0]) == 0xEF &&
		static_cast<unsigned char>(s[1]) == 0xBB &&
		static_cast<unsigned char>(s[2]) == 0xBF) {
		s.erase(0, 3);
	}
	// Remove CR (\r) no final, se houver
	while (!s.empty()) {
		char c = s.back();
		if (c == '\r' || c == '\n') {
			s.pop_back();
		} else {
			break;
		}
	}
}


