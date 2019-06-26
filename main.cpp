#include <iostream>
#include <stdlib.h>
#include <QString>
#include <stdio.h>
#include <string.h>
#include <list>
#include <principal.h>
using namespace std;


/*                       Funcion Principal
---------------------------------------------------------------------*/

int main()
{
    Principal *p = new Principal();
    int op;
 cout<<"*-*-*-*-*-*-*-*-(M I N I M A R K E T)*-*-*-*-*-*-*-*-"<<endl;
 cout<<"*-*-*-*-*-*-*-*-( 2 0 1 7 0 0 3 7 8 )*-*-*-*-*-*-*-*-"<<endl;
 p->PedirDatos();
 p->Graficar();

 do{
     cout<< "Cuantos clientes entran al MiniMarket?: "<<endl; cin>> op;
     p->ClienteColaEspera(op);
     p->Graficar();
 }while(op!=0);

}


