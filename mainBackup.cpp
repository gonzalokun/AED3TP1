#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstring>

//Comentar linea: ctrl-shift-c, descomentar: ctrl-shift-x

//Todo el código se encuentra en el mismo archivo
//para facilitar lectura/localizacion del código

//Código de Input/Output (IO)
std::pair<int, std::vector<int> > handleInput2(){
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

std::pair<int, std::vector<int> > handleInput(char* ar){
    int cantElem, valorObjetivo;
    std::vector<int> conjunto;

    //std::ifstream archivo("input.txt");
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

//Vamos probando con todo hasta encontrar uno que vaya

//Devuelve el menor entre a y b, pero si uno es negativo devuelve el otro
int minimoPositivo(int a, int b){ //O(1)
    if(a < 0)
        return b;
    if(b < 0)
        return a;

    return (a < b)? a : b;
}

//Función recursiva que resuelve el backtracking
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
            //Corte De Factibilidad, como esta ordenado el conjunto seguir por esta rama nunca puede dar la solucion
            return -1;
        }
        else if(sumActual == sumActual + conjuntoInicial[inicio]){
            //El elemento que sigue es un cero, conviene no incluirlo en el conjunto asi no aumenta la cardinalidad
            return subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual, sumActual);
        }
        else{
            //
            //if(sumActual < 0)
                //sumActual = 0;

            return minimoPositivo(subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual + 1, sumActual + conjuntoInicial[inicio]), subsetSumBTRec(conjuntoInicial, valorObjetivo, inicio + 1, longActual, sumActual));
        }
    }
}

int subsetSumBacktracking(std::vector<int>& conjuntoInicial, int valorObjetivo){//O(2^n) Explicar con dibujo!!!
    //Ordeno el conjunto
    std::sort(conjuntoInicial.begin(), conjuntoInicial.end()); //n*log(n) (REVISAR)

    //subsetSumBTRec(conjuntoInicial, valorObjetivo, 0, 0, -1); Si sumar 0 en un conjunto sin numeros no es vólido
    return subsetSumBTRec(conjuntoInicial, valorObjetivo, 0, 0, 0); //O(algo)
}

//Fin código BT

///////////////////////////////////////////////////////////////////////////////////

//Código de Programación Dinámica (PD)

//Version Top Down

int subsetSumPDTDRec(std::vector<int>& conjuntoInicial, int i, int j, std::vector<std::vector<int> > &matriz){

    //std::cout << "Entre con: i = " << i << ", j = " << j << std::endl;

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
            //matriz[i][j] = (conjuntoInicial[i] == j) ? 1 : -1;
            if(j == 0){
                matriz[i][j] = 0;
            }
            else{
                matriz[i][j] = (conjuntoInicial[i] == j) ? 1 : -1;
            }
            return matriz[i][j];
        }
    }

    //Induccion
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

        //std::cout << "PONGO EN LA MATRIZ EL VALOR " << matriz[i][j] << std::endl;

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

    //subsetSumPDTDRec(conjuntoInicial, conjuntoInicial.size() - 1, valorObjetivo, matriz);

    /*
    std::cout << std::endl;

    std::cout << "DEBUG - Imprimiendo Matriz" << std::endl;

    for(int i = 0; i < conjuntoInicial.size(); i++){

        for(int j = 0; j < valorObjetivo + 1; j++){
            std::cout << matriz[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    */

    //return matriz[conjuntoInicial.size() - 1][valorObjetivo];
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
            //matriz[i][j] = (m1 == -1 && m2 == -1)? -1 : (minimoPositivo(m1, m2) + 1);
            if(minimoPositivo(m1, m2) == m1){
                matriz[i][j] = m1;
            }
            else{
                matriz[i][j] = m2 + 1;
            }
        }
    }

    return matriz[conjuntoInicial.size() - 1][valorObjetivo];

    /*
    std::cout << std::endl;

    std::cout << "DEBUG - Imprimiendo Matriz" << std::endl;

    for(int i = 0; i < conjuntoInicial.size(); i++){

        for(int j = 0; j < valorObjetivo + 1; j++){
            std::cout << matriz[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    */

    //return matriz[conjuntoInicial.size() - 1][valorObjetivo];
}

//Fin código PD

