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

#include <time.h>
#include "fecha.h"

// RETORNA EL FORMATO CORRESPONDOENTE A LA FECHA U HORA, MEDIANTE 'CAD'
char *funcion(int n){  
    time_t tiempo;
    char *cad;
    struct tm *tmPtr;
    cad = (char *) calloc(sizeof(char)*80,2);
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    switch (n) {
           case 0: strftime( cad, 80, " %d/%B/%Y", tmPtr ); break;//Esta funcion retorna la fecha en forma ---03/junio/2006---
           case 1: strftime( cad, 80, " %d/%m/%y", tmPtr ); break;//Esta funcion retorna la fecha en forma ---03/03/06---
           case 2: strftime( cad, 80, " %d/%m/%Y", tmPtr ); break;//Esta funcion retorna la fecha en forma ---03/03/2005---
           case 3: strftime( cad, 80, " %d/%B/%y", tmPtr ); break;//Esta funcion retorna la fecha en forma ---03/marzo/05---
           case 4: strftime( cad, 80, " %H:%M:%S", tmPtr ); break;//Esta funcion retorna la hora del sistema en forma ---12:06:08---
           case 5: strftime( cad, 80, " %I:%M:%S %p", tmPtr ); break;//Esta funcion retorna la hora con el correspondiente AM-PM.
           }     
        
    return cad;
}
                    
/* Esta funcion retorna en formato de fecha u hora, segun el numero que se 
recibe como parametro*/
char *formato (int n)
{
  
  int x,val;
  if(n){ //En caso de que sea distinto de 0 se analizara sobre la variante fecha
    char *vec[5];
     vec[0]="dd/MM/yyyy : 03/marzo/2005";
     vec[1]="dd/mm/yy : 03/03/05";
     vec[2]="dd/mm/yyyy : 03/03/2005";
     vec[3]="dd/MM/yy : 03/marzo/05";
     printf("\nElija una opcion para la fecha:\n");

     for (x=0; x<4;x++)
        printf ("\n  Opcion %d\t%s\n",x+1, vec[x]);
    }
    
  else{ //En caso de que sea 0, se analizara sobre la variante hora
      char *vec[1];
      vec[0]="hh/mm/ss : 23.10.05";
      vec[1]="HH/mm/ss : 11:05:05 pm";
      printf("\nElija una opcion para la hora:\n");
      for (x=0; x<2;x++)
        printf ("\n  Opcion %d\t%s\n",x+1, vec[x]);
    }
  printf ("-------------------\n Elija opcion ");
  scanf("%d",&val); 
  while (!rango(val, x+1))
 {      printf ("Fuera del rango esperado\n");
        scanf ("%d", &val);
 }  
  char *ret= calloc (sizeof(char), 2);

  
  
  *ret= val+=48; //como el ASCII  printf ("Valor::%s\n", ret);

  return ret;  
}
