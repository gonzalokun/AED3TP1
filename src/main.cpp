#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstring>
#define CANTREP 4

//Todo el código se encuentra en el mismo archivo
//para facilitar lectura/localizacion del código

//Código de Input/Output (IO)
std::pair<int, std::vector<int> > handleInput(char* ar){
    int cantElem, valorObjetivo;
    std::vector<int> conjunto;
    std::ifstream archivo(ar);

    archivo >> cantElem;
    archivo >> valorObjetivo;

    for(int i = 0; i < cantElem; i++){
        int elem;
        archivo >> elem;
        conjunto.push_back(elem);
    }

    archivo.close();

    return std::make_pair(valorObjetivo, conjunto);
}

//Fin código IO

//Código de Fuerza Bruta (FB)

//Resuelvo el problema pasando por todos los conjuntos del conjunto partes
int subsetSumFuerzaBruta(std::vector<int> conjuntoInicial, int valorObjetivo){//O(n*(2^n))
    //std::vector<std::vector<int> > conjuntoPartes;
    unsigned long contador;
    unsigned long tamFinal = pow(2, conjuntoInicial.size());

    //bool existe = false;
    int longMin = -1;

    //Acó pasamos por todos los conjuntos del conjunto partes
    for(contador = 0; contador <= tamFinal; contador++){//O(2^n)
        int sumaTotal = 0;
        int longActual = 0;

        //Me fijo el valor binario de contador, donde los 1 equivalen
        //a incluir el elemento en el conjunto solucion
        for(int elem = 0; elem < conjuntoInicial.size(); elem++){//O(n)
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

///////////////////////////////////////////////////////////////////////////////////

//Código de Backtracking (BT)

//Devuelve el menor entre a y b, pero si uno es negativo devuelve el otro
int minimoPositivo(int a, int b){ //O(1)
    if(a < 0)
        return b;
    if(b < 0)
        return a;

    return (a < b)? a : b;
}

//Función recursiva que resuelve el backtracking
int subsetSumBTRec(std::vector<int>& conjuntoInicial, int valorObjetivo, int inicio, int longActual, int sumActual, int& tamMejorSol){
    if(inicio == conjuntoInicial.size()){
        if(sumActual == valorObjetivo){
            tamMejorSol = minimoPositivo(tamMejorSol, longActual);
            return longActual;
        }
        else{
            return -1;
        }
    }
    else{
        if(tamMejorSol != -1 && longActual >= tamMejorSol){
            //Poda de optimalidad, si el tamaño actual es mas grande que el mejor que encontramos, se sale de la función
            return -1;
        }

        if(sumActual == valorObjetivo){
            tamMejorSol = minimoPositivo(tamMejorSol, longActual);
            return minimoPositivo(longActual, subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio, longActual - 1, sumActual - conjuntoInicial[inicio - 1], tamMejorSol));
        }
        else if(sumActual > valorObjetivo){
            //Corte De Factibilidad, como esta ordenado el conjunto seguir por esta rama nunca puede dar la solucion
            return -1;
        }
        else if(sumActual == sumActual + conjuntoInicial[inicio]){
            //El elemento que sigue es un cero, conviene no incluirlo en el conjunto asi no aumenta la cardinalidad
            return subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual, sumActual, tamMejorSol);
        }
        else{
            return minimoPositivo(subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual + 1, sumActual + conjuntoInicial[inicio], tamMejorSol), subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual, sumActual, tamMejorSol));
        }
    }
}

int subsetSumBacktracking(std::vector<int>& conjuntoInicial, int valorObjetivo){//O(2^n)
    //Ordeno el conjunto
    std::sort(conjuntoInicial.begin(), conjuntoInicial.end()); //n*log(n)
    int tamMejorSol = -1;
    return subsetSumBTRec(conjuntoInicial, valorObjetivo, 0, 0, 0, tamMejorSol); //O(2^n)
}

//Fin código BT

///////////////////////////////////////////////////////////////////////////////////

