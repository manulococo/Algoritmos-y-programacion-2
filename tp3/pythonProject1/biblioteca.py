from collections import deque

import tda_grafo as Grafo


def caminos_minimos(grafo, origen):
    q = deque()
    visitados = set()
    distancia = {origen: 0}
    visitados.add(origen)
    q.append(origen)

    while len(q):
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                distancia[w] = distancia[v] + 1
                q.append(w)
                visitados.add(w)
    return distancia


def diametro(grafo):
    max_min_dist = 0
    for v in grafo:
        distancias = caminos_minimos(grafo, v)
        for w in distancias:
            if distancias[w] > max_min_dist:
                max_min_dist = distancias[w]
    return max_min_dist


def rango(grafo, v, n):
    visitados = set()
    padres = {}
    orden = {v: 0}
    padres[v] = None
    visitados.add(v)
    q = deque()
    q.append(v)
    contador = 0
    while orden[v] < n:
        v = q.pop()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                if orden[w] == n:
                    contador += 1
                else:
                    q.append(w)
                visitados.add(w)
    return contador


def bfs(grafo, origen):
    visitados = set()
    padres = {origen: None}
    orden = {origen: 0}
    visitados.add(origen)
    q = deque()
    q.append(origen)
    while len(q):
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                visitados.add(w)
                q.append(w)
    return padres, orden


def reconstruir_camino(padres, destino):
    recorrido = []
    while destino is not None:
        recorrido.append(destino)
        destino = padres[destino]
    return recorrido[::-1]


def camino_mas_corto(grafo, origen, destino):
    padres = bfs(grafo, origen)
    return reconstruir_camino(padres, destino)


def navegacion_por_primer_link(grafo, v):
    lista = []
    for i in range(20):
        lista.append(v)
        if len(v.adyacentes) == 0:
            return lista
        v = v.adyacentes[0]
    return lista

def comunidades(grafo):
    label = {}
    for i in grafo.vertices:
        label[i] = i
        