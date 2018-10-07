import io

def procesarComp1():
    archivo = io.open("output.csv")
    salida = io.open("outputComp.csv", "w")

    lines = archivo.readlines()

    for i in range(len(lines)):
        if i == 0:
            salida.write(lines[i])
        else:
            lineAr = lines[i].split(",")
            stringFinal = ""
            for j in range(len(lineAr)):
                if j == 2:
                    calc = int(lineAr[0])*(2**int(lineAr[0]))
                    calc = (int(lineAr[j]) / calc)
                    stringFinal += str(calc) + ","
                else:
                    stringFinal += lineAr[j] + ("," if (j < len(lineAr)-1) else "")
            
            salida.write(stringFinal)

    archivo.close()

def procesarComp2():
    archivo = io.open("output.csv")
    salida = io.open("outputComp.csv", "w")

    lines = archivo.readlines()

    for i in range(len(lines)):
        if i == 0:
            salida.write(lines[i])
        else:
            lineAr = lines[i].split(",")
            stringFinal = ""
            for j in range(len(lineAr)):
                if j == 3:
                    calc = int(lineAr[0])*(2**int(lineAr[0]))
                    calc = (int(lineAr[j]) / calc)
                    stringFinal += str(calc) + ","
                else:
                    stringFinal += lineAr[j] + ("," if (j < len(lineAr)-1) else "")
            
            salida.write(stringFinal)

    archivo.close()

def procesarComp3():
    archivo = io.open("output.csv")
    salida = io.open("outputComp.csv", "w")

    lines = archivo.readlines()

    for i in range(len(lines)):
        if i == 0:
            salida.write(lines[i])
        else:
            lineAr = lines[i].split(",")
            stringFinal = ""
            for j in range(len(lineAr)):
                if j == 4:
                    calc = int(lineAr[0])*(int(lineAr[1]))
                    calc = (int(lineAr[j]) / calc)
                    stringFinal += str(calc) + ","
                else:
                    stringFinal += lineAr[j] + ("," if (j < len(lineAr)-1) else "")
            
            salida.write(stringFinal)

    archivo.close()

def procesarComp4():
    archivo = io.open("output.csv")
    salida = io.open("outputComp.csv", "w")

    lines = archivo.readlines()

    for i in range(len(lines)):
        if i == 0:
            salida.write(lines[i])
        else:
            lineAr = lines[i].split(",")
            stringFinal = ""
            for j in range(len(lineAr)):
                if j == 5:
                    calc = int(lineAr[0])*(int(lineAr[1]))
                    calc = (int(lineAr[j]) / calc)
                    stringFinal += str(calc) + "\n"
                else:
                    stringFinal += lineAr[j] + ("," if (j < len(lineAr)-1) else "")
            
            salida.write(stringFinal)

    archivo.close()

#procesarComp1()
#procesarComp2()
#procesarComp3()
procesarComp4()
