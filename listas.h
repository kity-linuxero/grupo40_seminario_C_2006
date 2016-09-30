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

#include <stdio.h>
#include "defines.h"

/* CREA EL ARCHIVO DE CONJUNTOS.*/


  
typedef struct nodo {char *id;  struct nodo*sig;} *lista_aux;

typedef struct nn {char *linea; struct nn *sig;} *lista;

// LA LISTA  ORDENADA QUE VAMOS A DEVOLVER.
typedef struct lis {char *nom ; lista ptr ; struct lis *sig;} *lis_ordenada; 

//se inserta en la lista.
lista_aux insertar_auxiliar (lista_aux aux, char *str);


// PARA INSERTAR EN LA LISTA. CADA NODO REPRESENTA UNA LINEA.
lista insertar (lista l, char *cosa);

//PARA CARGAR A MEMORIA EL TEXTO
lista cargar_memoria (FILE *archivo);

//imprime la lista.
int imprimir (lista l);

//imprime la lista ordenada.
void imprimir_lis_ord (lis_ordenada l);

/*IMPRIME EL ARCHIVO DE MENU QUE SE HA CARGADO CON ANTERIORIDAD EN MEMORIA
  Retorna la cantidad de opciones que existen.*/
int imp_menu_mem (lista lista_menu);

// Para agregar un elemento en el menú cuando éste está cargado en memoria.
lista cargar_menu_mem (lista l_menu, char* cad);

/* ESTE MÓDULO RETORNA EL NOMBRE DEL CAMPO VARIABLE QUE ESTÁ EN LA POSICION
   INDICADA POR "opcion".*/
char *dev_campo_mem (char *opcion, lista menu);

// ESTA FUNCION EXTRAE EL CRITERIO  EJ.---NOMBRE|JOSE---EXTRAE NOMBRE
char *extraer_criterio (char *nom);

//ESTA FUNCION EXTRAE EL DATO QUE ACOMPAÑA AL CRITERIO EJ.---NOMBRE|JOSE---EXTRAE JOSE
char *extraer_dato (char *nom);

//insertar ordenado por nombre
lis_ordenada insertar_ord (char *nom,lista p,lis_ordenada l);

/*Recibe un criterio para ordenar para ordenar a la lista. O puede recibir 0 para indicar
que el usuario no quiere tener un orden*/
lis_ordenada  retorna_orden (char *criterio, lista p, int com, int fin);

//imprime el tipo de lista que tendrá o no, un tipo de orden.
void imp_lista_ordenada (lis_ordenada l);

/*Recorre un texto buscando los campos variables*/
int recorrer (lista l);

//primera funcion que esta llama a la recursiva, le manda una linea.
lista primer_funcion (lista base, lista_aux l_aux);

/*Esta función realiza la combinacion en el texto base que se ha ingresado por teclado.*/
char* recur_lin (char* linea, lista_aux l_aux, int *veces);

//VERIFICA SI POSEE CAMPO VARIABLE , RETORNA 0 SI NO POSEE.
int posee_campo(char *p);

/*VERIFICA SI POSEE CAMPO VARIABLE , RETORNA 0 SI NO POSEE. Es válido para el reeplazo
de los campos del texto base cuando están vacíos*/
int posee_campo_a(char *p);

/*Para la funcion del programa que modifica las lineas del texto base*/
lista modificar_linea(lista base, int lin);

/*ESTA ES LA FUNCION QUE CARGA EN UNA LISTA AUXILIAR LOS ITEMS ELEGIDOS EN EL MENU.*/
lista_aux funcion_menu1 (lista lista_menu, int cant);

/*Crea la lista pero sin orden. Mantiene el mismo tipo que la lista ordenada, para
reutilizar código*/
lis_ordenada insertar_sin_ord(lista p,lis_ordenada l);

//imprime la lista.
void imprimir_ant (lista l);

/*Se reciben base (corresponde al texto base), datos (que corresponde) a los conjuntos de datos
  y items_del_base, que es una lista de los posibles ordenes que puede tener la combinación de
  datos. Ej.: se puede pedir al programa que se ordene los resultados por el campo nombre.*/
lista combinacion (lista base, lista datos, lista items_del_base);

//realiza el reemplazo en el texto.
void reemplazar(char *linea , lista conj, FILE *archivo);

/*va a imprimir los campos variables que hay, para poder especificar
correctamente el orden. Retorna la cantidad de items*/
int imprimir_items (lista items_del_base);

/*ESTA FUNCION RETORNA LA CANTIDAD DE CONJUNTOS DE DATOS, 
IMPORTANTE!!  RECIBE COMO PARAMETRO DATOS DE TIPO LISTA*/
int cant_conj_datos(lista datos);

//Esta funcion modifica una linea del conjunto de datos.
lista modificar_linea_conj (lista conj, int conjunto, int linea);

void imprimir_conjunto(lista conj);


