#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>

struct Resultado_Distancia {
	int idLog;
	double distancia;
};

void Converter_Maiusculo(std::string &texto);
void Dividir_Por_PontoEVirgula(const std::string &linha, std::string campos[], int maxCampos, int &qtde);
void Dividir_Por_Espaco(const std::string &linha, std::string palavras[], int maxPalavras, int &qtde);
double Calcular_Distancia_Euclidiana(double x1, double y1, double x2, double y2);

void Ordenar_Inteiros(int *valores, int inicio, int fim);
void Ordenar_Inteiros(int *valores, int tamanho);
void Ordenar_Resultados(Resultado_Distancia *itens, int inicio, int fim);
void Ordenar_Resultados(Resultado_Distancia *itens, int tamanho);

bool Linha_Vazia_ou_Espacos(const std::string &s);
void Normalizar_Linha(std::string &s);

#endif


