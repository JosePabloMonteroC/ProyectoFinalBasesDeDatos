#include "def.h"

/* Funcion para limpiar el Buffer de entrada de datos */
extern void limpiarBuffer(void);

/* Funciones para desplegar los menús */
extern char mostrarMenuPrincipal(void); // Main Menu.
extern char mostrarMenuA(void); // Menu Administrador.
extern char mostrarMenuU(void); // Menu Alumno/

/* Iniciar sesión. */
extern int login(MYSQL mysql, char buffer[1024],char pass[15]);

/* Funciones para administradores */
void agregarUsuario(MYSQL mysql, char buffer[1024]);
void modificar(MYSQL mysql, char buffer[1024]);
char eliminarUsuario(MYSQL mysql, char buffer[1024]);
extern int buscarUsuario(MYSQL mysql, char buffer[1024]);

/* Funciones para modificar Administradores */
void datosAdmin(MYSQL mysql, char buffer[1024],int numUser);
void modAdmin(MYSQL mysql, char buffer[1024]);
void cambioAdmin(MYSQL mysql, char buffer[1024], int numCuenta, int cambio);
void datosAdmin(MYSQL mysql, char buffer[1024],int numUser);

/* Funciones para modificar Alumnos. */
void modUsuario(MYSQL mysql, char buffer[1024]);
void datosAlumno (MYSQL mysql, char buffer[1024], int numCuenta);
void cambioAlumno(MYSQL mysql, char buffer[1024], int numCuenta, int cambio);

/* Funciones para alumnos */
extern int mostrarCatalogo(MYSQL mysql, char buffer[1024], int usuario);
void misLibros(MYSQL mysql,char buffer[1024],int usuario);

/**
 * @fn limpiarBuffer
 * @brief Funcion para limpiar el buffer de entrada de datos.
 */
extern void limpiarBuffer(void)
{
  int limpiar;
  while((limpiar = getchar()) != '\n' && limpiar !=EOF) {}

  return;

} 

