#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#include<windows.h>

#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string)   "\x1b[31m" string "\x1b[0m"
#define BLUE(string)  "\x1b[34m" string "\x1b[0m"
#define YEL(string)   "\x1b[33m" string "\x1b[0m"
#define MAG(string)   "\x1b[35m" string "\x1b[0m"
#define CYAN(string)  "\x1b[36m" string "\x1b[0m"

///////////////////////////////////////Estructuras////////////////////////////////////////////////////////////
typedef struct {
    char nombre[20];
    char apellido[20];
    int edad;
    char dni[20];
    int anio,division;
    int diaA,mesA,anioA,diaB,mesB,anioB,diaC,mesC,anioC;        //lo usamos para saber la fecha de la cuota a vencer, fecha de alta y baja
    int idAlumno;
    int bajaAlumno;         //sirve para saber si el alumno esta activo en el colegio o si ya se fue del colegio
}stAlumno;

typedef struct{

    char nombre[20];
    char apellido[20];
    int edad;
    char materia[20];
    char dni[20];
    int anio[10];
    int division[10];
    int cantCursos;
    int diaA,mesA,anioA,diaB,mesB,anioB;
    int idDocente;
    int bajaDocente;
}stDocente;

typedef struct nodoArbolAlumno{
    stAlumno alumno;
    struct  nodoArbolAlumno *izq;           //en el arbol alumnos tengo toda la informacion de los alumnos
    struct nodoArbolAlumno *der;
}nodoArbolAlumno;

typedef struct nodoArbolDocente{
    stDocente docente;
    struct  nodoArbolDocente *izq;           //en el arbol tengo toda la informacion de los  y docentes
    struct nodoArbolDocente *der;
}nodoArbolDocente;


typedef struct nodoAlumno
{
 stAlumno alumno;
  struct nodoAlumno* siguiente;
} nodoAlumno;

typedef struct nodoDocente
{
    stDocente docente;
 struct nodoDocente* siguiente;
} nodoDocente;



typedef struct celdaCursos
{
    int anio,division;
    nodoAlumno* listaAlumnos;
    nodoDocente *listaDocentes;
}celdaCursos;


/////////////////////////////////////////////Encabezados//////////////////////////////////////////////////////


///Lectura de archivos.
int cargaCursosTxt(celdaCursos arreglo[],int validos,int dimension);
struct nodoArbolDocente* archivoToDocentes(celdaCursos arreglo[],int validos,nodoArbolDocente *arbolDocentes);
struct nodoArbolAlumno *archivoToAlumnos(celdaCursos arreglo[],int validos,nodoArbolAlumno *arbolAlumnos);

///Carga de arboles
nodoArbolAlumno *inicArbolA();
nodoArbolDocente *inicArbolD();
struct nodoArbolDocente * altaDocentes(celdaCursos arreglo[],int validos,stDocente auxDocente,nodoArbolDocente *arbolDocentes);
struct nodoArbolAlumno * altaAlumnos(celdaCursos arreglo[],int validos,stAlumno auxAlumno,nodoArbolAlumno *arbolAlumnos);
struct nodoArbolAlumno* crearNodoArbolAlumno (stAlumno alumno);
struct nodoArbolAlumno* insertarArbolAlumnos(struct nodoArbolAlumno*arbol,struct nodoArbolAlumno * nuevo);
struct nodoArbolDocente* crearNodoArbolDocente (stDocente docente);
struct nodoArbolDocente* insertarArbolDocente(struct nodoArbolDocente*arbol,struct nodoArbolDocente* nuevo);
void inorderDocentes(nodoArbolDocente * arbol);
void inorderAlumnos(nodoArbolAlumno * arbol);

///Carga del arreglo de listas.
void cargaDocentes(celdaCursos A[],int validos ,stDocente docentes);
nodoDocente *crearNodoDocente(stDocente docentes);
nodoDocente *agregarAlFinalDocente(nodoDocente *lista,nodoDocente *auxDocente);
nodoDocente *buscarUltimoDocente(nodoDocente *lista);
nodoDocente * inicListaDocente();
nodoAlumno * inicListaAlumno();
void mostrarArreglo(celdaCursos a[],int validos);


int control_menu_opcion(int cant_opciones);

///Carga de Alumno
struct nodoArbolAlumno *cargaAlumno(celdaCursos arreglo[],int validos,nodoArbolAlumno *arbolAlumnos);
int alumno_id(char archivo[]);
int usuario_exist(char archivo[], char nuevo_dni[],stAlumno  *datos );
void alumno_carga(char archivo[],stAlumno aux);  //funcion para guardar los datos en el archivo alumnos
///Eliminar alumno
struct nodoArbolAlumno *bajaAlumno(celdaCursos arreglo[],int validos,nodoArbolAlumno *arbolAlumnos);
nodoAlumno * borrarNodoAlumno(nodoAlumno * lista, char dni[]);
struct nodoArbolAlumno *bajaArbolAlumnos(nodoArbolAlumno *arbol,char dni[]);   //cambia en tiempo real el estado del alumno en el arbol

void alumno_eliminar(char nombre[],stAlumno aux);
///Busca alumno
void buscaAlumno(nodoArbolAlumno *arbolAlumnos);
struct nodoArbolAlumno *buscarArbolAlumnos(nodoArbolAlumno *arbol,char dni[]);
///Alumnos Listado
void alumnosListado(celdaCursos arreglo[],int validos);
void alumnosListadoTotal(celdaCursos arreglo[],int validos);
///Carga docente
struct nodoArbolDocente *altaDocente(celdaCursos arreglo[],int validos,nodoArbolDocente *arbolDocentes);
int docente_exist(char archivo[], char nuevo_dni[],stDocente *datos );
void docente_carga(char archivo[],stDocente aux);  //funcion para guardar los datos en el archivo Docentes
int docente_id(char archivo[]);///ENCUENTRA LA SIGUIENTE ID A USAR (ultima)
///Baja docente
struct nodoArbolDocente *bajaDocente(celdaCursos arreglo[],int validos,nodoArbolDocente *arbolDocentes);
nodoDocente * borrarNodoDocente(nodoDocente * lista, char dni[]);
struct nodoArbolDocente *bajaArbolDocente(nodoArbolDocente *arbol,char dni[]);   //cambia en tiempo real el estado del alumno en el arbol
void docente_eliminar(char nombre[],stDocente aux); ///elimina el alumno buscado.
///Busca Docente
struct nodoArbolDocente *buscarArbolDocentes(nodoArbolDocente *arbol,char dni[]);
void buscaDocente(nodoArbolDocente *arbol);
///Docentes Listado
void docentesListado(celdaCursos arreglo[],int validos);
void docentesListadoTotal(celdaCursos arreglo[],int validos);
void alumnosDeudores();

