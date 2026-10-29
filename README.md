# Taller de programación imperativa en C

## Integrantes

Pablo Esteban Rivera Redondo

**Lenguaje:** C (C11).

## Compilación y ejecución

Desde la carpeta que contiene `main.c`, en Windows con PowerShell:

```powershell
gcc -std=c11 -Wall -Wextra -pedantic main.c -o taller.exe.\taller.exe
```

En Linux/macOS:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o taller
./taller
```

No se necesita entrada interactiva. El `main` ejecuta automáticamente los ejemplos y muestra los resultados por ejercicio.

## Resultados de las pruebas

1. **Intercambio:** `(8, -3)` pasa a `(-3, 8)`.
2. **Estadísticas:** para `[4, -2, 0, 7, -5]`: suma `4`, mínimo `-5`, máximo `7`, negativos `2`, inverso `-5 7 0 -2 4`.
3. **Copia independiente:** original `[4, -2, 0, 7, -5]` y copia modificada `[99, -2, 0, 7, -5]`.
4. **Ordenamiento:** copia ordenada `[-5, -2, 0, 4, 7]`; el original no cambia.
5. **Búsqueda de pares:** `[-4,-1,0,2,5]` con objetivo `1` encuentra `(-4,5)`; con objetivo `8` no encuentra; `[0,0]` con objetivo `0` encuentra `(0,0)`; `[3]` con objetivo `6` no encuentra; un arreglo de longitud cero tampoco encuentra.
6. **3Sum:** `[-1,0,1,2,-1,-4]` produce `(-1,-1,2)` y `(-1,0,1)`; `[0,1,1]` ninguna; `[0,0,0]` una; `[0,0,0,0]` una; `[-2,0,0,2,2]` una; longitud menor a 3 produce cero.
7. **Máximos acumulados:** para `[3,0,2,0,4]`, izquierda `[3,3,3,3,4]`, derecha `[4,4,4,4,4]`.
8. **Agua atrapada:** `[5]` → `0`; `[0,1,2,3]` → `0`; `[3,2,1,0]` → `0`; `[2,2,2]` → `0`; `[3,0,3]` → `3`; `[3,0,2,0,4]` → `7`; `[4,2,0,3,2,5]` → `9`; `[0,1,0,2,1,0,1,3,2,1,2,1]` → `6`.

**Caso propio (agua):** `[2,0,1,0,2]` → `5`. Las posiciones internas retienen `2`, `1` y `2` unidades, respectivamente, porque están limitadas por columnas de altura 2 en ambos extremos: `2 + 1 + 2 = 5`.

**Detalle por posición** para `[3,0,2,0,4]`:

| Posición | Altura | Máximo izquierda | Máximo derecha | Agua |
|---|---:|---:|---:|---:|
| 0 | 3 | 3 | 4 | 0 |
| 1 | 0 | 3 | 4 | 3 |
| 2 | 2 | 3 | 4 | 1 |
| 3 | 0 | 3 | 4 | 3 |
| 4 | 4 | 4 | 4 | 0 |

Total: `7`.

## Explicaciones solicitadas

### Punteros, intercambio y alcance

`swap` recibe direcciones (`int *`) para modificar las variables del llamador. Modificar `*a` cambia el entero apuntado; asignar otro valor a `a` cambiaría solamente la copia local del puntero. La variable auxiliar `temp` existe únicamente en el bloque de `swap` y deja de estar disponible después de la llamada.

### Copia independiente

La asignación `int *other = original;` hace que ambos punteros indiquen el mismo bloque; no duplica sus elementos. `copyArray` reserva otro bloque con `malloc`, comprueba `NULL` y copia los enteros uno por uno. El llamador libera la copia con `free` cuando ya no la utiliza.

### Por qué funciona la búsqueda de dos índices

En un arreglo ordenado, si la suma de los extremos es menor que el objetivo, el valor izquierdo es demasiado pequeño: mantenerlo y mover el extremo derecho hacia adentro no aumentaría la suma. Si la suma excede el objetivo, el valor derecho es demasiado grande: conservarlo y mover el izquierdo hacia adentro no disminuiría la suma. Así es posible descartar un extremo en cada paso.

### Cómo se evitan ternas duplicadas en 3Sum

Primero se ordena una copia, conservando la entrada original. Para cada posición inicial `i`, se omite el elemento si es igual al anterior. Tras hallar una terna, los índices izquierdo y derecho avanzan saltando todos los valores repetidos. Como se mantiene `i < left < right`, cada terna utiliza tres posiciones distintas; la búsqueda con dos índices requiere O(n²) en total después del ordenamiento.

### Por qué el agua depende del menor de los máximos

El nivel de agua posible en una columna está limitado por la barrera más baja entre la mayor altura disponible a su izquierda y la mayor altura disponible a su derecha. Si una barrera es más baja, el agua se desbordaría al superar esa altura. Por eso la contribución es `min(leftMax[i], rightMax[i]) - height[i]`. Los máximos incluyen la propia posición, así que la contribución no es negativa. El cálculo requiere O(n) tiempo y O(n) memoria auxiliar.

### Alcance de variables

En `swap`, `temp` es una variable local accesible solamente dentro de esa función. En `main`, las variables `a` y `b` son locales a `main` y se modifican al pasar sus direcciones a `swap`. El programa no utiliza variables globales.

### Manejo de memoria: C y Go

En C, `malloc` reserva memoria dinámica y devuelve un puntero que debe comprobarse frente a `NULL`; el programador debe liberar cada bloque con `free`, también ante fallos de reservas posteriores. En Go, `make` crea slices y el recolector de basura administra la recuperación de memoria cuando ya no quedan referencias accesibles. En este código, `copyArray`, `threeSum`, `trappedWater` y la función auxiliar de detalle comprueban las reservas y liberan los bloques obtenidos.

## Observaciones

La salida en consola está dividida en ocho secciones, una por ejercicio. Los casos de 3Sum y agua atrapada muestran la cantidad/resultado obtenido, el esperado y `OK` o `ERROR`. En C, `threeSum` retorna `-1` si falla la reserva; `trappedWater` también retorna `-1` en ese caso.
