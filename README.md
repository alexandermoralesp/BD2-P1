# Proyecto 1

## Integrantes

- Morales Panitz, Alexander 
- Ugarte Quispe, Grover
- Gutierrez Luis

| Apellidos y Nombres       | Código de alumno | % Participación |
|---------------------------|------------------|-----------------|
| Morales Panitz, Alexander | 202020195        | 100%            |
| Ugarte Quispe, Grover     | 202020195        | 100%            |
| Gutierrez Guanilo, Luis   | 202010074        | 100%            |

## Introducción

El presente proyecto tiene como objetivo el aprendizaje de los diferentes métodos de manejo de archivos e indexación en los sistemas de gestión de bases de datos por medio de su implementación en un lenguaje de programación de bajo nivel. Entre los medios de organización vistos se encuentran el archivo secuencial, ISAM, B+ tree y hash extensible. Para esta entrega del proyecto, se decidió realizar la implementación del archivo secuencial y hash extensible.

Con el motivo de demostrar un buen funcionamiento de las implementaciones, se decidió ponerlas a prueba mediante la carga/ construcción por medio de dos bancos de datos de la página Kaggle. El primer banco de datos corresponde a los valores nutricionales de marcas de cereales y el segundo corresponde a las cartas de jugadores del videojuego FIFA 22.

![](IMG/cereal-milk.gif)
![](IMG/ecLxP2.gif)

Posteriormente a lo mencionado, los datos serán alterados por medio de operaciones CRUD tales como: actualizar, eliminar, insertar, búsqueda singular y búsqueda por rango. Por motivos experimentales, se ha toma en cuenta el tiempo tomado en alguna operación y su cantidad de accesos a memoria secundaria con la finalidad de evaluar en que casos algún método de organización es más efectivo.

## Fundamentación de técnicas de organización de archivos

Como se mencionó anteriormente, los medios de organización a utilizar fueron el archivo secuencial y el hash extensible. Por ese motivo, es necesario explicar como es que se realizan las operaciones CRUD.

### Archivo Secuencial (Sequential File)

Esta técnica de indexación consiste en guardar los registros en un archivo de tal forma que se les adiciona un indicador entero que nos otorga el orden del siguiente registro con un carácter que define el archivo (‘a’ o ‘d’). Aquel indicador es también agregado antes del primer registro para saber cual es el registro con menor llave. Este mismo formato de registro-puntero es empleado en un archivo auxiliar que nos permite agregar una cantidad determinada de registros con una complejidad constante, hasta que sea necesario reorganizar el archivo de datos principal. En cuanto a los valores de los punteros, se definen como: eliminado (0), siguiente registro (>0) y ultimo registro (-1).

![](IMG/sq.png)

#### Insertar

- Si la cantidad de registros en el archivo auxiliar es igual a la máxima definida, se reorganiza el archivo
- Abrimos el archivo de datos en modo lectura y aplicamos una búsqueda binaria con los parámetros l y r
	- Si l <= r, entonces la llave existe, por lo que el algoritmo retorna una excepción
	- Si r == -1, entonces el registro insertado es el que tiene el menor orden, por lo que se lee el puntero en la cabecera
	- De lo contrario, leemos el registro l ya que es el puntero cuyo registro que lo acompañe tiene la llave que es un orden menor al registro insertado
- Sabiendo que el archivo auxiliar puede tener un registro mayor al leído pero menor al que está por añadir, se abre aquel archivo en lectura y se realiza una búsqueda lineal y se obtiene el orden del registro si alguno cumple
- Se abre el archivo auxiliar para agregar el nuevo registro y el puntero leído previamente
- Se va al orden del registro del archivo respectivo y se sobrescribe el puntero por la cantidad total de registros en el archivo auxiliar junto con el carácter ’a’

#### Remover

- Si la cantidad de registros eliminado en el archivo auxiliar es igual a lo máximo definida, se reorganiza el archivo
- Aplicamos el algoritmo de búsqueda para hallar el registro y puntero que coincidan con la llave introducida en la función.
	- Si no es hallada, se retorna una excepción
- Ya que los punteros también se encuentran ordenados (a excepción del archivo auxiliar), realizamos una búsqueda para hallar el registro y puntero que apunten a la posición de aquel registro y coincidan con su indicador de archivo.
	- Ambos archivos deben ser abiertos de tal forma que acepten lectura y sobreescritura
	- Antes de iniciar todo el algoritmo de búsqueda, podemos evitarlo si leemos la cabecera y comprobamos si esta apunta al registro
- Una vez encontrado, se clona el puntero previo en una variable temporal
- Se retrocede en el tamaño del puntero y se sobrescribe su puntero con el puntero que colinda con el registro a eliminar
- Utilizando el puntero copia, regresamos a la posición del registro objetivo, ignoramos todo su bloque de información y sobrescribimos el puntero con uno que apunte a la posición 0

#### Buscar

- Abrimos el archivo principal  en modo lectura y realizamos una búsqueda binaria entre sus registros, leyendo también el puntero que lo acompaña.
- Si no se encuentra un registro que contenga la llave o si su puntero apunta a 0 (lo que significa que ese registro fue eliminado), abrimos el archivo auxiliar en modo lectura y realizamos una búsqueda lineal, asegurándonos que el puntero que lo acompañe no sea 0.
- Si luego de examinar el archivo auxiliar no se encontró una coincidencia o el puntero nos dice que el registro está eliminado, retornamos una excepción de que no se halló un registro con esa llave. En caso contrario, se retorna el registro.

