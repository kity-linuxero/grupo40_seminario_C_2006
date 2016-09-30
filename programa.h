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

/* Interface de programa.c*/
#include "defines.h"
#include "listas.h"
//#include "archivos.h"

/*No se han mandado parámetros, así que iniciará en "modo interactivo".*/
int modo_1 (void);

/*Recibe un parámetro. Se debe identificar si es "/h" o el nombre del archivo de texto.*/
int modo_2 (char *arg);

/*Recibe tres argumentos, es nombre del archivo base, el nombre del archivo de 
conjunto y recibe el tercer parámetro que si es /P es que desea imprimir
por pantalla y sino se imprime por pantalla pero existe la opción de poder guardar el archivo.*/
int modo_3 (char *nom_base, char *nom_conjunto, char* parametro, short cant);

/* Recibe todos los argumentos, el nombre del archivo base, el de conjunto, especifíca que el
   "resultado" de la combinación */
int modo_5 (char *nom_base, char *nom_conjunto, char *modo, char *nom_arch_res);

lista mod_lin(lista base); //retorna la lista modificada.

