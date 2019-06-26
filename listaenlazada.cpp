#include <iostream>
#include <stdlib.h>
using namespace std;

struct nodo{
       int id;        // en este caso es un numero entero
       struct nodo *siguiente;
};

typedef struct nodo *ListaEnlazada;

void insertarInicio(ListaEnlazada &lista, int valor)
{
    ListaEnlazada q;
    q = new(struct nodo);
    q->id = valor;
    q->siguiente = lista;
    lista  = q;
}

void insertarFinal(ListaEnlazada &lista, int valor)
{
    ListaEnlazada t, q = new(struct nodo);
    q->id  = valor;
    q->siguiente = NULL;

    if(lista==NULL)
    {
        lista = q;
    }
    else
    {
        t = lista;
        while(t->siguiente!=NULL)
        {
            t = t->siguiente;
        }
        t->siguiente = q;
    }

}

int insertarAntesDespues()
{
    int _op, band;
    cout<<endl;
    cout<<"\t 1. Antes de la posicion           "<<endl;
    cout<<"\t 2. Despues de la posicion         "<<endl;

    cout<<"\n\t Opcion : "; cin>> _op;

    if(_op==1)
        band = -1;
    else
        band = 0;

    return band;
}

void insertarElemento(ListaEnlazada &lista, int valor, int pos)
{
    ListaEnlazada q, t;
    int i;
    q = new(struct nodo);
    q->id = valor;

    if(pos==1)
    {
        q->siguiente = lista;
        lista = q;
    }
    else
    {
        int x = insertarAntesDespues();
        t = lista;

        for(i=1; t!=NULL; i++)
        {
            if(i==pos+x)
            {
                q->siguiente = t->siguiente;
                t->siguiente = q;
                return;
            }
            t = t->siguiente;
        }
    }
    cout<<"   Error...Posicion no encontrada..!"<<endl;
}

void buscarElemento(ListaEnlazada lista, int valor)
{
    ListaEnlazada q = lista;
    int i = 1, band = 0;

    while(q!=NULL)
    {
        if(q->id==valor)
        {
            cout<<endl<<" Encontrada en posicion "<< i <<endl;
            band = 1;
        }
        q = q->siguiente;
        i++;
    }

    if(band==0)
        cout<<"\n\n Numero no encontrado..!"<< endl;
}

void reportarLista(ListaEnlazada lista)
{
     int i = 0;

     while(lista != NULL)
     {
          cout <<"Nodo"<< i+1 <<" [label =\"" << lista->id <<"\"width = 1.5, group =1]; " << endl;
          lista = lista->siguiente;
          i++;
     }
}


void eliminarElemento(ListaEnlazada &lista, int valor)
{
    ListaEnlazada p, ant;
    p = lista;

    if(lista!=NULL)
    {
        while(p!=NULL)
        {
            if(p->id==valor)
            {
                if(p==lista)
                    lista = lista->siguiente;
                else
                    ant->siguiente = p->siguiente;

                delete(p);
                return;
            }
            ant = p;
            p = p->siguiente;
        }
    }
    else
        cout<<" Lista vacia..!";
}

void eliminaRepetidos(ListaEnlazada &lista, int valor)
{
    ListaEnlazada q, ant;
    q = lista;
    ant = lista;

    while(q!=NULL)
    {
        if(q->id==valor)
        {
            if(q==lista) // primero elemento
            {
                lista = lista->siguiente;
                delete(q);
                q = lista;
            }
            else
            {
                ant->siguiente = q->siguiente;
                delete(q);
                q = ant->siguiente;
            }
        }
        else
        {
            ant = q;
            q = q->siguiente;
        }

    }// fin del while

    cout<<"\n\n Valores eliminados..!"<<endl;
}