///Paga deuda
void alumno_pagar(char nombre[],stAlumno aux); ///
void pagarDeuda();


int main()
{

    int validos=0;
    int dimension=10;
    celdaCursos  arreglo[dimension];
    nodoArbolAlumno  *arbolAlumnos=inicArbolA();
    nodoArbolDocente *arbolDocentes=inicArbolD();
    validos=cargaCursosTxt(arreglo,validos,dimension);
    arbolDocentes=archivoToDocentes(arreglo,validos,arbolDocentes);
    arbolAlumnos=archivoToAlumnos(arreglo,validos,arbolAlumnos);

    int control;

    printf("Men%c Principal: \n\n", 163);
    printf("1] Administraci%cn de Alumnos \n", 162);
    printf("2] Administraci%cn de Docentes \n", 162);
    printf("0] Salir del programa. \n\n");
    printf("OPCION: ");
    int cant_opciones = 3;



    switch(control_menu_opcion(cant_opciones))
    {
    case 1 :
    do
    {
        /// Menu Administracion de Alumnos
        printf("Men%c Administraci%cn de Alumnos: \n\n", 163, 162);
        printf(GREEN ("1] Alta Alumno \n"));
        printf(RED("2] Baja Alumno \n"));
        printf(BLUE("3] Consulta \n"));
        printf(YEL("4] Listado  Por curso\n"));
        printf(YEL("5] Listado  Total\n"));
        printf(YEL("6] Listado  de Alumnos con deuda\n"));
        printf(MAG("7] Pagar Deuda Alumno \n\n"));
        printf("0] Volver al menu Principal \n\n");
        printf("OPCION: ");

        int cant_opciones = 8;



        switch(control=control_menu_opcion(cant_opciones))
        {
        case 1 :
            arbolAlumnos=cargaAlumno(arreglo,validos,arbolAlumnos);
            system("cls");
            break;
        case 2 :
            arbolAlumnos=bajaAlumno(arreglo,validos,arbolAlumnos);
            system("cls");
            break;
        case 3 :
            buscaAlumno(arbolAlumnos);
            system("cls");
            break;
        case 4 :
            alumnosListado(arreglo,validos);
            system("cls");
            break;
        case 5 :
            alumnosListadoTotal(arreglo,validos);
            system("cls");
            break;
        case 6 :
            alumnosDeudores();
            system("cls");
            break;
        case 7 :
            pagarDeuda();
            system("cls");
            break;


        }
    }
    while(control!=0);
        break;

    case 2 :

    do
    {
        /// Menu Administracion de Docentes
        printf("Men%c Administraci%cn de Docentes: \n\n", 163, 162);
        printf(GREEN("1] Alta Docente \n"));
        printf(RED("2] Baja Docente \n"));
        printf(BLUE("3] Consulta Docente\n"));
        printf(YEL("4] Listado  de Docentes por curso\n"));
        printf(YEL("5] Listado  de Docentes por cursos \n\n"));
        printf("0] Volver al menu Principal \n\n");
        printf("OPCION: ");

        int cant_opciones = 6;

        ///Listado de opciones disponibles en el menu.

        switch(control=control_menu_opcion(cant_opciones))
        {
        case 1 :
            arbolDocentes=altaDocente(arreglo,validos,arbolDocentes);
            system("cls");
            break;
        case 2 :
            arbolDocentes=bajaDocente(arreglo,validos,arbolDocentes);
            system("cls");
            break;
        case 3 :
            buscaDocente(arbolDocentes);
            system("cls");
            break;
        case 4 :
            docentesListado(arreglo,validos);
            system("cls");
            break;
        case 5:
            docentesListadoTotal(arreglo,validos);
            system("cls");
            break;

        case 0 :

            system("cls");
            break;

        }
    }
    while(control!=0);
        break;
    case 0 :
        exit(0);
        break;



    }

    return 0;
}

//////////////////Funcion que asigna los cursos en el arreglo///////////////
void mostrarArreglo(celdaCursos a[],int validos){

    for(int i=0;i<validos;i++)
    {
      printf("----------Curso %i-%i ----------\n",a[i].anio,a[i].division);
      printf("-----Docentes-----\n");

    nodoDocente *auxNodo;
    auxNodo=a[i].listaDocentes;
    while(auxNodo!=NULL)
    {
        printf("Nombre:%s  Apellido:%s \n",auxNodo->docente.nombre,auxNodo->docente.apellido);
        auxNodo=auxNodo->siguiente;
    }
    printf("----Alumnos----\n");
    nodoAlumno *auxAlumno;
    auxAlumno=a[i].listaAlumnos;

    while(auxAlumno!=NULL)
    {
        printf("Nombre:%s  Apellido:%s \n",auxAlumno->alumno.nombre,auxAlumno->alumno.apellido);
        auxAlumno=auxAlumno->siguiente;
    }

    }

}


int cargaCursosTxt(celdaCursos arreglo[],int validos,int dimension){


    FILE *pArch=fopen("cursos.txt","r");

    if(pArch!=NULL)
        {
          while( fscanf(pArch,"%i %i",&arreglo[validos].anio,&arreglo[validos].division)>0           && validos<dimension)
          {
            arreglo[validos].listaAlumnos=inicListaAlumno();
            arreglo[validos].listaDocentes=inicListaDocente();
            validos++;
          }
        }
        else
        {
            printf("\n el archivo de Cursos no existe \n");
        }
    fclose(pArch);
    return validos;
}
nodoArbolAlumno *inicArbolA(){
    return NULL;
}
nodoArbolDocente *inicArbolD(){
    return NULL;
}
nodoAlumno * inicListaAlumno() {
return NULL;
}
nodoDocente * inicListaDocente() {
return NULL;
}
void inorderDocentes(nodoArbolDocente * arbol){
    if(arbol != NULL)
    {
    inorderDocentes(arbol->izq);
    printf("Nombre:%s ,Apellido:%s ,Dni :%s \n", arbol->docente.nombre,arbol->docente.apellido,arbol->docente.dni);
    inorderDocentes(arbol->der);
    }
}
void inorderAlumnos(nodoArbolAlumno * arbol){
    if(arbol != NULL)
    {
    inorderAlumnos(arbol->izq);
    printf("Nombre:%s ,Apellido:%s ,Dni :%s  \n", arbol->alumno.nombre,arbol->alumno.apellido,arbol->alumno.dni);

    inorderAlumnos(arbol->der);
    }
}
struct nodoArbolDocente * archivoToDocentes(celdaCursos arreglo[],int validos,nodoArbolDocente *arbolDocentes){

