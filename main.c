/**
 * @file main.c
 * @author José Pablo Montero y Emilio Roman
 * @brief Sistema de administración de una biblioteca
 * @version 1.0
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* ARCHIVO EN EL QUE SE ALMACENAN LAS BIBLIOTECAS */
#include "def.h"

/* PROTOTIPOS DE FUNCION */
void limpiarBuffer(void);
char mostrarMenuPrincipal(void);
int login(MYSQL mysql, char buffer[1024],char pass[15]);
char mostrarMenuA(void);
char mostrarMenuU(void);
int mostrarCatalogo(MYSQL mysql, char buffer[1024], int usuario);
void misLibros(MYSQL mysql,char buffer[1024],int usuario);

void agregarUsuario(MYSQL mysql, char buffer[1024]);
void modificar(MYSQL mysql, char buffer[1024]);
char eliminarUsuario(MYSQL mysql, char buffer[1024]);
int buscarUsuario(MYSQL mysql, char buffer[1024]);

/* MAIN FUNCTION */
int main (int argc, char **argv)
{
    unsigned int i = 0,j=0;
    int usuario, sesion,ext=0, cat,busc;
    char buffer[1024];
    char opcionMenu,opcionMenuA,opcionMenuU,pass[15],salirE;
    unsigned int num_fields;

    char *server = "localhost";
    char *user = "ic20jmc";
    char *passwd = "220929";
    char *db = "ic20jmc";

    // Variables para lograr la comunicación con la BD y que vienen incluidas en la librería mysql.h
    MYSQL mysql;  /*Estructura que representa el manejador de la conexión a la base de datos.*/
    MYSQL_RES *res; /*Estructura que representa el resultado de un query que regresa renglones (resul set)*/
    MYSQL_ROW row; /*Este tipo de datos es el utilizado para obtener un solo renglón como resultado de un query. 
	                 Los renglones pueden ser obtenidos llamando a la función mysql_fetch_row().*/
    MYSQL_FIELD *fields; /*Esta estructura contiene información acerca del campo obtenido, tal y como su nombre,
					tipo y tamaño. Los campos de una tabla se pueden obtener mandando llamar a la función
					mysql_fetch_field(). Los valores de los campos no son parte de esta estructura sino que se
					encuentran en la estructura MYSQL_ROW.*/



    mysql_init(&mysql); // Prepara la conexión al servidor de bases de datos

    // Se conecta al servidor de base de datos y verifica que no haya error
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
      fprintf(stderr, "Error al conectarse a la BD: Error: %s\n",mysql_error(&mysql));
      return(0);
    }

    // Se conecta a la base de datos deseada
    if( mysql_select_db(&mysql,db) ){
        fprintf(stderr,"No existe la base de datos seleccionada: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
    
    opcionMenu = mostrarMenuPrincipal();// Verificamos si es un Alumno o un Administrador.
    if(opcionMenu == 's')opcionMenu = 'S';
    switch(opcionMenu)
    {
      case 'A': // Administrador
      {

        while (ext==0)
        {
        system("clear");
        if(j!=0){
          printf("\t\tADMINISTRADOR\n\nLos datos no coinciden, favor de intentarlo de nuevo\n\nPor favor Ingresa tu numero de USUARIO: ");
        }else if(j==0){
          printf("\t\tADMINISTRADOR\n\nPor favor Ingresa tu numero de USUARIO: ");
        }
        scanf(" %i", &usuario);
        printf("Contraseña: ");
        scanf(" %[^\n]", pass);
        sprintf(buffer, "SELECT pass FROM login_admin WHERE usuario = %d AND pass = '%s'", usuario, pass);
        system("clear");
        ext=login(mysql, buffer,pass); // Verificamos que el usuario y la contraseña sean correctas.
        j++;
        }
        do
        {
          system("clear");
          // BIENVENIDA
          sprintf(buffer,"SELECT f_buscarNombreA(%d)", usuario); // Recuperar el nombre del usuario actual.
          if( mysql_query(&mysql,buffer) ){
          fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
          exit(1);
          }
          // Obtiene el query
          if( !(res = mysql_store_result(&mysql)) ){
          fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
          exit(1);
          }
          printf("\nPerfil: "); 
          // Despliega el resultado del query
          while( (row = mysql_fetch_row(res)) ){
          i = 0;
          for( i=0 ; i < mysql_num_fields(res); i++ ){
          printf("%s ",row[i]);
          }
          fputc('\n',stdout);
          }
          mysql_free_result(res); // IMPORTANTE
          opcionMenuA = mostrarMenuA();
          switch (opcionMenuA)
          {
            case 'A': // Agregar un usuario.
            {
              system("clear");
              agregarUsuario(mysql, buffer);
              printf("\n\nUsuario agregado exitósamente! Presiona ENTER para continuar\n");
              limpiarBuffer();
              getchar();
              break;
            }
            case 'M': // Modificar a un usuario.
            {
              system("clear");
              modificar(mysql,buffer);
              break;
            }
            case 'B': // Buscar.
            {
              do{
                system("clear");
                busc = buscarUsuario(mysql,buffer);                
              }while(busc!=1);
              
              break;
            }
            case 'E': // Eliminar a un usuario.
            {
              system("clear");
              do
              {
                salirE = eliminarUsuario(mysql,buffer);
              } while (salirE != 's' && salirE != 'S');
              
              
    
              break;
            }
            case 'S': // Salir.
            {
              system("clear");
              printf("Hasta pronto! (._.)/\n\n");
              break;
            }
            default:
            {
              printf("OPCION INVALIDA...PRESIONA ENTER E INTENTA DE NUEVO");
              limpiarBuffer();
              getchar();
              break;
            }
          }
        }while(opcionMenuA != 's' && opcionMenuA != 'S');
        break;
      }
        case 'U': // Alumno.
        {
          while (ext==0)
          {
          system("clear");
          if(j!=0){
            printf("\t\tALUMNO\n\nLos datos no coinciden, favor de intentarlo de nuevo\n\nPor favor Ingresa tu NUMERO DE CUENTA: ");
          }else if(j==0){
          printf("\t\tALUMNO\n\nPor favor Ingresa tu NUMERO DE CUENTA: ");
          }
          scanf(" %i", &usuario);
          printf("Contraseña: ");
          scanf(" %[^\n]", pass);
          system("clear");
          sprintf(buffer, "SELECT * FROM datos_alumnos WHERE numCuenta = %d AND pass = '%s'", usuario, pass); // Verificamos que existe y que es correcto.
          ext=login(mysql, buffer,pass); 
          j++;
          }
          
          do
          {
            system("clear");
            //BIENVENIDA
            sprintf(buffer,"SELECT f_buscarNombre('%d')", usuario);
            if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
            // Obtiene el query
            if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
            }
            printf("\nPerfil: ");
            // Despliega el resultado del query
            while( (row = mysql_fetch_row(res)) ){
            i = 0;
            for( i=0 ; i < mysql_num_fields(res); i++ ){
            printf("%s ",row[i]);
            }
            fputc('\n',stdout);
            }
            mysql_free_result(res);//IMPORTANTE 
            opcionMenuU = mostrarMenuU(); 

            switch (opcionMenuU)
            {
              case 'C': // Muestra el catálogo de los libros y su disponibilidad.
              {
                system("clear");
                do{
                  cat=mostrarCatalogo(mysql, buffer, usuario);
                }while (cat!=1);
                
                break;
              }
              case 'M': // Muestra los libros que el usuario tiene en posesion.
              {
                system("clear");
                misLibros(mysql,buffer,usuario);
               
              }
              case 'S': // Salir.
              {
                system("clear");
                printf("Hasta pronto! (._.)/\n\n");
                break;
              }
            
              default:
              {
                printf("OPCION INVALIDA...PRESIONA ENTER E INTENTA DE NUEVO");
                limpiarBuffer();
                getchar();
                break;
              }
            } 
          } while (opcionMenuU != 's' && opcionMenuU != 'S');
          
                 
          break;
        }
        case 'S':
        {
          system("clear");
          printf("Hasta pronto! (._.)/\n\n");
          break;
        }
        default:
        {
          printf("OPCION INVALIDA...PRESIONA ENTER E INTENTA DE NUEVO");
          limpiarBuffer();
          getchar();
          break;
        }
    }
    // cierra la conexion con al servidor
    mysql_close(&mysql);

    return 0;
}
