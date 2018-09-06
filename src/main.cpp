#include <iostream>
#include <vector>
#include <math.h>

//Comentar linea: ctrl-shift-c, descomentar: ctrl-shift-x

//Todo el código se encuentra en el mismo archivo
//para facilitar lectura/localizacion del código

//Código de Input/Output (IO)
std::pair<int, std::vector<int>> handleInput(){
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
//Fin código BT

//Código de Programación Dinámica (PD)
//Fin código PD

int main()
{
    std::cout << "--------------------AED3TP1--------------------" << std::endl;
    std::pair<int, std::vector<int>> entrada;
    entrada = handleInput();

    std::cout << "Valor Objetivo: " << entrada.first << std::endl;
    std::cout << "Conjunto: [";
    for(int i = 0; i < entrada.second.size(); i++){
        std::cout << entrada.second[i] << ((i==entrada.second.size()-1)?"":", ");
    }
    std::cout << "]" << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    int resultadoFB = -1, resultadoBT = -1, resultadoPD = -1;

    //AGREGAR LOS CLOCKS PARA MEDIR TIEMPO
    std::cout << "Resolviendo con Fuerza Bruta" << std::endl;
    resultadoFB = subsetSumFuerzaBruta(entrada.second, entrada.first);
    return 0;
}
