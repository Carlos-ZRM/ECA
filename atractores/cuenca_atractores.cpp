//
//  cuenca_atractores.cpp
//  test
//
//  Created by Carlos Reyes on 14/04/18.
//  Copyright © 2018 LCCOMP. All rights reserved.
//g++ cuenca_atractores.cpp  -o c $(pkg-config --cflags --libs cairo)

#include "cuenca_atractores.hpp"

#include <cairo.h>


/*
 fdp -Tps graphRegla90Anillo256.dot -o Neo190Anillo256.ps
fdp −Tsvg  graphRegla90Anillo256.dot -o graphRegla90Anillo256.svg
 g++ cuenca_atractores.cpp  -o c $(pkg-config --cflags --libs cairo)
 */
/**
 Funcion que crea una matriz de insidencia a partir de un anillo
 
 */
void printAllSubArbol( raiz * _raiz ,raiz * _origen, int anillo, int rule, int * ciclos)
{
    if( (* _raiz)==NULL)
        return;
        //el nodo no ha sido visitado
    printAllSubArbol( &(*_raiz)->izq, _origen, anillo, rule, ciclos);
    if( (* _raiz)->flag!=2)
    {
        
        (* ciclos)++;
        
        string file = "graphRegla"+to_string(rule)+"Anillo"+to_string(anillo)+"_atractor_"+to_string((* ciclos));
        ofstream fs(file+".dot");
        fs << "graph "+file + "\n{\n  graph[center =\"1\",size=\"5,5\"];\n  edge [weight=\"10\",len =\"0.1\"]; \n  node[ shape=point,color=darkslateblue    ];" ;
        
        printSubArbolStream( _raiz, _origen,anillo,rule, fs);
        
        fs << "\n}";
        fs.close();
        string comando ="fdp -Tsvg  "+file+".dot -o "+file+".svg";
        system(("echo "+file).c_str());

        
        system(comando.c_str());
    }
    
    printAllSubArbol(&(*_raiz)->der, _origen, anillo, rule, ciclos);
    
    
}

void printSubArbolStream(raiz * _raiz, raiz * _origen, int anillo, int rule, std::ofstream & fs)
{
    int ciclo, produccion;
    raiz sub;
    //si el arbol ya fue visitado retorna la funcion
    if ((* _raiz)==NULL|| (* _raiz)->flag == 2)
        return;
    else
        //si no se marca como visitado
        (* _raiz)->flag = 2;
    
    fs << endl << (*_raiz)->indice << "--{";
    fs << (* _raiz)->lista[0]<<" ";
    //vemos si hay un ciclo
    for (int x = 1 ; x < (* _raiz)->tamanio_lista; x++)
    {
        fs <<", " << (* _raiz)->lista[x];
        //si Xi prodice a Xi es un ciclo de longitud 1
        if(   (* _raiz)->indice == (* _raiz)->lista[x])
        {
            ciclo=1;
        }
    }
    fs << "}\n";
    
    for (int x = 0 ; x < (* _raiz)->tamanio_lista; x++)
    {
        sub = BuscarABB( ( * _origen) ,(* _raiz)->lista[x]);
          printSubArbolStream( &sub, _origen, anillo, rule, fs);
    }
    //si encontro el ciclo
    if(ciclo==1)
        return;
    produccion = evolucion_int((*_raiz)->indice, anillo, rule );
    
    sub = BuscarABB( ( * _origen) ,produccion);
    
    printSubArbolStream( &sub ,  _origen, anillo, rule, fs);
    
}
void printSubArbol(raiz * _raiz, raiz * _origen, int anillo, int rule)
{
    int ciclo, produccion;
    raiz sub;
    //si el arbol ya fue visitado retorna la funcion
    if ((* _raiz)==NULL|| (* _raiz)->flag == 2)
        return;
    else
        //si no se marca como visitado
        (* _raiz)->flag = 2;
    
    cout << endl << (*_raiz)->indice << " : ";
    
    //vemos si hay un ciclo
    for (int x = 0 ; x < (* _raiz)->tamanio_lista; x++)
    {
        cout << (* _raiz)->lista[x]<<" ";
        //si Xi prodice a Xi es un ciclo de longitud 1
        if(   (* _raiz)->indice == (* _raiz)->lista[x])
        {
            ciclo=1;
        }
    }
    for (int x = 0 ; x < (* _raiz)->tamanio_lista; x++)
    {
        sub = BuscarABB( ( * _origen) ,(* _raiz)->lista[x]);
        printSubArbol( &sub, _origen, anillo, rule);
    }
    //si encontro el ciclo
    if(ciclo==1)
        return;
    produccion = evolucion_int((*_raiz)->indice, anillo, rule );
    
    sub = BuscarABB( ( * _origen) ,produccion);
    printSubArbol( &sub ,  _origen, anillo, rule);
    
}

