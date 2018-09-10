#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

//Comentar linea: ctrl-shift-c, descomentar: ctrl-shift-x

//Todo el código se encuentra en el mismo archivo
//para facilitar lectura/localizacion del código

//Código de Input/Output (IO)
std::pair<int, std::vector<int> > handleInput(){
    int cantElem, valorObjetivo;
    std::vector<int> conjunto;

    std::cout << "Ingrese la cantidad de valores y el valor objetivo:" << std::endl;
    std::cin >> cantElem;
    std::cin >> valorObjetivo;

    //std::cout << "cantElem: " << cantElem << std::endl;
    //std::cout << "valorObjetivo: " << valorObjetivo << std::endl;

    for(int i = 0; i < cantElem; i++){
        int num;
        std::cin >> num;
        conjunto.push_back(num);
    }

    return std::make_pair(valorObjetivo, conjunto);
}
//Fin código IO

//Código de Fuerza Bruta (FB)

//Resuelvo el problema pasando por todos los conjuntos del conjunto partes
int subsetSumFuerzaBruta(std::vector<int> conjuntoInicial, int valorObjetivo){
    //std::vector<std::vector<int> > conjuntoPartes;
    unsigned long contador;
    unsigned long tamFinal = pow(2, conjuntoInicial.size());

    //bool existe = false;
    int longMin = -1;

    //Acá pasamos por todos los conjuntos del conjunto partes
    for(contador = 0; contador <= tamFinal; contador++){
        int sumaTotal = 0;
        int longActual = 0;

        //Me fijo el valor binario de contador, donde los 1 equivalen
        //a incluir el elemento en el conjunto solucion
        for(int elem = 0; elem < conjuntoInicial.size(); elem++){
            if(contador & (1 << elem)){
                //El valor va en la solucion
                sumaTotal += conjuntoInicial[elem];
                longActual++;
            }
        }

        //Ya tengo la suma de un intento de solucion
        if(sumaTotal == valorObjetivo){
            if(longMin < 0){
                longMin = longActual;
            }
            else if(longMin > longActual){
                longMin = longActual;
            }
        }

    }

    //Ahora longMin es la cardinal más chica los conjuntos que suman valorObjetivo
    return longMin;
}

//Fin código FB

//Código de Backtracking (BT)

//Vamos probando con todo hasta encontrar uno que vaya

//Devuelve el menor entre a y b, pero si uno es negativo devuelve el otro
int minimoPositivo(int a, int b){
    if(a < 0)
        return b;
    if(b < 0)
        return a;

    return (a < b)? a : b;
}

//Funcion recursiva que resuelve el backtracking
int subsetSumBTRec(std::vector<int>& conjuntoInicial, int valorObjetivo, int inicio, int longActual, int sumActual){
    if(inicio == conjuntoInicial.size()){
        if(sumActual == valorObjetivo){
            return longActual;
        }
        else{
            return -1;
        }
    }
    else{
        if(sumActual == valorObjetivo){
            return minimoPositivo(longActual, subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio, longActual - 1, sumActual - conjuntoInicial[inicio - 1]));
        }
        else if(sumActual > valorObjetivo){
            return -1;
        }
        else{
            if(sumActual < 0)
                sumActual = 0;

            return minimoPositivo(subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual + 1, sumActual + conjuntoInicial[inicio]), subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual, sumActual));
        }
    }
}

int subsetSumBacktracking(std::vector<int>& conjuntoInicial, int valorObjetivo){
    //Ordeno el conjunto
    std::sort(conjuntoInicial.begin(), conjuntoInicial.end());
    //int res = subsetSumBTRec(conjuntoInicial, valorObjetivo, 0, 0, 0);
    //return (res == 0) ? -1 : res;

    return subsetSumBTRec(conjuntoInicial, valorObjetivo, 0, 0, -1);
}

//Suma los elementos de conjunto de la siguiente forma:
//Primero suma posInicial y despues a eso le suma los
//elementos de conjunto empezando desde sumaDesde hasta
//sumaHasta
//int sumarSalteando(std::vector<int> conjunto, int posInicial, int sumaDesde, int sumaHasta){
//    int suma = 0;
//    suma += conjunto[posInicial];
//
//    //Empieza por salto
//    for(int elem = sumaDesde; elem < sumaHasta && elem < conjunto.size(); elem++){
//        suma += conjunto[elem];
//    }
//
//    return suma;
//}

//Fin código BT

//Código de Programación Dinámica (PD)
//Fin código PD

int main()
{
    std::cout << "--------------------AED3TP1--------------------" << std::endl;
    std::pair<int, std::vector<int> > entrada;
    entrada = handleInput();

    std::cout << "Valor Objetivo: " << entrada.first << std::endl;
    std::cout << "Conjunto: {";
    for(int i = 0; i < entrada.second.size(); i++){
        std::cout << entrada.second[i] << ((i == entrada.second.size()-1)?"":", ");
    }
    std::cout << "}" << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    int resultadoFB = -1, resultadoBT = -1, resultadoPD = -1;

    //AGREGAR LOS CLOCKS PARA MEDIR TIEMPO
    std::cout << "Resolviendo con Fuerza Bruta" << std::endl;
    resultadoFB = subsetSumFuerzaBruta(entrada.second, entrada.first);
    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoFB << std::endl;

        std::cout << "-----------------------------------------------" << std::endl;

    std::cout << "Resolviendo con Backtracking" << std::endl;
    resultadoBT = subsetSumBacktracking(entrada.second, entrada.first);
    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoBT << std::endl;
    return 0;
}
