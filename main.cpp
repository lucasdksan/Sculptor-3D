#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sculptor.h>

using namespace std;
//Exemplo que contém todos as funções
int main()
{
    string arqOFF="arqOFF";
    string arqVECT = "arqVECT";
    Sculptor a(100,100,100);
    a.setColor(1,0,0,1);
    a.putSphere(49,49,49,50);
    a.cutEllipsoid(0,0,0,50,40,30);
    a.setColor(0.5,0.5,0.8,1);
    a.putEllipsoid(30,30,30,50,40,30);
    a.cutBox(40,40,40,70,70,70);
    a.setColor(0,0.8,1,1);
    a.putBox(40,40,40,71,71,71);
    a.cutVoxel(0,0,0);
    a.setColor(0,0,0,1);
    a.putVoxel(0,0,0);
    a.writeVECT(arqVECT);
    a.writeOFF(arqOFF);
    return 0;
}
