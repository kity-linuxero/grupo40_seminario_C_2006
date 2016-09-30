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

// el punto c de los argumentos al main
#include "programa.h"

//#include "listas.h"
/*No se han mandado parámetros, así que iniciará en "modo interactivo".*/
int modo_1 (void)
{      
       //carga el archivo base. Y especifíca los campos determinados por "<<>>"
       splash ("Se inicia el modo interactivo.");
       printf ("Ingrese el texto base\n\n");      
       
       lista lis_base= (lista) cargar_text (NOM_PORDEFECTO);
       


       /*El archivo se encuentra bien?... Desea modificar alguna línea. Acá debe
       estar la opcion de modificar línea.*/
       mod_lin (lis_base);
       



       /*SE CARGAN LOS CAMPOS VARIABLES QUE ESTÁN EN EL TEXTO BASE*/
      lista conjunto= (lista) generar_archivo_conjuntos (lis_base,0);
       
       FILE *archivo=fopen(ARCH_CRT_TMP,"r");
       
       lista items = cargar_memoria(archivo);

      
       //ahora realiza la combinación con los datos
       lista resultado_comb = combinacion (lis_base, conjunto,items);

       /*ahora tenemos que imprimir el resultado de la combinación.*/
       //imprime la lista ordenada.
       imprimir (resultado_comb);

       guardar_disco_completo (resultado_comb); //por si lo quiere guardar.
       
       return 0; 
}
       

/*Recibe un parámetro. Se debe identificar si es "/h" o el nombre del archivo de texto.*/
int modo_2 (char *arg)
{
   
   if (!strcmp(arg, "/h")) //si el argumento pasado es el de la ayuda.
     { 
              
     FILE* ayuda= fopen (FILE_HLP, "r");              
     imprimir_ant (cargar_memoria(ayuda));
     
     }
     else {

       // es que viene el texto base.
       //para el caso de que existe el texto base. (se debe comprobar su existencia.
       FILE* base;
       if (base= fopen (arg,"r")) //comprueba si existe el archivo.
       {

       lista lis_base=cargar_memoria(base);
       //crea en una lista el conjunto que le inserte el usuario.

     

       lista conjunto= (lista) generar_archivo_conjuntos (lis_base,0);
       
       FILE *archivo=fopen(ARCH_CRT_TMP,"r");
       
       lista items = cargar_memoria(archivo);
       
       
       //imprime en pantalla los conjuntos enumerados.
 //      short cant= listar_conjuntos (conjunto);
       
        /* Pide si se quiere procesar solo un rango de los conjuntos.
       esta función, a su vez llama a la segunda función del orden. */
       
        
       
       //ahora realiza la combinación con los datos
       lista resultado_comb = combinacion (lis_base, conjunto, items);

       /*ahora tenemos que imprimir el resultado de la combinación.*/
       imprimir_ant(resultado_comb);
       //Por si se quiere guardar
       guardar_disco_completo (resultado_comb);
//       return resultado_comb;
       }
        else {
             printf ("[error] EL ARCHIVO NO EXISTE.\n");

             return 0;
             
             }
       }
       
}

/*Recibe dos argumentos. El primero es el nombre del archivo de texto y el segundo
  el nombre del arhivo de conjuntos.*/
int modo_3 (char *nom_base, char *nom_conjunto, char* parametro, short cant)
{
    
    
    FILE* base; FILE* conj;
    splash ("MODO 3");
    
    if ((base = fopen (nom_base, "r")) && (conj= fopen (nom_conjunto, "r")))
    {
       //carga en la memoria los dos archivos.
          lista conjunto= cargar_memoria (conj);
          lista lis_base=cargar_memoria (base);
          if (conjunto_valido(conjunto)) { 
    
       lista items= (lista) generar_archivo_conjuntos (lis_base,1);
          

        lista resultado_comb = combinacion (lis_base, conjunto, items);

        /*ahora tenemos que imprimir el resultado de la combinación.*/
        imprimir_ant (resultado_comb);

        if (cant == 4) {
           if (strcmp (parametro, "/P") && strcmp (parametro, "/p")) {
               printf ("\n[aviso] Se ha ingresado un parametro invalido para este modo\n\n");   
               guardar_disco_completo (resultado_comb);
           }
    
        }
    
        else
            guardar_disco_completo (resultado_comb);
     }
     else printf ("[error] EL ARCHIVO DE CONJUNTOS DE DATOS TIENE UN FORMATO INVALIDO\n");
     }
     else 
          printf ("[error] EL ARCHIVO NO EXISTE.\n");

}



/* Recibe todos los argumentos, el nombre del archivo base, el de conjunto, especifíca que el
   "resultado" de la combinación */
int modo_5 (char *nom_base, char *nom_conjunto, char *modo, char *nom_arch_res)
{
    if (!(strcmp (modo, "/A") && strcmp (modo, "/a")))

       {
            
            FILE* base; FILE* conj;
            splash ("MODO 4");
    
            if ((base = fopen (nom_base, "r")) && (conj= fopen (nom_conjunto, "r")))
            {
            //carga en la memoria los dos archivos.
            lista conjunto= cargar_memoria (conj);
            lista lis_base=cargar_memoria (base);
            if (conjunto_valido(conjunto)) { 
    
            lista items= (lista) generar_archivo_conjuntos (lis_base,1);
          

          lista resultado_comb = combinacion (lis_base, conjunto, items);

        /*ahora tenemos que imprimir el resultado de la combinación.*/
        

      guardar_disco (resultado_comb, nom_arch_res);  
     }
     else printf ("[error] EL ARCHIVO DE CONJUNTOS DE DATOS TIENE UN FORMATO INVALIDO\n");
     }
     else 
          printf ("[error] EL ARCHIVO NO EXISTE.\n");
    
}
printf ("[error] PARAMETRO INVALIDO.\n");
}

 //retorna la lista modificada.
lista mod_lin (lista base)
{
       int cant= imprimir (base); // se imprime el archivo.
       printf ("\nDesea cambiar alguna linea del texto?\n    s/n: ");
       if(elegir_opcion()) //si se desea modificar alguna línea.
       {  printf ("numero de linea a modificar: ");
          int var;
          scanf ("%d", &var);
          while (!rango(var,cant)) //mientras esté fuera del rango
                 scanf ("%d", &var);
          base= modificar_linea (base, var);
        }
     limpiar;
     printf ("El texto queda asi\n");
     imprimir (base);
     stop;
     return base;
}

