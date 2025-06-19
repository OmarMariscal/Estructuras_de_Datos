# Hash Table
La Hash Table o Tabla Hash es una estructura de datos especializada en la búsqueda de elementos.  

![Imagen Tabla Hash](https://miro.medium.com/v2/resize:fit:712/0*dDigLnLd-HbaaB1G.jpg)

Se centra en el uso de una **Función Hash**, la cual, se encarga de transformar una clave en un índice numérico, con el cuál, se buscará el valor en un arreglo.  

## Partes de la Hash Table
Las tablas hash tienen dos partes principales, **Función Hash y la Tabla hash**  

- La función hash es la encargada de a partir de una clave, obtener un índice del orden de 0 a n-1, donde n, es la capacitdad total de la Tabla Hash
- La tabla hash es un arreglo en el que se almacenan los valores, están ordenados a partir del índice que se obtienen de la función hash.

### Ejemplo de Hash Table
Imaginemos que queremos guardar los puntos de equipos de fútbol, y asociamos una llave a un deteminado valor entero, como la clave "Barcelona" asociado al valor 79, o "Valladolid" asociado al valor 50.  


La función Hash se encarga de realizar una serie de operaciones sobre el string "Barcelona" para obtener un índice entre 0 y m, y poner en ese índice el valor 79.

Si quisieramos acceder a ese valor, no tendríamos que recorrer el arreglo completo, sino que solo tendríamos que calcular el valor de la clave y acceder directo a esa posición, teniendo una complejidad algoritmica ideal de O(1).

## Desventajas de Hash Table
Una de los principales problemas son las **Colisiones**.  
Una función hash, puede dar el mismo índice para dos distintas claves, y es aquí cuando se produce una colisión.

### Colisiones
Dado que no podemos almacenar el mismo valor en el mismo lugar de memoria, podemos tratar estas colisiones de dos maneras:
#### Hash Table Cerrada
Una Hash Table Cerrada es aquella que con las colisiones, busca el siguiente espacio disponible en el vector y almacena ahí el siguiente valor.
- Esto propicia que la estructura tenga un espacio limitado.
#### Hash Table Abierta
Esta estrategia se basa en que cada espacio del vector sea ota estructura de datos dinámica como una lista enlazada, y en ellas ir guardando los valores cuyas claves colisionen.
- Esta estrategia nos da un control dinámico, sin embargo, una mala función hash acaba creando una Hash Table desproporcionada, y en el peor de los casos, todos los valores quedarán en el mismo espacio, perdiendo las virtudes de una Hash Table.


