#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

//estrutura para os blocos.
struct Voxel{
    float red,green,blue; //Cores.
    float alpha;    //Transparência.
    bool isOn; //incluir ou não.
};
//classe para moldar.
class Sculptor{
private:
    Voxel ***v;//Matriz 3D.
    int nl,nc,np;//Dimensões.
    float r,g,b,a;//Cores.
public:
    //Alocação da Matriz 3D.
    Sculptor(int _nx=0, int _ny=0, int _nz=0);
    //Liberar a memória utilizada.
    ~Sculptor();
    //Atribuir as cores.
    void setColor(float _r, float _g, float _b, float alpha);
    //Criar um Voxel.
    void putVoxel(int x, int y, int z);
    //Cortar um Voxel.
    void cutVoxel(int x, int y, int z);
    //Criar uma sequência de Voxels em forma de caixa.
    void putBox(int x0, int y0, int z0, int x1, int y1, int z1);
    //Cortar uma sequência de Voxels em forma de caixa.
    void cutBox(int x0, int y0, int z0, int x1, int y1, int z1);
    //Criar uma sequência de Voxels em forma de esfera.
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    //Cortar uma sequência de Voxels em forma de esfera.
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    //Criar uma sequência de Voxels em forma de elipsóide.
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    //Cortar uma sequência de Voxels, Em forma de elipsóide.
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    //Criar arquivo para leitura do desenho, contendo as dimensões e as cores.
    void writeOFF(string filename);
    //Criar arquivo para armazenar quantidades de poligonos,vertices e posições.
    void writeVECT(string filename);
};
#endif // SCULPTOR_H
