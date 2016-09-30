/*
 *  Copyright 2006
 *  Cristian Giambruni <cgiambruni@gmail.com>
 *  Jose Giraldo <eljosegiraldo@gmail.com>
 *  Elian Curccio <elian41@gmail.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "listas.h"
#include <stdio.h>
#include "defines.h"

/*Se necesita crear una lista para ir pidiendo los datos. */
//se inserta en la lista.
lista_aux insertar_auxiliar (lista_aux lis, char *str)
{ 
  if (lis == NULL)
  { lis= (lista_aux) calloc (sizeof(struct nodo),2);
    lis->id = calloc (strlen(str)*sizeof(char),2);
    strcpy (lis->id, str);
    lis->sig= NULL;
  }
  else
  { lista_aux aux = lis, nue = (lista_aux) calloc (sizeof(struct nodo),2);

    while (aux->sig != NULL)
          aux= aux->sig;
    aux->sig=nue;
    nue->id = calloc (strlen(str)*sizeof(char),2);
    strcpy (nue->id, str);
    nue->sig= NULL;
  }
  return lis;
}


/* PARA INSERTAR EN LA LISTA. CADA NODO REPRESENTA UNA LINEA */
lista insertar (lista l, char *cosa)
{
      if (l == NULL)
      { 
        l= (lista) calloc (sizeof(struct nn),2);
        l->linea = calloc (sizeof(char)*MAX_BUF, 2);
        l->linea = cosa;
        l->sig= NULL;
      }
      else
      { lista aux= l, nue = (lista) calloc (sizeof(struct nn),2);
        while (aux->sig != NULL)
              aux= aux->sig;
        nue->linea = cosa;
        nue->sig = NULL;
        aux->sig = nue;
      }
      return l;
}

/*Recorre un texto buscando los campos variables*/
int recorrer (lista l)
{int i=0, aux=0, contador=0, ok;
     while (l->sig != NULL) 
     {     
           while (l->linea[i] != '\n' && l->linea[i++] != '<' && contador < 2);
           if (l->linea[i-1] == '<')
              contador++;
           if (contador == 2) //ahora buscará los signos de clausura.
           {  contador=0; ok=1;
              while (l->sig != NULL && ok)
              {     i--;
                    while (l->linea[i] != '\n' && l->linea[i++] != '>' && contador < 2);
                         if (l->linea[i-1] == '>')
                            contador++;
                         if (contador ==2)
                         {   
                             contador=0;
                             aux++; //encontró un campo variable.
                             ok=0;
                         }
               }
           }
           if (l->linea[i] == '\n')
           {    i=0;
                l=l->sig;
           }
     }
     return aux; //devuelve la cantidad de campos variables en un archivo en memoria.
}

/*IMPRIME EL ARCHIVO DE MENU QUE SE HA CARGADO CON ANTERIORIDAD EN MEMORIA.
  Retorna la cantidad de opciones que existen en el menú.*/
int imp_menu_mem (lista lista_menu)
{char *c=calloc (sizeof(char),2); int i=1, ok=1,b=0;
 static int flag=1;

 printf (" %d- ", i++);
 while (b < strlen(lista_menu->linea) && ok)
 {     *c= lista_menu->linea[b++];
       while (*c != '|' && b < strlen(lista_menu->linea))
       {  putchar(*c);
          *c=lista_menu->linea[b++];
       }
       if (*c == '|' && b != strlen(lista_menu->linea))
          printf ("\n %d- ", i++);
       else
       {   if (*c!= '|')
           {  printf ("Nuevo valor\n");          
              ok=0;
           }
           else
           {  printf ("\n %d- Nuevo valor\n", i++);
              ok=0;
           }
       }
 }
 printf ("------------------------------\n");
 return (i-2);
}

//imprime la lista ordenada.
void imprimir_lis_ord (lis_ordenada l)
{ 
  while (l != NULL)
  {      printf ("%s\n", l->nom);
         printf("%s",*l->ptr);
         l= l->sig;
  }
  printf ("\n\n");

}

