class KDTree(object):
    
    """
    Esta implementación solo admite distancias euclidianas. 

    Uso:
    1. Crea el KD-Tree:
    `kd_tree = KDTree(puntos, dimensión)`
    2. Luego puedes usar `get_knn` para obtener los k vecinos más cercanos o 
    `get_nearest` para el vecino más cercano.

    Los puntos deben ser una lista de puntos: [[0, 1, 2], [12.3, 4.5, 2.3], ...]
    """
    def __init__(self, points, dim, dist_sq_func=None):
        """
        Crea el KD-Tree para una búsqueda rápida.

        Parámetros
        ----------
        points : list<point>
            Una lista de puntos.
        dim : int 
            La dimensión de los puntos. 
        dist_sq_func : función(point, point), opcional
            Una función que devuelve la distancia euclidiana al cuadrado
            entre dos puntos. 
            Si se omite, se utiliza la implementación predeterminada.
        """

        if dist_sq_func is None:
            dist_sq_func = lambda a, b: sum((x - b[i]) ** 2 
                for i, x in enumerate(a))
                
        def make(points, i=0):
            if len(points) > 1:
                points.sort(key=lambda x: x[i])
                i = (i + 1) % dim
                m = len(points) >> 1
                return [make(points[:m], i), make(points[m + 1:], i), 
                    points[m]]
            if len(points) == 1:
                return [None, None, points[0]]
        
        def add_point(node, point, i=0):
            if node is not None:
                dx = node[2][i] - point[i]
                for j, c in ((0, dx >= 0), (1, dx < 0)):
                    if c and node[j] is None:
                        node[j] = [None, None, point]
                    elif c:
                        add_point(node[j], point, (i + 1) % dim)

        import heapq
        def get_knn(node, point, k, return_dist_sq, heap, i=0, tiebreaker=1):
            if node is not None:
                dist_sq = dist_sq_func(point, node[2])
                dx = node[2][i] - point[i]
                if len(heap) < k:
                    heapq.heappush(heap, (-dist_sq, tiebreaker, node[2]))
                elif dist_sq < -heap[0][0]:
                    heapq.heappushpop(heap, (-dist_sq, tiebreaker, node[2]))
                i = (i + 1) % dim
                # Goes into the left branch, then the right branch if needed
                for b in (dx < 0, dx >= 0)[:1 + (dx * dx < -heap[0][0])]:
                    get_knn(node[b], point, k, return_dist_sq, 
                        heap, i, (tiebreaker << 1) | b)
            if tiebreaker == 1:
                return [(-h[0], h[2]) if return_dist_sq else h[2] 
                    for h in sorted(heap)][::-1]

        def walk(node):
            if node is not None:
                for j in 0, 1:
                    for x in walk(node[j]):
                        yield x
                yield node[2]

        self._add_point = add_point
        self._get_knn = get_knn 
        self._root = make(points)
        self._walk = walk

    def __iter__(self):
        return self._walk(self._root)
        
    def add_point(self, point):

        if self._root is None:
            self._root = [None, None, point]
        else:
            self._add_point(self._root, point)

    def get_knn(self, point, k, return_dist_sq=True):

        return self._get_knn(self._root, point, k, return_dist_sq, [])

    def get_nearest(self, point, return_dist_sq=True):

        l = self._get_knn(self._root, point, 1, return_dist_sq, [])
        return l[0] if len(l) else None
    


class KDTreeClassifier(object):
    def __init__(self, points, dim, classes, dist_sq_func=None):
        self.points = points
        self.dim = dim
        self.classes = classes

        if dist_sq_func is None:
            dist_sq_func = lambda a, b: sum((x - b[i]) ** 2 for i, x in enumerate(a))

        self.dist_sq_func = dist_sq_func
        
        # Crear el diccionario de puntos y etiquetas
        self.point_label_dict = {tuple(point): label for point, label in zip(self.points, self.classes)}

        self.kd_tree = self.build_kd_tree()

    def build_kd_tree(self, dist_sq_func=None):
        if dist_sq_func is None:
            dist_sq_func = lambda a, b: sum((x - b[i]) ** 2 for i, x in enumerate(a))
        
        return KDTree(self.points, self.dim, dist_sq_func)
    
    def classify(self, point, k):
        # Obtener los vecinos más cercanos
        knn_points = self.kd_tree.get_knn(point, k, return_dist_sq=False)

        # Contar las clases de los vecinos más cercanos
        class_votes = {}
        for nearest_point in knn_points:
            if tuple(nearest_point) in self.point_label_dict:
                label = self.point_label_dict[tuple(nearest_point)]
                if label in class_votes:
                    class_votes[label] += 1
                else:
                    class_votes[label] = 1

        # Devolver la clase con más votos
        most_voted_label = max(class_votes, key=class_votes.get)
        return most_voted_label
