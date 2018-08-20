//
//  cuenca_atractores.hpp
//  test
//
//  Created by Carlos Reyes on 14/04/18.
//  Copyright © 2018 LCCOMP. All rights reserved.
//

#ifndef cuenca_atractores_hpp
#define cuenca_atractores_hpp

#include <fstream>
#include "Hash_AB.cpp"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>




using namespace std;

/*
 gcc hello.c -o hello $(pkg-config --cflags --libs cairo)
 */

int longitud_semilla, x, y;
int ** matriz;
int regla;

int evolucion_int(int s, int longitud_semilla, int rule);
void make_img(int l, int r);
unsigned char fi(unsigned char x, unsigned char x1, unsigned char x2, int r);
void ramificacion(int x, int a);
void agregar_rama(int arbol);
int ** make_matriz_ady(int s , int r);
raiz make_matriz_in(int anillo , int rule, raiz _raiz);
void make_matriz_img(int ** matriz, int regla, int x, int y);
void make_dot(int ** matriz, int regla, int x, int y);

void printSubArbol(raiz * _raiz, raiz * _origen, int anillo, int rule);
void printSubArbolStream(raiz * _raiz, raiz * _origen, int anillo, int rule, std::ofstream & fs);
void printAllSubArbol(raiz * _raiz, raiz * _origen, int anillo, int rule, int * ciclos);

#endif /* cuenca_atractores_hpp */
