#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include <string>
#include <stdio.h>
using namespace std;

class Principal
{
public:
    Principal();
    void Graficar();
    void PedirDatos();
    void ClienteColaEspera(int n);
    void ClienteCompra();
    void RevisionCarretas();
    void ClienteCaja(int cliente, int carreta);
    void TiempoCumplido();
};

#endif // PRINCIPAL_H
