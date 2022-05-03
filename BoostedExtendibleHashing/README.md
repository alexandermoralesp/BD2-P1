# BoostedExtendibleHashing

- Se corrigió los errores de implementación. La complejidad de acceso a la posicion del registro en los nodos hojas es O(1) ya que se maneja por medio de maps.
- Se implementó la escritura y lectura del bucket tanto leaf como no leaf para strings y cualquier valor (se utilizó type_traits)
- Se realizó las pruebas a gran escala, y es mucho más eficiente que la implementación principal del extendible hashing
- Se limpió el código y se mantuvo buenas prácticas.

```
NOTA: Se tuve problemas con el compilador de g++ en Windows, pero sí corrió todas las pruebas con el compilador de MSCVC de Windows.
```