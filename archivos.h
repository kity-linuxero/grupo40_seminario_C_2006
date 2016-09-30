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

/* FUNCIONES DE ARCHIVOS. LIBRERÍA ARCHIVOS.H*/


#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

/*inserta las lineas teniendo en cuenta el buffer máximo, cargando en un archivo.*/
lista cargar_text (char* nombre);

/* CARGAR/MODIFICAR EL ARCHIVO DE MENU :
AHORA COMO CAMBIE LA ORGANIZACION DEL ARCHIVO DEBO CAMBIAR EL ALGORITMO
el parámetro formal *cad" pertenece al nombre del nuevo campo*/
void cargar_menu (FILE *menu, char *cad);

/*IMPRIME EL ARCHIVO DE MENU. COMO VIENE EN UNA SOLA LÍNEA, LO ORGANIZA Y LO IMPRIME*/
int imp_menu (FILE *menu);

//imprime en pantalla el archivo base por línea.
int imp_archivo (FILE *archivo);

/*ESTE MÓDULO DEVUELVE UN VALOR DEL ARCHIVO AUXILIAR. ES NECESARIO PARA IR PIDIENDO LOS CAMPOS PARA 
  INGRESAR LOS DATOS. EJ.: nombre1 : (scanf...). LA OPCION INGRESADA ESTÁ EN RANGO.*/
char *dev_campo (char *opcion, FILE *menu);

//Guarda primero en una lista el tipo de campos variables.
lista definir_conjunto (lista lis);

/*Para guardar los cambios en el disco. De una lista a un archivo, recibe el nombre
físico del archivo.*/
void guardar_disco (lista ptr, char *nom_archivo);

//"macro" que devuelve 1 si la opción es 's' 0 si es '0', es caso que no sea ninguno, sigue preguntando.
short elegir_opcion (void);

/*Pregunta si desea guardar el archivo en el disco. Y si el usuario elige que si
deberá especificar el nombre del mismo. La función verificará si el archivo
existe para preguntar si se quiere sobreescribir.
La extensión por defecto es .txt*/
void guardar_disco_completo (lista arch);


lista generar_archivo_conjuntos (lista archivo_base, int modo);
void alistar_criterio (char *pun, FILE *arc);

/*RETORNA LA CANTIDAD DE <<>> QUE CONTIENE EL ARCHIVO*/
int cantidad_campos(lista arch_base);

short elegir_opcion (void);

int conjunto_valido (lista conjunto);

lista posicionar_lista (lista l);

int verificar_conj (lista l);

char *armar_hof (char *l);

char* completa_linea (char* linea);

/*LA LISTA NUEVA QUE ESTÁ EN EL CUADERNO*/
lista nue_definir_conjunto (lista items);
