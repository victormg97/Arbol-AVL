#include <stdlib.h>
#include <stdio.h>

int RotacionIzquierda=0,RotacionDerecha=0,RotacionID=0,RotacionDI=0;

typedef struct _Nodo{
	int dato;
	int altura;
	struct _Nodo *hizq,*hder;
}AVL;

// Una funcion para obtener el máximo entre dos enteros
int max(int a, int b){
    if(a>b) return a;
    else return b;
}

// Obtiene la altura del árbol
int Altura(AVL *p){
    if(p==NULL){
        return 0;
    }else{return p->altura;}
}

AVL *nuevoNodo(int dato){
    AVL *nodo = (struct _Nodo*)malloc(sizeof(AVL));
    nodo->dato   = dato;
    nodo->hizq   = NULL;
    nodo->hder   = NULL;
    nodo->altura = 1;  // Nuevo nodo es inicializado añadiendo una hoja
    return(nodo);
}

// Una función para rotar a la derecha el árbol con raíz en K1
AVL *rotacionDerecha(AVL *K1){

    AVL *K2;
    // Perform rotation
    K2=K1->hder;
    K1->hder=K2->hizq;
    K2->hizq=K1;

    // Update heights
    K1->altura = 1 + max(Altura(K1->hizq), Altura(K1->hder));
    K2->altura = 1 + max(Altura(K2->hizq), K1->altura);

    // Return new root
    return K2;
}

// Una función para rotar a la izquierda el árbol con raíz en K2
AVL *rotacionIzquierda(AVL *K2){

    AVL *K1;
    // Realiza la rotación
    K1=K2->hizq;
    K2->hizq=K1->hder;
    K1->hder=K2;

    //  Actualiza las alturas
    K2->altura = 1 + max(Altura(K2->hizq),Altura(K2->hder));
    K1->altura = 1 + max(Altura(K1->hizq),K2->altura);
    // Devuelve nueva raíz
    return K1;
}

AVL *dobleRotacionConDerecha(AVL *arbol){

    arbol->hder=rotacionIzquierda(arbol->hder);
    return rotacionDerecha(arbol);
}

AVL *dobleRotacionConIzquierda(AVL *arbol){

    arbol->hizq=rotacionDerecha(arbol->hizq);
    return rotacionIzquierda(arbol);
}


AVL *InsertarValorArbolAVL(AVL *arbol, int dato)
{
    /* 1.  Performa una inserción BST normal */
    if (arbol == NULL)
        return(nuevoNodo(dato));
    if (dato < arbol->dato){
        arbol->hizq  = InsertarValorArbolAVL(arbol->hizq, dato);
        /* 3. Obtiene el balance de este nodo predecesor
              para chequear si este nodo pasó a estar
              desbalanceado */
        if(Altura(arbol->hizq)-Altura(arbol->hder)==2){
            if(dato<arbol->hizq->dato){
                ////
                RotacionIzquierda++;
                ////

                arbol=rotacionIzquierda(arbol);
            }else{
                ////
                RotacionDI++;
                ////

                arbol=dobleRotacionConIzquierda(arbol);
            }
        }
    }
    else{if (dato > arbol->dato){
        arbol->hder = InsertarValorArbolAVL(arbol->hder, dato);
            if(Altura(arbol->hder)-Altura(arbol->hizq)==2){
                if(dato>arbol->hder->dato){
                    ////
                    RotacionDerecha++;
                    ////

                    arbol=rotacionDerecha(arbol);
                }else{
                    ////
                    RotacionID++;
                    ////

                    arbol=dobleRotacionConDerecha(arbol);
                }
            }
        }
    }
    // Los datos iguales no son permitidos en los BST
        //return arbol;
    /* 2. Actualiza la altura de este nodo predecesor */
    arbol->altura = 1 + max(Altura(arbol->hizq),Altura(arbol->hder));
    return arbol;
}

AVL *leeArchivoEnAVL(const char *nombreArchivoDatos){
    AVL *arbol=NULL;
    int i,n, *numeros;
    FILE *archivo = fopen(nombreArchivoDatos,"rb");
    fread(&n, sizeof(int), 1, archivo);
    numeros = malloc(sizeof(int)*n);
    fread(numeros, sizeof(int), n, archivo);
    arbol=InsertarValorArbolAVL(arbol,numeros[0]);
    for(i = 1; i < n; i++){
        arbol=InsertarValorArbolAVL(arbol,numeros[i]);
    }
    free(numeros);
    return(arbol);
}

int ContarAVL(AVL *arbol){
    if(arbol==NULL){
        return(0);
    }else{
        return(ContarAVL(arbol->hizq)+1+(ContarAVL(arbol->hder)));
    }
}

void Info(AVL *arbol){
    int tamanoArbol=Contar(arbol);
    printf("Altura del árbol: %i\n",arbol->altura);
    printf("Tamaño del árbol: %i\n",tamanoArbol);
    printf("Se realizaron:\n");
    printf("Rotaciones a la izquierda: %i\n",RotacionIzquierda);
    printf("Rotaciones a la derecha: %i\n",RotacionDerecha);
    printf("Rotaciones doble izquierda derecha: %i\n",RotacionID);
    printf("Rotaciones doble derecha izquierda: %i\n",RotacionDI);
}

/* Imprime los nodos a un nivel dado */
void printGivenLevel(AVL *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->dato);
    else if (level > 1)
    {
        printGivenLevel(root->hizq, level-1);
        printGivenLevel(root->hder, level-1);
    }
}

/* Función para recorrer un árbol en orden por nivel */
void printLevelOrder(AVL *root)
{
    printf("\nRecorrido del árbol por nivel: \n");
    int h = root->altura;   //Altura(root)+1;
    int i;
    for (i=1; i<=h; i++){
        printf("Nivel %i:  ", i);
        printGivenLevel(root, i);
        printf("\n");
    }
}