int main(int argc, char** argv)
{
    std::cout << "------------------------AED3TP1------------------------" << std::endl;
    std::pair<int, std::vector<int> > entrada;
    //entrada = handleInput2();
    if(strcmp(argv[1], "") == 0){
        std::cout << "Error al leer archivo!" << std::endl;
        return 0;
    }

    entrada = handleInput(argv[1]);

    std::cout << "Valor Objetivo: " << entrada.first << std::endl;
    std::cout << "Tam. Conjunto: " << entrada.second.size() << std::endl;
//    std::cout << "Conjunto: {";
//    for(int i = 0; i < entrada.second.size(); i++){
//        std::cout << entrada.second[i] << ((i == entrada.second.size()-1)?"":", ");
//    }
//    std::cout << "}" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;

    int resultadoFB = -1, resultadoBT = -1, resultadoPDTD = -1, resultadoPDBU = -1;

    //*/
    std::cout << "Resolviendo con Fuerza Bruta" << std::endl;

    //auto ahora = std::chrono::_V2::high_resolution_clock::now();
    auto ahora = std::chrono::_V2::steady_clock::now();
    //resultadoFB = subsetSumFuerzaBruta(entrada.second, entrada.first);
    resultadoFB = -10;
    auto fin = std::chrono::_V2::steady_clock::now();

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoFB << std::endl;

    auto duracion1 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);


    std::cout << "El Algoritmo de Fuerza Bruta tardo: " << duracion1.count() << " milisegundos" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;
    //*/

    //*/
    std::cout << "Resolviendo con Backtracking" << std::endl;

     //auto ahora = std::chrono::_V2::steady_clock::now();
    ahora = std::chrono::_V2::steady_clock::now();
    //resultadoBT = subsetSumBacktracking(entrada.second, entrada.first);
    resultadoBT = -10;
    //auto fin = std::chrono::_V2::steady_clock::now();
    fin = std::chrono::_V2::steady_clock::now();

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoBT << std::endl;

    auto duracion2 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);

    std::cout << "El Algoritmo de Backtracking tardo: " << duracion2.count() << " milisegundos" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;

    //*/

    std::cout << "Resolviendo con Programancion Dinamica (Algoritmo Top Down)" << std::endl;

    //auto ahora = std::chrono::_V2::steady_clock::now();
    ahora = std::chrono::_V2::steady_clock::now();

    resultadoPDTD = subsetSumPDTD(entrada.second, entrada.first);

    //auto fin = std::chrono::_V2::steady_clock::now();
    fin = std::chrono::_V2::steady_clock::now();

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoPDTD << std::endl;

    auto duracion3 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);

    std::cout << "El Algoritmo de Prog. Dinamica (Top Down) tardo: " << duracion3.count() << " milisegundos" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;

    std::cout << "Resolviendo con Programancion Dinamica (Algoritmo Bottom Up)" << std::endl;

    //auto ahora = std::chrono::_V2::steady_clock::now();
    ahora = std::chrono::_V2::steady_clock::now();
    resultadoPDBU = subsetSumPDBU(entrada.second, entrada.first);
    //auto fin = std::chrono::_V2::steady_clock::now();
    fin = std::chrono::_V2::steady_clock::now();

    std::cout << "Tam. de conjunto minimo que suma " << entrada.first << ": " << resultadoPDBU << std::endl;

    auto duracion4 = std::chrono::duration_cast<std::chrono::milliseconds>(fin - ahora);
    //auto duracion4 = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - ahora);

    std::cout << "El Algoritmo de Prog. Dinamica (Bottom Up) tardo: " << duracion4.count() << " milisegundos" << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;

    //Escritura de output en archivo

    std::ofstream salida("output.csv", std::ios::app);

    //salida << entrada.second.size() << std::endl;
    //salida << entrada.first << std::endl;
    //salida << std::endl;
    salida << entrada.second.size() << "," << entrada.first << ",";
    //salida << duracion1.count() << ","; //<< std::endl;
    //salida << duracion2.count() << ","; //<< std::endl;
    salida << 0 << ","; //<< std::endl;
    salida << 0 << ","; //<< std::endl;
    salida << duracion3.count() << ","; //<< std::endl;
    salida << duracion4.count() << std::endl;
    //salida << entrada.second.size() << " " << entrada.first << " " << duracion2.count() << std::endl;
    //salida << entrada.second.size() << " " << entrada.first << " " << duracion3.count() << std::endl;
    //salida << entrada.second.size() << " " << entrada.first << " " << duracion4.count() << std::endl;
    //salida << "------------------------------" <<std::endl;

    salida.close();
    return 0;
}
