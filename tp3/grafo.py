from sys import call_tracing


class Grafo():
    def __init__(self, es_dirigido):
        self.vertices = {}
        self.es_dirigido = es_dirigido
        self.cantidad = 0

    def agregar_vertice(self, vertice):
        if vertice in self.vertices:
            return False
        self.vertices.setdefault(vertice, {})
        self.cantidad += 1
        return True

    def sacar_vertice(self, vertice):
        if vertice not in self.vertices:
            return False
        self.vertices.pop(vertice)
        for aristas in self.vertices:
            aristas.pop(vertice)

    def agregar_arista(self, vertice1, vertice2, peso):
        if vertice1 not in self.vertices or vertice2 not in self.vertices:
            return False
        self.vertices[vertice1].setdefault(vertice2, peso)
        if not self.es_dirigido:
            self.vertices[vertice2].setdefault(vertice1, peso)

    def estan_unidos(self, vertice1, vertice2):
        if self.vertices[vertice1] in vertice2:
            return True
        return False

    def sacar_arista(self, vertice1, vertice2):
        if vertice1 not in self.vertices or vertice2 not in self.vertices:
            return False
        peso = self.vertices[vertice1][vertice2]
        self.vertices[vertice1].pop(vertice2)
        if not self.es_dirigido:
            self.vertices[vertice2].pop(vertice1)
        return peso

    def adyacentes(self, vertice):
        lista_adyacentes = []
        for adyacentes in self.vertices[vertice]:
            lista_adyacentes.append(adyacentes)
        return lista_adyacentes

    def peso_arista(self, vertice1, vertice2):
        if vertice1 not in self.vertices or vertice2 not in self.vertices:
            return False
        return self.vertices[vertice1][vertice2]

    def ob_vertices(self):
        return list((self.vertices).keys())

    def obtener_cantidad(self):
        return self.cantidad