/*ESTA ES LA FUNCION QUE CARGA EN UNA LISTA AUXILIAR LOS ITEMS ELEGIDOS EN EL MENU.*/
lista_aux funcion_menu1 (lista lista_menu, int cantidad)
{
char *opcion=malloc (sizeof(char)); int cambio=0;
 lista_aux auxiliar= NULL; int i;
 
  for (i=0; i<cantidad;i++)
  {    
      limpiar;
      printf ("\n   .:: Menu de campos variables ::.\n\n Elija opcion para el campo %d\n\n",i+1); 
      int cant= imp_menu_mem(lista_menu); //imprime el menu.

      printf ("\n Su opcion:");
      scanf ("%s", opcion);
      char *str= calloc (sizeof(char)*20,2);
      if (atoi(opcion) == cant+1) //si se quiere agregar un elemento que no existe.
           { printf ("\n  Ingrese el nuevo valor: ");
             cambio=1;
             scanf ("%s",str);
             
             lista_menu= cargar_menu_mem (lista_menu, str);
        /*Cuando se define un nuevo elemento, se inserta inmediatamente a la lista de 
        campos variables. Se supone que cuando se desea agregar un nuevo elemento seguro
        que debe ir en la lista de campos variables*/   
           }
        else
        {   
            if (atoi(opcion)== 1)
              strcpy (str, "f");
            else 
            {  if (atoi(opcion)==2)
                 strcpy (str, "h");
               else //no es ni fecha u hora, ó ya se ha especificado antes.
               {     if (rango(atoi(opcion),cant+1))
                       str= dev_campo_mem(opcion, lista_menu);
                     
                     else
                     {   while (atoi (opcion) && !rango(atoi(opcion), cant+1))
                         {      printf (" Fuera del rango esperado\n");
                                scanf ("%s", opcion);
                         }
                         
                     }
               }
            }
        }
        
        auxiliar= insertar_auxiliar (auxiliar, str);
  } //fin for
        
  if (cambio)
  { printf ("\n El archivo de menu ha cambiado!.\nDesea guardar los cambios.\n s/n : ");
    if (elegir_opcion())
       guardar_disco (lista_menu, NOM_MENU); //guarda los cambios en el archivo.
  }
  return auxiliar;        
}

/* PARA CARGAR A MEMORIA EL TEXTO */
lista cargar_memoria (FILE *archivo)
{lista l=NULL;
      char *c= calloc (sizeof(char),2);
      fseek (archivo, 0,0);
      while (!feof(archivo))
      {
         char *string= calloc (sizeof(char)*MAX_BUF,2);
         do
         {  *c=fgetc(archivo);   
            strcat (string, c);
         }
         while (*c != '\n' && !feof(archivo));
            string[strlen(string)]='\b';
            l=insertar(l,string);
      }
      return l;
}

//imprime la lista por línea y retorna la cantidad de ellas.
int imprimir (lista l)
{ int c=1;

  while (l != NULL)
  {      printf ("Lin%d- %s", c++, l->linea);
         l= l->sig;
  }
  printf ("\n\n");
  return c-1;
}

//imprime la lista.
void imprimir_ant (lista l)
{ 
  while (l != NULL)
  {      printf ("%s", l->linea);
         l= l->sig;
  }
  printf ("\n\n");
}

/*AGREGA UN NUEVO ELEMENTO EN EL MENÚ QUE ESTÁ CARGADO EN MEMORIA*/
lista cargar_menu_mem (lista l_menu, char* cad)
{ lista aux= l_menu;
      strcat (l_menu->linea,cad);
      strcat (l_menu->linea, DELIMITADOR);
      return l_menu;

}

/* ESTE MÓDULO RETORNA EL NOMBRE DEL CAMPO VARIABLE QUE ESTÁ EN LA POSICION
   INDICADA POR "opcion".*/
