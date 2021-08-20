#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;

struct empleado
{
    int id;
    char nombre[60];
    int edad;
    int dni;
    int celular;
    char email[40];
} empleado;

struct horasTrabajadas
{
    int id;
    int idEmpleado;
    bool cancelado;
    float horas;
    float horasExtras;
    char fecha[12];
    bool falta;
    char justificacion[200];
    bool permiso;
    char detallePermiso[200];
} horas;

struct pagos
{
    int id;
    int idEmpleado;
    char fecha[12];
    float monto;
    float horas;
    float horasExtras;
    float precioHora;
    int idBonificacion;
    int idGratificacion;
} pago;
struct bonificaciones
{
    int id;
    int idEmpleado;
    char fecha[12];
    float monto;
    float porcentaje;
    char detalle[200];
} bonificacion;
struct gratificaciones
{
    int id;
    int idEmpleado;
    char fecha[12];
    float monto;
    char detalle[200];
} gratificacion;

struct seguros
{
    //  int id;
    int idEmpleado;
    char tipo[20];
} seguro;

FILE *fichero;
FILE *fichero2;
FILE *fichero3;
FILE *fichero4;

int lengthEmpleado = sizeof(struct empleado);
int lengthHoras = sizeof(struct horasTrabajadas);
int lengthPago = sizeof(struct pagos);
int lengthSeguro = sizeof(struct seguros);
int lengthBonificacion = sizeof(struct bonificaciones);
int lengthGratificacion = sizeof(struct gratificaciones);

void validarCaso(int);
int ultimoElemento();
void ultimoElementoHoras();
void ultimoElementoPago();
void ultimoElementoSeguro();
void ultimoElementoBonificacion();
void ultimoElementoGratificacion();
void registrarEmpleado();
void registrarHoras(int);
void registrarPago(int);
void registrarSeguro(int);
int registrarBonificacion(int, char[], float, float, char[]);
int registrarGratificacion(int, char[], float, char[]);
int consultarEmpleado(int);
void verHorasTrabajo(int, bool);
void verBonificaciones(int);
void verGratificaciones(int);
void verTodosEmpleados();
void verPagos(int);
void verSeguros(int);
void actualizarHoras(int);
void modificarHoras(int);

void menuEmpleado(int);
int main()
{
    int opcion;
    system("color 0A");
    do
    {
        system("cls");
        cout << "1.- Añadir empleado" << endl;
        cout << "2.- buscar empleado" << endl;
        cout << "3.- ver empleados" << endl;
        cout << "5. salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        validarCaso(opcion);
        system("pause");
    } while (opcion != 5);

    return 0;
}

