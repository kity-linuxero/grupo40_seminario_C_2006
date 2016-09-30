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


#include "programa.h"

int main(int argc, char *argv[])
{ 
 int res;
 switch (argc)
      { case 1: res= modo_1 (); break;
        case 2: res= modo_2 (argv[1]); break;
        case 3: res= modo_3 (argv[1], argv[2], argv[3], argc); break;
        case 4: res= modo_3 (argv[1], argv[2], argv[3], argc); break; //se recibe el argumento [\P] está implícito.
        case 5: res= modo_5 (argv[1], argv[2], argv[3], argv[4]); break;
        
        default :
        {    printf ("[error] Demasiados parametros.\n"); res=0; break;}
      }
  imp ("\n\n  FIN DEL PROGRAMA!!!");
  stop;
  return 0;
         
}