    FILE  *archDocentes=fopen("docentes.bin","rb");
    stDocente auxDocente;


    if(archDocentes){
        while(fread(&auxDocente,sizeof(stDocente),1,archDocentes)>0){
            arbolDocentes=altaDocentes(arreglo,validos,auxDocente,arbolDocentes);
        }
        fclose(archDocentes);
    }
    else{
        printf("Error al abrir el archivo Docentes \n");
    }

return arbolDocentes;

}
struct nodoArbolAlumno * archivoToAlumnos(celdaCursos arreglo[],int validos,nodoArbolAlumno *arbolAlumnos){


FILE  *archAlumnos=fopen("alumnos.bin","rb");


  stAlumno   auxAlumno;
    if(archAlumnos){
        while(fread(&auxAlumno,sizeof(stAlumno),1,archAlumnos)>0 ){
            arbolAlumnos=altaAlumnos(arreglo,validos,auxAlumno,arbolAlumnos);


        }
        fclose(archAlumnos);

    }
    else{
        printf("Error al abrir el archivo Alumnos \n");
    }



return arbolAlumnos;


}
/////////////////Lista de docentes///////////////////////////////
nodoDocente* crearNodoDocente(stDocente docente){


    nodoDocente* aux=(nodoDocente*) malloc (sizeof(nodoDocente));
    strcpy(aux->docente.nombre,docente.nombre);
    strcpy(aux->docente.apellido,docente.apellido);
    aux->docente.edad=docente.edad;
    strcpy(aux->docente.materia,docente.materia);
    strcpy(aux->docente.dni,docente.dni);
    for(int i=0;i<docente.cantCursos;i++){
     aux->docente.anio[i]=docente.anio[i];
     aux->docente.division[i]=docente.division[i];
    }

    aux->docente.cantCursos=docente.cantCursos;
    aux->docente.diaA=docente.diaA;
    aux->docente.mesA=docente.mesA;
    aux->docente.anioA=docente.anioA;
    aux->docente.diaB=docente.diaB;
    aux->docente.mesB=docente.diaB;
    aux->docente.anioB=docente.diaB;
    aux->docente.idDocente=docente.idDocente;
    aux->docente.bajaDocente=docente.bajaDocente;

    aux->siguiente=NULL;

    return aux;
}
nodoDocente* buscarUltimoDocente(nodoDocente* lista){
    nodoDocente* seg = lista;
   if(seg != NULL)
      while(seg->siguiente != NULL)
        {
         seg=seg->siguiente;
        }
    return seg;
 }
nodoDocente* agregarAlFinalDocente(nodoDocente* lista, nodoDocente* nuevoNodo){

   if(lista == NULL)
    {
      lista = nuevoNodo;
    }
   else
    {
      nodoDocente* ultimo = buscarUltimoDocente(lista);
      ultimo->siguiente = nuevoNodo;
    }

   return lista;
}
////////////////////////////////Lista de alumnos////////////////////////////////////////////////////
nodoAlumno* crearNodoAlumno(stAlumno alumno){
    nodoAlumno* aux=(nodoAlumno*) malloc (sizeof(nodoAlumno));
    aux->alumno=alumno;
    aux->siguiente=NULL;

    return aux;
}
nodoAlumno* buscarUltimoAlumno(nodoAlumno* lista){
   nodoAlumno* seg = lista;
   if(seg != NULL)
      while(seg->siguiente != NULL)
        {
         seg = seg->siguiente;
        }
    return seg;
 }
nodoAlumno* agregarAlFinalAlumno(nodoAlumno* lista, nodoAlumno* nuevoNodo){
   if(lista == NULL)
    {
      lista = nuevoNodo;
    }
   else
    {
      nodoAlumno * ultimo = buscarUltimoAlumno(lista);
      ultimo->siguiente = nuevoNodo;
    }
   return lista;
}
////////////////////Arbol de docentes/////////////////////////////////////////
struct nodoArbolDocente* crearNodoArbolDocente (stDocente docente){
    nodoArbolDocente* aux=(nodoArbolDocente*)malloc(sizeof(nodoArbolDocente));

    strcpy(aux->docente.nombre,docente.nombre);
    strcpy(aux->docente.apellido,docente.apellido);
    aux->docente.edad=docente.edad;
    strcpy(aux->docente.materia,docente.materia);
    strcpy(aux->docente.dni,docente.dni);
    for(int i=0;i<docente.cantCursos;i++){
     aux->docente.anio[i]=docente.anio[i];
     aux->docente.division[i]=docente.division[i];
    }

    aux->docente.cantCursos=docente.cantCursos;
    aux->docente.diaA=docente.diaA;
    aux->docente.mesA=docente.mesA;
    aux->docente.anioA=docente.anioA;
    aux->docente.diaB=docente.diaB;
    aux->docente.mesB=docente.diaB;
    aux->docente.anioB=docente.diaB;
    aux->docente.idDocente=docente.idDocente;
    aux->docente.bajaDocente=docente.bajaDocente;



    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}
struct nodoArbolDocente* insertarArbolDocente(struct nodoArbolDocente* arbol,struct nodoArbolDocente* nuevo){


    if(arbol==NULL)
        arbol=nuevo;
    else
    {
        if(strcmp(nuevo->docente.dni,arbol->docente.dni)>0)
            arbol->der=insertarArbolDocente(arbol->der,nuevo);
        else
            arbol->izq=insertarArbolDocente(arbol->izq,nuevo);
    }
    return arbol;
}
/////////////////////////////Arbol de alumnos///////////////////////////////////////////
struct nodoArbolAlumno* crearNodoArbolAlumno (stAlumno alumno){
    nodoArbolAlumno* aux=malloc(sizeof(nodoArbolAlumno));
    aux->alumno=alumno;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}
