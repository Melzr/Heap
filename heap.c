#include "heap.h"
#include <stdlib.h>

static const int OK = 0;
static const int ERROR  = -1;
//static const int PRIMERO_MENOR = -1;
//static const int PRIMERO_MAYOR = 1;
static const int IGUALES = 0;


void intercambiar(void* vector[], int i, int j) {
	void* aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor) {

	if (comparador == NULL)
		return NULL;
	
	heap_t* heap = calloc( 1, sizeof(heap_t) );
	if (!heap) return NULL;

	heap->tope = 0;
	heap->comparador = comparador;
	heap->destructor = destructor;

	return heap;
}

/*
 * Dada la posicion de un elemento en el vector del heap,
 * devuelve la posicion de su padre en el mismo 0 -1 si es la raiz.
 */
int posicion_padre(int n) {

	if (n == 0)
		return -1;

	return (n-1)/2;
}

/*
 * Dada la posicion de un elemento en el vector del heap,
 * devuelve la posicion de su hijo derecho.
 */
int posicion_hijo_derecho(int n) {
	return (2*n)+2;
}

/*
 * Dada la posicion de un elemento en el vector del heap,
 * devuelve la posicion de su hijo izquierdo.
 */
int posicion_hijo_izquierdo(int n) {
	return (2*n)+1;
}

/*
 * Sube un elemento en la posicion recibida hasta una posicion
 * que cumpla con las condiciones de heap minimal.
 */
void sift_up(heap_t* heap, int posicion) {

	if (posicion == 0) return; //llegue a la raiz

	int padre = posicion_padre(posicion);

	if ( heap->comparador(heap->vector[posicion], heap->vector[padre]) < IGUALES ) {
		intercambiar( heap->vector, posicion, padre );
		sift_up( heap, padre );
	}

}

/*
 * Baja un elemento en la posicion recibida hasta
 * que cumpla con las condiciones de heap minimal.
 */
void sift_down(heap_t* heap, int posicion) {

	int pos_derecha = posicion_hijo_derecho(posicion);
	int pos_izquierda = posicion_hijo_izquierdo(posicion);
	int pos_menor = pos_izquierda;

	if (pos_izquierda >= heap->tope)
		return;

	if (pos_derecha < heap->tope) {
		if ( heap->comparador(heap->vector[pos_derecha], heap->vector[pos_izquierda]) < IGUALES )
			pos_menor = pos_derecha;
	}

	if ( heap->comparador(heap->vector[posicion], heap->vector[pos_menor]) > IGUALES ) {
		intercambiar( heap->vector, posicion, pos_menor);
		sift_down(heap, pos_menor);
	}

}

int heap_insertar(heap_t* heap, void* elemento) {

	if (!heap) return ERROR;

	if (heap->comparador == NULL) return ERROR;

	heap->tope++;
	void* aux = realloc( heap->vector, (sizeof(void*) * (size_t)heap->tope));
	if (!aux) {
		heap->tope--;
		return ERROR;
	}	

	heap->vector = aux;
	heap->vector[heap->tope-1] = elemento;
	sift_up( heap, heap->tope-1 );

	return OK;
}

void* heap_raiz(heap_t* heap) {

	if (!heap) return NULL;
	if (!heap->vector) return NULL;

	return heap->vector[0];
} 

bool heap_vacio(heap_t* heap) {

	return (!heap || !heap->vector || heap->tope <= 0);
}

void heap_borrar_raiz(heap_t* heap) {

	if (!heap || !heap->vector || !heap->comparador)
		return;

	if (heap->tope <= 0)
		return;

	void* aux = heap->vector[0];
	heap->vector[0] = heap->vector[heap->tope-1];

	if (heap->destructor != NULL)
		heap->destructor(aux);
	heap->tope--;

	if (heap->tope != 0)
		sift_down( heap, 0 );

}

void heap_destruir(heap_t* heap) {

	if (!heap) return;

	if (heap->vector != NULL) {

		if (heap->destructor != NULL) {
			for (int i = 0; i < heap->tope; i++) {
				heap->destructor(heap->vector[i]);
			}
		}

		free(heap->vector);
	}

	free(heap);
}