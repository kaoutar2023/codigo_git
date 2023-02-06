#include "AccesoBD.hpp"

using namespace std;


AccesoBD::AccesoBD() {
    int error = sqlite3_open_v2(BD_Alquileres, &handle_BD, SQLITE_OPEN_READWRITE, nullptr);
    if (error == SQLITE_OK) {
        cout << "Base de datos abierta" << endl;
        return;
    } else {
        crearBD();
    }
}

AccesoBD::~AccesoBD() {
    sqlite3_close(handle_BD);
}


bool AccesoBD::crearBD() {
    int error = sqlite3_open_v2(BD_Alquileres, &handle_BD, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
    if (error != SQLITE_OK) {
        cout << "No se pudo crear la BD" << endl;
        return false;
    }
    const char* sentencia = "CREATE TABLE Propietarios (" \
        "id_propietario INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
        "nombre TEXT(15) NOT NULL," \
        "apellidos TEXT(50) NOT NULL," \
        "nif text(9) NOT NULL," \
        "direccion TEXT(50) NOT NULL," \
        "valoracion INTEGER);";
    crearTabla(sentencia);

    sentencia = "CREATE TABLE Inquilinos (" \
        "id_inquilino INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
        "nombre TEXT(15) NOT NULL," \
        "apellidos TEXT(50) NOT NULL," \
        "nif text(9) NOT NULL," \
        "direccion TEXT(50) NOT NULL," \
        "ingresos INTEGER," \
        "pago_preferido TEXT(20)," \
        "valoracion INTEGER);";
    crearTabla(sentencia);

    sentencia = "CREATE TABLE Viviendas (" \
        "id_vivienda INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
        "direccion TEXT(50) NOT NULL," \
        "precio INTEGER NOT NULL," \
        "metros INTEGER NOT NULL," \
        "num_habitaciones INTEGER NOT NULL," \
        "max_personas INTEGER NOT NULL," \
        "valoracion INTEGER," \
        "id_propietario INTEGER NOT NULL," \
        "CONSTRAINT Viviendas_FK FOREIGN KEY (id_propietario) REFERENCES Propietarios(id_propietario));";
    crearTabla(sentencia);

    sentencia = "CREATE TABLE Reservas (" \
        "id_reserva INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
        "id_inquilino INTEGER NOT NULL," \
        "id_vivienda INTEGER NOT NULL," \
        "fecha_inicio TEXT(10)," \
        "fecha_fin TEXT(10)," \
        "precio_total INTEGER," \
        "CONSTRAINT Inquilinos_FK FOREIGN KEY (id_inquilino) REFERENCES Inquilinos(id_inquilino)," \
        "CONSTRAINT Viviendas_FK FOREIGN KEY (id_vivienda) REFERENCES Viviendas(id_vivienda));";
    crearTabla(sentencia);

    sentencia = "CREATE TABLE Comentarios (" \
        "id_comentario INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
        "id_inquilino INTEGER NOT NULL," \
        "id_vivienda INTEGER NOT NULL," \
        "comentario TEXT(100) NOT NULL," \
        "valoracion INTEGER NOT NULL," \
        "CONSTRAINT Inquilinos_FK FOREIGN KEY (id_inquilino) REFERENCES Inquilinos(id_inquilino)," \
        "CONSTRAINT Viviendas_FK FOREIGN KEY (id_vivienda) REFERENCES Viviendas(id_vivienda));";
    crearTabla(sentencia);

    return true;
}


bool AccesoBD::crearTabla(const char *sentencia) {
    char* mensaje_error;
    int error = sqlite3_exec(handle_BD, sentencia, nullptr, 0, &mensaje_error);
    if (error == SQLITE_OK) {
        cout << "Error: " << mensaje_error << endl;
        free(mensaje_error);
        return false;
    }

    return true;
}