struct nodoArbolAlumno* insertarArbolAlumnos(struct nodoArbolAlumno*arbol,struct nodoArbolAlumno * nuevo){
    if(arbol==NULL)
        arbol=nuevo;
    else
    {
        if(strcmp(nuevo->alumno.dni,arbol->alumno.dni)>0)
            arbol->der=insertarArbolAlumnos(arbol->der,nuevo);
        else
            arbol->izq=insertarArbolAlumnos(arbol->izq,nuevo);
    }
    return arbol;
}
////////////////Busco curso en el arreglo//////////////////////////
int buscarEnArreglo(celdaCursos A[],int validos,stAlumno alumno){
    int i=0;
    int pos;

    while(i<validos)
    {
        if(A[i].anio==alumno.anio && A[i].division==alumno.division)
            pos=i;
        i++;
    }
return pos;
}
/////////////////////////////////////////////////////////////////////////////////
struct nodoArbolAlumno * altaAlumnos(celdaCursos A[],int validos,stAlumno alumnos,nodoArbolAlumno* arbolAlumnos){
   nodoArbolAlumno* aux=crearNodoArbolAlumno(alumnos);
    arbolAlumnos=insertarArbolAlumnos(arbolAlumnos,aux);



   if(alumnos.bajaAlumno==0)
   {
           int pos=buscarEnArreglo(A,validos,alumnos);
           nodoAlumno* auxAlumno=crearNodoAlumno(alumnos);
           A[pos].listaAlumnos=agregarAlFinalAlumno(A[pos].listaAlumnos,auxAlumno);

   }
return arbolAlumnos;
}
struct nodoArbolDocente *altaDocentes(celdaCursos A[],int validos,stDocente docentes,nodoArbolDocente* arbolDocentes){
    nodoArbolDocente* aux=crearNodoArbolDocente(docentes);
    arbolDocentes=insertarArbolDocente(arbolDocentes,aux);
   if(docentes.bajaDocente==0)
   {
           cargaDocentes(A,validos,docentes);

   }
return arbolDocentes;
}
///////////////////////////////////////////////////////////////////////////
void cargaDocentes(celdaCursos A[],int validos ,stDocente docentes){

     nodoDocente* auxDocente;
       for(int i=0;i<docentes.cantCursos;i++){

            for(int j=0;j<=validos;j++){

                if(A[j].anio==docentes.anio[i] && A[j].division==docentes.division[i]){

                    auxDocente=crearNodoDocente(docentes);
                  A[j].listaDocentes=agregarAlFinalDocente(A[j].listaDocentes,auxDocente);

                }

        }

    }


}
///////////////////////////////////////************************////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int control_menu_opcion(int cant_opciones){ ///CONTROLA LA SELECCION DEL MENU
    int menu_opcion;
    int exito=0;

    do
    {
        fflush(stdin);
        scanf("%d", &menu_opcion);

        if (menu_opcion < 0 || menu_opcion > cant_opciones-1)
        {
            printf("La opci%cn seleccionada no es valida, intentelo nuevamente\n", 162);
        }
        else
        {
            exito=1;
        }
    }
    while ( exito == 0);

    system("cls");
    return menu_opcion;
}


///////////////////////carga un alumno/////////////////
struct nodoArbolAlumno *cargaAlumno(celdaCursos arreglo[],int validos,nodoArbolAlumno *arbolAlumnos){


    stAlumno auxAlumno;
    char nombreA[]="alumnos.bin";




    int control=0;


    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);


    auxAlumno.idAlumno=alumno_id(nombreA); ///busca la proxima id a usar
    printf("Id del proximo Alumno: %d \n\n", auxAlumno.idAlumno);

    ///USUARIO
    while(control==0)
    {
        printf("\n Ingrese numero de documento sin los puntos:\n ");
        fflush(stdin);
        scanf("%s",auxAlumno.dni);
        control=usuario_exist(nombreA,auxAlumno.dni,&auxAlumno);
        //    printf("%i",control);

        if(control==0)
        {
            printf("\nEl cliente ya existe.\n");
            printf("Nombre: %s \nApellido:%s \nDNI:%s\n",auxAlumno.nombre,auxAlumno.apellido,auxAlumno.dni);
            printf("\n ************************\n");
        }
        else
        {
           printf("\n Ingrese nombre del Alumno \n");
           fflush(stdin);
           gets(auxAlumno.nombre);
           printf("\n Ingrese nombre apellido del Alumno \n");
           fflush(stdin);
           gets(auxAlumno.apellido);
           printf("Ingrese la edad del Alumno\n");
           scanf("%i",&auxAlumno.edad);
           printf("\n Ingrese el Anio a cursar \n");
           scanf("%i",&auxAlumno.anio);
           printf("\n Ingrese division a cursar \n");
           scanf("%i",&auxAlumno.division);
           auxAlumno.diaA=tm->tm_mday;
           auxAlumno.mesA=tm->tm_mon+1;
           auxAlumno.anioA=1900+tm->tm_year;
           auxAlumno.diaC=tm->tm_mday;
           auxAlumno.mesC=tm->tm_mon+2;
           auxAlumno.anioC=1900+tm->tm_year;
           auxAlumno.bajaAlumno=0;        // el cliente esta activo 0
           system("cls");

            printf("LOS DATOS SON \n");
            printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \nAnio y Division:%i-%i\n",auxAlumno.nombre,auxAlumno.apellido,auxAlumno.edad,auxAlumno.dni,auxAlumno.anio,auxAlumno.division);
            printf("Fecha de alta %i /%i /%i\n",auxAlumno.diaA,auxAlumno.mesA,auxAlumno.anioA);
            printf("Fecha Proxima Cuota %i/%i/%i\n",auxAlumno.diaC,auxAlumno.mesC,auxAlumno.anioC);


           printf("\n ingrese 0 para  volver a cargar datos,  1 para confirmar confimar \n");
            control=control_menu_opcion(2);

        }

    }

    system("pause");
        alumno_carga(nombreA,auxAlumno);
        nodoArbolAlumno* aux=crearNodoArbolAlumno(auxAlumno);
        arbolAlumnos=insertarArbolAlumnos(arbolAlumnos,aux);

        int pos=buscarEnArreglo(arreglo,validos,auxAlumno);
        nodoAlumno* auxL=crearNodoAlumno(auxAlumno);
        arreglo[pos].listaAlumnos=agregarAlFinalAlumno(arreglo[pos].listaAlumnos,auxL);