char *dev_campo_mem (char *opcion, lista menu)
{ 
  int i=0, b=0, op=atoi (opcion); 
  for (i=1;i<op;i++)
      while (menu->linea[b++] != C_DELIMIT);
  i=0;
  char str[20]; //arreglo auxiliar de catacteres.
  str[i]= menu->linea[b-1];
  while (menu->linea[b] != C_DELIMIT)
        str[i++]= menu->linea[b++];
  str[i]= '\0';
  char *dev= calloc(sizeof(char)*20,2);
  strcpy (dev, str);
  return dev;
}

//insertar ordenado por criterio
lis_ordenada insertar_ord (char *nom, lista p, lis_ordenada l)
{
 if (l != NULL) //si la lista tiene al menos un elemento.
 {
    lis_ordenada anterior=NULL, actual=l; //declaración de variables auxiliares.
/* ahora hay una iteración condicional por si n > actual->dato. Antes el programa no me andaba
   y me dí cuenta que cambiando el orden de la condición funciona. Ya que C, al ver que como no
   se cumple la primer condición, no pregunta por la otra. Que en un caso, era condición de error */
    while (actual != NULL && (strcmp(nom, actual->nom)) > 0) 
    //busca el lugar para insertar por orden, o en caso que se termine la lista, se inserta a lo último.
    {
          anterior = actual;
          actual= actual->sig;
    }
    if (anterior == NULL) //si se debe insertar al principio de la lista (no entró en el while).
    {
       anterior = (lis_ordenada) malloc (sizeof(struct lis));
       anterior->nom = calloc (sizeof(char)*MAX_BUF, 2);
       strcpy (anterior->nom, nom);
       anterior->ptr=p;
       anterior->sig = actual;
       return anterior; //retorna anterior, ya que es el nuevo "primer elemento".
    }
       else
       {
           lis_ordenada nue;
           nue= (lis_ordenada) malloc (sizeof(struct lis));
           nue->nom = calloc (sizeof(char)*MAX_BUF, 2);
           strcpy (nue->nom, nom);
           nue->ptr = p;
           anterior->sig = nue;
           nue->sig= actual;
       }
  }  
 else
 {
  l= (lis_ordenada) malloc(sizeof(struct lis));
  l->nom = calloc (sizeof(char)*MAX_BUF, 2);
  strcpy (l->nom, nom);
  l->ptr=p;
  l->sig= NULL;
 }
 return l;
}

/*Crea la lista pero sin orden. Mantiene el mismo tipo que la lista ordenada, para
reutilizar código*/
lis_ordenada insertar_sin_ord(lista p,lis_ordenada l){
  
   if(l==NULL){
     l=(lis_ordenada) malloc (sizeof(struct lis));         
     l->ptr=p;
     l->sig=NULL;
    }
    else{
      lis_ordenada nue=(lis_ordenada) malloc (sizeof(struct lis));  
      lis_ordenada aux=l;
  
      while (aux->sig != NULL)
         aux=aux->sig;   
      nue->ptr=p;
    
      aux->sig=nue;
      nue->sig=NULL;      
      }        
   return l;
}

// ESTA FUNCION EXTRAE EL CRITERIO  EJ.---NOMBRE|JOSE---EXTRAE NOMBRE
char *extraer_criterio (char *nom){
     int i=0;
     char *n= calloc (sizeof(char)*MAX_BUF,2);
     if(nom[0]=='*')
        return "*";
     else
        while (nom[i] != '|'){
           n[i]=nom[i];
           i++;
           }
     return n;
 }
//ESTA FUNCION EXTRAE EL DATO QUE ACOMPAÑA AL CRITERIO EJ.---NOMBRE|JOSE---EXTRAE JOSE
char *extraer_dato (char *nom){
     int i=0;
     char *n= calloc (sizeof(char)*MAX_BUF,2);
     
     while (nom[i++] != '|');
  
     int j=0;
     while (nom[i] != '\n'){
          n[j++]=nom[i++];
     }            
     n[i]= '\0';
     return n;
 }

