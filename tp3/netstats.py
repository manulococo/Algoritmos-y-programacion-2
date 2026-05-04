#!/usr/bin/python3
from collections import deque
import sys
import funciones_grafo
from collections import deque
from grafo import Grafo

def clustering(grafo, v):
    adyacentes = grafo.adyacentes(v)
    contador = 0
    if (len(adyacentes) < 2):
        return 0.000
    for w in adyacentes:
        if (w == v): continue
        adyacentes_w = grafo.adyacentes(w)
        for x in adyacentes_w:
            if(x == w): continue
            if (x in adyacentes):
                contador += 1

    coeficiente_clustering = contador / (len(adyacentes) * (len(adyacentes) - 1))
    return round(coeficiente_clustering, 3)

def clustering_toda_la_red(grafo):
    suma_clustering = 0
    vertices = grafo.ob_vertices()
    for v in vertices:
        coeficiente = clustering(grafo, v)
        suma_clustering += coeficiente
    return round(suma_clustering / grafo.obtener_cantidad(), 3)



def conectividad(grafo, origen, diccionario_conectados):
    cfc = funciones_grafo.componentes_fuertemente_conexas(grafo, origen)
    cadena = crear_cadena_conectividad("", cfc)
    print(cadena)
    print(len(cfc))
    diccionario_conectados[origen] = cfc
    return diccionario_conectados

def todos_en_rango(grafo, origen, n):
    contador = 0
    padres, distancias = funciones_grafo.bfs(grafo, origen)
    for clave in grafo.ob_vertices():
        if(distancias[clave] == n):
            contador += 1
    print(contador)

def navegacion_por_primer_link(grafo, origen):
    cadena = origen
    cantidad = 0
    primer_link = origen
    while cantidad != 20:
        ads = grafo.adyacentes(primer_link)
        if len(ads) == 0: break
        primer_link = ads[0]
        cadena += " -> " + primer_link
        cantidad += 1
    print(cadena)

def lectura_2_am(grafo, vertices):


def diametro(grafo):
    padres_mayor, distancias_mayor = {}, {}
    mayor = 0
    padre_mayor = ""
    claves = grafo.ob_vertices()
    for clave in claves:
        padres, distancias = funciones_grafo.bfs(grafo, clave)
        for clave in claves:
            if distancias[clave] > mayor and distancias[clave] != float("inf"):
                mayor = distancias[clave]
                padre_mayor = clave
                padres_mayor = padres
                distancias_mayor = distancias
    cola = funciones_grafo.bfs_camino_minimo(padres_mayor, distancias_mayor, padre_mayor)
    cadena = convertir_cadena(cola)

    print(cadena)
    print("costo:", mayor)
    return cadena, mayor


def camino_mas_corto(grafo, origen, destino):
    padres, distancia = funciones_grafo.bfs(grafo, origen)
    cola =  funciones_grafo.bfs_camino_minimo(padres, distancia, destino)
    if not cola:
        return
    cadena = convertir_cadena(cola)

    print(cadena)
    print("costo:", distancia[destino])


def listar_operaciones():
    operaciones = ["camino", "diametro", "navegacion", "rango", "conectados", "clustering"]
    print(operaciones[0])
    print(operaciones[1])
    print(operaciones[2])
    print(operaciones[3])
    # print(operaciones[4])
    print(operaciones[5])


def crear_cadena_conectividad(cadena,cfc):
    for i in range(len(cfc)):
        if (i != len(cfc) - 1):
            cadena += cfc[i] + ", "
        else:
            cadena += cfc[i]
    return cadena


def convertir_cadena(cola):
    cadena = ""
    while len(cola) != 0:
        if (len(cola) == 1):
            cadena += cola.popleft()
        else:
            cadena += cola.popleft() + " -> "
    return cadena


def crear_grafo(nombre_archivo):
    grafo = Grafo(True)
    archivo = open(nombre_archivo, "r")
    for linea in archivo:
        vertice = linea.rstrip("\n").split("\t")
        grafo.agregar_vertice(vertice[0])
        for i in range(1, len(vertice)):
            grafo.agregar_vertice(vertice[i])
            grafo.agregar_arista(vertice[0], vertice[i], 1)
    archivo.close()
    return grafo


def main():

    costo_diametro = 0
    cadena_diametro = ""
    diccionario_conectados = {}

    if len(sys.argv) != 2:
        print("Cantidad de argumentos invalida")
        return

    grafo = crear_grafo(sys.argv[1])

    for linea in sys.stdin:

        linea = linea.rstrip("\n").split(" ", 1)
        if (len(linea) > 1):
            linea[1] = linea[1].split(",")

        if (len(linea) == 0): continue

        comando = linea[0]

        if (comando == "listar_operaciones"):
            listar_operaciones()

        if (comando == "camino"):
            camino_mas_corto(grafo, linea[1][0], linea[1][1])

        if (comando == "diametro"):
            if costo_diametro > 0:
                print(cadena_diametro)
                print("costo:", costo_diametro)
            else:
                cadena_diametro, costo_diametro = diametro(grafo)

        if (comando == "navegacion"):
            navegacion_por_primer_link(grafo, linea[1][0])

        if (comando == "rango"):
            todos_en_rango(grafo, linea[1][0], int(linea[1][1]))

        if (comando == "conectados"):
            if (linea[1][0] in diccionario_conectados):
                cadena_conectados = crear_cadena_conectividad("",diccionario_conectados[linea[1][0]])
                print(cadena_conectados)
            else:
                conectividad(grafo, linea[1][0], diccionario_conectados)

        if (comando == "clustering"):
            if (len(linea) > 1):
                coeficiente = clustering(grafo, linea[1][0])
            else:
                coeficiente = clustering_toda_la_red(grafo)
            print("{0:.3f}".format(coeficiente))
        if (comando == "ciclo"):
            if
main()
