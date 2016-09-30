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

#include "archivos.h"
#include "fecha.h"

/* IMPLEMENTACIÓN DE LA LIBRERÍA ARCHIVOS.H */
/*inserta las lineas teniendo en cuenta el buffer máximo, cargando en un archivo.*/
lista cargar_text (char* nombre)
{ char c; short ok=1, i=0;
  FILE* archivo= fopen (nombre, "w");
  while (ok)
  {     c=getchar();
        while (putc(c,archivo) != FINAL && i++ < MAX_BUF && c != '\n')
              c=getchar();
        if (c == FINAL)
           ok=0; //sale del módulo porque llegó al final.
        else 
        
        if (i >= MAX_BUF)
           putc('\n',archivo);
        i=1;
  }

  fclose (archivo);
  fflush (archivo); //elimina del buffer el archivo. 
 
  /* 2ª fase.
    Veo que el momento correcto para pedir los campos variables es ahora.
    ya que cuando se carga el archivo, los campos están vacíos y no se podrá 
    reemplazarlos si no están definidos-*/ 
 
  archivo= fopen (nombre, "r"); //Se cambia la manera de tratar al archivo.
  fseek (archivo,0,0);
    
  lista arch_base= cargar_memoria (archivo); //el archivo se sube a memoria para trabajar mejor.
  
  limpiar; //limpia la pantalla.
  
  FILE *menu = fopen(NOM_MENU, "r");
 
  lista lista_menu= cargar_memoria (menu); //ahora tiene el archivo menu en memoria.

  lista_aux l_aux = funcion_menu1 (lista_menu, cantidad_campos(arch_base));

  /*Los campos a reemplazar serán los primeros n, siendo n la cantidad de campos variables. De haber
  campos de más, éstos ultimos no se agregarán.
  Tal vez hubiera sido mejor que la función pida la cantidad exacta de campos variables, pero me veo
  limitado con el tiempo a la entrega.*/
  

  lista arch_base1= primer_funcion (arch_base, l_aux);
  limpiar;
  printf ("TERMINO DE REEMPLAZAR LOS DATOS!\nEl archivo quedo de la siguiente manera:\n");
  
  imprimir (arch_base1);

  close (menu);
  fflush(menu);
  return arch_base1;
  
}


/* CARGAR/MODIFICAR EL ARCHIVO DE MENU :
   el parámetro formal *cad" pertenece al nombre del nuevo campo */
void cargar_menu (FILE *menu, char *cad)
{
    menu=fopen (NOM_MENU, "a"); //se agregará al final.
    strcat (cad, DELIMITADOR);
    fwrite (cad, sizeof(char), strlen(cad)-1, menu);
}



       
/* Guarda un archivo de texto que está en memoria como una lista de líneas en el archivo
  que indicará "nom_archivo".*/
void guardar_disco (lista ptr, char *nom_archivo)
{
     FILE* archivo= fopen (nom_archivo, "w");
     fseek (archivo, 0,0);
     while (ptr != NULL)
     { 
     fwrite (ptr->linea,1,strlen(ptr->linea),archivo);

       ptr=ptr->sig;
     }         
     fclose (archivo);
     fflush(archivo);   
}   
          
          
//"macro" que devuelve 1 si la opción es 's' 0 si es '0', es caso que no sea ninguno, sigue preguntando.
short elegir_opcion (void)
{ char c= getchar();
  while (c != 's' && c!= 'n')
        c= getchar();
  if (c== 's')
     return 1;
  return 0;      
}

/*Pregunta si desea guardar el archivo en el disco. Y si el usuario elige que si
deberá especificar el nombre del mismo. La función verificará si el archivo
existe para preguntar si se quiere sobreescribir.
La extensión por defecto es .txt*/
void guardar_disco_completo (lista arch)
{  printf ("Desea guardar el archivo?\n\ts/n: ");
  
  /*Para guardar el archivo base generado en el disco.*/
  if (elegir_opcion()) {
     char *nombre_definitivo = calloc (sizeof(char)*12,2);
     short ok=1;
    // while (ok) {   
        printf ("Nombre de archivo (la extension por defecto será %s) : ",EXT_POR_DEFECTO);
        char *nombre = calloc (sizeof(char)*8,2); //solo se tomarán 8 caracteres para el nombre.
        scanf ("%s", nombre);
           strcpy (nombre_definitivo, nombre);
        strcat (nombre_definitivo, EXT_POR_DEFECTO);
      
       guardar_disco (arch, nombre_definitivo);       
   }
}