return arbolAlumnos;


}



int alumno_id(char archivo[]) ///ENCUENTRA LA SIGUIENTE ID A USAR (ultima)
{
    FILE*cli;

    int control=0;

    cli=fopen(archivo,"r+b");

    if(cli!=NULL)
    {
        fseek(cli, 0, SEEK_END);
        control=ftell(cli)/sizeof(stAlumno);

        fclose(cli);
    }
    return control;
}




int usuario_exist(char archivo[], char nuevo_dni[],stAlumno *datos ) ///RETORNA 0 SI ENCONTRO EL USUARIO
{
    FILE* cli;

    stAlumno aux;
    int control=1;

    cli=fopen(archivo,"rb");

    if(cli!=NULL)
    {
        while(!feof(cli)&& control!=0)
        {
            fread(&aux,sizeof(stAlumno),1,cli);

            if(strcmp(aux.dni,nuevo_dni)==0)
            {
              control=0;
              *datos=aux;
            }
        }
        fclose(cli);
    }


    return control;
}


void alumno_carga(char archivo[],stAlumno aux)  //funcion para guardar los datos en el archivo alumnos
{
  FILE *cli;
  cli=fopen(archivo,"a+b");
  if(cli!=NULL)
    {


        fwrite(&aux,sizeof(stAlumno),1,cli);

        fclose(cli);

        system("cls");
        printf(GREEN("La carga se ha realizado con exito!\n\n"));
        system("pause");
        system("cls");

    }


}
////////////////////////////////Baja Alumno/////////////////////
struct nodoArbolAlumno *bajaAlumno(celdaCursos arreglo[],int validos,nodoArbolAlumno *arbolAlumnos){

    char nombreA[]="alumnos.bin";

    stAlumno aux;
    int control=1;


    char baja=' ';


    printf("BAJA Alumno\n\n");
    printf("Ingrese su DNI: ");

    scanf("%s",aux.dni);
    control=usuario_exist(nombreA,aux.dni,&aux); ///0 encuentra..


    if(control!=0)
    {
        printf("\nEl alumno no es valido. \n");
    }
    else
    {
        if(aux.bajaAlumno==1) ///en caso de que el usuario este eliminado
        {
            printf("\nEl alumno no esta activo. \n");
            printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \n",aux.nombre,aux.apellido,aux.edad,aux.dni);
            printf(RED("Fecha de Baja %i /%i /%i\n"),aux.diaB,aux.mesB,aux.anioB);
        }
        else
        {



            printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \nAnio y Division:%i-%i\n",aux.nombre,aux.apellido,aux.edad,aux.dni,aux.anio,aux.division);
            printf(GREEN("Fecha de alta %i /%i /%i\n"),aux.diaA,aux.mesA,aux.anioA);


                printf("\n\nQuiere dar de baja su cuenta? S/N: ");
                fflush(stdin);
                scanf("%c",&baja);
                if(baja=='s'||baja=='S')
                {
                    baja='n';
                    printf("\nEsta seguro? S/N: ");
                    fflush(stdin);
                    scanf("%c",&baja);
                    if(baja=='s'||baja=='S')
                    {


                        alumno_eliminar(nombreA,aux);

                        for(int i=0;i<validos;i++){

                          if(arreglo[i].anio==aux.anio && arreglo[i].division==aux.division){

                                 arreglo[i].listaAlumnos=borrarNodoAlumno(arreglo[i].listaAlumnos,aux.dni);

                            i=validos;
                            }

                        }
                    printf(RED("\n-----------------\n.....Alumno eliminado.....\n-----------------\n"));

                    }

                }
        }
    }

    system("pause");

    arbolAlumnos=bajaArbolAlumnos(arbolAlumnos,aux.dni);

    return arbolAlumnos;
}


nodoAlumno * borrarNodoAlumno(nodoAlumno * lista, char dni[]) {
            nodoAlumno * seg;
            nodoAlumno * ante; //apunta al nodo anterior que seg.
            if((lista != NULL) && (strcmp(dni, lista->alumno.dni)==0 )) {
            nodoAlumno * aux = lista;
            lista = lista->siguiente; //salteo el primer nodo.
            free(aux); //elimino el primer nodo.
            }else {
            seg = lista;
            while((seg != NULL) && (strcmp(dni, seg->alumno.dni)!=0 )) {
                ante = seg;
                seg = seg->siguiente;
            }
            //en este punto tengo en la variable ante la dirección de
            //memoria del nodo anterior al buscado, y en la variable seg,
            //la dirección de memoria del nodo que quiero borrar.
            if(seg!=NULL) {
                ante->siguiente = seg->siguiente;
            //salteo el nodo que quiero eliminar.
            free(seg);
            //elimino el nodo.
            }
}
return lista;
}



void alumno_eliminar(char nombre[],stAlumno aux) ///elimina el alumno buscado.
{

    FILE* cli;
    cli=fopen(nombre,"r+b");

    stAlumno aux_cli=aux;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);


    aux_cli.bajaAlumno=1;
    aux_cli.diaB= tm->tm_mday;
    aux_cli.mesB=tm->tm_mon+1;
    aux_cli.anioB=1900+tm->tm_year;



    if(cli!=NULL)
    {
        fseek(cli,sizeof(stAlumno)*(aux_cli.idAlumno),SEEK_SET);
        fwrite(&aux_cli,sizeof(stAlumno),1,cli);
        fclose(cli);


    }
}


struct nodoArbolAlumno *bajaArbolAlumnos(nodoArbolAlumno *arbol,char dni[]){



    if(arbol!=NULL)
        {
            if(strcmp(dni,arbol->alumno.dni)==0)
                arbol->alumno.bajaAlumno=1;
            else
            if(strcmp(dni,arbol->alumno.dni)>0)
                arbol = bajaArbolAlumnos(arbol->der, dni);
            else
                arbol = bajaArbolAlumnos(arbol->izq, dni);
        }
return arbol;




}
///////////////////////////////////////////