void validarCaso(int opcion)
{
    int dni;
    int idEmpleado;
    switch (opcion)
    {
    case 1:
        registrarEmpleado();
        break;
    case 2:
        cout << "DNI: ";
        cin >> dni;
        idEmpleado = 0;
        idEmpleado = consultarEmpleado(dni);
        if (idEmpleado > 0)
        {
            system("pause");
            menuEmpleado(idEmpleado);
        }
        break;
    case 3:
        verTodosEmpleados();
        break;
    }
}
void menuEmpleado(int idEmpleado)
{
    int opcion;
    do
    {
        system("cls");

        cout << "1.- agregar horas trabajo" << endl;
        cout << "2.- ver horas trabajo por pagar" << endl;
        cout << "3.- ver horas trabajo pagadas" << endl;
        cout << "4.- pagar" << endl;
        cout << "5.-ver todos los  pagos" << endl;
        cout << "6.- consultar bonificaciones" << endl;
        cout << "7.- consultar gratificaciones" << endl;
        cout << "8.- consultar seguros" << endl;
        cout << "10.- salir" << endl;
        cout << "opcion: ";
        cin >> opcion;
        switch (opcion)
        {

        case 1:
            registrarHoras(idEmpleado);
            break;
        case 2:
            verHorasTrabajo(idEmpleado, false);
            break;
        case 3:
            verHorasTrabajo(idEmpleado, true);
            break;
        case 4:
            registrarPago(idEmpleado);
            break;
        case 5:
            verPagos(idEmpleado);
            break;
        case 6:
            verBonificaciones(idEmpleado);
            break;
        case 7:
            verGratificaciones(idEmpleado);
            break;
        case 8:
            verSeguros(idEmpleado);
            break;
        default:
            break;
        }
        system("pause");
    } while (opcion != 10);
}
void registrarEmpleado()
{
    empleado.id = 0;
    char resp;

    ultimoElemento();
    if ((fichero = fopen("empleados.dat", "ab")) != NULL)
    {
        do
        {

    empleado.id++;
            fflush(stdin);
            cout << "Introduzca los datos del Empleado" << endl;
            cout << "Nombre: ";
            cin.getline(empleado.nombre, 60);
            cout << "Edad: ";
            cin >> empleado.edad;
            cout << "DNI: ";
            cin >> empleado.dni;
            cout << "Celular: ";
            cin >> empleado.celular;
            fflush(stdin);
            cout << "Email: ";
            cin.getline(empleado.email, 40);

            fwrite(&empleado, lengthEmpleado, 1, fichero);

                 registrarSeguro(empleado.id);
            cout << "Desea añadir otro empleado? (S/N) ";
            cin >> resp;
            cout << endl;

        } while (resp == 'S' || resp == 's');

        fclose(fichero);
    }
    else
    {
        cout << "Error al abrir el fichero" << endl;
    }
}
int consultarEmpleado(int dni)
{
    int idEmpleado = -1;
    bool encontrado = false;
    if ((fichero = fopen("empleados.dat", "rb")) != NULL)
    {
        while (fread(&empleado, lengthEmpleado, 1, fichero))
        {

            if (empleado.dni == dni)
            {

                cout << "ID: " << empleado.id << endl;
                cout << "Nombre: " << empleado.nombre << endl;
                cout << "Edad: " << empleado.edad << endl;
                cout << "DNI: " << empleado.dni << endl;
                cout << "Celular: " << empleado.celular << endl;
                cout << "Email: " << empleado.email << endl
                     << endl;
                idEmpleado = empleado.id;
                encontrado = true;
            }
        }
    }
    fclose(fichero);

    if (encontrado == false)
    {
        cout << "No se encontro el empleado" << endl;
        empleado.id = -1;
    }
    //system("pause");
    return idEmpleado;
}
void verTodosEmpleados()
{
    if ((fichero = fopen("empleados.dat", "rb")) != NULL)
    {
        while (fread(&empleado, lengthEmpleado, 1, fichero))
        {
            cout << "ID: " << empleado.id << endl;
            cout << "Nombre: " << empleado.nombre << endl;
            cout << "Edad: " << empleado.edad << endl;
            cout << "DNI: " << empleado.dni << endl;
            cout << "Celular: " << empleado.celular << endl;
            cout << "Email: " << empleado.email << endl
                 << endl;
        }
        fclose(fichero);
    }
    else
    {
        cout << "Error al abrir el fichero" << endl;
    }
}

