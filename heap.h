#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>

/*
 * Recibe dos elementos del heap. Devuelve 1 si el primero es mayor, -1 si el segundo es mayor
 * o 0 si son iguales.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos del heap, se llamara al destruir el heap o eliminar un elemento.
 */
typedef void (*heap_destructor)(void*);

typedef struct heap {
	void** vector;
	int tope;
	heap_comparador comparador;
	heap_destructor destructor;
} heap_t;


/*
 * Crea el heap y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del heap,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor);

/*
 * Inserta un elemento en el heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El heap admite elementos con valores repetidos.
 */
int heap_insertar(heap_t* heap, void* elemento);

/*
 * Borra la raiz del heap (minimo elemento) invocando al destructor con el mismo.
 * La nueva raiz sera el menor elemento que haya quedado en el heap.
 */
void heap_borrar_raiz(heap_t* heap);

/*
 * Devuelve el elemento almacenado como raiz o NULL si el heap está
 * vacío o no existe.
 */
void* heap_raiz(heap_t* heap);

/*
 * Devuelve true si el heap esta vacio o no existe.
 */
bool heap_vacio(heap_t* heap);

/*
 * Destruye el heap liberando la memoria reservada por el mismo, invocando al
 * destructor con cada elemento.
 */
void heap_destruir(heap_t* heap);


#endif /* __HEAP_H__ */