//Código de Programación Dinámica (PD)

//Version Top Down

int subsetSumPDTDRec(std::vector<int>& conjuntoInicial, int i, int j, std::vector<std::vector<int> > &matriz){
    //Casos Base

    if(i < 0){
        return -1;
    }

    if(j < 0){
        return -1;
    }

    if(j == 0){
        if(matriz[i][j] != -10){
            return matriz[i][j];
        }
        else{
            matriz[i][j] = 0;
            return matriz[i][j];
        }
    }

    if(i == 0){
        if(matriz[i][j] != -10){
            return matriz[i][j];
        }
        else{
            if(j == 0){
                matriz[i][j] = 0;
            }
            else{
                matriz[i][j] = (conjuntoInicial[i] == j) ? 1 : -1;
            }
            return matriz[i][j];
        }
    }

    //Inducción
    if(matriz[i][j] != -10){
        return matriz[i][j];
    }
    else{
        int m1 = subsetSumPDTDRec(conjuntoInicial, i-1, j, matriz);
        int m2 = subsetSumPDTDRec(conjuntoInicial, i-1, j - conjuntoInicial[i], matriz);

        if(m1 == -1 && m2 == -1){
            matriz[i][j] = -1;
        }
        else{
            if(minimoPositivo(m1, m2) == m1){
                matriz[i][j] = m1;
            }
            else{
                matriz[i][j] = m2 + 1;
            }
        }

        return matriz[i][j];
    }
}

int subsetSumPDTD(std::vector<int> &conjuntoInicial, int valorObjetivo){
    std::vector<std::vector<int> > matriz (conjuntoInicial.size(), std::vector<int>(valorObjetivo + 1));

    for(int i = 0; i < conjuntoInicial.size(); i++){
        for(int j = 0; j < valorObjetivo + 1; j++){
            matriz[i][j] = -10; //Valor arbitrario que indica que no hay nada guardado en [i][j]
        }
    }

    return subsetSumPDTDRec(conjuntoInicial, conjuntoInicial.size() - 1, valorObjetivo, matriz);
}

//Version Bottom Up

int subsetSumPDBU(std::vector<int>& conjuntoInicial, int valorObjetivo){
    std::vector<std::vector<int> > matriz (conjuntoInicial.size(), std::vector<int>(valorObjetivo + 1));

    for(int i = 0; i < conjuntoInicial.size(); i++){
        matriz[i][0] = 0;
    }

    for(int j = 1; j < valorObjetivo + 1; j++){
        matriz[0][j] = (conjuntoInicial[0] == j)? 1 : -1;
    }

    for(int i = 1 ; i < conjuntoInicial.size(); i++){
        for(int j = 1; j < valorObjetivo + 1; j++){
            int m1 = matriz[i - 1][j];
            int m2 = ((j - conjuntoInicial[i]) < 0)? -1 : matriz[i - 1][j - conjuntoInicial[i]];

            if(minimoPositivo(m1, m2) == m1){
                matriz[i][j] = m1;
            }
            else{
                matriz[i][j] = m2 + 1;
            }
        }
    }

    return matriz[conjuntoInicial.size() - 1][valorObjetivo];
}

//Fin código PD