///////////////////////busca alumno////////////////
void buscaAlumno(nodoArbolAlumno *arbolAlumnos){
    char dni[10];
    printf("Ingrese el documento para buscar informacion del alumno\n");
    scanf("%s",dni);
    nodoArbolAlumno *datos=buscarArbolAlumnos(arbolAlumnos,dni);

    printf("Nombre:%s\n",datos->alumno.nombre);
    printf("Apellido:%s\n",datos->alumno.apellido);
    printf("DNI:%s\n",datos->alumno.dni);
    if(datos->alumno.bajaAlumno==0){
        printf(GREEN("El alumno esta activo desde %i/%i/%i \n"),datos->alumno.diaA,datos->alumno.mesA,datos->alumno.anioA);
    }
    else{
       printf(RED("El alumno fue dado de baja el  %i/%i/%i \n"),datos->alumno.diaB,datos->alumno.mesB,datos->alumno.anioB);

    }

    system("pause");

}

struct nodoArbolAlumno *buscarArbolAlumnos(nodoArbolAlumno *arbol,char dni[]){


     nodoArbolAlumno * rta=NULL;
    if(arbol!=NULL)
        {
            if(strcmp(dni,arbol->alumno.dni)==0)
                rta = arbol;
            else
            if(strcmp(dni,arbol->alumno.dni)>0)
                rta = buscarArbolAlumnos(arbol->der, dni);
            else
                rta = buscarArbolAlumnos(arbol->izq, dni);
        }
return rta;




}
//////////////////////////////Listado de Alumnos/////
void alumnosListado(celdaCursos arreglo[],int validos){

    int anio,division,control=0;

    printf("Ingrese Anio a Lista\n");
    scanf("%i",&anio);
    printf("ingrese Division a Listar\n");
    scanf("%i",&division);


    for(int i=0;i<validos;i++){

        if(arreglo[i].anio==anio && arreglo[i].division==division){
                 printf(YEL("----------------------------------------------------------------------------------------\n"));
                 printf(YEL("\t\t\t\t Alumnos %i-%i \n"),anio,division);
                 printf(YEL("----------------------------------------------------------------------------------------\n"));
                 nodoAlumno *auxAlumno;
                 auxAlumno=arreglo[i].listaAlumnos;

                while(auxAlumno!=NULL)
                {
                    printf("Nombre:|%s\t| Apellido:|%s\t|  DNI:|%s\t|\n",auxAlumno->alumno.nombre,auxAlumno->alumno.apellido,auxAlumno->alumno.dni);
                    auxAlumno=auxAlumno->siguiente;
                }
                control=1;
        }
    }
    if(control==0){
        printf("El curso ingresado no es valido\n");
    }


    system("pause");

}
void alumnosListadoTotal(celdaCursos arreglo[],int validos){



    for(int i=0;i<validos;i++){

        printf(YEL("----------------------------------------------------------------------------------------\n"));
        printf(YEL("\t\t\t\t Alumnos %i-%i\n"),arreglo[i].anio,arreglo[i].division);
        printf(YEL("----------------------------------------------------------------------------------------\n"));
        nodoAlumno *auxAlumno;
        auxAlumno=arreglo[i].listaAlumnos;

        while(auxAlumno!=NULL)
            {
            printf("Nombre:|%s\t|  Apellido:|%s\t|  DNI:|%s\t|\n",auxAlumno->alumno.nombre,auxAlumno->alumno.apellido,auxAlumno->alumno.dni);
            auxAlumno=auxAlumno->siguiente;
            }

        }
        system("pause");

    }



/////////////////////////carga docente/////////////////////////
struct nodoArbolDocente *altaDocente(celdaCursos arreglo[],int validos,nodoArbolDocente *arbolDocentes){


    stDocente auxDocente;
    char nombreA[]="docentes.bin";


    int flag=0;
    int i=0;
    int control=0;


    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);


    auxDocente.idDocente=docente_id(nombreA); ///busca la proxima id a usar
    printf("Id del proximo Docente: %d \n\n", auxDocente.idDocente);

    ///USUARIO
    while(control==0)
    {
        printf("\n Ingrese numero de documento sin los puntos:\n ");
        fflush(stdin);
        scanf("%s",auxDocente.dni);
        control=docente_exist(nombreA,auxDocente.dni,&auxDocente);


        if(control==0)
        {
            printf(GREEN("\nEl Docente ya existe.\n"));
            printf("Nombre: %s \nApellido:%s \nDNI:%s\n",auxDocente.nombre,auxDocente.apellido,auxDocente.dni);
            printf("\n ************************\n");
        }
        else
        {
           printf("\n Ingrese nombre del Docente \n");
           fflush(stdin);
           gets(auxDocente.nombre);
           printf("\n Ingrese nombre apellido del Docente \n");
           fflush(stdin);
           gets(auxDocente.apellido);
           printf("Ingrese la edad del Docente\n");
           scanf("%i",&auxDocente.edad);
           printf("Ingrese el nombre de la materia \n");
           fflush(stdin);
           scanf("%s",auxDocente.materia);
           while(flag==0){
                printf("Ingrese anio a cursar \n");
                scanf("%i",&auxDocente.anio[i]);
                printf("Ingrese Division a cursar \n");
                scanf("%i",&auxDocente.division[i]);
                printf("Desea agregar otro curso \n 1(no) /0 (si)\n");
                auxDocente.cantCursos=i+1;
                scanf("%i",&flag);
                i++;
            }

           auxDocente.diaA=tm->tm_mday;
           auxDocente.mesA=tm->tm_mon+1;
           auxDocente.anioA=1900+tm->tm_year;

           auxDocente.bajaDocente=0;        // el docente esta activo
           system("cls");

            printf("LOS DATOS SON \n");
            printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \n",auxDocente.nombre,auxDocente.apellido,auxDocente.edad,auxDocente.dni);
            printf("MAteria :%s \n",auxDocente.materia);
            printf("Los Cursos son :\n");
            for(int i=0;i<auxDocente.cantCursos;i++){
                printf("%i-%i\n",auxDocente.anio[i],auxDocente.division[i]);
            }
            printf("Fecha de alta %i /%i /%i\n",auxDocente.diaA,auxDocente.mesA,auxDocente.anioA);


           printf("\n ingrese 0 para  volver a cargar datos,  1 para confirmar confimar \n");
            control=control_menu_opcion(2);

        }

    }

    system("pause");
       docente_carga(nombreA,auxDocente);
        nodoArbolDocente* aux=crearNodoArbolDocente(auxDocente);
        arbolDocentes=insertarArbolDocente(arbolDocentes,aux);

        for(int i=0;i<auxDocente.cantCursos;i++){

            for(int j=0;j<=validos;j++){

                if(arreglo[j].anio==auxDocente.anio[i] && arreglo[j].division==auxDocente.division[i]){

                   nodoDocente * aux=crearNodoDocente(auxDocente);
                  arreglo[j].listaDocentes=agregarAlFinalDocente(arreglo[j].listaDocentes,aux);

                }

            }

        }