extern char mostrarMenuPrincipal(void)
{
    char opcion;

    do
    { 
        system("clear");
        printf("\t\t\tBienvenido a la biblioteca digital JUANBOOKS\n\nPor favor, elige una opcion de inicio de sesion:\n\t[U]Usuario\n\t[A]Administrador\n\n\t[S]Salir\n\nOpcion: ");
        scanf(" %c", &opcion);
        if(opcion == 'A' || opcion == 'U') return opcion;
        if(opcion == 'S' || opcion == 's') return opcion;
        else{
            switch(opcion)
            {
                case 'a':
                {
                    opcion = 'A';
                    break;
                }
                case 'u':
                {
                    opcion = 'U';
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
            return opcion;
        }
        
    } while (opcion != 'A' && opcion != 'a' && opcion != 'U' && opcion != 'u');

}

extern int login(MYSQL mysql, char buffer[1024],char pass[15])
{
    unsigned int i =0;
    int sal;

    MYSQL_RES *res; 
    MYSQL_ROW row;
    sal=0;
    // Buscamos que el usuario exista 
    // Obtiene el query
    mysql_query(&mysql, buffer);
    if( !(res = mysql_store_result(&mysql)) ){
    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
    abort();
    }
    // Despliega el resultado del query
    while( (row = mysql_fetch_row(res)) ){
    i = 0;
    for( i=0 ; i < mysql_num_fields(res); i++ ){
        if (strcmp(row[i],pass)==0)
        {
            printf("Bienvenido, tu login se ha logrado correctamente\n");
            sal=1;
        }
    }
    fputc('\n',stdout);
    }
    mysql_free_result(res);//IMPORTANTE
    return sal;
}

extern char mostrarMenuA(void)
{
   char opcion;

    do
    { 
        printf("\n\t\tMENU DE ADMINISTRADOR\n\nPor favor, elige una opcion:\n\t[A]Agregar usuario\n\t[M]Modificar datos\n\t[B]Buscar usuario\n\t[E]Eliminar usuario\n\n\t[S]Salir\n\nOpcion: ");
        scanf(" %c", &opcion);
        if(opcion == 'A' || opcion == 'M' || opcion == 'B' || opcion == 'E' || opcion == 'S') return opcion;
        else{
            switch(opcion)
            {
                case 'a':
                {
                    opcion = 'A';
                    break;
                }
                case 'm':
                {
                    opcion = 'M';
                    break;
                }
                case 'b':
                {
                    opcion = 'B';
                    break;
                }
                case 'e':
                {
                    opcion = 'E';
                    break;
                }
                case 's':
                {
                    opcion = 'S';
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
            return opcion;
        }
        
    } while (opcion != 'A' && opcion != 'M' && opcion != 'B' && opcion != 'E' && opcion != 'S');
    
}
extern char mostrarMenuU(void)
{
    char opcion;

    do
    { 
        printf("\n\t\tMENU PRINCIPAL\n\nPor favor, elige una opcion:\n\t[C]Catálogo\n\t[M]Mis Libros\n\n\t[S]Salir\n\nOpcion: ");
        scanf(" %c", &opcion);
        if(opcion == 'C' || opcion == 'M' || opcion == 'S') return opcion;
        else{
            switch(opcion)
            {
                case 'c':
                {
                    opcion = 'C';
                    break;
                }
                case 'm':
                {
                    opcion = 'M';
                    break;
                }
                case 's':
                {
                    opcion = 'S';
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
            return opcion;
        }
        
    } while (opcion != 'C' && opcion != 'M' && opcion != 'S');
    
}

void agregarUsuario(MYSQL mysql, char buffer[1024])
{
    char opcion, pass[15], nombre[35];
    int usuario, i =0;
    MYSQL_RES *res; 
    MYSQL_ROW row;

    //Variables Usuario
    char apPaterno[25],apMaterno[25], fecha[15], correo[65];
    int sem,idCarrera;
    
    do
    {
        system("clear");
        printf("\tDAR DE ALTA UN USUARIO\n\n");
        printf("Que tipo de usuario darás de alta?: \n\t[A]Administrador\n\t[U]Usuario\n\nOpcion: ");
        scanf(" %c", &opcion);
        if(opcion=='A' || opcion=='a')
        {
            printf("\nIngresa el numero de usuario: ");
            scanf(" %d", &usuario);
            printf("Ingresa la contraseña (Máximo 14 dígitos): ");
            scanf(" %[^\n]", pass);
            printf("Ingresa el nombre: ");
            scanf(" %[^\n]", nombre);
            sprintf(buffer,"INSERT INTO login_admin(usuario, pass, nombre, tipoUsuario) VALUES('%d','%s','%s', '1')",usuario, pass, nombre);
            if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
        }
        else if(opcion=='U' || opcion=='u')
        {
            printf("\nIngresa el nombre: ");
            scanf(" %[^\n]", nombre);
            printf("Ingresa el apellido paterno: ");
            scanf(" %[^\n]", apPaterno);
            printf("Ingresa el apellido materno: ");
            scanf(" %[^\n]", apMaterno);
            printf("Ingresa el semestre que se esta cursando: ");
            scanf(" %d", &sem);
            printf("Ingresa tu fecha de nacimiento con el siguiente formato (AAAA/MM/DD): ");
            scanf(" %[^\n]", fecha);
            printf("Ingresa el correo electronico: ");
            scanf(" %[^\n]", correo);
            // Añadimos un nuevo usuario. 
            sprintf(buffer,"SELECT * FROM info_carreras ORDER BY idCarrera ASC");
            if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
            // Obtiene el query
            if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
            }
            // Despliega el resultado del query
            printf("\nCarreras:\n");
            printf("\n[id] [     Carrera     ]\n");
            while( (row = mysql_fetch_row(res)) ){
            i = 0;
            for( i=0 ; i < mysql_num_fields(res); i++ ){
            printf(" %s   ",row[i]);
            }
            fputc('\n',stdout);
            }
            mysql_free_result(res);//IMPORTANTE
            printf("\nIngresa el ID de la carrera: ");
            scanf("%d", &idCarrera);
            printf("Ingresa la contraseña (Máximo 14 dígitos): ");
            scanf(" %[^\n]", pass);
            sprintf(buffer,"INSERT INTO datos_alumnos (nombre, apPaterno, apMaterno, numSemestre, fechaNac, correo, idCarrera, pass, tipoUsuario) VALUES ('%s','%s','%s','%d','%s','%s','%d', '%s','0');",nombre, apPaterno, apMaterno,sem,fecha,correo,idCarrera,pass);
            if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
            //NumCuenta nuevo
            sprintf(buffer,"SELECT numCuenta FROM datos_alumnos WHERE nombre = '%s' AND apPaterno = '%s' AND apMaterno = '%s'", nombre, apPaterno, apMaterno);
            if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
            if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
            }
            // Despliega el resultado del query
            printf("\nEl número de Cuenta de %s es: ", nombre);
            while( (row = mysql_fetch_row(res)) ){
            i = 0;
            for( i=0 ; i < mysql_num_fields(res); i++ ){
            printf("%s   ",row[i]);
            }
            fputc('\n',stdout);
            }
            mysql_free_result(res);//IMPORTANTE

        }
        else
        {
            printf("OPCION INVALIDA...PRESIONA ENTER E INTENTA DE NUEVO");
            limpiarBuffer();
            getchar();
        }
    }while(opcion != 'A' && opcion != 'a' && opcion != 'U' && opcion != 'u');

}

void modificar(MYSQL mysql, char buffer[1024])
{
    char opcion, column[20], nuevoCampo[30];
    int i =0, numUser;
    MYSQL_RES *res; 
    MYSQL_ROW row;
    
    do
    {
        system("clear");
        printf("\tMODIFICAR UN USUARIO\n\n");
        printf("Que tipo de usuario quieres modificar?: \n\t[A]Administrador\n\t[U]Usuario\n\nOpcion: ");
        scanf(" %c", &opcion);
        if(opcion=='A' || opcion=='a')
        {
          modAdmin(mysql,buffer);  
        }
        else if(opcion=='U' || opcion=='u')
        {
            modUsuario(mysql, buffer);
        }
        else
        {
            printf("OPCION INVALIDA...PRESIONA ENTER E INTENTA DE NUEVO");
            limpiarBuffer();
            getchar();
        }
    }while(opcion != 'A' && opcion != 'a' && opcion != 'U' && opcion != 'u');
    return;
}

void modAdmin(MYSQL mysql, char buffer[1024])
{
    int numUser=0,opc=0;
    int i=1;
    
    do
    {


    system("clear");
    printf("Ingrese el numero de usuario que quiera modificar: ");
    scanf(" %d", &numUser);

    while (opc>=0 || opc<=3)
    {
    system("clear");
    printf("Los datos del usuario son: ");
    datosAdmin(mysql,buffer,numUser);

    printf("\nPara salir presione [3]\n");  
    printf("\nIngrese el dato que quiera modificar: ");
    scanf(" %d",&opc);
    if(opc==3) break;

    cambioAdmin(mysql, buffer, numUser, opc);


    printf("Los nuevos datos del usuario son: ");
    datosAdmin(mysql,buffer,numUser);
    }
    printf("¿Deseas cambiar datos de otro administrador? [1]Si [0]No   ");
    scanf("%d", &i);

    }while (i != 0);

    return;
}

void cambioAdmin(MYSQL mysql, char buffer[1024], int numUser, int cambio)
{
    MYSQL_RES *res; 
    MYSQL_ROW row;
    char nuevoCampo[30];
    int sem=0,i;

    switch (cambio)
    {
        case 1:
            printf("Ingrese la nueva contraseña del administrador: ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE login_admin SET pass = '%s' WHERE usuario = '%d'", nuevoCampo,numUser);
  
            break;
        case 2:
            printf("Ingrese el nombre del admin: ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE login_admin SET nombre = '%s' WHERE usuario = '%d'", nuevoCampo,numUser);

            break;
    }

    if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }

    return;
}

void datosAdmin(MYSQL mysql, char buffer[1024],int numUser)
{
    MYSQL_RES *res; 
    MYSQL_ROW row;
    int i=0;

    sprintf(buffer,"SELECT * FROM login_admin WHERE usuario=%d",numUser);
    mysql_query(&mysql,buffer);

    if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
            }
            // Despliega el resultado del query
            while( (row = mysql_fetch_row(res)) ){
            printf("\n\tDatos del administrador:\n");
            i = 0;
            
            for( i=0 ; i < mysql_num_fields(res); i++ ){
                switch (i)
                {
                case 0:
                    printf("Usuario:             %s\n",row[i]);
                    break;
                case 1:
                    printf("[1]Contraseña:       %s\n",row[i]);
                    break;
                case 2:
                    printf("[2]Nombre:           %s\n",row[i]);
                    break;
                default:
                    break;
                }  
            }
            }
return;
}

void modUsuario(MYSQL mysql, char buffer[1024])
{
    int numCuenta=0,cambio=0, j=1;
    do
    {
    system("clear");
    printf("Ingrese el numero de cuenta que desea modificar: ");
    scanf("%d",&numCuenta);
    datosAlumno(mysql, buffer, numCuenta);

    while (cambio>=0 || cambio<=8)
    {

        printf("\nPara salir presione [9]\n");    
        printf("Ingrese el dato que desea modificar: ");    
    
        scanf("%d",&cambio);
        printf("\n");
        if(cambio==9) break;

        cambioAlumno(mysql, buffer, numCuenta,cambio);
        printf("El cambio de datos fue exitoso, los nuevos datos son:\n");
        datosAlumno(mysql, buffer, numCuenta);
    }

    printf("¿Deseas cambiar datos de otro alumno? [1]Si [0]No   ");
    scanf("%d", &j);

    } while (j!=0);
    
    
   
    return;
}

void cambioAlumno(MYSQL mysql, char buffer[1024], int numCuenta, int cambio)
{
    MYSQL_RES *res; 
    MYSQL_ROW row;
    char nuevoCampo[30];
    int sem=0,i;

    switch (cambio)
    {
        case 1:
            printf("Ingrese el nombre del alumno: ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE datos_alumnos SET nombre = '%s' WHERE numCuenta = '%d'", nuevoCampo,numCuenta);
  
            break;
        case 2:
            printf("Ingrese el apellido paterno del alumno: ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE datos_alumnos SET apPaterno = '%s' WHERE numCuenta = '%d'", nuevoCampo,numCuenta);

            break;
        case 3:
            printf("Ingrese el apellido materno del alumno: ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE datos_alumnos SET apMaterno = '%s' WHERE numCuenta = '%d'", nuevoCampo,numCuenta);

            break;
        case 4:

            printf("Ingrese el semestre del alumno: ");
            scanf(" %d", &sem);
            sprintf(buffer,"UPDATE datos_alumnos SET numSemestre = '%d' WHERE numCuenta = '%d'", sem,numCuenta);
            break;
        case 5:
            printf("Ingrese la fecha de nacimiento del alumno (AAAA/MM/DD): ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE datos_alumnos SET fechaNac = '%s' WHERE numCuenta = '%d'", nuevoCampo,numCuenta);
            break;
        case 6:
            printf("Ingrese el correo del alumno: ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE datos_alumnos SET correo = '%s' WHERE numCuenta = '%d'", nuevoCampo,numCuenta);
            break;
        case 7:
            printf("Ingresa el ID de carrera que estudia el alumno: ");
            scanf(" %d", &sem);

            sprintf(buffer,"SELECT nombreCarrera FROM info_carreras WHERE idCarrera = '%d'",sem);
            if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
            // Obtiene el query
            if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
            }
            // Despliega el resultado del query
            while( (row = mysql_fetch_row(res)) ){
            printf("\nEl alumno ahora estudia: ");
            i = 0;
            for( i=0 ; i < mysql_num_fields(res); i++ ){
            printf("%s",row[i]);
            }
            fputc('\n',stdout);
            }
            mysql_free_result(res);//IMPORTANTE

            sprintf(buffer,"UPDATE datos_alumnos SET idCarrera = '%d' WHERE numCuenta = '%d'", sem,numCuenta);
            break;
        case 8:
            printf("Ingrese la nueva contraseña del alumno: ");
            scanf(" %[^\n]", nuevoCampo);
            sprintf(buffer,"UPDATE datos_alumnos SET pass = '%s' WHERE numCuenta = '%d'", nuevoCampo,numCuenta);
            break;
        default:
            printf("ERROR FAVOR DE INTENTARLO DE NUEVO");
            break;
        }

      if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
return;
}


void datosAlumno (MYSQL mysql, char buffer[1024], int numCuenta)
{
    MYSQL_RES *res; 
    MYSQL_ROW row;
    int i=0;

    sprintf(buffer,"SELECT * FROM datos_alumnos WHERE numCuenta=%d",numCuenta);
    mysql_query(&mysql,buffer);

    if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
            }
            // Despliega el resultado del query
            while( (row = mysql_fetch_row(res)) ){
            printf("\n\tDatos del alumno\n");
            i = 0;
            
            for( i=0 ; i < mysql_num_fields(res); i++ ){
                switch (i)
                {
                case 0:
                    printf("Num cuenta:             %s\n",row[i]);
                    break;
                case 1:
                    printf("[1]Nombre:              %s\n",row[i]);
                    break;
                case 2:
                    printf("[2]Apellido paterno:    %s\n",row[i]);
                    break;
                case 3:
                    printf("[3]Apellido materno:    %s\n",row[i]);
                    break;
                case 4:
                    printf("[4]Semestre:            %s\n",row[i]);
                    break;
                case 5:
                    printf("[5]Fecha de nacimiento: %s\n",row[i]);
                    break;
                case 6:
                    printf("[6]Correo:              %s\n",row[i]);
                    break;
                case 7:
                    printf("[7]Carrera:             %s\n",row[i]);
                    break;
                case 8:
                    printf("[8]Contraseña:          %s\n",row[i]);
                    break;
                default:
                    break;
                }  
            }
}
return;
}

