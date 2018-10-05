#Generamos un input, lo pasamos al programa y se tiene que generar un output
import subprocess
import random

#Crea inputs y genera un Output, este se utiliza para crear tests con V fijo
#Inserta elemAInsertar en el conjunto, tiene que ser un numero
def generarOutputsExp1(valorObjetivo, tamConjInicial, tamConjFinal, elemAInstertar, paso=1):
    #Genero un input

    for n in range(tamConjInicial, tamConjFinal + 1, paso):
        archivo = open("input.txt", "w")
        archivo.write(str(n) + " " + str(valorObjetivo) + "\n")

        for j in range(n):
            archivo.write(elemAInstertar)
            archivo.write(" ")

        archivo.close()

        #CAMBIAR "AED3TP1(CodeBlocks).exe" AL NOMBRE DEL PROGRAMA COMPILADO
        subprocess.run("AED3TP1(CodeBlocks).exe input.txt")

#Crea inputs y genera un Output, este se utiliza para crear tests con n fijo
#Inserta elemAInsertar en el conjunto
def generarOutputsExp2(TamConjunto, valorObjetivoInicial, valorObjetivoFinal, elemAInstertar, paso=1):

    for n in range(valorObjetivoInicial, valorObjetivoFinal + 1, paso):
        archivo = open("input.txt", "w")
        archivo.write(str(TamConjunto) + " " + str(n) + "\n")

        for j in range(TamConjunto):
            archivo.write(elemAInstertar)
            archivo.write(" ")

        archivo.close()

        #CAMBIAR "AED3TP1(CodeBlocks).exe" AL NOMBRE DEL PROGRAMA COMPILADO
        subprocess.run("AED3TP1(CodeBlocks).exe input.txt")

#generarOutputsExp1(valorObjetivo, tamConjInicial, tamConjFinal, elemAInsertar, paso=1)

#Ejemplo de uso
#generarOutputsExp1(6, 10, 10, "1", 1)

#generarOutputsExp2(TamConjunto, valorObjetivoInicial, valorObjetivoFinal, elemAInsertar, paso=1)