return arbolDocentes;


}

int docente_exist(char archivo[], char nuevo_dni[],stDocente *datos ) ///RETORNA 0 SI ENCONTRO EL USUARIO
{
    FILE* cli;

    stDocente aux;
    int control=1;

    cli=fopen(archivo,"rb");

    if(cli!=NULL)
    {
        while(!feof(cli)&& control!=0)
        {
            fread(&aux,sizeof(stDocente),1,cli);


            if(strcmp(aux.dni,nuevo_dni)==0)
            {
              control=0;
              *datos=aux;
            }

        }

        fclose(cli);
    }


    return control;
}
void docente_carga(char archivo[],stDocente aux)  //funcion para guardar los datos en el archivo alumnos
{
  FILE *cli;
  cli=fopen(archivo,"a+b");
  if(cli!=NULL)
    {


        fwrite(&aux,sizeof(stDocente),1,cli);

        fclose(cli);

        system("cls");
        printf("La carga se ha realizado con exito!\n\n");
        system("pause");
        system("cls");

    }


}
int docente_id(char archivo[]) ///ENCUENTRA LA SIGUIENTE ID A USAR (ultima)
{
    FILE*cli;

    int control=0;

    cli=fopen(archivo,"r+b");

    if(cli!=NULL)
    {
        fseek(cli, 0, SEEK_END);
        control=ftell(cli)/sizeof(stDocente);

        fclose(cli);
    }
    return control;
}
//////////////baja docente//////////////////////////////



struct nodoArbolDocente *bajaDocente(celdaCursos arreglo[],int validos,nodoArbolDocente *arbolDocentes){

    char nombreA[]="docentes.bin";

    stDocente aux;
    int control=1;


    char baja=' ';


    printf(RED("BAJA Docente\n\n"));
    printf("Ingrese su DNI: ");

    scanf("%s",aux.dni);
    control=docente_exist(nombreA,aux.dni,&aux); ///0 encuentra..
    if(control!=0)
    {
        printf(RED("\nEl Docente no es valido. \n"));
    }
    else
    {
        if(aux.bajaDocente==1) ///en caso de que el usuario este eliminado
        {
            printf(RED("\nEl docente no esta activo. \n"));
            printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \n",aux.nombre,aux.apellido,aux.edad,aux.dni);
            printf("Fecha de Baja %i /%i /%i\n",aux.diaB,aux.mesB,aux.anioB);
        }
        else
        {



            printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \n",aux.nombre,aux.apellido,aux.edad,aux.dni);
            printf("Fecha de alta %i /%i /%i\n",aux.diaA,aux.mesA,aux.anioA);


                printf("\n\nQuiere dar de baja su cuenta? S/N: ");
                fflush(stdin);
                scanf("%c",&baja);
                if(baja=='s'||baja=='S')
                {
                    baja='n';
                    printf("\nEsta seguro? S/N: ");
                    fflush(stdin);
                    scanf("%c",&baja);
                    if(baja=='s'||baja=='S')
                    {


                        docente_eliminar(nombreA,aux);

                        for(int i=0;i<aux.cantCursos;i++){
                         for(int j=0;j<validos;j++){
                             if(arreglo[j].anio==aux.anio[i] && arreglo[j].division==aux.division[i]){

                                 arreglo[j].listaDocentes=borrarNodoDocente(arreglo[j].listaDocentes,aux.dni);

                                j=validos;
                            }
                         }


                        }
                    printf(RED("\n-----------------\n.....Docente eliminado.....\n-----------------\n"));

                    }

                }
        }
    }

    system("pause");

    arbolDocentes=bajaArbolDocente(arbolDocentes,aux.dni);

return arbolDocentes;
    }

nodoDocente * borrarNodoDocente(nodoDocente * lista, char dni[]) {
            nodoDocente * seg;
            nodoDocente * ante; //apunta al nodo anterior que seg.
            if((lista != NULL) && (strcmp(dni, lista->docente.dni)==0 )) {
            nodoDocente * aux = lista;
            lista = lista->siguiente; //salteo el primer nodo.
            free(aux); //elimino el primer nodo.
            }else {
            seg = lista;
            while((seg != NULL) && (strcmp(dni, seg->docente.dni)!=0 )) {
                ante = seg;
                seg = seg->siguiente;
            }
            //en este punto tengo en la variable ante la dirección de
            //memoria del nodo anterior al buscado, y en la variable seg,
            //la dirección de memoria del nodo que quiero borrar.
            if(seg!=NULL) {
                ante->siguiente = seg->siguiente;
            //salteo el nodo que quiero eliminar.
            free(seg);
            //elimino el nodo.
            }
}
return lista;
}



void docente_eliminar(char nombre[],stDocente aux) ///elimina el alumno buscado.
{

    FILE* cli;
    cli=fopen(nombre,"r+b");

    stDocente aux_cli=aux;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);


    aux_cli.bajaDocente=1;
    aux_cli.diaB= tm->tm_mday;
    aux_cli.mesB=tm->tm_mon+1;
    aux_cli.anioB=1900+tm->tm_year;


    if(cli!=NULL)
    {
        fseek(cli,sizeof(stDocente)*(aux_cli.idDocente),SEEK_SET);
        fwrite(&aux_cli,sizeof(stDocente),1,cli);
        fclose(cli);


    }
}


struct nodoArbolDocente *bajaArbolDocente(nodoArbolDocente *arbol,char dni[]){

    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);

    if(arbol!=NULL)
        {
            if(strcmp(dni,arbol->docente.dni)==0){
               arbol->docente.bajaDocente=1;
                arbol->docente.diaB= tm->tm_mday;
                arbol->docente.mesB=tm->tm_mon+1;
                arbol->docente.anioB=1900+tm->tm_year;
            }

            else
            if(strcmp(dni,arbol->docente.dni)>0)
                arbol = bajaArbolDocente(arbol->der, dni);
            else
                arbol = bajaArbolDocente(arbol->izq, dni);
        }