extern int buscarUsuario(MYSQL mysql, char buffer[1024])
{
    char opcion, opcionS;
    char nombreInput[50];
    MYSQL_RES *res; 
    MYSQL_ROW row;
    int i=0,input;

    printf("\t\tBUSQUEDA\n\nSelecciona el parámetro que quieras usar para la búsqueda:\n\t[N]Nombre\n\t[C]Cuenta\n\t[I]ID Carrera\n\t[L]Nombre del libro\n\n\t[S]Salir\n\nOpcion: ");
    scanf(" %c", &opcion);
    system("clear");
    if(opcion == 'n')opcion = 'N';
    else if(opcion == 'c')opcion = 'C';
    else if(opcion == 'i')opcion = 'I';
    else if(opcion == 'l')opcion = 'L';
    else if(opcion == 's'|| opcion == 'S')return 1;

    switch (opcion)
    {
    case 'N':
        printf("\t\tBUSCAR POR NOMBRE\n\nIngresa el nombre del alumno que quieras consultar: ");
        scanf(" %[^\n]", nombreInput);
        sprintf(buffer,"SELECT numCuenta, nombre, apPaterno, fechaInicio, fechaFin, nombreLibro FROM datos_alumnos NATURAL JOIN datos_libros NATURAL JOIN info_prestamos WHERE nombre = '%s'",nombreInput);
        break;

    case 'C':
        printf("\t\tBUSCAR POR NUMERO DE CUENTA\n\nIngresa el numero de cuenta que quieras consultar: ");
        scanf(" %d", &input);
        sprintf(buffer,"SELECT numCuenta, nombre, apPaterno,fechaInicio, fechaFin, nombreLibro FROM datos_alumnos NATURAL JOIN datos_libros NATURAL JOIN info_prestamos WHERE numCuenta = %d",input);
        break;

    case 'I':
        printf("\t\tBUSCAR POR ID de Carrera\n\nIngresa el Id de Carrera que quieras consultar: ");
        scanf(" %d", &input);
        sprintf(buffer,"SELECT numCuenta, nombre, apPaterno, fechaInicio, fechaFin, nombreLibro FROM datos_alumnos NATURAL JOIN datos_libros NATURAL JOIN info_prestamos WHERE idCarrera = %d",input);
        break;

    case 'L':
        printf("\t\tBUSCAR POR NOMBRE DE LIBRO\n\nIngresa el Nombre del Libro que quieras consultar: ");
        scanf(" %[^\n]", nombreInput);
        sprintf(buffer,"SELECT numCuenta, nombre, apPaterno, fechaInicio, fechaFin, nombreLibro FROM datos_alumnos NATURAL JOIN datos_libros NATURAL JOIN info_prestamos WHERE nombreLibro = '%s'",nombreInput);
        break;
    
    default:
        break;
    }

       if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
        exit(1);
        }
        // Obtiene el query
        if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
        }
        // Despliega el resultado del query
        printf("\n[numCuenta]  [Nombre]\t [apPaterno]\t[fecha inicio]\t\t[fecha fin]\t      [nombreLibro]\n");
        while( (row = mysql_fetch_row(res)) ){
        i = 0;
        for( i=0 ; i < mysql_num_fields(res); i++ ){
        printf("   %s      ",row[i]);
        }
        fputc('\n',stdout);
        }
        mysql_free_result(res);//IMPORTANTE
        printf("\n\nPresiona la tecla ENTER para continuar");
        limpiarBuffer();
        getchar();
        printf("\nQuieres buscar algo más? [S]Si [N]No: ");
        scanf(" %c", &opcionS);
        if(opcionS == 's' || opcionS == 'S')return 0;
        else if(opcionS == 'n' || opcionS == 'N')return 1;