int ultimoElemento()
{
    int temp;
    if ((fichero = fopen("empleados.dat", "rb")) != NULL)
    {
        while (fread(&empleado, lengthEmpleado, 1, fichero))
        {
            temp = empleado.id;
        }
    }
    fclose(fichero);
    return temp;
}
void ultimoElementoHoras()
{

    if ((fichero = fopen("horas.dat", "rb")) != NULL)
    {
        while (fread(&horas, lengthHoras, 1, fichero))
        {
        }
    }
    fclose(fichero);
}
void registrarHoras(int idEmpleado)
{
    char resp, resp2;
    horas.id = 0;
    ultimoElementoHoras();
    horas.cancelado = false;
    horas.idEmpleado = 0;
    horas.falta = false;
    horas.permiso = false;
    horas.horas = 0;
    horas.horasExtras = 0;
    strcpy(horas.justificacion, "");
    strcpy(horas.detallePermiso, "");

    if ((fichero = fopen("horas.dat", "ab")) != NULL)
    {
        horas.id++;
        fflush(stdin);
        horas.idEmpleado = idEmpleado;
        cout << "Introduzca los datos del trabajo" << endl;
        cout << "Fecha: ";
        cin.getline(horas.fecha, 20);
        cout << "¿falto ? S/N: ";
        cin >> resp;
        if (resp == 'S' || resp == 's')
        {
            horas.falta = 1;
            fflush(stdin);
            cout << "justificacion: ";
            cin.getline(horas.justificacion, 200);
            horas.horas = 0;
            horas.horasExtras = 0;
        }
        cout << "¿pidio permiso ? S/N: ";
        cin >> resp2;
        if (resp2 == 'S' || resp2 == 's')
        {
            horas.permiso = 1;
            fflush(stdin);
            cout << "detalles del permiso: ";
            cin.getline(horas.detallePermiso, 200);
        }
        if (resp != 'S' && resp != 's')
        {

            cout << "horas de trabajo: ";
            cin >> horas.horas;
        }
        if (horas.horas > 8)
        {

            horas.horasExtras = horas.horas - 8;
            horas.horas = 8;
        }
        fwrite(&horas, lengthHoras, 1, fichero);
        fclose(fichero);
    }
    else
    {
        cout << "Error al abrir el fichero" << endl;
    }
}
void verHorasTrabajo(int idEmpleado, bool opcion)
{
    bool valid = false;
    if ((fichero = fopen("horas.dat", "rb")) != NULL)
    {
        while (fread(&horas, lengthHoras, 1, fichero))
        {
            if (horas.idEmpleado == idEmpleado && horas.cancelado == opcion)
            {
                cout << "ID: " << horas.id << endl;
                cout << "ID Empleado: " << horas.idEmpleado << endl;
                cout << "Fecha: " << horas.fecha << endl;
                cout << "falta" << horas.falta << endl;
                cout << "justificacion: " << horas.justificacion << endl;
                cout << "permiso: " << horas.permiso << endl;
                cout << "detalles permiso" << horas.detallePermiso << endl;
                cout << "horas: " << horas.horas << endl;
                cout << "horas extras: " << horas.horasExtras << endl;
                cout << "cancelado: " << horas.cancelado << endl;
                cout << endl;
                valid = true;
            }
        }
    }
    fclose(fichero);
    if (!valid)
    {
        cout << "Horas de trabjo no encontradas" << endl;
    }
}

