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
int subsetSumFuerzaBruta(std::vector<int> conjuntoInicial, int valorObjetivo){//O(n*(2^n))
    //std::vector<std::vector<int> > conjuntoPartes;
    unsigned long contador;
    unsigned long tamFinal = pow(2, conjuntoInicial.size());

    //bool existe = false;
    int longMin = -1;

    //Acá pasamos por todos los conjuntos del conjunto partes
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
            //Corte De Factibilidad, como esta ordenado el conjunto seguir por esta rama nunca puede dar la solucion
            return -1;
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

    //subsetSumBTRec(conjuntoInicial, valorObjetivo, 0, 0, -1); Si sumar 0 en un conjunto sin numeros no es válido
    return subsetSumBTRec(conjuntoInicial, valorObjetivo, 0, 0, 0); //O(algo)
}

//Fin código BT

///////////////////////////////////////////////////////////////////////////////////

//Código de Programación Dinámica (PD)

//Version Top Down

int subsetSumPDTDRec(std::vector<int>& conjuntoInicial, int i, int j, std::vector<std::vector<int>>& matriz){

    //Casos Base

    if(i < 0){
        return -1;
    }

    if(j < 0){
        return -1;
    }

    if(i == 0){
        matriz[i][j] = (conjuntoInicial[i] == j) ? 1 : -1;
        return matriz[i][j];
    }

    if(j == 0){
        matriz[i][j] = 0;
        return matriz[i][j];
    }

    //Induccion

    int m1 = subsetSumPDTDRec(conjuntoInicial, i-1, j, matriz);
    int m2 = subsetSumPDTDRec(conjuntoInicial, i-1, j - conjuntoInicial[i], matriz);

    if(m1 == -1 && m2 == -1){
        matriz[i][j] = -1;
    }
    else{
        matriz[i][j] = minimoPositivo(m1, m2) + 1;
    }

    return matriz[i][j];
}

int subsetSumPDTD(std::vector<int>& conjuntoInicial, int valorObjetivo){
    std::vector<std::vector<int>> matriz (conjuntoInicial.size(), std::vector<int>(valorObjetivo + 1));

    for(int i = 0; i < conjuntoInicial.size(); i++){
        for(int j = 0; j < valorObjetivo; j++){
            matriz[i][j] = -10; //Valor arbitrario que indica que no hay nada guardado en [i][j]
        }
    }

    //
}

//Version Bottom Up

int subsetSumPDBU(){
    //
}

//Esta puede no hacer falta
int subsetSumPDBURec(){
    //
}

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