#### Buscar por rango

- Aplicamos el algoritmo de búsqueda mencionado anteriormente para las llaves de inicio y fin del rango (leyendo tanto el registro y el puntero)
	- Si no se encontró el registro, se retorna una excepción
- Creamos un vector de registros y agregamos el registro con la llave de inicio
- Realizamos lecturas de registros y punteros hasta que estos coincidan con las lecturas asociadas a la llave final
	- Dependiendo del carácter del puntero, nos posicionamos en la dirección que apunta en el archivo respectivo
	- Realizamos una lectura de registro y puntero
	- Agregamos el registro al vector de registros
- Se retorna el vector de registros que se encuentren inclusivamente en el rango introducido

#### Reorganizar (Adicional)

- Abrimos el archivo de datos y el auxiliar en modo lectura
- Creamos un nuevo archivo en modo escritura para organizar ambos archivos
- Leemos el puntero cabecera y vamos leyendo cada registro 
	- Si el puntero tiene un carácter ‘a’, dirigirnos al archivo auxiliar
	- De lo contrario, leer el registro n en el archivo principal
	- Escribir el puntero y el registro leído actual 
	- Leemos el registro que acompaña el registro
	- Mientras el registro no direccione a -1, repetimos lo anterior
- Escribimos el registro que apunta a -1 al final del archivo ya que este no es escrito en el bucle
- Truncamos ambos archivos
- Nos dirigimos al archivo de datos y copiamos todos los datos del archivo temporal creado
- Eliminamos el archivo temporal

#### Consideraciones 
- Ya que al realizar una búsqueda binaria nos enfocamos en una complejidad logarítmica, con el objetivo de que a lo mucho se duplique el tiempo, la cantidad de registros eliminados y presentes en el archivo auxiliar no deben sobrepasar $\lg(n)+1$. Siendo $n$ la cantidad de registros en el archivo principal.


## Resultados experimentales

### Consideraciones peliminares

Para tomar las métricas de accesos a memoria secundaria y el tiempo tomado para cada instrucción, se toma en cuenta lo siguiente:

- Para el tiempo, se empleará la librería de c++ chrono
- Para la cantidad de accesos a memoria secundaria, se agregara un contador que incrementará cuando suceda lo siguiente:

	- Un archivo es abierto
	- Existe una lectura o escritura
	- Nos posicionamos en una ubicación del archivo		

### Definición del plan de instrucciones a ejecutar

Adicionalmente, se definieron los siguientes pasos para evaluar las métricas por las instrucciones mencionadas:

- Dataset Cereal
	1.  Búsqueda de la llave ```Cocoa Puffs```
	2. Para i=0 hasta 10
		- Insertar ```Crispy Wheat & Raisins + tostring(i),G,C,100,2,1,140,2,11,10,120,25,3,1,0.75,36.176196```
	3. Búsqueda de la llave ```Crispy Wheat & Raisins9```
	4. Búsqueda en rango desde la llave ```Cream of Wheat (Quick)``` hasta ```Froot Loops```
	5. Eliminación de la llave ```Cocoa Puffs```

- Dataset Fifa
	1. Búsqueda de la llave ```Pele```
	2. Para i=0 hasta 20
		- Insertar ```Johan Cruyff + to_string(i),R,CF,H,L,94,91,92,91,94,42,73,5,-1,-1,-1,-1,-1,-1```
	3. Búsqueda de la llave ``` Johan Cruyff 19```
	4. Búsqueda en rango desde la llave ```Javier Zanetti``` hasta ```Joshua Kimmich```
	5. Eliminación de la llave ```Pele```

### Resultados y graficos


	
### Análisis e interpretación

## Pruebas de uso

Para realizar pruebas de uso en nuestra aplicación creada, emplearemos un ensayo reducido al presentado en el apartado de ```Definición del plan de instrucciones a ejecutar```:

- Dataset Cereal
	1.  Búsqueda de la llave ```Cocoa Puffs```
	2. Para i=0 hasta 2
		- Insertar ```Crispy Wheat & Raisins + tostring(i),G,C,100,2,1,140,2,11,10,120,25,3,1,0.75,36.176196```
	3. Búsqueda de la llave ```Crispy Wheat & Raisins9```
	4. Búsqueda en rango desde la llave ```Cream of Wheat (Quick)``` hasta ```Froot Loops```
	5. Eliminación de la llave ```Cocoa Puffs```

- Dataset Fifa
	1. Búsqueda de la llave ```Pele```
	2. Para i=0 hasta 2
		- Insertar ```Johan Cruyff + to_string(i),R,CF,H,L,94,91,92,91,94,42,73,5,-1,-1,-1,-1,-1,-1```
	3. Búsqueda de la llave ``` Johan Cruyff 19```
	4. Búsqueda en rango desde la llave ```Javier Zanetti``` hasta ```Joshua Kimmich```
	5. Eliminación de la llave ```Pele```

