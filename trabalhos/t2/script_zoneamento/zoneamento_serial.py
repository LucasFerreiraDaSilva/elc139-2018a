import multiprocessing as mp
from subprocess import call
#import argparse
import csv
import os
from shutil import copy, move
import io
import timeit


# parser = argparse.ArgumentParser(description = 'Script para executar simulações para as as 25 regiões')

# ai = af = di = df = None

# parser.add_argument('-ai', action='store', dest=ai, required=True, help='Ano inicial')
# parser.add_argument('-af', action='store', dest=af, required=True, help='Ano final')
# parser.add_argument('-di', action='store', dest=di, required=True, help='Dia inicial')
# parser.add_argument('-df', action='store', dest=df, required=True, help='Dia final')

#parser.add_argument('-m', action='store', dest=m, required=True, help='Caminho do modelo')
#parser.add_argument('-fp', action='store', dest=fp, required=True, help='Caminho dos arquivos')

#arg = parser.parse_args()

anoInicial = 1990
anoFinal = 2015
diaInicial = 1
diaFinal = 100

cultivarType = 1
cultivar = 1
emergence = False

#modelpath = str(arg.m)
#filespath = str(arg.fp)

def phenogladAlert(table, data, column):
    # colunas do arquivo
    tmin = 3
    tmax = 4
    dvs = 7

    # Freezing temperature reached: Crop killed by frost = 3
    c = 0
    for l in table[1:]:
        if ((float(l[tmin-1]) < -2.0) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.0)):
            c+=1
        else:
            c=0
    if ((c > 3) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.0)):
        return ";3"

    # Spike dead by frost = 2
    c = 0
    for l in table[1:]:
        if ((float(l[tmin-1]) > -2.0) and (float(l[tmin-1]) < 3.0) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.64)):
            c+=1
        else:
            c=0

    for l in table[1:]:
        if ((float(l[tmin-1]) <= -2.0) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.64)):
            return ";2"

    if ((c > 3) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.64)):
        return ";2"

    # Risk of severe burning of  florets = 1
    c = 0
    for l in table[1:]:
        if((float(l[tmax-1]) >= 34) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.8) and (float(l[dvs-1]) <= 1.05)):
            c+=1
        else:
            c=0
    if ((c >= 3) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.8) and (float(l[dvs-1]) <= 1.05)):
        return ";1"

    c = 0
    for l in table[1:]:
        if((float(l[tmax-1]) >= 34) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 1.05) and (float(l[dvs-1]) <= 2.9)):
            c+=1
        else:
            c=0
    if ((c >= 3) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 1.05) and (float(l[dvs-1]) <= 2.9)):
        return ";1"

    # Crop killed by heat. = 4
    c = 0
    for l in table[1:]:
        if ((float(l[tmax-1]) > 48) and (float(l[column-1]) <= data) and (float(l[dvs-1]) >= 0.0)):
            return ";4"

    return ""

def executeParallelYears(data):

    filespath = os.path.join(data[2], "files")
    valEmerge = str(emergence).upper()

    param = str(cultivarType)+'\n'+str(cultivar)+'\n'+str(valEmerge)+'\n'+str(data[1])+'\n'+str(data[0])+'\n'
    paramFile = os.path.join(filespath, str(data[1])+"param.txt")
    parameters = open(paramFile, 'w')
    parameters.write(param)
    parameters.close
    parameters = open(paramFile, 'rb')

    os.chdir(data[2])

    call("./PhenoGlad", stdin=parameters)

    os.rename(filespath+'/'+str(data[1])+'result.txt', filespath+'/'+format(data[0], '03')+'/'+str(data[1])+'result.txt')
    os.remove(filespath+'/'+str(data[1])+"param.txt")

def executeSimulations(local):
    filespath = os.path.join(local, "files")
    for dia in range(int(diaInicial), int(diaFinal)+1):
        os.makedirs(filespath+"/"+format(dia, '03'), exist_ok=True)

        for ano in range(int(anoInicial), int(anoFinal)+1):
            valEmerge = str(emergence).upper()

            param = str(cultivarType)+'\n'+str(cultivar)+'\n'+str(valEmerge)+'\n'+str(ano)+'\n'+str(dia)+'\n'
            paramFile = os.path.join(filespath, str(ano)+"param.txt")
            parameters = open(paramFile, 'w')
            parameters.write(param)
            parameters.close
            parameters = open(paramFile, 'rb')

            os.chdir(local)

            call("./PhenoGlad", stdin=parameters)

            os.rename(filespath+'/'+str(ano)+'result.txt', filespath+'/'+format(dia, '03')+'/'+str(ano)+'result.txt')
            os.remove(filespath+'/'+str(ano)+'param.txt')

