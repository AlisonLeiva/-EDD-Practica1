#include "pila.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <iostream>
using namespace std;
//-----------------------------------------  PILA       ---------------------------------------

NodoPila::NodoPila(int id){
    this->id = id;
    this->siguiente = NULL;
}

Pila::Pila(){
    this->inicio  = NULL;
}

void Pila::Push(int id){
    NodoPila *nuevo = new NodoPila(id);
            nuevo->siguiente=inicio;
            inicio = nuevo;
}
bool Pila::estaVacia(){
    return  inicio == NULL;
}

NodoPila *Pila::Pop(){
    if(inicio!=NULL){
        NodoPila *actual = inicio;
        inicio = inicio->siguiente;
        return actual;
    }
}

int Pila::Size(){
    NodoPila *aux = inicio;
    int i =0;
     while(aux!=NULL){
         i++;
         aux = aux->siguiente;
     }
     return i;
}

void Pila::Mostrar(){
    NodoPila *aux = inicio;
     while(aux!=NULL){
         cout<<aux->id<<endl;
         aux = aux->siguiente;
     }
}


QString Pila::SubgraphPila(QString nombre)
{
     NodoPila *aux = inicio;
     QString nodos="";

     if(!estaVacia()){
      nodos +="\n subgraph "+ nombre+" {\n node [shape=box fontname=\"Calibri Light\"] \n "+nombre+" [label=<<table bgcolor = \"#B5B9E9\" "+
             "border=\"0\"  cellborder=\"1\"  cellspacing=\"0\">";

     while(aux!=NULL)
         {
             nodos +="<tr><td> Carreta " +QString::number(aux->id) + "</td></tr> \n";
              aux = aux->siguiente;
         }

     nodos += "</table>>]; }";
}
return nodos;
}