return arbol;




}
////////////////////////////Busca Docente//////////////////////
void buscaDocente(nodoArbolDocente *arbolDocentes){
    char dni[10];
    printf("Ingrese el documento para buscar informacion del Docente\n");
    scanf("%s",dni);
    nodoArbolDocente *datos=buscarArbolDocentes(arbolDocentes,dni);
    printf("Nombre:%s\n",datos->docente.nombre);
    printf("Apellido:%s\n",datos->docente.apellido);
    printf("DNI:%s\n",datos->docente.dni);
    printf("Materia:%s \n",datos->docente.materia);
    if(datos->docente.bajaDocente==0){
        printf(GREEN("El Docente esta activo desde %i/%i/%i \n"),datos->docente.diaA,datos->docente.mesA,datos->docente.anioA);
    }
    else{
       printf(RED("El Docente fue dado de baja el  %i/%i/%i \n"),datos->docente.diaB,datos->docente.mesB,datos->docente.anioB);

    }

    system("pause");

}

struct nodoArbolDocente *buscarArbolDocentes(nodoArbolDocente *arbol,char dni[]){


     nodoArbolDocente * rta=NULL;
    if(arbol!=NULL)
        {
            if(strcmp(dni,arbol->docente.dni)==0)
                rta = arbol;
            else
            if(strcmp(dni,arbol->docente.dni)>0)
                rta = buscarArbolDocentes(arbol->der, dni);
            else
                rta = buscarArbolDocentes(arbol->izq, dni);
        }
return rta;




}
//////////////////////////////////Listado Docentes///////////
void docentesListado(celdaCursos arreglo[],int validos){

    int anio,division,control=0;

    printf("Ingrese Anio a Lista\n");
    scanf("%i",&anio);
    printf("ingrese Division a Listar\n");
    scanf("%i",&division);


    for(int i=0;i<validos;i++){

        if(arreglo[i].anio==anio && arreglo[i].division==division){
                 printf(YEL("----------------------------------------------------------------------------------------\n"));
                 printf(YEL("\t\t\t\t Docentes %i-%i\n"),anio,division);
                 printf(YEL("----------------------------------------------------------------------------------------\n"));
                 nodoDocente *auxDocente;
                 auxDocente=arreglo[i].listaDocentes;

                while(auxDocente!=NULL)
                {
                    printf("Nombre:|%s\t|  Apellido:|%s\t|  DNI:|%s\t| Materia :|%s\t|\n",auxDocente->docente.nombre,auxDocente->docente.apellido,auxDocente->docente.dni,auxDocente->docente.materia);
                    auxDocente=auxDocente->siguiente;
                }
                control=1;
        }
    }
    if(control==0){
        printf(RED("El curso ingresado no es valido\n"));
    }


    system("pause");

}


void docentesListadoTotal(celdaCursos arreglo[],int validos){



    for(int i=0;i<validos;i++){

        printf(YEL("----------------------------------------------------------------------------------------\n"));
        printf(YEL("\t\t\t\t  Docentes %i-%i \n"),arreglo[i].anio,arreglo[i].division);
        printf(YEL("----------------------------------------------------------------------------------------\n"));
        nodoDocente *auxDocente;
        auxDocente=arreglo[i].listaDocentes;

        while(auxDocente!=NULL)
            {
            printf("Nombre:|%s|\t  Apellido:|%s \t| DNI:|%s|  \t Materia:|%s\t|\n",auxDocente->docente.nombre,auxDocente->docente.apellido,auxDocente->docente.dni,auxDocente->docente.materia);
            auxDocente=auxDocente->siguiente;
            }

        }
        system("pause");

    }

void alumnosDeudores(){
    printf(RED("----------------------------------------------------------------------------------------------------------------\n"));
    printf(RED("\t\t\t\t\t\tAlumnos Deudores \n"));
     printf(RED("----------------------------------------------------------------------------------------------------------------\n"));
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    int dia,mes;


    dia= tm->tm_mday;
    mes=tm->tm_mon+1;




    FILE* cli;

    stAlumno auxAlumno;


    cli=fopen("alumnos.bin","rb");

    if(cli!=NULL)
    {

        while(    fread(&auxAlumno,sizeof(stAlumno),1,cli)>0       ){


            if(auxAlumno.bajaAlumno==0){
            if(auxAlumno.mesC<mes || (auxAlumno.diaC<dia && auxAlumno.mesC==mes)){
                printf("Nombre:|%s\t|  Apellido:|%s\t|  DNI:|%s\t|  Fecha de la cuota :|%i/%i/%i\t| \n",auxAlumno.nombre,auxAlumno.apellido,auxAlumno.dni,auxAlumno.diaC,auxAlumno.mesC,auxAlumno.anioC);
                }
            }



        }
    fclose(cli);



}
        system("pause");

}
void pagarDeuda(){

    char nombreA[]="alumnos.bin";
    int control=0;
    char dni[20];
    stAlumno aux;
    printf("Ingrese el dni para buscar al alumno\n");
    fflush(stdin);
    scanf("%s",dni);

    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);


    aux.idAlumno=docente_id(nombreA); ///busca la proxima id a usar
    control=usuario_exist(nombreA,dni,&aux);

    if(control==1){
        printf("El Alumno no existe");
    }
    else{
          printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \n",aux.nombre,aux.apellido,aux.edad,aux.dni);

          aux.diaC=tm->tm_mday;
          aux.mesC=tm->tm_mon+1;
          aux.anioC=1900+tm->tm_year;
          alumno_pagar(nombreA,aux);

        printf("el pago se realizo con exito \n\n");
    }



    system("pause");



}


void alumno_pagar(char nombre[],stAlumno aux) ///elimina el alumno buscado.
{

    FILE* cli;
    cli=fopen(nombre,"r+b");

    stAlumno aux_cli=aux;



    if(cli!=NULL)
    {
        fseek(cli,sizeof(stAlumno)*(aux_cli.idAlumno),SEEK_SET);
        fwrite(&aux_cli,sizeof(stAlumno),1,cli);
        fclose(cli);

    }
}
