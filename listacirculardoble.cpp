#include "listacirculardoble.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <iostream>
using namespace std;

//-----------------------------------------  LISTA DOBLEMENTE ENLAZADA       ---------------------------------------

int size;

NodoCompra::NodoCompra(int id, int carreta){
    this->id = id;
    this->carreta = carreta;
    this->siguiente = NULL;
    this->anterior = NULL;
}

ListaCircularDoble::ListaCircularDoble(){
    this->inicio = this->fin = NULL;
}

void ListaCircularDoble::Insertar(int cliente, int carreta){
    NodoCompra *nuevoD = new NodoCompra(cliente,carreta);

    if(inicio == NULL){
         inicio = nuevoD;
         inicio->siguiente=inicio;
         nuevoD->anterior = fin;
         fin = nuevoD;
    }else{
            fin->siguiente = nuevoD;
            nuevoD->siguiente = inicio;
            nuevoD->anterior = fin;
            fin = nuevoD;
            inicio->anterior = fin;
    }
    size++;
}


NodoCompra *ListaCircularDoble::Eliminar(int  posicion){
    NodoCompra *aux = inicio;
    NodoCompra *aux2 = fin;
    int i=1;
    do{
       if(i==posicion){
                if(aux==inicio){
                    inicio = inicio->siguiente;
                    fin->siguiente=inicio;
                    inicio->anterior=fin;
                    size--;
                }else if(aux==fin){
                    fin = aux2;
                    inicio->anterior = fin;
                    fin->siguiente = inicio;
                    size--;

                }else{
                    aux2->siguiente= aux->siguiente;
                    aux->siguiente->anterior=aux2;
                    size--;

                }
                return aux;
        }
        i++;
        aux2=aux;
        aux = aux->siguiente;
    }while(aux!=inicio);
}

int ListaCircularDoble::Size(){
    return size;
}


void ListaCircularDoble::Mostrar(){
    NodoCompra *aux = inicio;

    do{
        cout<<aux->id<<endl;
        aux = aux->siguiente;
    } while(aux!=inicio);

}

QString ListaCircularDoble::Subgraph()
{
     NodoCompra *aux = inicio;
     QString texto = "";

   if(Size()!=0){

       texto += " \n subgraph Compras{  rankdir=TB; ranksep = 1; node [shape = record, style=filled, fontname=\"Calibri Light\", fillcolor=\"#A2F1E2\" penwidth =0 width = 1]";
           do{
               texto +="ClienteCompra" + QString::number(aux->id)+" [penwidth =0 label =\"Cliente " + QString::number(aux->id)+"\\n Carreta "+QString::number(aux->carreta)+"\"]; \n";
               aux = aux->siguiente;
           } while(aux!=inicio);


           aux = inicio;
           do
           {
               texto +="ClienteCompra" +QString::number(aux->id) + "->";
                aux = aux->siguiente;
                texto +="ClienteCompra" + QString::number(aux->id) +"; \n";
           } while(aux!=inicio);


           aux = fin;
          do
           {
                texto +="ClienteCompra" +QString::number(aux->id) + "->";
                aux = aux->anterior;
                texto +="ClienteCompra" + QString::number(aux->id) +"; \n";
           }while(aux!=fin);
           texto += "}";

   }
     return texto;
}
