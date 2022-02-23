'BUSCAR NOMBRE ALUMNO'
DELIMITER $$

CREATE FUNCTION f_buscarNombre(numeroCuenta INTEGER) RETURNS VARCHAR(25)
BEGIN
	DECLARE name VARCHAR(25);
SELECT nombre INTO name FROM datos_alumnos WHERE numeroCuenta = numCuenta;
RETURN name;

END $$
DELIMITER ;

'BUSCAR NOMBRE ADMIN'
DELIMITER $$

CREATE FUNCTION f_buscarNombreA(numUser INTEGER) RETURNS VARCHAR(25)
BEGIN
	DECLARE name VARCHAR(25);
SELECT nombre INTO name FROM login_admin WHERE numUser = usuario;
RETURN name;

END $$
DELIMITER ;

'PROCEDURES'
DELIMITER $$

CREATE PROCEDURE p_apartarLibro(cuenta INT, isbnL BIGINT)
proc:BEGIN
	DECLARE fechaI DATE;
	DECLARE fechaF DATE;
	DECLARE cant INT;
	SET fechaI = CURDATE();
	SET fechaF = DATE_ADD(fechaI,INTERVAL 8 DAY);
	SELECT cantidadDisponible INTO cant FROM cant_libros WHERE isbn = isbnL;
	IF cant = 0 THEN
		LEAVE proc;
	ELSE
		SET cant = cant -1;
		INSERT INTO info_prestamos(numCuenta,isbn,fechaInicio,fechaFin, estado) VALUES (cuenta,isbnL,fechaI,fechaF, 'apartado');
		UPDATE cant_libros SET cantidadDisponible = cant WHERE isbn = isbnL;
	END IF;
END$$
DELIMITER ;

'DEVOLVER'
DELIMITER $$

CREATE PROCEDURE p_devolverLibro(cuenta INT, isbnL BIGINT)
BEGIN
	DECLARE cant INT;
	SELECT cantidadDisponible INTO cant FROM cant_libros WHERE isbn = isbnL;
	SET cant = cant +1;
	DELETE FROM info_prestamos WHERE isbn = isbnL AND numCuenta = cuenta LIMIT 1;
	UPDATE cant_libros SET cantidadDisponible = cant WHERE isbn = isbnL;

END$$
DELIMITER ;