/*RETORNA POR MEDIO DE UNA LISTA EL RANGO ELEGIDO POR EL USUARIO,
ORDENADO POR EL CRITERIO ELEGIDO POR EL USUARIO
SI CRITERIO = 0 INSERTA SIN ORDEN*/
lis_ordenada  retorna_orden (char *criterio, lista p, int com, int fin){
    lis_ordenada l=NULL;
    lista aux;

    char *nom1= calloc (sizeof(char)*MAX_BUF,2);
    char *cri= calloc (sizeof(char)*MAX_BUF,2);
    char *dato= calloc (sizeof(char)*MAX_BUF,2);
    char *c =calloc (sizeof(char)*MAX_BUF,2);
    int ok,ind=1;

    while ( ind < com ){ // mientras no llegue al comienzo deseado...
       while(p->linea[0] != '*'){  //voy a pasar por conjuntos de datos que no me interesan
             p=p->sig;               
          }
          if(p->sig!=NULL){
             p=p->sig;
             ind++;
          }
    }
    criterio[strlen(criterio)-2]= '\0'; 
    //criterio se carga mal, por eso ponemos esta solución.
    
    if(strcmp(criterio,"0")) // si hay algun tipo de orden
    {

      while(ind<=fin && ok){    //mientras no llegue a donde deseo "fin"
          aux=p;         
          strcpy (nom1, aux->linea); //tomo el total de la linea, EJ nombre|jose
          
          cri= extraer_criterio(nom1); //tomo solo el criterio, EJ nombre
         
          dato=extraer_dato(nom1); // tomo solo el dato, EJ jose

          while (strcmp (cri,criterio)){ // mientras no se encuentre el criterio deseado
                aux= aux->sig; // avanzo...
                strcpy (nom1,aux->linea); //tomo el total de la linea, EJ nombre|jose
                cri=extraer_criterio(nom1); //tomo solo el criterio, EJ nombre
                dato=extraer_dato(nom1); // tomo solo el dato, EJ jose
          }
          l=insertar_ord(dato,p,l); 
          /* una vez insertado el dato, me muevo hasta llegar al '*'; fin del
               conjunto de datos*/
          strcpy(c, aux->linea);
          
          while (c[0] != '*') {      
                 aux=aux->sig;
                 strcpy(c, aux->linea);
          }      
          if(aux->sig!=NULL){ 
             p=aux->sig; /*actualizo p, posicionandolo al principio del sig conjunto de datos.*/      
             ind++;
             }
          else ok=0;
     }
    }//FIN DEL IF QUE COMPARA CRITERIO CON 0
    else // no deseo ningun orden, inserto sin criterio
      {   fin--;
         l=insertar_sin_ord(p,l);
           while(ind<=fin && ok){
              while(p->linea[0]!='*')
                   p=p->sig;
              if(p->sig!=NULL){
                 p=p->sig;
                 ind++;
                 l=insertar_sin_ord(p,l);
               }
               else 
                 ok=0;     
           }
     }
     return l;
}


/*Para la funcion del programa que modifica las lineas del texto base*/
lista modificar_linea(lista base, int lin){

   lista lis_aux= base;
   
   FILE *ar_tmp = fopen (NOM_TMP,"w");
   int i=0;
   getchar(); //elimina el buffer del teclado.
      
   while (fputc(getchar(),ar_tmp)!= '\n' && i++<MAX_BUF);

   fclose(ar_tmp);
   ar_tmp= fopen(NOM_TMP, "r" );

   lista lis_modificar = cargar_memoria(ar_tmp);

   int z=1;
   
   lista ll=base;

   while(z++ < lin)
             ll=ll->sig;
   
   if(z-1 == lin)
      strcpy(ll->linea,lis_modificar->linea);   
   return base;
}

//VERIFICA SI POSEE CAMPO VARIABLE, RETORNA 0 SI NO POSEE.
int posee_campo (char *str)
{
    short ok=1, i=0;
    while (ok==1){
           while (str[i] != '\n' && str[i] != '<')
             i++;
           if (str[i] == '<'){
            if (str[i+1] == '<'){
 
           while (ok) {
 
               while (str[i] != '>' && str[i] != '\0')
                  i++;
 
               if(str[i]=='\0'){
                  return 0;
               }
               else
                  if (str[i] == '>')
                    if (str[i+1] == '>'){ 
                          return 1;
                    }
                    else                 
                         i++;
               }
          }
          }
          if (!str[++i])
              ok=0;
   }
  return ok;
}

