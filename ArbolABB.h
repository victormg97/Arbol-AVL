#include <stdlib.h>
#include <stdio.h>

typedef struct _nodo{
	int dato;
	struct _nodo *hizq,*hder;
}Abb;

Abb *InsertaValorArbol(Abb *arbol,int dato){
	if(arbol==NULL){
		Abb *arbolAux=malloc(sizeof(struct _nodo));
		arbolAux->dato=dato;
		arbolAux->hizq=arbolAux->hder=NULL;
		return(arbolAux);
	}
	if(arbol->dato > dato){
		arbol->hizq=InsertaValorArbol(arbol->hizq,dato);
	}
	else if(arbol->dato < dato){
		arbol->hder=InsertaValorArbol(arbol->hder,dato);
	}
	return(arbol);
}

Abb *leeArchivoEnABB(const char *nombreArchivoDatos){
    Abb *arbol=NULL;
    int i,n, *numeros;
    FILE *archivo = fopen(nombreArchivoDatos,"rb");
    fread(&n, sizeof(int), 1, archivo);
    numeros = malloc(sizeof(int)*n);
    fread(numeros, sizeof(int), n, archivo);
    arbol=InsertaValorArbol(arbol,numeros[0]);
    for(i = 1; i < n; i++){
        InsertaValorArbol(arbol,numeros[i]);
    }
    free(numeros);
    return(arbol);
}

int Contar(Abb *arbol){
    if(arbol==NULL){
        return(0);
    }else{
        return(Contar(arbol->hizq)+1+(Contar(arbol->hder)));
    }
}

void EscribeArbol(Abb *arbol,FILE *miArchivo){
    if(arbol!=NULL){
        EscribeArbol(arbol->hizq,miArchivo);
        fwrite(&arbol->dato,sizeof(int),1,miArchivo);
        EscribeArbol(arbol->hder,miArchivo);
    }
}

/**int generaArchivoOrdenado(Abb *arbol , const char *nombreArchivoOrdenado){
    int cantidad=0;
 	FILE *miArchivo=fopen(nombreArchivoOrdenado,"wb");
 	cantidad=Contar(arbol);
 	fwrite(&cantidad,sizeof(int),1,miArchivo);
 	EscribeArbol(arbol,miArchivo);
	fclose(miArchivo);
}**/

void eliminaAbb(Abb *arbol){
    if(arbol==NULL){
        return;
    }
    eliminaAbb(arbol->hizq);
    eliminaAbb(arbol->hder);
    free(arbol);
}