void alistar_criterio (char *pun, FILE *arc)
{
   lista lis_aux=NULL;
   int i=-1; char *dato= calloc(sizeof(char)*MAX_BUF,2);
   if (posee_campo(pun)!= 0){
      while (pun [i] != '\n'){
            i++;
        while (pun [i]!= '<' && pun[i] != '\n')
               i++;
        if (pun [i] == '<' && pun [i+1] == '<'){
            i+=2;
            int j=0;
            strcpy (dato,"");
            while (pun[i] != '>'){
                  dato[j++]=pun[i];
                  i++;}
            dato[j]='\n';
            dato[j+1]='\0';
            fwrite (dato,strlen (dato),1,arc);
            
            lis_aux = insertar (lis_aux,dato);
            i++;
        }
      }
   }
        
}     
        
/*Con el fin de reutilizar esta funcion, decidí hacer dos modos para la misma.
El modo 0 retorna el conjunto y el modo 1 retorna los campos variables del base.*/
lista generar_archivo_conjuntos (lista archivo_base, int modo){
FILE *archivo= fopen(ARCH_CRT_TMP,"w");

while (archivo_base != NULL){
      alistar_criterio(archivo_base->linea,archivo);
      archivo_base=archivo_base->sig;
     }
      fclose(archivo);
      archivo=fopen(ARCH_CRT_TMP,"r");
      lista listado;
      if (!modo){ 
             lista lis_criterio= cargar_memoria(archivo);
             listado = nue_definir_conjunto (lis_criterio);
             
      }
      else
          return cargar_memoria (archivo);
            
      fclose(archivo);
      return listado;
}

/*RETORNA LA CANTIDAD DE "<<>>" QUE CONTIENE EL ARCHIVO*/
int cantidad_campos(lista arch_base)
{
    lista aux= arch_base;
    int cant=0,i;
    while (aux) //mientras != NULL
    {  i=0;
       while (aux->linea[i++])
         if(aux->linea [i-1] == '<' && aux->linea [i] == '<' && aux->linea [i+1] == '>' && aux->linea [i+2] == '>')
         {   cant++;
             i+=3; //avanza todos los campos que ya comprobó!
         }
       aux=aux->sig;
    }
    return cant;
}

/*VERIFICA SI EL ARCHIVO DE CONJUNTO ES VÁLIDO*/
int verificar_conj (lista l)
{int ok=1;
int i=1;

while (l->linea[0]!= '*' && ok==1 )
{     i=1;
      if (l->linea[0] == '|')
         ok=0;
      else{
          
          while (l->linea[i] != '|' && l->linea[i] != '\0')
                i++;
          
          if (l->linea [i] == '|')
             l=l->sig;
          else
              ok=0;
      
              }
     }
return ok;
}

//POSICIIONA LA LISTA EN EL CAMPO SUGUIENTE AL '*'

lista posicionar_lista (lista l)
{
     
     while (l->linea [0]!='*')
           l=l->sig;
     
     l=l->sig; //retorna l en la posicion que le sigue al '*'
     return l;
}
 

//retorna 1 si el conjunto de datos es valido, 0 en caso contrario 

int conjunto_valido (lista conjunto)
{int t=1;
     
     while (conjunto != NULL && t==1){
           
           
           if ( t=verificar_conj(conjunto) == 1)
              
           
              conjunto=posicionar_lista(conjunto);
             
           
     }
     return t;           
}           
 

/*DEFINIR CONJUNTO NUEVO */
lista nue_definir_conjunto (lista items)
{
      lista conjunto= NULL, items_tmp;
      int ok=1; char *str=calloc (sizeof(char)*MAX_BUF,2);
      while (ok){
            items_tmp=items;
            while (items_tmp->sig != NULL){
                  str=completa_linea(items_tmp->linea);
                  conjunto= insertar (conjunto, str);
                  items_tmp=items_tmp->sig;
            }
           
            conjunto= insertar (conjunto, "*");
            printf ("  Desea definir otro conjunto?\n\ts/n: ");
            
            ok=elegir_opcion();
            limpiar;
      }
      return conjunto;      
}

/*PROCESA INDIVIDUALMENTE UNA LINEA*/      
char* completa_linea (char* items)
{char*str=calloc (sizeof(char)*MAX_BUF,2);
 char*str_aux= malloc (10);
      if (!(es_fuh(items))){
            printf ("  Ingrese dato para %s ", items);
            scanf ("%s",str_aux);
            strncpy(str, items,strlen(items)-2);
            strcat(str, "|");
            strcat(str, str_aux);
            strcat(str, "\n");
      }
      else // es fecha u hora
      { if(es_fech(items)){
             strcpy (str, "f|");
             strcat (str, formato(1)); 
             strcat (str, "\n");
         }
         else //es hora
         { 
              str=calloc (4,2);
              strcpy (str, "h|");
              strcat (str, formato(0));
                           strcat (str, "\n");
           }
         }
      return str;           
}
