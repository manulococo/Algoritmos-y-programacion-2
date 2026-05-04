from collections import deque
from grafo import Grafo
from sys import setrecursionlimit

setrecursionlimit(100000)

def bfs(grafo, origen):
    distancia, padres, visitados = {}, {}, {}
    for v in grafo.ob_vertices():
        distancia[v] = float("inf")
    padres[origen] = None
    distancia[origen] = 0
    visitados[origen] = True

    cola = deque([origen])

    while len(cola) != 0:
        vertice = cola.popleft()
        for w in grafo.adyacentes(vertice):
            if w not in visitados:
                distancia[w] = distancia[vertice] + 1
                padres[w] = vertice
                visitados[w] = True
                cola.append(w)
    return padres, distancia

def bfs_camino_minimo(padres, distancia, destino):
    if distancia[destino] == float("inf"):
        print("No se encontro recorrido")
        return None
    cola = deque()
    padre = destino
    cola.appendleft(padre)
    for i in range(distancia[destino], 0, -1):
        padre = padres[padre]
        cola.appendleft(padre)
    return cola

def componentes_fuertemente_conexas(grafo, origen):
	orden, mas_bajo = {}, {}
	cfcs = []
	orden[origen] = 0
	pila = deque()
	apilados = set()
	visitados = set()
	cfcs = _componentes_fuertemente_conexas(grafo, origen, visitados, pila, apilados, orden, mas_bajo, cfcs)
	return cfcs


def _componentes_fuertemente_conexas(grafo, v, visitados, pila, apilados, orden, mas_bajo, cfcs):
	visitados.add(v)
	mas_bajo[v] = orden[v]
	pila.append(v)
	apilados.add(v)

	for w in grafo.adyacentes(v):
		if w not in visitados:
			orden[w] = orden[v] + 1
			_componentes_fuertemente_conexas(grafo, w, visitados, pila, apilados, orden, mas_bajo, cfcs)

		if w in apilados:
			mas_bajo[v] = min(mas_bajo[v], mas_bajo[w])


	if orden[v] == mas_bajo[v] and len(pila) > 0:
		nueva_cfc = []
		while True:
			w = pila.pop()
			apilados.remove(w)
			nueva_cfc.append(w)
			if w == v:
				break

		return nueva_cfc
