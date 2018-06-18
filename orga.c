#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct{
    char **nombreRegistro;
    int *valoresRegistros;
}Registros;

typedef struct{
    char *instruccion;
    char *rd;
    char *rt;
    char *rs;
    int regwrite;
    int memread;
    char *regdest;

}Buffer;

int contarInstrucciones(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo,"r");
    int contador = 0;
    char *buffer = (char *)malloc(100*sizeof(char));
    while(!feof(archivo)){
        fgets(buffer,100,archivo);
        contador++;
    }
    fclose(archivo);
    return contador;
}


char ** leerInstrucciones(char *nombreArchivo){
    int cantidadinstrucciones = contarInstrucciones(nombreArchivo);
    FILE *archivo = fopen(nombreArchivo,"r");
    int i = 0;
    char **matrizInstrucciones = (char **)malloc(cantidadinstrucciones*sizeof(char *));
    char *buffer = (char *)malloc(100*sizeof(char ));
    for(i=0;i<cantidadinstrucciones-1;i++){
        matrizInstrucciones[i] = (char *)malloc(100*sizeof(char ));
        fgets(buffer,100,archivo);
        strcpy(matrizInstrucciones[i],buffer);
    }
    return matrizInstrucciones;
}

Registros leerValores(char *nombreArchivo){
    Registros r;
    FILE *archivo = fopen(nombreArchivo,"r");
    r.nombreRegistro = (char **)malloc(sizeof(char *)*32);
    r.valoresRegistros = (int *)malloc(31*sizeof(int ));
    int i = 0;
    while(!feof(archivo)){
        r.nombreRegistro[i] = (char *)malloc(sizeof(char )*6);
        char *linea = (char *)malloc(sizeof(char)*1000);
        fgets(linea,1000,archivo);
        r.nombreRegistro[i] = strtok(linea," ");
        char *valor = strtok(NULL,"\n");
        r.valoresRegistros[i] = atoi(valor);
        i++;
    }
    fclose(archivo);
    return r;
}

Buffer* InicializarBuffer(){
    Buffer *nuevo;
    return nuevo;
}


void MoverBuffers(){

}

void fetch(Buffer *ifid,Buffer *idex,Buffer *exmem,Buffer *memwb,char *instruccion){
    char *instruccionCompleta;
    strcpy(instruccionCompleta,instruccion);
    char *operacion = strtok(instruccion," ");
    if(strcmp(operacion,"add") == 0 || strcmp(operacion,"sub") ==0 || strcmp(operacion,"mul") ==0 || strcmp(operacion,"div") == 0){
        if(ifid == NULL){
            ifid = InicializarBuffer();
            ifid->rd = strtok(NULL," ");
            ifid->rs = strtok(NULL," ");
            ifid->rt = strtok(NULL," ");
            strcpy(ifid->regdest,ifid->rt);
            ifid->regwrite = 1;
            ifid->memread = 0;            
            ifid->instruccion = instruccionCompleta;
        }
        else{
            MoverBuffers(ifid,idex,exmem,memwb);
            ifid->rd = strtok(NULL," ");
            ifid->rs = strtok(NULL," ");
            ifid->rt = strtok(NULL," ");
            strcpy(ifid->regdest,ifid->rt);
            ifid->regwrite = 1;
            ifid->memread = 0;
            ifid->instruccion = instruccionCompleta;
        }
    }
    if(strcmp(operacion,"addi") ==0 || strcmp(operacion,"subi") ==0){
        if(ifid == NULL){
            ifid = InicializarBuffer();
            ifid->rt = strtok(NULL," ");
            ifid->rs = strtok(NULL," ");
            ifid->rt = NULL;
            ifid->regdest = 0;
            ifid->regwrite = 1;
            ifid->memread = 0;
            ifid->instruccion = instruccionCompleta;
        }
        else{
            MoverBuffers(ifid,idex,exmem,memwb);
            ifid->rt = strtok(NULL," ");
            ifid->rs = strtok(NULL," ");
            ifid->rt = NULL;
            ifid->regdest = 0;
            ifid->regwrite = 1;
            ifid->memread = 0;
            ifid->instruccion = instruccionCompleta;
        }
    }
    
}



int main(){
    int i = contarInstrucciones("M1.asm");
    char **m = leerInstrucciones("M1.asm"); 
    Registros r = leerValores("M2.txt");
    printf("nombre:%s valor:%i",r.nombreRegistro[31],r.valoresRegistros[31]);
    return 0;
}

