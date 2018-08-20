//
//  Hash_AB.cpp
//  
//
//  Created by Carlos Reyes on 25/04/18.
//

#include "Hash_AB.hpp"



raiz CrearNODO(int indice, int valor)
{
    raiz nuevo;
    
    nuevo=(raiz)malloc(sizeof(ELEMENTODEARBOLBINARIO));
    nuevo->indice=indice;
    nuevo->lista = (int *)malloc(sizeof(int));
    if(nuevo->lista == NULL)
    {
        cout << "Error de asignacion ";
       return NULL;
    }
    nuevo->lista[0]=valor;
    nuevo->tamanio_lista = 1;
    nuevo->flag=0;
    nuevo->izq=nuevo->der=NULL;
    return nuevo;
}

 
int Profundidad(raiz _raiz)
{
    if(!_raiz)
        return 0;
    else
    {
        int profundidadI, profundidadD;
        profundidadI=Profundidad(_raiz->izq);
        profundidadD=Profundidad(_raiz->der);
        if(profundidadI>profundidadD)
        {
            return(profundidadI+1);
        }
        else
        {
            return(profundidadD+1);
        }
    }
}
void Hojas(raiz _raiz, int*cont)
{
    if((_raiz->izq)==(_raiz->der))
    {
        (*cont)++;
        return;
    }
    else
    {
        Hojas(_raiz->izq, cont);
        Hojas(_raiz->der, cont);
    }
}
void BorrarArbol(raiz _raiz)
{
    if(_raiz)
    {
        BorrarArbol(_raiz->izq);
        BorrarArbol(_raiz->der);
        printf("%d", _raiz->indice);
        free(_raiz);
    }
}
void NumElem(raiz _raiz, int*cont)
{
    if(_raiz)
    {
        NumElem(_raiz->izq, cont);
        NumElem(_raiz->der, cont);
        printf("%d", _raiz->indice);
        (*cont)++;
    }
}
void Preorden(raiz _raiz)
{
    if(_raiz)
    {
        printf("%d ", _raiz->indice);
        Preorden(_raiz->izq);
        Preorden(_raiz->der);
    }
}
void Enorden(raiz _raiz)
{
    if(_raiz)
    {
        Enorden(_raiz->izq);
        
        cout << endl <<_raiz->indice << " : ";
        
        for (int x = 0; x < _raiz->tamanio_lista; x++)
        {
            cout << " "<< _raiz->lista[x];
        }
        
        Enorden(_raiz->der);
    }
}
void Postorden(raiz _raiz)
{
    if(_raiz)
    {
        Postorden(_raiz->izq);
        Postorden(_raiz->der);
        printf("%d ", _raiz->indice);
    }
}
raiz BuscarABB(raiz _raiz, int x)
{
    if(_raiz==NULL)
    {
        return NULL;
    }
    else if(_raiz->indice == x)
    {
        return _raiz;
    }
    else
    {
        if(x > (_raiz->indice))
            return BuscarABB(_raiz->der, x);
        else
            return BuscarABB(_raiz->izq, x);
            }
}

/*
raiz * BuscarABB( raiz * _raiz , int x)
{
    if(_raiz==NULL)
    {
        return NULL;
    }
    else if(_raiz->indice == x)
    {
        return _raiz;
    }
    else
    {
        return((_raiz->indice)>x?BuscarABB(_raiz->izq, x):BuscarABB(_raiz->der, x));
    }
}
 */
void InsertarABB(raiz * _raiz, int indice, int valor)
{
   
    if(!(*_raiz))
    {
        (*_raiz)=CrearNODO(indice,valor);
    }
    else if( (*_raiz)->indice == indice)
    {
        (*_raiz)->tamanio_lista=(*_raiz)->tamanio_lista+1;
        
        int * aux_lista = (int*) realloc ((*_raiz)->lista, (*_raiz)->tamanio_lista * sizeof(int));
        
        if(aux_lista!=NULL)
        {
            
            aux_lista [(*_raiz)->tamanio_lista -1] = valor;
           // free((*_raiz)->lista);
            (*_raiz)->lista = aux_lista;
        }
        else
        {
            cout<< "Error de asignacion realloc";
            return;
        }
        
    }
    else if( indice > (*_raiz)->indice)
    {
        InsertarABB( &((*_raiz)->der), indice, valor);
    }
    else
    {
        InsertarABB(&((*_raiz)->izq), indice, valor);
    }
}
void reemplazar(raiz*_raiz)
{
    raiz aux1, aux2;
    aux1=(*_raiz);
    aux2=(*_raiz)->izq;
    while(aux2->der)
    {
        aux1=aux2;
        aux2=aux2->der;
    }
    (*_raiz)->indice=aux2->indice;
    if(aux1==(*_raiz))
    {
        (*_raiz)->izq=aux2->izq;
    }
    else
    {
        aux1->der=aux2->izq;
    }
    (*_raiz)=aux2;
}
void EliminarABB(raiz* _raiz, int x)
{
    raiz aux;
    if(!(*_raiz))
    {
        puts("No encontrado\n");
    }
    else if((*_raiz)->indice<x)
    {
        EliminarABB(&(*_raiz)->der, x);
    }
    else if((*_raiz)->indice>x)
    {
        EliminarABB(&(*_raiz)->izq, x);
    }
    else
    {
        aux=*_raiz;
        if(aux->der==NULL)
        {
            (*_raiz)=aux->izq;
        }
        else if(aux->izq==NULL)
        {
            (*_raiz)=aux->der;
        }
        else
            reemplazar(&aux);
        free(aux);
    }
}

void InsertarRaiz(raiz * _raiz, raiz * _rama)
{
    if ( (*_raiz)==NULL)
        (*_raiz) = (*_rama);
    else if( (*_raiz)->indice == (*_rama)->indice  )
        return;
    else if((*_rama)->indice < (*_raiz)->indice   )
        InsertarRaiz( &(*_raiz)->izq, _rama);
    else
         InsertarRaiz( &(*_raiz)->der, _rama);
}

raiz copiarNodo(raiz origen)
{
    raiz nuevo;
    
    nuevo=(raiz)malloc(sizeof(ELEMENTODEARBOLBINARIO));
    nuevo->indice= origen->indice;
    nuevo->tamanio_lista = origen->tamanio_lista;

    nuevo->lista = (int *)malloc(sizeof(int)*origen->tamanio_lista);
    if(nuevo->lista == NULL)
    {
        cout << "Error de asignacion ";
        return NULL;
    }
    for (int x = 0; x<origen->tamanio_lista; x++) {
        nuevo->lista[x]= origen->lista[x];
    }
    nuevo->flag=0;
    nuevo->izq=nuevo->der=NULL;
    return nuevo;
}

void copySubArbol( raiz * _raiz, raiz * _origen, raiz * _destino )
{
    
    

     if ( (* _origen)->flag == 2)
        return;
    else
        (* _origen)->flag = 2;
    
  
    raiz a = copiarNodo((* _origen));
    
    InsertarRaiz(_destino, &a );
    
    raiz aux = NULL;


    for (int x = 0 ; x < (* _origen)->tamanio_lista; x++)
    {
        aux = BuscarABB((* _raiz),(* _origen)->lista[x] );
        if(aux!=NULL)
          copySubArbol(_raiz, &aux, _destino);
    }
    
}

