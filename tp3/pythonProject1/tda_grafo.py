class Vertice:
    def __init__(self, nombre):
        self.adyacentes_salida = {}
        self.adyacentes_entrada = {}
        self.nombre = nombre


class Grafo:
    def __init__(self):
        self.vertices = {}

    def estan_unios(self, v, w):
        if self.vertices[v].adyacentes_salida[w]:  # O(1)
            return True
        return False

    def borrar_arista(self, v, w):
        if self.estan_unidos(v, w):  # O(1)
            if w == v.adyacentes_salida.pop[w]:
                if v == w.adyacentes_entrada.pop[v]:
                    return True
            return False
        return True

    def agregar_vertice(self, v):
        if not self.vertices[v]:
            self.vertices[v] = v  # O(1)
            return True
        return False

    def borrar_vertice(self, v):
        for i in self.vertices[v]:
            if i.adyacentes_salida[v]:
                if not v == i.adyacentes_salida.pop[v]:
                    return False
            if i.adyacentes_entrada[v]:
                if not v == i.adyacentes_entrada.pop[v]:
                    return False
        self.vertices[v].adyacentes_entrada.clear()
        self.vertices[v].adyacentes_salida.clear()
        self.vertices.pop(v)
        return True

    def agregar_arista(self, v, w):
        if self.estan_unidos(v, w):
            return True
        self.vertices[v].adyacentes_salida[w] = w
        self.vertices[w].adyacentes_entrada[v] = v
        return True

    def adyacentes(self, v):
        ady = set()
        for i in self.vertices[v].adyacentes_salida:
            ady.add(i)
        return ady
