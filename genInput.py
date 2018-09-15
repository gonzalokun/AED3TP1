#Generamos un input, lo pasamos al programa y se tiene que poner en el output

import subprocess
import random

def genInput():
    #Genero un input
    valorObjetivo = 20

    for n in range(5, 26):
        archivo = open("input.txt", "w")
        archivo.write(str(n) + " " + str(valorObjetivo) + "\n")
        #print("VALOR N:" + str(n))
        for j in range(n):
            #print("VALOR J: " + str(j))
            archivo.write(str(random.randint(0, 50)))
            if j != n-1:
                archivo.write(" ")

        #Corre el programa del TP
        subprocess.run("E:/Proyectos/AED3TP1/bin/Debug/AED3TP1(CodeBlocks).exe")

genInput()