void registrarPago(int idEmpleado)
{
    char resp;
    int posHora;
    float porcentajeBonificacion;
    char detalleBonificacion[200];
    float dineroGratificacion;
    char detalleGratificacion[200];
    pago.id = 0;

    ultimoElementoPago();
    pago.idEmpleado = idEmpleado;
    pago.monto = 0;
    pago.horas = 0;
    pago.horasExtras = 0;
    pago.idBonificacion = 0;
    pago.idGratificacion = 0;

    if ((fichero = fopen("horas.dat", "r+b")) != NULL)
    {
        while (fread(&horas, lengthHoras, 1, fichero))
        {
            if (horas.idEmpleado == idEmpleado && horas.cancelado == false)
            {
                pago.horas += horas.horas;
                pago.horasExtras += horas.horasExtras;
            }
        }
        fclose(fichero);
    }

    cout << "Introduca el precio por hora: ";
    cin >> pago.precioHora;
    cout << "Catidad de horas: " << pago.horas << endl;
    cout << "Cantidad de horas extras: " << pago.horasExtras << endl;
    cout << "Cantidad a pagar: " << (pago.horas + pago.horasExtras) * pago.precioHora << endl;
    cout << endl;
    if ((pago.horas + pago.horasExtras) * pago.precioHora == 0)
    {
        return;
    }
    cout << "Desea Pagar? S/N: ";
    cin >> resp;
    if (resp == 'S' || resp == 's')
    {

        pago.monto = (pago.horas + pago.horasExtras) * pago.precioHora;
        cout << "Introduzca la fecha de pago: ";
        fflush(stdin);
        cin.getline(pago.fecha, 20);
        cout << "¿desea agregar bonificacion? S/N: ";
        cin >> resp;
        if (resp == 'S' || resp == 's')
        {
            cout << "Introduzca el porcentaje a dar: ";
            cin >> porcentajeBonificacion;
            cout << "Introduzca el detalle de la bonificacion: ";
            fflush(stdin);
            cin.getline(detalleBonificacion, 200);
            pago.idBonificacion = registrarBonificacion(pago.idEmpleado, pago.fecha, pago.monto, porcentajeBonificacion, detalleBonificacion);
        }
        else
        {
            pago.idBonificacion = 0;
        }

        cout << "¿desea agregar gratificacion? S/N: ";
        cin >> resp;
        if (resp == 'S' || resp == 's')
        {
            cout << "introduca cantidad de dinero a dar: ";
            cin >> dineroGratificacion;
            cout << "introduce detalle de gratificacion: ";
            fflush(stdin);
            cin.getline(detalleGratificacion, 200);
            pago.idGratificacion = registrarGratificacion(pago.idEmpleado, pago.fecha, dineroGratificacion, detalleGratificacion);
        }

        if ((fichero4 = fopen("pagos.dat", "a+b")) != NULL)
        {
            pago.id++;

            fwrite(&pago, lengthPago, 1, fichero4);
            fclose(fichero4);
        }

        actualizarHoras(idEmpleado);
        cout << "Pago registrado" << endl;
    }
}
void actualizarHoras(int idEmpleado)
{
    char resp;
    int posHora;

    if ((fichero = fopen("horas.dat", "r+b")) != NULL)
    {
        while (fread(&horas, lengthHoras, 1, fichero))
        {
            if ((horas.idEmpleado == idEmpleado && horas.cancelado == false))
            {

                posHora = (horas.id - 1) * lengthHoras;
                modificarHoras(posHora);
            }
        }
        fclose(fichero);
    }
}
void modificarHoras(int pos)
{

    if ((fichero2 = fopen("horas.dat", "r+b")) != NULL)
    {

        fseek(fichero2, pos, 0);
        horas.cancelado = true;
        fwrite(&horas, lengthHoras, 1, fichero2);
        fclose(fichero2);
    }
}

void ultimoElementoPago()
{

    if ((fichero3 = fopen("gratificaciones.dat", "rb")) != NULL)
    {
        while (fread(&gratificacion, lengthGratificacion, 1, fichero3))
        {
        }
        fclose(fichero3);
    }
}

void verPagos(int idEmpleado)
{
    if ((fichero = fopen("pagos.dat", "rb")) != NULL)
    {
        while (fread(&pago, lengthPago, 1, fichero))
        {
            if (pago.idEmpleado == idEmpleado)
            {

                cout << "id: " << pago.id << endl;
                cout << "idEmpleado: " << pago.idEmpleado << endl;
                cout << "fecha: " << pago.fecha << endl;
                cout << "monto: " << pago.monto << endl;
                cout << "idBonificacion: " << pago.idBonificacion << endl;
                cout << "idGratificacion: " << pago.idGratificacion << endl;
                cout << "horas: " << pago.horas << endl;
                cout << "horasExtras: " << pago.horasExtras << endl;
                cout << "precioHora: " << pago.precioHora << endl;
                cout << endl;
            }
        }
        fclose(fichero);
    }
    system("PAUSE");
}
int registrarBonificacion(int idEmpleado, char fecha[20], float dinero, float porcentaje, char detalle[200])
{

    bonificacion.id = 0;
    ultimoElementoBonificacion();
    bonificacion.monto = dinero;
    bonificacion.idEmpleado = idEmpleado;
    strcpy(bonificacion.fecha, fecha);
    bonificacion.porcentaje = porcentaje;
    strcpy(bonificacion.detalle, detalle);
    bonificacion.monto = dinero * (porcentaje / 100);

    if ((fichero2 = fopen("bonificaciones.dat", "ab")) != NULL)
    {
        bonificacion.id++;
        fwrite(&bonificacion, lengthBonificacion, 1, fichero2);
        fclose(fichero2);
    }
    else
    {
        cout << "Error al abrir el fichero" << endl;
        
    }
    return bonificacion.id;
}
void verBonificaciones(int idEmpleado)
{
    bool valid = false;
    if ((fichero2 = fopen("bonificaciones.dat", "rb")) != NULL)
    {
        while (fread(&bonificacion, lengthBonificacion, 1, fichero2))
        {
            if (bonificacion.idEmpleado == idEmpleado)
            {
                cout << "ID: " << bonificacion.id << endl;
                cout << "ID Empleado: " << bonificacion.idEmpleado << endl;
                cout << "Fecha: " << bonificacion.fecha << endl;
                cout << "porcentaje: " << bonificacion.porcentaje << endl;
                cout << "detalle: " << bonificacion.detalle << endl;
                cout << "monto: " << bonificacion.monto << endl;
                cout << endl;
                valid = true;
            }
        }
        fclose(fichero2);
    }
    if (!valid)
    {
        cout << "No hay bonificaciones registradas" << endl;
    }
}