/*VERIFICA SI POSEE CAMPO VARIABLE , RETORNA 0 SI NO POSEE. Es válido para el reeplazo
de los campos del texto base cuando están vacíos*/
int posee_campo_a(char *p)
{   short i=0, ok=0;
     while (!ok) {
       
       while ( p[i]!= '<'  &&  p[i++]!='\n' );
   
       if (p[i] == '<'  &&  p[i+1] == '<' && p[i+2] == '>' && p[i+3] == '>')
                  
             ok=1;
       else
           if (p[i-1] == '\n')
              return 0;
              else i+=2; //para que no vuelva a pasar por "<<"
     }
     return i+2;
}
  
/*Cuando se realiza la combinacion en el texto base que se ha ingresado por teclado se
  invoca a esta función recursiva que trata solo una línea del texto base. */
char* recur_lin (char* linea, lista_aux l_aux, int *veces)
{  char* cad= calloc (MAX_BUF,2); short pos;
    
   if (l_aux != NULL)  //corta en caso de que la lista auxiliar se termine.
   {  int i=0; 
      
      if (pos=posee_campo_a (linea)) //si tiene al menos un campo variable.
      {  
         strncpy (cad, linea, pos); //copia hasta lo que leyó.
         strncat (cad, l_aux->id, strlen (l_aux->id)); //es así porque tengo que eliminar el '\n'
        
         short j= strlen (cad);
         
         while (linea [pos-1])
               cad[j++]= linea[pos++];
         *veces+=1;
         return recur_lin (cad, l_aux->sig, veces); //vuelve al proceso recursivo.
      }
   }  
   return linea;
}


//primera funcion que esta llama a la recursiva, le manda una linea.
lista primer_funcion (lista base, lista_aux l_aux)
{  
  lista aux_base= base;

  char* cad= malloc (MAX_BUF);
  int veces=0, i;
  
  while (aux_base != NULL)
  {     
        cad= recur_lin(aux_base->linea, l_aux, &veces); //retorna la cadena completa.
        strcpy (aux_base->linea,cad);
        //la lista auxiliar debe avanzar        
        for (i=0; i<veces; i++)
            l_aux=l_aux->sig;
        aux_base = aux_base->sig;
        veces=0;       
  }     
  return base;      
}

