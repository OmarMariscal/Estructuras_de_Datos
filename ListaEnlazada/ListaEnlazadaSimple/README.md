# Listas Enlazadas
Las listas enlazadas son un tipo de estructura de datos donde sus contenidos, no están almacenados en la memoria de manera continua como lo estaría un vector.  
- Estan almacenadas en diferentes posiciones de memoria
- Para su orden, cada uno de los elementos tiene un apuntador que apunta al siguiente dato.


## Particularidades
Esta particular forma de almacenar los datos tiene sus ventajas y desventajas, por ejemplo:  


### Ventajas
- Agregar y quitar elementos es mucho más fácil que en un vector


### Desventajas
- La búqueda y obtención de los elementos es más complicada, ya que se tiene que recorrer la lista desde la cabeza hasta el final, por lo que la complejidad suele ser un O(n)