raiz make_matriz_in(int s , int r)
{

    raiz _raiz = NULL;
    int num_nodos;
    int result;
    regla = r;
    int anillo = s;
    num_nodos=  pow(2,anillo); //numero de nodos del grafo
   
    
    for (int x = 0; x < num_nodos; x++)
    {
        result =  evolucion_int(x, anillo, r);
        InsertarABB(&_raiz, result, x);

        // cout<< result << " "<< x<<endl;
    }
    
//    make_matriz_img(matriz, num_nodos,num_nodos );
    return _raiz;
}

/**
 Funcion que crea una matriz AxA de adyacencia a partir de un anillo
 
 */
int ** make_matriz_ady(int anillo , int r)
{
    int ** matriz;
    int num_nodos;
    int result;
    regla = r;

    num_nodos=  pow(2,anillo); //numero de nodos del grafo
    matriz = new int * [num_nodos];
    
    // inicializa la matriz
  
    
    for (int i = 0; i < num_nodos; i++)
    {
        //llena la matriz cuadrada de ceros
        matriz[i] = new int [num_nodos];
        for (int j = 0; j< num_nodos; j++)
        {
            matriz[i][j] = 0;
        }
    }
    
    
    for (int x = 0; x < num_nodos; x++)
    {
        result =  evolucion_int(x, anillo,r);
        matriz [x][result] = 1;
      //  matriz [result][x] = 1;
       // cout<< x << " "<< result<<endl;
    }
    
    //make_matriz_img(matriz, r, num_nodos,num_nodos );
    make_dot(matriz, r, num_nodos,num_nodos );
    return matriz;
}




void make_matriz_img(int ** matriz, int regla,  int x , int y)
{
    cairo_surface_t *surface;
    cairo_t * cr; //  contexto
    int p = 10;
    int WIDTH = x * p;
    int HEIGHT = y * p;
    int STRIDE = (WIDTH * 4);

    unsigned char image[STRIDE*HEIGHT];
   // surface = cairo_image_surface_create_for_data (image, CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT, STRIDE);
    surface = cairo_image_surface_create ( CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
    cr = cairo_create (surface);
    
    cairo_move_to(cr,0,0);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j< y; j++)
        {
            //establece blanco
            if(matriz[i][j]==0)
            {
                cairo_set_source_rgb(cr,255,255,255);
                
            }
            else
            {
                cairo_set_source_rgb(cr,0,0,0);
                
            }
           // cout<< " "<< matriz[i][j];
            cairo_rectangle (cr, i*p ,j*p, p , p );
            cairo_fill (cr);
        }
        //cout<<endl;
    }

    string buf2= to_string(regla)+"_"+to_string(x)+".png";
    
    cairo_surface_write_to_png (surface, buf2.c_str());
    
    cairo_destroy (cr);
    
    cairo_surface_destroy (surface);
    

}


/**
 Funcion que hace una matriz que almacena en m[i][i] el numero de su evolucíon
 */

void make_img(int s, int r)
{
    longitud_semilla = s;
    regla = r;
    
    int  m = 0, n = 0, numero_arb = -1;
    unsigned int c = 0, result=0;

    ofstream fs("graphRegla"+to_string(r)+"Anillo"+to_string(s)+".txt");
    fs << "graph_regla_"<<r<<"_anillo"<<s<<"= ";
    //Graph[{1 -> 2, 2 -> 3, 3 -> 1, 4 -> 5}, DirectedEdges -> False]
    
    if (s%2 == 0)
    {   x = pow(2,s/2);
        y = x;
    }else
    {
        x = pow(2,s/2);
        y = 2*x;
        
    }
    
    matriz = new  int *[x];
    for (int i = 0; i < x; i++)
    {
        matriz[i] = new int [y];
        for (int j = 0; j< y; j++)
        {
            matriz[i][j] = -1;
            
        }
    }
    
    fs << "Graph[\n     {" << endl;
    
     // std::cout << x  << " " << y<<"\n";
    for (int i = 0 ; i <x ; i++ )
    {
        for (int j = 0; j < y; j++)
        {
            
            result =  evolucion_int( c, s, r);
            m =(result/y);
            n =result%y;
            
    //        std::cout <<"\n"<<result<<":"<< m<<" , "<<n<<" ";
            if (matriz[m][n] == -1)
            {
                numero_arb++;
                matriz[m][n] = numero_arb;
                matriz[i][j] = numero_arb;
                
            }
            else
            {
                 matriz[i][j] = matriz[m][n];
            }
            if(x==0 && y == 0)
                fs << to_string(c)+"->"+to_string(result)<<" ";
            else
                fs <<" , " << to_string(c)+"->"+to_string(result);
            c++;
        }
    }
    fs << "}, DirectedEdges -> False]";
    fs.close();
    //std::cout << result << "\n";
   // std::cout << numero_arb << "\n";

    
    

}