//realiza el reemplazo en el texto.
void reemplazar(char *linea , lista conj, FILE *archivo){
   
   char *criterio= calloc(sizeof(char)*MAX_BUF,2);
   char *cadena= calloc(sizeof(char)*MAX_BUF,2);
   char *dato= calloc(sizeof(char)*MAX_BUF,2);
   char *cadena_aux= calloc(sizeof(char)*MAX_BUF,2);
   char *cri= calloc(sizeof(char)*MAX_BUF,2);
   lista a=conj;

   int ok=0, tam=0, i=0 ,e=0 ,x=0, u=0, j=0;
  
   ok=posee_campo(linea);  
   
   if (!ok)
     fwrite (linea,1,strlen(linea),archivo);

   else{
      while (linea[i]!= '<')
         cadena[e++]=linea[i++];
          
      if(linea[i]=='<' && linea[i+1]== '<'){
         i+=2;
         while(linea[i]!= '>')
            criterio[x++]=linea[i++];
         criterio[x]='\0';
         if ((strcmp(criterio, "f")==0) || (strcmp(criterio, "h")==0)){           
            cri = extraer_criterio(conj->linea);
            if (criterio[0] == 'f'){
               while(strcmp(cri,criterio)!=0  &&  cri[0] != '*'){
                  conj= conj->sig; 
                  cri= extraer_criterio(conj->linea);
               }
               if(cri[0] == '*')
                  dato="::NO EXISTE DATO::";
               else
                  if(strcmp(cri,criterio)==0){
                     int var = atoi(extraer_dato(conj->linea));
                     dato= (char*) funcion (var);    
                  }
           }
           else {  // es = a hora
                while(strcmp(cri,criterio)!=0  &&  cri[0] != '*'){
                   conj= conj->sig; 
                   cri= extraer_criterio(conj->linea);
                }
                if(cri[0] == '*')
                  dato="::NO EXISTE DATO::";
                else
                   if(strcmp(cri,criterio)==0){
                      short numero= atoi(extraer_dato(conj->linea));
                      dato=(char*) funcion(numero+4);  
                   }
           }
         conj=a;
         }
         
         else{            
         cri = extraer_criterio(conj->linea);
         while(strcmp(cri,criterio)!=0  &&  cri[0] != '*'){
            conj= conj->sig; 
            cri= extraer_criterio(conj->linea);
         }
         if(cri[0] == '*'){
            dato="::NO EXISTE DATO::";
         }
         else
            dato=extraer_dato(conj->linea);
         }
         conj=a;   
         tam=strlen(dato);
         
         while(u<=tam)
            cadena[e++]=dato[u++];
         i+=2;
         while(linea[i]!='\n')
            cadena_aux[j++]=linea[i++];   
         cadena_aux[j]='\n';      
          
         strcat(cadena,cadena_aux);
 
         reemplazar(cadena,conj,archivo);
         }                     
    }
}

/*Se reciben base (corresponde al texto base), datos (que corresponde) a los conjuntos de datos
  y items_del_base, que es una lista de los posibles ordenes que puede tener la combinación de
  datos. Ej.: se puede pedir al programa que se ordene los resultados por el campo nombre.*/
lista combinacion (lista base, lista datos, lista items_del_base)
{
  printf ("\nDesea modificar alguna linea de un conjunto?\n\ts/n: ");
  if (elegir_opcion())
  {
     short int ok=1;
     while (ok)
     {     
        imprimir_conjunto (datos); //va a imprimir un conjunto con sus campos.
        /*Se hace de la siguiente manera, pareciéndo complicar un poco el código
        pero facilitándo la interfaz del usuario*/
        printf ("Escriba el numero de conjunto que desee cambiar y la linea\nnumero_conjunto (espacio) numero_linea ó 0 para borrar el conjunto.\n\t");

        char* conj=calloc (sizeof(char)*2,2);
        scanf ("%s", conj);
        
        if (atoi(conj)) //Si el conjunto es 0, se cancela la operación (por si el usuario se equivoca).
        {
           char* line=calloc (sizeof(char)*2,2);
           scanf ("%s", line);
           
           datos= modificar_linea_conj (datos, atoi (conj), atoi (line));
        
           printf ("Desea modificar otra linea?\n\ts/n: ");
          
        if (!elegir_opcion())
           ok=0;
        } else
              ok=0;
     }
  }
  getchar ();//elimina el enter del buffer 
  printf ("Desea imprimir los resultados con algun orden en especial?\n\ts/n: ");
 
  char *criterio= calloc (sizeof(char)*50,2);
  
  if (elegir_opcion())  //quiere ordenarlas por un criterio
  {     //Pedirá un criterio de orden
        int cant= imprimir_items (items_del_base); //imprimirá en pantalla los criterios de ordenación posibles.

        scanf("%s", criterio);
        while (!rango(atoi(criterio),cant))
               scanf("%s", criterio);
        int i;
         //avanza la lista para llegar a la posición que se encuentra el orden deseado
        for (i=1; i<atoi(criterio); i++)
            items_del_base= items_del_base->sig;


         strcpy (criterio, items_del_base->linea);  
    }
    else
        strcpy (criterio, "0"); //lo hace sin orden.
  //retorna una lista ordenada por el criterio ya especificado
   /*IMPRIMIR LOS CONJUNTOS Y PREGUNTAR SI QUIERE RANGO.*/
   lis_ordenada datos_conj;
   printf ("\nDesea imprimir solo un rango de los conjuntos?\n\ts/n: "); 
   if (elegir_opcion()){
       short desde, hasta;
       printf ("Se imprimiran los conjuntos\n\tdesde el conjunto: "); scanf ("%d", &desde);
       printf ("\thasta el conjunto: "); scanf ("%d", &hasta);
       datos_conj = retorna_orden (criterio, datos, desde, hasta);
       }
   else //El resultado abarca todos los conjunto de datos.Desde el primero hasta la cantidad total.
        datos_conj = retorna_orden (criterio, datos, 1, cant_conj_datos(datos));

  lista aux=base;
  FILE *archivo=fopen(RESULTADO_TMP,"w");
  //se crea un archivo temporal sobre el cual se escriben los resultados temporalmente. 
  short contador=1;  
  while (datos_conj != NULL){
     fprintf(archivo, "\n\n   TEXTO %d\n",contador++);   
     while ( base != NULL ){
         reemplazar(base->linea,datos_conj->ptr, archivo);
         base=base->sig;  
     }
   
     if (base == NULL){
        base=aux;
        datos_conj=datos_conj->sig;
     }
  }
      
  fclose(archivo);      //cierra el archivo.
  archivo=fopen (RESULTADO_TMP, "r");
  return cargar_memoria(archivo);
}


