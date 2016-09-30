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

/*DEFINICION DE CONSTANTES*/

//Nombres predefinidos de archivos 
#define NOM_PORDEFECTO ".\\source\\file.tmp" //es un nombre de archivo temporal por defecto
#define NOM_TMP ".\\source\\mod_lin.tmp"
#define NOM_MENU ".\\source\\menu.dat" //el nombre del menú será siempre el mismo, pero toda
#define FILE_HLP ".\\source\\ayuda.dat"
#define RESULTADO_TMP ".\\source\\res_00.tmp"
#define ARCH_CRT_TMP ".\\source\\crt.tmp"


//Macros - funciones del programa
#define limpiar system ("cls")
#define rango(x,y)  (x<=y && x>0)? 1 : 0
#define stop system ("pause")
#define splash(text) printf ("\t--------------------------------------------\n\t\t %s\n\t--------------------------------------------\n\n",text)
#define rupt printf ("Stop del programa\n"); system ("pause")
#define imp(x)      printf("%s\n",x)
#define leer(linea) int zz=0; \
                    while ((linea[zz++]= getchar()) != '\n');\
                    linea[zz+1] = '\0';\
                    getchar();
//si es fecha u hora
#define es_fuh(linea) ((linea[0]== 'f') || (linea[0] == 'h') && linea[1]=='\n')? 1 : 0

#define es_fech(linea) (linea[0]== 'f' && linea[1]== '\n')? 1 : 0

#define es_hora(linea) ((linea[0]=='h' && linea[1]=='\n')? 1 : 0



//Constantes
#define MAX_BUF 99 //máximo de caracteres por lìnea
#define C_DELIMIT '|'
#define DELIMITADOR "|"
#define CORTE "0" //condición de final de ingreso de conjuntos
#define FINAL '&'
#define EXT_POR_DEFECTO ".txt"