int main(int argc, char** argv)
{
    std::cout << "------------------------AED3TP1------------------------" << std::endl;
    std::pair<int, std::vector<int> > entrada;
    if(strcmp(argv[1], "") == 0){
        std::cout << "Error al leer archivo!" << std::endl;
        return 0;
    }

    entrada = handleInput(argv[1]);

    std::cout << "Valor Objetivo: " << entrada.first << std::endl;
    std::cout << "Tam. Conjunto: " << entrada.second.size() << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;

    int resultadoFB = -1, resultadoBT = -1, resultadoPDTD = -1, resultadoPDBU = -1;

    std::cout << "Resolviendo con Fuerza Bruta" << std::endl;
    auto ahora = std::chrono::_V2::steady_clock::now();
    auto fin = std::chrono::_V2::steady_clock::now();
    auto duracion1 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora).count();
    duracion1 = 0;

    for(int rep = 0; rep < CANTREP;rep++){
        //
        ahora = std::chrono::_V2::steady_clock::now();
        //resultadoFB = subsetSumFuerzaBruta(entrada.second, entrada.first);
        //resultadoFB = -1;
        fin = std::chrono::_V2::steady_clock::now();

        auto temp = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);

        duracion1 += temp.count();
    }

    duracion1 /= CANTREP;
    //std::chrono::milliseconds duracion1 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoFB << std::endl;
    std::cout << "El Algoritmo de Fuerza Bruta tardo: " << duracion1 << " milisegundos" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "Resolviendo con Backtracking" << std::endl;

    //ahora = std::chrono::_V2::steady_clock::now();
    //resultadoBT = subsetSumBacktracking(entrada.second, entrada.first);
    //fin = std::chrono::_V2::steady_clock::now();
    auto duracion2 = duracion1;
    duracion2 = 0;

    for(int rep = 0; rep < CANTREP; rep++){
        ahora = std::chrono::_V2::steady_clock::now();
        //resultadoBT = subsetSumBacktracking(entrada.second, entrada.first);
        //resultadoBT = -1;
        fin = std::chrono::_V2::steady_clock::now();

        auto temp = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);

        duracion2 += temp.count();
    }

    duracion2 /= CANTREP;

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoBT << std::endl;
    std::cout << "El Algoritmo de Backtracking tardo: " << duracion2 << " milisegundos" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "Resolviendo con Programancion Dinamica (Algoritmo Top Down)" << std::endl;

    //ahora = std::chrono::_V2::steady_clock::now();
    //resultadoPDTD = subsetSumPDTD(entrada.second, entrada.first);
    //fin = std::chrono::_V2::steady_clock::now();

    auto duracion3 = duracion1;
    duracion3 = 0;

    for(int rep = 0; rep < CANTREP; rep++){
        ahora = std::chrono::_V2::steady_clock::now();
        resultadoPDTD = subsetSumPDTD(entrada.second, entrada.first);
        //resultadoPDTD = -1;
        fin = std::chrono::_V2::steady_clock::now();

        auto temp = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);

        duracion3 += temp.count();
    }

    duracion3 /= CANTREP;

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoPDTD << std::endl;
    //auto duracion3 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);
    std::cout << "El Algoritmo de Prog. Dinamica (Top Down) tardo: " << duracion3 << " milisegundos" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "Resolviendo con Programancion Dinamica (Algoritmo Bottom Up)" << std::endl;

    //ahora = std::chrono::_V2::steady_clock::now();
    //resultadoPDBU = subsetSumPDBU(entrada.second, entrada.first);
    //fin = std::chrono::_V2::steady_clock::now();

    auto duracion4 = duracion1;
    duracion4 = 0;

    for(int rep = 0; rep < CANTREP; rep++){
        ahora = std::chrono::_V2::steady_clock::now();
        resultadoPDBU = subsetSumPDBU(entrada.second, entrada.first);
        //resultadoPDBU = -1;
        fin = std::chrono::_V2::steady_clock::now();

        auto temp = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);

        duracion4 += temp.count();
    }

    duracion4 /= CANTREP;

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoPDBU << std::endl;
    //auto duracion4 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);
    std::cout << "El Algoritmo de Prog. Dinamica (Bottom Up) tardo: " << duracion4 << " milisegundos" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    //Escritura de output en archivo
    std::ofstream salida("output.csv", std::ios::app);

    salida << entrada.second.size() << "," << entrada.first << ",";
    salida << duracion1 << ",";
    salida << duracion2 << ",";
    salida << duracion3 << ",";
    salida << duracion4; //<< ",";
    //salida << resultadoFB << ",";
    //salida << resultadoBT << ",";
    //salida << resultadoPDTD << ",";
    //salida << resultadoPDTD;
    salida << std::endl;

    salida.close();
    return 0;
}