return 1;
}

char eliminarUsuario(MYSQL mysql, char buffer[1024])
{
    int i =0, eliminado;
    MYSQL_RES *res; 
    MYSQL_ROW row;
    char opcion, salir;

    system("clear");
    printf("\t\t\tELIMINAR USUARIO\nQue tipo de usuario quieres eliminar?\n\t[A]Administrador\n\t[U]Usuario\n\n\t[S]Salir\n\nOpcion: ");
    scanf(" %c", &opcion);
    if(opcion == 'a')opcion = 'A';
    else if (opcion == 'u')opcion = 'U';
    else if(opcion == 's')opcion = 'S';

    switch(opcion)
    {
        case 'A':
        {
            do
            {
                sprintf(buffer,"SELECT * FROM login_admin");
                if( mysql_query(&mysql,buffer) ){
                fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
                exit(1);
                }
                // Obtiene el query
                if( !(res = mysql_store_result(&mysql)) ){
                fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                exit(1);
                }
                printf("\n[Usuario]   [Pass]     [Nombre]    [TipoUsuario]\n");
                // Despliega el resultado del query
                while( (row = mysql_fetch_row(res)) ){
                i = 0;
                for( i=0 ; i < mysql_num_fields(res); i++ ){
                printf(" %s     ",row[i]);
                }
                fputc('\n',stdout);
                }
                mysql_free_result(res);//IMPORTANTE
                printf("\nEscribe el numero de usuario que deseas eliminar o Presiona [0] para salir: ");
                scanf(" %d", &eliminado);
                if(eliminado == 0)
                {
                    salir = 'S';
                    return salir;
                    break;
                }
                sprintf(buffer,"DELETE FROM login_admin WHERE usuario = '%d'", eliminado);
                if( mysql_query(&mysql,buffer) ){
                fprintf(stderr,"Error processing query Error: %s\n",mysql_error(&mysql));
                abort();
                }
                printf("\nUsuario eliminado exitósamente, Quieres eliminar otro usuario? [S]Si [N]No\nOpcion: ");
                scanf(" %c", &salir); 
                if(salir == 's' || salir == 'S')system("clear");
            } while (salir != 'n' && salir != 'N');
             
            break;
        }
        case 'U':
        {
            do
            {
                sprintf(buffer,"SELECT numCuenta,idCarrera,numSemestre, nombre, apPaterno, apMaterno FROM datos_alumnos");
                if( mysql_query(&mysql,buffer) ){
                fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
                exit(1);
                }
                // Obtiene el query
                if( !(res = mysql_store_result(&mysql)) ){
                fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                exit(1);
                }
                printf("\n[numCuenta] [Semestre] [idCarrera] [Nombre]     [ApPaterno]    [ApMaterno]\n");
                // Despliega el resultado del query
                while( (row = mysql_fetch_row(res)) ){
                i = 0;
                for( i=0 ; i < mysql_num_fields(res); i++ ){
                printf("   %s      ",row[i]);
                }
                fputc('\n',stdout);
                }
                mysql_free_result(res);//IMPORTANTE
                printf("\nEscribe el numero de cuenta del usuario que deseas eliminar o Presiona [0]para salir: ");
                scanf(" %d", &eliminado);
                if(eliminado == 0)
                {
                    salir = 'S';
                    return salir;
                    break;
                }
                sprintf(buffer,"DELETE FROM datos_alumnos WHERE numCuenta = '%d'", eliminado);
                if( mysql_query(&mysql,buffer) ){
                fprintf(stderr,"Error processing query Error: %s\n",mysql_error(&mysql));
                abort();
                }
                printf("\nUsuario eliminado exitosamente, Quieres eliminar otro usuario? [S]Si [N]No\nOpcion: ");
                scanf(" %c", &salir);
                if(salir == 's' || salir == 'S')system("clear");
            } while (salir != 'n' && salir != 'N');
                  
            break;
         }
        case 'S':
        {
            salir = 'S';
            return salir;
            break;
        }
        default:
        {
            printf("OPCION INVALIDA... PRESIONA ENTER Y VUELVE A INTENTARLO.");
            limpiarBuffer();
            getchar();
            break;
        }
    }
    return salir;
}


