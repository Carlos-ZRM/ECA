//
//  Hash_AB.hpp
//  
//
//  Created by Carlos Reyes on 25/04/18.
//

#ifndef Hash_AB_hpp
#define Hash_AB_hpp

#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;


typedef struct arbol
{
    int indice;
    int * lista ;
    int tamanio_lista;
    int flag;
    struct arbol *izq, *der;
} ELEMENTODEARBOLBINARIO;
typedef ELEMENTODEARBOLBINARIO * raiz;
raiz CrearNODO (int indice, int valor);
void NuevoArbol(int x, raiz I, raiz D, raiz* _raiz);
int Profundidad(raiz _raiz);
void Hojas(raiz _raiz, int*cont);
void BorrarArbol(raiz _raiz);
void NumElem(raiz _raiz, int*cont);
void Preorden(raiz _raiz);
void Enorden(raiz _raiz);
void Postorden(raiz raiz);
raiz BuscarABB(raiz _raiz, int x);
void InsertarABB(raiz* _raiz, int indice, int valor);
void InsertarRaiz(raiz * _raiz, raiz * _rama);
void reemplazar(raiz* _raiz);
void EliminarABB(raiz* _raiz, int x);
raiz copiarNodo(raiz origen);
void copySubArbol(raiz * _raiz, raiz * _origen, raiz * _destino );
#endif /* Hash_AB_hpp */
