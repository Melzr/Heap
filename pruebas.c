#include "heap.h"
#include <stdio.h>

int comparador(void* i, void* j) {
	if ((int*)i > (int*)j)
		return 1;
	if ((int*)i < (int*)j)
		return -1;

	return 0;
}

void destructor(void* i) {
	return;
}

int main() {

	int vector[] = {3,5,1,7,6,2,10,1,4,11,14,12,20,3};

	heap_t* heap = heap_crear(comparador, destructor);

	for (int i = 0; i < 14; i++) {
		heap_insertar(heap, (void*)vector[i]);
	}

	for (int i = 0; i < 14; i++) {
		printf("%i,  ", (int)heap->vector[i]);
	}

	printf("\n\n\n\n");

	for (int i = 0; i < 14; i++) {
		printf("%i,  ", (int)heap_raiz(heap) );
		heap_borrar_raiz(heap);
	}

	heap_destruir(heap);

	return 0;
}