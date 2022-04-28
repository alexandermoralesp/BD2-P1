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

Con el motivo de demostrar un buen funcionamiento de las implementaciones, se decidió ponerlas a prueba mediante la carga/ construcción por medio de dos bancos de datos de la página Kaggle. El primer banco de datos corresponde a los valores nutricionales de marcas de cereales y el segundo corresponde a la clásica aplicación de aprendizaje de operaciones por medio de los datos de los tripulantes del Titanic.

Posteriormente a lo mencionado, los datos serán alterados por medio de operaciones CRUD tales como: actualizar, eliminar, insertar, búsqueda singular y búsqueda por rango. Por motivos experimentales, se ha toma en cuenta el tiempo tomado en alguna operación y su cantidad de accesos a memoria secundaria con la finalidad de evaluar en que casos algún método de organización es más efectivo.

## Fundamentación de técnicas de organización de archivos

Como se mencionó anteriormente, los medios de organización a utilizar fueron el archivo secuencial y el hash extensible. Por ese motivo, es necesario explicar como es que se realizan las operaciones CRUD.

### Archivo Secuencial (Sequential File)

Esta técnica de indexación consiste en guardar los registros en un archivo de tal forma que se les adiciona un indicador entero que nos otorga el orden del siguiente registro con un carácter que define el archivo (‘a’ o ‘d’). Aquel indicador es también agregado antes del primer registro para saber cual es el registro con menor llave. Este mismo formato de registro-puntero es empleado en un archivo auxiliar que nos permite agregar una cantidad determinada de registros con una complejidad constante, hasta que sea necesario reorganizar el archivo de datos principal. En cuanto a los valores de los punteros, se definen como: 0-eliminado, >0-siguiente registro y -1-ultimo registro.

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

#### Buscar

#### Buscar por rango

#### Reorganizar (Adicional)

- Abrimos el archivo de datos y el auxiliar en modo lectura
- Creamos un nuevo archivo en modo escritura para organizar ambos archivos
- Leemos el puntero cabecera y vamos leyendo cada registro 
	- Si el puntero tiene un carácter ‘a’, dirigirnos al archivo auxiliar
	- De lo contrario, leer el registro n en el archivo principal
	- Escribir el puntero y el registro leído actual 
	- Leemos el registro que acompaña el registro
	- Mientras el registro no direccione a -1, repetimos lo anterior
- Escribimos el registro que apunta a -1
- Truncamos ambos archivos
- Nos dirigimos al archivo de datos y copiamos todos los datos del archivo temporal creado
- Eliminamos el archivo temporal


## Resultados experimentales

## Pruebas de uso
