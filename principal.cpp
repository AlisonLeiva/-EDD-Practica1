#include "principal.h"
#include <iostream>
#include <stdlib.h>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <list>
#include  <listacirculardoble.h>
#include <pila.h>
#include  <listadoble.h>
#include <cola.h>
#include <ctime>

static ListaCircularDoble *Compras = new ListaCircularDoble();
static Pila *Pila1 = new Pila();
static Pila *Pila2 = new Pila();
static Cola *ColaEspera = new Cola();
static Cola *ColaPagar = new Cola();
static ListaDoble *Caja = new ListaDoble();
static int i=0;
static int contadorCliente=1;
static int contadorCarretas = 1;
static int CantidadCajas;
static int paso=1;
time_t TiempoActual;
struct tm turno;

Principal::Principal()
{
}
//******************************************CLIENTE ENTRA A COLA DE ESPERA ********************************************
void Principal::ClienteColaEspera(int NoClientes){
    for (int j = 0; j<NoClientes;j++) {
        cout<<"******************************Paso "<<paso<<"*********************************"<<endl;
        cout<<"llega Cliente "<< contadorCliente <<" se agrega a la cola de espera de carreta."<<endl;
        ColaEspera->EncolarCliente(contadorCliente,NULL);
        contadorCliente++;
            if( !(Pila1->estaVacia()) || !(Pila2->estaVacia()) )
            {
                ClienteCompra();
            }else{
                TiempoCumplido();
            }
        paso++;
        cout<<endl;
    }
}
//******************************************CLIENTE TOMA CARRETA Y SE DIRIGE A COMPRAR ********************************************
void Principal::ClienteCompra(){
     while(Pila1->Size()!=0 && ColaEspera->Size()!=0 || Pila2->Size()!=0 && ColaEspera->Size()!=0 ){
         if(Pila1->Size()!=0  && ColaEspera->Size()!=0){
                NodoCola *cliente = ColaEspera->Desencolar();
                NodoPila *carreta = Pila1->Pop();

                cout<<"Cliente "<< cliente->id <<" toma Carreta: "<<carreta->id<<", se dirige a comprar"<<endl;
                Compras->Insertar(cliente->id,carreta->id);

             }else if(Pila2->Size()!=0 && ColaEspera->Size()!=0){
                NodoCola *cliente = ColaEspera->Desencolar();
                NodoPila *carreta = Pila2->Pop();

                cout<<"Cliente "<< cliente->id <<" toma Carreta: "<<carreta->id<<", se dirige a comprar"<<endl;
                Compras->Insertar(cliente->id,carreta->id);
            }
       }
//******************************************CLIENTE SE DIRIGE A COLA DE PAGO********************************************
  srand(time(0));
  int posicion= 1+rand()%100;
           if(posicion < Compras->Size()){
               NodoCompra *Cliente = Compras->Eliminar(posicion);
               ColaPagar->EncolarCliente(Cliente->id,Cliente->carreta);
               cout<<"Cliente "<< Cliente->id<<", se dirige a cola de pago."<<endl;
           }else{
               TiempoCumplido();
            }
               while(Caja->Disponible()  && ColaPagar->Size()!=0){
                        NodoCola *ClienteACaja =ColaPagar->Desencolar();
                        ClienteCaja(ClienteACaja->id,ClienteACaja->carreta);
               }
}
//******************************************CLIENTE SE DIRIGE A CAJA  ***********************************************
void Principal::ClienteCaja(int cliente, int carreta){
    TiempoActual = time(NULL);
    turno = * localtime(&TiempoActual);
    int segundos = (turno.tm_min)*60 + turno.tm_sec;
    Caja->BuscarDisponible(cliente,carreta,segundos);
    TiempoCumplido();
}
//******************************************VERIFICACION DE LAS CAJAS***********************************************
void Principal::TiempoCumplido(){
        TiempoActual = time(NULL);
        turno = * localtime(&TiempoActual);
        int segundos = (turno.tm_min)*60 + turno.tm_sec;
        Caja->ActualizarCajas(segundos, Pila1, Pila2);
}
void Principal::PedirDatos(){
    system("color 0b");

    int _dato;
    string nombre;

    cout<< "\n Cantidad de clientes en cola de espera de carretas: "; cin>> _dato;

    for (int j = 0;j<_dato;j++) {
        ColaEspera->EncolarCliente(contadorCliente,NULL);
        contadorCliente++;
    }

    cout<< "\n Cantidad de carretas por pila: "; cin>> _dato;
    for (int j = 0;j<_dato;j++) {
        Pila1->Push(contadorCarretas);
        contadorCarretas++;
            }
    for (int j = 0;j<_dato;j++) {
        Pila2->Push(contadorCarretas);
        contadorCarretas++;
            }

    cout<< "\n Cantidad de clientes comprando: "; cin>> _dato;
    for (int j = 0;j<_dato;j++) {
        Compras->Insertar(contadorCliente,contadorCarretas);
        contadorCliente++;
        contadorCarretas++;
    }


    cout<< "\n Cantidad de clientes en cola de pagos: "; cin>> _dato;
    for (int j = 0;j<_dato;j++) {
        ColaPagar->EncolarCliente(contadorCliente,contadorCarretas);
        contadorCliente++;
        contadorCarretas++;

    }

    cout<< "\n Cantidad de cajas: "; cin>> CantidadCajas;
    for (int j = 1;j<=CantidadCajas;j++) {
        Caja->Insertar(j,NULL,NULL);
    }

}

void Principal::Graficar()
{
    QString grafo;

    grafo = "digraph Grafica { subgraph Pilas_Carretas{ ";
    grafo += Pila1->SubgraphPila("Pila1");
    grafo += Pila2->SubgraphPila("Pila2");
    grafo += "}";

    grafo += ColaEspera->Subgraph("ColaEspera", "E6C1EC");
    grafo += Compras->Subgraph();
    grafo += ColaPagar->Subgraph("ColaPagar","F1ADA2");
    grafo += Caja->Subgraph();
    grafo += "subgraph Imagen{nodeImage [shape = none, label =\"\" penwidth =0 width = 1.5, image=\"C:\\Users\\GAMING\\Desktop\\EDD_VACACIONES2019\\build-Estructuras-Desktop_Qt_5_12_2_MinGW_64_bit-Debug\\Grafica.jpg\"];  } }";
    i++;
    QFileInfo fi("temp");
        QString path = fi.absolutePath() +"/";
        QFile qFile(path+"Simulacion"+QString::number(i)+".txt");
        if(qFile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&qFile);
            out << grafo;
            qFile.close();
        }
        QString cadenaComando = "dot -Tjpg " + path + "Simulacion"+QString::number(i)+".txt -o " + path+"Simulacion"+QString::number(i)+".jpg ";
        system(cadenaComando.toUtf8().constData());

        QString imagen =   path+"Simulacion"+QString::number(i)+".jpg";
        system(imagen.toUtf8().constData());


}