void make_dot(int ** matriz, int regla, int x, int y)
{
    string file = "graphRegla"+to_string(regla)+"Anillo"+to_string(x);
    ofstream fs(file+".dot");
    fs << "graph "+file + "\n{\n    graph[center =\"1\",size=\"6,6\"];\n   edge [weight=\"10\",len =\"0.1\"]; \n  node[ shape=point,color=darkslateblue    ];" ;
    
    for(int i = 0; i< x ; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (matriz[i][j]==1)
                fs << "\n "+ to_string(i)+"--"+ to_string(j)+";";
        }
    }
    fs << "\n}";
     fs.close();
    string comando ="fdp -Tsvg  "+file+".dot -o "+file+".svg";
    system("echo hola");

    system(comando.c_str());
}


int evolucion_int(int s, int longitud_semilla, int rule)
{
    int r = 0;
    unsigned char * arreglo, * arreglo_r;
    arreglo = (unsigned char *) std::malloc(sizeof(unsigned char)* longitud_semilla);
    arreglo_r = (unsigned char *) std::malloc(sizeof(unsigned char)* longitud_semilla);
    for (int x = longitud_semilla -1; x >=0 ; x--)
    {
        arreglo[longitud_semilla-x-1] = (s>>x)&1;
    }
    for (int x = 0; x < longitud_semilla; x++)
    {
        if (x == 0)
            arreglo_r[x]= fi(arreglo[longitud_semilla-1], arreglo[x], arreglo[x+1] , rule);
        else if (x == longitud_semilla-1)
            arreglo_r[x]= fi(arreglo[x-1], arreglo[x], arreglo[0],rule );
        else
            arreglo_r[x]= fi(arreglo[x-1], arreglo[x], arreglo[x+1],rule );
    }

    for (int x = longitud_semilla -1; x >=0 ; x--)
    {
        r += (static_cast<int>(arreglo_r[x]))<<(longitud_semilla-x-1);
    }
    
    /* std::cout<<"***********\n";
    for (int x = 0; x < longitud_semilla; x++)
    {
        if(arreglo[x]==1)
            std::cout<<"1";
        else
            std::cout<<"0";
    }
    std::cout<<"\n";
    for (int x = 0; x < longitud_semillla; x++)
    {
        if(arreglo_r[x]==1)
            std::cout<<'1';
        else
            std::cout<<'0';
    }
    
   std::cout << " "<<s<<" , "<<r<<" ";
    
    std::cout<<"***********\n";
    */
    return r;
    
}


unsigned char fi(unsigned char x0, unsigned char x1, unsigned char x2, int regla )
{
    
    return (regla>>(4*x0 +2*x1 + x2))&1;
    
}




int main(int argc, const char * argv[])
{
    int fractales []= {26,94,154,164, 18,22,60,90, 122, 126, 105, 146, 150};
   // int fractales []= {90};
    int c1[] ={0, 8, 32, 40, 128, 136, 160, 168};
    int c2[] ={1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 19, 23,24, 25, 26, 27, 28, 29, 33, 34, 35, 36, 37, 38, 42, 43, 44, 46, 50, 51, 56, 57, 58, 62, 72, 73, 74, 76, 77, 78, 94, 104, 108, 130, 132, 134, 138, 140, 142,152, 154, 156, 162, 164, 170, 172, 178, 184, 200,204, 232};
    int c3[] ={18, 22, 30, 45, 60, 90, 105, 122, 126, 146, 150};
    int c4[] ={41, 54, 106, 110};
    int anillo[]={2,4,8,16};
    
    raiz r;
    int ciclos;
   for (int y = 0; y < 13; y++)
        {
            for (int x = 0; x < 16; x++)
            {// make_img(x, reglas[y]);
               // int ** mat = make_matriz_ady(anillo[x],fractales[0]);
                // r = make_matriz_in( a, rule);
                ciclos= 0;
                r = make_matriz_in( x, fractales[y]);
                printAllSubArbol( &r , &r , x, fractales[y], &ciclos );
                free(r);
            }
        }
    

   
    
    //Enorden(r);
   
    
    return 0;
}