/*va a imprimir los campos variables que hay, para poder especificar
correctamente el orden. Retorna la cantidad de items*/
int imprimir_items (lista items_del_base)
{ int i=1;
 while (items_del_base->sig){
       printf ("%d - %s", i++, items_del_base->linea);
       items_del_base= items_del_base->sig;
       }
 return i-1;  
}

/*ESTA FUNCION RETORNA LA CANTIDAD DE CONJUNTOS DE DATOS, 
IMPORTANTE!!  RECIBE COMO PARAMETRO DATOS DE TIPO LISTA*/
int cant_conj_datos(lista datos){
  int cant=0;
  
  while (datos != NULL){
     cant++;

     while (datos->linea[0] != '*')
        datos=datos->sig;
     datos=datos->sig;
       }      
  return cant;
}

//Esta funcion modifica una linea del conjunto de datos.
lista modificar_linea_conj (lista conj, int conjunto, int linea){
        int c=1;
        lista aux=conj,a=conj;
                     
        while(c<conjunto){  //avanza en la lista mientras no encuentre el conjunto de datos a modificar
          while(aux->linea[0]!='*'){
             a=aux;
             aux=aux->sig;
             }
          a=aux;
          aux=aux->sig;
          c++;
        }
        if(linea){
        c=1;
        while (c<linea){ // avanza en la lista, mientres no encuenter la linea a modificar.
          a=aux;     
          aux=aux->sig; 
          c++;
        }
        char *cri= calloc(sizeof(char)*MAX_BUF,2);
        char *dato= calloc(sizeof(char)*MAX_BUF,2);
        //// va estar parado sobre la linea a modificar  ////
        cri=extraer_criterio(aux->linea);
        printf("Ingrese un nuevo dato para %s : ",cri);
        scanf("%s",dato);
        strcat(cri,"|");      
        strcat(cri,dato);                  
        strcpy(aux->linea,cri);
        strcat (aux->linea, "\n");
     }
     else{ //la linea va a ser igual a 0, por lo tanto elimino conjunto entero
        lista ant=a;
        while(aux->linea[0]!='*'){
           aux=aux->sig;
          }
         
        ant->sig=aux->sig;        
        }
  return conj;
 }
 
//IMPRIME CONJUNTO DE DATO
void imprimir_conjunto(lista conj){
   int i=1;
   short x=1;
   while(conj != NULL){
      printf ("\n     Conjunto %d\n", x++);
      while (conj->linea[0]!='*'){
         printf("Linea%d: %s",i++,conj->linea);
         conj=conj->sig;
      }
      i=1;              
      stop; 
      conj=conj->sig; 
   }
}