void ultimoElementoBonificacion()
{

    if ((fichero2 = fopen("bonificaciones.dat", "rb")) != NULL)
    {
        while (fread(&bonificacion, lengthBonificacion, 1, fichero2))
        {
        }
        fclose(fichero2);
    }
}

int registrarGratificacion(int idEmpleado, char fecha[20], float dinero, char detalle[200])
{

    gratificacion.id = 0;
    ultimoElementoGratificacion();
    gratificacion.monto = 0.0;
    gratificacion.idEmpleado = 0;
    gratificacion.idEmpleado = idEmpleado;
    strcpy(gratificacion.fecha, fecha);
    strcpy(gratificacion.detalle, detalle);
    gratificacion.monto = dinero;
    if ((fichero3 = fopen("gratificaciones.dat", "ab")) != NULL)
    {
        gratificacion.id++;
        fwrite(&gratificacion, lengthGratificacion, 1, fichero3);
        fclose(fichero3);
    }
    else
    {
        cout << "Error al abrir el fichero" << endl;
    }
        return gratificacion.id;

}
void verGratificaciones(int idEmpleado)
{
    bool valid = false;
    if ((fichero3 = fopen("gratificaciones.dat", "rb")) != NULL)
    {
        while (fread(&gratificacion, lengthGratificacion, 1, fichero3))
        {
            if (gratificacion.idEmpleado == idEmpleado)
            {
                cout << "ID: " << gratificacion.id << endl;
                cout << "ID Empleado: " << gratificacion.idEmpleado << endl;
                cout << "Fecha: " << gratificacion.fecha << endl;
                cout << "detalle: " << gratificacion.detalle << endl;
                cout << "monto: " << gratificacion.monto << endl;
                cout << endl;
                valid = true;
            }
        }
        fclose(fichero3);
    }
    if (!valid)
    {
        cout << "No hay gratificaciones registradas" << endl;
    }
}
void ultimoElementoGratificacion()
{
    if ((fichero3 = fopen("gratificaciones.dat", "rb")) != NULL)
    {
        while (fread(&gratificacion, lengthGratificacion, 1, fichero3))
        {
        }
        fclose(fichero3);
    }
}
void registrarSeguro(int idEmpleado)
{

    char tipoSeguro[20];
    if ((fichero4 = fopen("seguros.dat", "ab")) != NULL)
    {
        seguro.idEmpleado = idEmpleado;
        cout << "Ingrese el tipo de seguro: ";
        fflush(stdin);
        cin.getline(tipoSeguro, 20);
        strcpy(seguro.tipo, tipoSeguro);
        fwrite(&seguro, lengthSeguro, 1, fichero4);
        fclose(fichero4);
    }
}
void verSeguros(int idEmpleado)
{
    if ((fichero4 = fopen("seguros.dat", "rb")) != NULL)
    {
        while (fread(&seguro, lengthSeguro, 1, fichero4))
        {
            if (seguro.idEmpleado == idEmpleado)
            {
                cout << "Tipo de seguro: " << seguro.tipo << endl;
            }
        }
    }
}
