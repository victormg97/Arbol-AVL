#include <stdio.h>
#include <stdlib.h>
#include "ArbolABB.h"
#include "ArbolAVL.h"

int main(){
    AVL *arbolAVL=NULL;
    arbolAVL=InsertarValorArbolAVL(arbolAVL,10);
    arbolAVL=InsertarValorArbolAVL(arbolAVL,20);
    arbolAVL=InsertarValorArbolAVL(arbolAVL,30);
    arbolAVL=InsertarValorArbolAVL(arbolAVL,40);
    arbolAVL=InsertarValorArbolAVL(arbolAVL,50);
    arbolAVL=InsertarValorArbolAVL(arbolAVL,25);
    //arbolAVL=leeArchivoEnAVL("file10e6");
    //arbolAVL=leeArchivoEnAVL("file10");
    //inOrden(arbolAVL);
    Info(arbolAVL);
    printLevelOrder(arbolAVL);
    return(0);
}