extern int mostrarCatalogo(MYSQL mysql, char buffer[1024], int usuario)
{
    int i =0, cantL;
    MYSQL_RES *res; 
    MYSQL_ROW row;
    long int isbnL;

    
   
    // Mostramos el catalogo de libros. 
    sprintf(buffer,"SELECT isbn, cantidadDisponible, nombreLibro, autor, editorial FROM datos_libros NATURAL JOIN cant_libros ORDER BY (nombreLibro)ASC");
    if( mysql_query(&mysql,buffer) ){
    fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
    exit(1);
    }
    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
    exit(1);
    }
    // Despliega el resultado del query
    printf("\t\t\t\tLIBROS\n\n");
    while( (row = mysql_fetch_row(res)) ){
    i = 0;
    for( i=0 ; i < mysql_num_fields(res); i++ ){
        switch (i)
                {
                case 0:
                    printf("\nISBN: %s\t",row[i]);
                    break;
                case 1:
                    printf("Disponible(s): %s\n",row[i]);
                    break;
                case 2:
                    printf("Libro:             %s\n",row[i]);
                    break;
                case 3:
                    printf("Autor:             %s\n",row[i]);
                    break;
                case 4:
                    printf("Editorial:         %s\n",row[i]);
                    break; 
                default:
                    printf("\n");
                    break;
                }
    }
    fputc('\n',stdout);
    }
    mysql_free_result(res);//IMPORTANTE

   
    printf("\nEscribe el [isbn] del libro que desees pedir o presiona [0] para salir: ");
    scanf(" %ld", &isbnL);
    if(isbnL == 0)return 1;
    sprintf(buffer, "SELECT cantidadDisponible FROM cant_libros WHERE isbn = %ld", isbnL);
    if( mysql_query(&mysql,buffer) ){
    fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
    exit(1);
    }
    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
    exit(1);
    }

    while( (row = mysql_fetch_row(res)) ){
    i = 0;
    for( i=0 ; i < mysql_num_fields(res); i++ ){
        
    cantL = atoi(row[i]);
    }
    fputc('\n',stdout);
    }
    mysql_free_result(res);//IMPORTANTE

    if(cantL == 0)
    {
        system("clear");
        printf("El libro que elegiste no tiene ejemplares disponibles, intenta con otro. Presiona ENTER para continuar...");
        limpiarBuffer();
        getchar();
        return 0;
    }
    else
    {
        sprintf(buffer,"CALL p_apartarLibro(%d, %ld)", usuario, isbnL);
        if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
        exit(1);
        }
        system("clear");
        printf("El libro se ha apartado correctamente! Recuerda que debes devolverlo en 8 días como máximo\n\nPresiona ENTER para continuar");
        limpiarBuffer();
        getchar();
        return 1;
    }
   

    
}

