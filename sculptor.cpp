#include "sculptor.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
//Alocação da Matriz 3D.
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nl=_nx;nc=_ny;np=_nz;
    if(nl<=0||nc<=0||np<=0){
        nl=nc=np=0;
    }
    v=new Voxel**[np];
    if(v==nullptr){
        cout<<"Erro na alocação."<<endl;
        exit(0);
    }
    v[0]=new Voxel*[np*nc];
    if(v[0]==nullptr){
        cout<<"Erro na alocação."<<endl;
        exit(0);
    }
    v[0][0]=new Voxel[nl*nc*np];
    if(v[0][0]==nullptr){
        cout<<"Erro na alocação."<<endl;
        exit(0);
    }
    for(int i=1;i<np;i++){
        v[i]=v[i-1]+nc;
    }
    for(int i=1;i<(np*nc);i++){
        v[0][i]=v[0][i-1]+nl;
    }
}
//Liberar a memória utilizada.
Sculptor::~Sculptor(){
    if(nl==0||nc==0||np==0){
        return;
    }
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}
//Atribuir as cores.
void Sculptor::setColor(float _r, float _g, float _b, float alpha){
    //Verificação das cores utilizadas.
    if((_r<=1||_r>=0)||(_g<=1||_g>=0)||(_b<=1||_b>=0)||(alpha<=1||alpha>=0)){
        r=_r;g=_g;b=_b;a=alpha;
    }
    else {
        cout<<"Cores invalidas"<<endl;
        exit(1);
    }
}
//Criar um Voxel.
void Sculptor::putVoxel(int x, int y, int z){
    //Verificação das dimensões atribuida.
    if(x<0 || x>nl || y<0 || y>nc || z<0 || z>np){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    //Atribuições das cores para o Voxel selecionado.
    else{
        v[x][y][z].isOn=true;
        v[x][y][z].red=r;
        v[x][y][z].blue=b;
        v[x][y][z].green=g;
        v[x][y][z].alpha=a;
    }
}
//Cortar um Voxel.
void Sculptor::cutVoxel(int x, int y, int z){
    //Verificação das dimensões atribuida.
    if(x<0 || x>nl || y<0 || y>nc || z<0 || z>np){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    //Utilizando o isOn para efetuar o corte.
    else{
        v[x][y][z].isOn=false;
    }
}
//Criar uma sequência de Voxels em forma de caixa.
void Sculptor::putBox(int x0, int y0, int z0, int x1, int y1, int z1){
    //Verificação das dimensões atribuida.
    if(x0<0 || x0>nl || y0<0 || y0>nc || z0<0 || z0>np || x1<0 || x1>nl || y1<0 || y1>nc || z1<0 || z1>np){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    else{
        //Análisando os Voxels no intervalo determinado e atribuindo as cores.
        for(int i=x0;i<x1;i++){
            for(int j=y0;j<y1;j++){
                for(int k=z0;k<z1;k++){
                    v[i][j][k].isOn=true;
                    v[i][j][k].red=r;
                    v[i][j][k].blue=b;
                    v[i][j][k].green=g;
                    v[i][j][k].alpha=a;
                }
            }
        }
    }
}
//Cortar uma sequência de Voxels em forma de caixa.
void Sculptor::cutBox(int x0, int y0, int z0, int x1, int y1, int z1){
    //Verificação das dimensões atribuida.
    if(x0<0 || x0>nl || y0<0 || y0>nc || z0<0 || z0>np || x1<0 || x1>nl || y1<0 || y1>nc || z1<0 || z1>np){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    //Utilizando o isOn para efetuar o corte em forma de caixa.
    else{
        for(int i=x0;i<=x1;i++){
            for(int j=y0;j<=y1;j++){
                for(int k=z0;k<=z1;k++){
                    v[i][j][k].isOn=false;
                }
            }
        }
    }
}
//Criar uma sequência de Voxels em forma de esfera.
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    //Verificação das dimensões atribuida.
    if(xcenter<0 || xcenter>nl || ycenter<0 || ycenter>nc || zcenter<0 || zcenter>np || (radius+xcenter)>nl || (radius+ycenter)>nc || (radius+zcenter)>np || radius < 0){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    //Análisando os Voxels no intervalo determinado e atribuindo as cores.
    else{
        //Variavel para armazenar o raio efetuando a transformação de int para double.
        double rd=radius/2.0;
        //Variavel para a distância da esfera em relação a todos os Voxel.
        double dist;
        for(int i=0;i<nl;i++){
            for(int j=0;j<nc;j++){
                for(int k=0;k<np;k++){
                    //Equação da esfera.
                    dist = (i-xcenter / 2.0 ) * (i-xcenter / 2.0 ) / (rd * rd) +
                              (j-ycenter / 2.0 ) * (j-ycenter / 2.0 ) /(rd * rd) +
                              (k-zcenter / 2.0 ) * (k-zcenter / 2.0 ) / (rd * rd);
                    //Condição para efetuar o desenho da esfera.
                    if(dist<=1.0){
                        v[i][j][k].isOn=true;
                        v[i][j][k].red=r;
                        v[i][j][k].blue=b;
                        v[i][j][k].green=g;
                        v[i][j][k].alpha=a;
                    }
                }
            }
        }
    }
}
//Cortar uma sequência de Voxels em forma de esfera.
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    //Verificação das dimensões atribuida.
    if(xcenter<0 || xcenter>nl || ycenter<0 || ycenter>nc || zcenter<0 || zcenter>np || (radius+xcenter)>nl || (radius+ycenter)>nc || (radius+zcenter)>np || radius < 0){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    else{
        //Variavel para armazenar o raio, assim, efetuando a transformação de int para double.
        double rd=radius/2.0;
        //Variavel para a distância da esfera em relação a todos os Voxel.
        double dist;
        for(int i=0;i<nl;i++){
           for(int j=0;j<nc;j++){
               for(int k=0;k<np;k++){
                   //Equação da esfera.
                   dist = (i-xcenter / 2.0 ) * (i-xcenter / 2.0 ) / (rd * rd) +
                   (j-ycenter / 2.0 ) * (j-ycenter / 2.0 ) /(rd * rd) +
                   (k-zcenter / 2.0 ) * (k-zcenter / 2.0 ) / (rd * rd);
                   //Condição para efetuar o corte da esfera.
                   if(dist<=1){
                       v[i][j][k].isOn=false;
                   }
                }
            }
        }
    }
}
//Criar uma sequência de Voxels em forma de elipsóide.
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    //Verificação das dimensões atribuida.
    if(xcenter<0 || xcenter>nl || ycenter<0 || ycenter>nc || zcenter<0 || zcenter>np || (xcenter+rx)>nl || (ycenter+ry)>nc || (zcenter+rz)>np || rx<0 || ry<0 || rz<0){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    else{
        //Variaveis para armazenarem os raios, assim, efetuando a transformação de int para double.
        double _rx=rx/2.0,_ry=ry/2.0,_rz=rz/2.0;
        //Variavel para a distância da esfera em relação a todos os Voxel.
        double dist;
        for(int i=0;i<nl;i++){
            for(int j=0;j<nc;j++){
                for(int k=0;k<np;k++){
                    //Equação da elipsóide.
                    dist = (i-xcenter / 2.0 ) * (i-xcenter / 2.0 ) / (_rx * _rx) +
                    (j-ycenter / 2.0 ) * (j-ycenter / 2.0 ) /(_ry * _ry) +
                    (k-zcenter / 2.0 ) * (k-zcenter / 2.0 ) / (_rz * _rz);
                    //Condição para efetuar o desenho da elipsóide.
                    if((dist<=1)&&(i<nl&&i>=0)&&(j<nc&&j>=0)&&(k<np&&k>=0)){
                        v[i][j][k].isOn=true;
                        v[i][j][k].red=r;
                        v[i][j][k].blue=b;
                        v[i][j][k].green=g;
                        v[i][j][k].alpha=a;
                    }
                }
            }
        }
    }
}
//Cortar uma sequência de Voxels em forma de elipsóide.
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    //Verificação das dimensões atribuida.
    if(xcenter<0 || xcenter>nl || ycenter<0 || ycenter>nc || zcenter<0 || zcenter>np || (xcenter+rx)>nl || (ycenter+ry)>nc || (zcenter+rz)>np || rx<0 || ry<0 || rz<0){
        cout <<"Dimensoes erradas, digite novamente"<<endl;
        exit(1);
    }
    else{
        //Variaveis para armazenarem os raios, assim, efetuando a transformação de int para double.
        double _rx=rx/2.0,_ry=ry/2.0,_rz=rz/2.0;
        //Variavel para a distância da esfera em relação a todos os Voxel.
        double dist;
        for(int i=0;i<nl;i++){
            for(int j=0;j<nc;j++){
                for(int k=0;k<np;k++){
                    //Equação da elipsóide.
                    dist = (i-xcenter / 2.0 ) * (i-xcenter / 2.0 ) / (_rx * _rx) +
                    (j-ycenter / 2.0 ) * (j-ycenter / 2.0 )/(_ry * _ry) +
                    (k-zcenter / 2.0 ) * (k-zcenter / 2.0 )/(_rz * _rz);
                    //Condição para efetuar o corte da elipsóide.
                    if(dist<=1){
                        v[i][j][k].isOn=false;
                    }
                }
            }
        }
    }
}
//Criar arquivo para leitura do desenho, contendo as dimensões e as cores.
void Sculptor::writeOFF(string filename){
    //Variavel para efetuar as funções de fluxos.
    ofstream fout2;
    //Contador para o número de vertices.
    int Nvertices=0;
    //Contador para o número de faces.
    int Nfaces=0;
    //Variavel auxiliar na execução e determinação de cada face para cada Voxel.
    int aux=0;
    //Abrindo arquivo.
    fout2.open("C:/Users/luquinha/Documents/C&T/PA/programas/C++/voxel/file/"+filename+".off");
    //Condição para determinar se o arquivo foi aberto.
    if(fout2.is_open()){
        cout << "arquivo OFF foi aberto\n";
    }
    else{
        cout << "arquivo OFF nao foi aberto\n";
        exit(1);
    }
    //Primeira linha do arquivo. Linha de reconhecimento.
    fout2<<"OFF"<<endl;
    //Contar a quantidade de vertices e faces. Obs.: isOn deve ser verdadeiro.
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    Nvertices=Nvertices+8;
                    Nfaces=Nfaces+6;
                }
            }
        }
    }
    //Segunda linha do arquivo. Linha para mostra quantidade de vertices e faces.
    fout2<<Nvertices<<" "<<Nfaces<<" "<<0<<endl;
    //Dimensionamento de cada vertice em relação a cada Voxel com isOn true. Obs.: dimensão de cada Voxel 1.
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                        fout2<<i-0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout2<<i-0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout2<<i+0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout2<<i+0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout2<<i-0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                        fout2<<i-0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout2<<i+0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout2<<i+0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                }
            }
        }
    }
    //Dimensionar cada face de cada Voxel e atribuindo as cores correspondente.
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    fout2<<4<<" "<<aux+0<<" "<<aux+3<<" "<<aux+2<<" "<<aux+1<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+4<<" "<<aux+5<<" "<<aux+6<<" "<<aux+7<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+0<<" "<<aux+1<<" "<<aux+5<<" "<<aux+4<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+0<<" "<<aux+4<<" "<<aux+7<<" "<<aux+3<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+3<<" "<<aux+7<<" "<<aux+6<<" "<<aux+2<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+1<<" "<<aux+2<<" "<<aux+6<<" "<<aux+5<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    aux=aux+8;
                }
            }
        }
    }
    //Condição para apresentar o fim do arquivo.
    if(fout2.is_open()){
        cout << "arquivo OFF salvo"<<endl;
    }

}
//Criar arquivo para armazenar quantidades de poligonos,vertices e posições.
void Sculptor::writeVECT(string filename){
    //Variavel para efetuar as funções de fluxos.
    ofstream fout;
    //Contador.
    int cont=0;
    //Abrindo arquivo.
    fout.open("C:/Users/luquinha/Documents/C&T/PA/programas/C++/voxel/file/"+filename+".vect");
    //Condição para determinar se o arquivo foi aberto.
    if(fout.is_open()){
        cout << "arquivo VECT foi aberto\n";
    }
    else{
        cout << "arquivo VECT nao foi aberto\n";
        exit(1);
    }
    //Primeira linha do arquivo. Linha de reconhecimento.
    fout<<"VECT"<<endl;
    //Contagem de cada Voxel com isOn true.
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    cont=cont+1;
                }
            }
        }
    }
    fout<<cont<<" "<<cont<<" "<<cont<<endl;
    for(int i=1;i<cont-1;i++){
        fout<<1<<" ";
    }
    fout<<1<<endl;
    for(int i=1;i<cont-1;i++){
        fout<<1<<" ";
    }
    fout<<1<<endl;
    //Linha do arquivo para salvar quais Voxels estão com isOn true.
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    fout<<i<<" "<<j<<" "<<k<<endl;
                }
            }
        }
    }
    //Linha do arquivo para salvar as cores de cada Voxel.
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    fout<<v[i][j][k].red<<" "<<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                }
            }
        }
    }
    //Condição para apresentar o fim do arquivo.
    if(fout.is_open()){
        cout << "arquivo VECT salvo"<<endl;
    }
}