def filterResults(local):
    directory = os.path.join(local, "files")
    simulation = True
    non_silent = True
    result_header = 1
    value_header = 7
    data = 1.0

    table = []
    resultFilter = []

    dayDirs = [d for d in os.listdir(directory) if os.path.isdir(os.path.join(directory, d))]
    dayDirs.sort()

    for day in dayDirs:
        dirDay = os.path.join(directory, day)
        yearFiles = os.listdir(dirDay)
        yearFiles.sort()
        resultYear = []
        resultYear.append(str(day))
        resultYear.append(str(int(day)))

        for yearFile in yearFiles:
            filtered = ""
            table = []
            with open(os.path.join(dirDay, yearFile), "r") as f:
                for line in f:
                    table.append(line.split())

            for l in table[1:]:
                if float(l[value_header-1]) >= data:
                    filtered = str(l[result_header-1])
                    break
            if filtered == "":
                filtered = "NONE"

            resultYear.append(filtered + phenogladAlert(table, data, value_header))

        resultFilter.append(resultYear)

    resultFile = [list(x) for x  in zip(*resultFilter)]

    with open(os.path.join(directory, "filtered.txt"), 'w') as f:
        writer = csv.writer(f, dialect="excel-tab")
        for row in resultFile:
            writer.writerow(row)

def countAlerts(locals, absolutPath):
    for local in locals:
        filteredFile = 'resultados/'+str(local)+'/files/filtered.txt'
        years = []
        with open(filteredFile) as filtered:
            for row in csv.reader(filtered, dialect="excel-tab"):
                years.append(row)
        finalCont = {}
        for day in range(diaFinal):
            sum_1 = sum_2 = sum_3 = sum_4 = 0
            for year in years:
                if (';' in year[day]):
                    num = int((year[day].split(';'))[1])
                    if (num == 1):
                        sum_1 += 1
                    elif (num == 2):
                        sum_2 += 1
                    elif (num == 3):
                        sum_3 += 1
                    elif (num == 4):
                        sum_4 += 1

            contDay = []
            contDay.append(sum_1)
            contDay.append(sum_2)
            contDay.append(sum_3)
            contDay.append(sum_4)

            finalCont[str(day+1)] = contDay

        with open("resultados/"+str(local)+"/alertas.txt", 'w') as f:
            writer = csv.writer(f, dialect="excel-tab")
            writer.writerow(["Dia", "Alerta 1", "Alerta 2", "Alerta 3", "Alerta 4"])

            for d in range(diaFinal):
                finalCont[str(d+1)].insert(0,(d+1))
                writer.writerow(finalCont[str(d+1)])

def runAutomation():
    locals = list(d.strip('.txt') for d in os.listdir('meteorologicFiles'))
    os.makedirs('resultados', exist_ok=True)
    scriptHome = os.getcwd()
    #sum_tsimulation = 0.0
    #sum_tfilter = 0.0

    for local in locals:
        os.makedirs('resultados/'+str(local), exist_ok=True)
        os.makedirs('resultados/'+str(local)+'/files', exist_ok=True)
        copy('meteorologicFiles/'+str(local)+'.txt', 'resultados/'+str(local)+'/files/meteorologicFile.txt')
        filesPath = 'resultados/'+str(local)+'/'
        copy('executaveis/PhenoGlad', filesPath)

        absolutPath = os.path.join(os.getcwd(),filesPath)
        # Execucao das simulacoes do modelo
        #ts_start = timeit.default_timer()
        print("Executando simulações...")
        executeSimulations(absolutPath)
        #ts_finish = timeit.default_timer()
        #sum_tsimulation += ts_finish - ts_start

        # Filtragem dos dados
        print("Filtrando dados...")
        #tf_start = timeit.default_timer()
        filterResults(absolutPath)
        #tf_finish = timeit.default_timer()
        #sum_tfilter += tf_finish - tf_start
        os.chdir(scriptHome)

    #print("[SIMUL]:%f" % (sum_tsimulation))
    #print("[FILTER]:%f" % (sum_tfilter))

    # Contagem de alertas
    #tcount_s = timeit.default_timer()
    print("Contando alertas...")
    countAlerts(locals, os.getcwd())
    #tcount_f = timeit.default_timer()
    #print("[CONT]:%f" % (tcount_f - tcount_s))

#ttotal_s = timeit.default_timer()
runAutomation()
#ttotal_f = timeit.default_timer()

print("Processo finalizado!")

#print("[TOTAL]:%f" % (ttotal_f - ttotal_s))