void misLibros(MYSQL mysql,char buffer[1024],int usuario)
{
    int i =0;
    MYSQL_RES *res; 
    MYSQL_ROW row;
    long int isbnL;
    char opcion;

    sprintf(buffer,"SELECT idPrestamo,isbn,fechaInicio,fechaFin,estado,nombreLibro FROM datos_libros NATURAL JOIN info_prestamos WHERE numCuenta = %d", usuario);
    if( mysql_query(&mysql,buffer) ){
    fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
    exit(1);
    }
    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
    exit(1);
    }
    printf("\n[idPrestamo]\t[isbn]\t\t  [fechaInicio]\t      [fechaFin]\t [estado]\t\t[nombreLibro]\t     \n");
    // Despliega el resultado del query
    while( (row = mysql_fetch_row(res)) ){
    i = 0;
    for( i=0 ; i < mysql_num_fields(res); i++ ){
    printf("   %s      ",row[i]);
    }
    fputc('\n',stdout);
    }
    mysql_free_result(res);//IMPORTANTE
    do
    {
        printf("\n\nPara devolver un libro, presiona [D]. Presiona [S] para salir: ");
        scanf(" %c", &opcion);
        if(opcion == 'd')opcion = 'D';
        else if(opcion == 's')opcion = 'S';

        switch (opcion)
        {
        case 'D':
            printf("\nIngresa el [isbn] del libro que quieres devolver: ");
            scanf(" %ld", &isbnL);
            sprintf(buffer, "CALL p_devolverLibro(%d, %ld)", usuario,isbnL);
            if( mysql_query(&mysql,buffer) ){
            fprintf(stderr,"Error processing query \"%s\" Error:%s\n",buffer,mysql_error(&mysql));
            exit(1);
            }
            printf("\n\nEl libro se devolvió correctamente, presiona la tecla ENTER para continuar");
            limpiarBuffer();
            getchar();
            system("clear");
            opcion = 'S';
            break;
        
        default:
            printf("\n\nOPCION INVALIDA, presiona ENTER y vuelve a intentarlo");
            
            break;
        }
            
    }while(opcion != 's' && opcion != 'S');

    return;
}
