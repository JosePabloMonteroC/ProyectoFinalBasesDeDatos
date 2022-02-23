'Creación de tablas del proyecto'

CREATE TABLE info_carreras( '1'
	idCarrera int NOT NULL AUTO_INCREMENT,
	nombreCarrera varchar (80) NOT NULL UNIQUE,
	PRIMARY KEY (idCarrera)
);'S'

INSERT INTO info_carreras (nombreCarrera) VALUES ('Ingeniería Química');

CREATE TABLE datos_alumnos ( '2'
	numCuenta  int NOT NULL AUTO_INCREMENT,
	nombre  varchar(50) NOT NULL,
	apPaterno varchar(50) NOT NULL,
	apMaterno varchar(50) DEFAULT NULL,
	numSemestre int NOT NULL,
	fechaNac date NOT NULL,
	correo varchar(65) NOT NULL UNIQUE,
	idCarrera int NOT NULL,
	pass VARCHAR(15) NOT NULL,
	tipoUsuario INT NOT NULL,
	PRIMARY KEY (`numCuenta`),
	FOREIGN KEY (idCarrera) REFERENCES info_carreras(idCarrera)
	ON DELETE CASCADE ON UPDATE CASCADE
);'S'

INSERT INTO datos_alumnos (nombre, apPaterno, apMaterno, numSemestre, fechaNac, correo, idCarrera, pass, tipoUsuario) VALUES ('Jaime','De la Barrera','Sanchez','3','2001/04/15','jsanchez02@hotmail.com','1', 'jaimeJuan12','0');



CREATE TABLE datos_libros ( 
	isbn bigint NOT NULL UNIQUE,
	nombreLibro varchar(150) NOT NULL,
	autor varchar(150) NOT NULL,
	editorial varchar(150) NOT NULL,
	PRIMARY KEY (isbn)
);'S'

INSERT INTO datos_libros (isbn,nombreLibro,autor, editorial, estado) VALUES ('9788483832356','Las Batallas En El Desierto', 'José Emilio Pacheco', 'Planeta', 'disponible');

CREATE TABLE cant_libros (
	isbn bigint NOT NULL UNIQUE,
	cantidadDisponible int NOT NULL,
	FOREIGN KEY (isbn) REFERENCES datos_libros(isbn)
	ON DELETE CASCADE ON UPDATE CASCADE
);'S'

INSERT INTO cant_libros (isbn, cantidadDisponible) VALUES ('9788483832356','4');

CREATE TABLE info_prestamos(
	idPrestamo int NOT NULL AUTO_INCREMENT,
	numCuenta int NOT NULL,
	isbn bigint NOT NULL,
	fechaInicio DATE NOT NULL,
	fechaFin DATE NOT NULL,
	estado varchar(15) NOT NULL,
	PRIMARY KEY (idPrestamo),
	FOREIGN KEY (isbn) REFERENCES datos_libros(isbn),
	FOREIGN KEY (numCuenta) REFERENCES datos_alumnos(numCuenta)
	ON DELETE CASCADE ON UPDATE CASCADE
);'S'

INSERT INTO info_prestamos(numCuenta, isbn, fechaInicio, fechaFin, estado) VALUES ('1','9788483832356','2021/11/01','2021/11/08','disponible');

CREATE TABLE login_admin (
    usuario int NOT NULL UNIQUE,
    pass varchar(15) NOT NULL,
	nombre varchar(25) NOT NULL,
    tipoUsuario int NOT NULL,
    PRIMARY KEY (usuario)
);'S'

INSERT INTO login_admin (usuario, pass,nombre, tipoUsuario) VALUES ('1221','adminDioro','Calubai',1);