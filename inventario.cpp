/*Luis Roberto Surec Morales
 *1990-20-4012
 *21/05/2022
 */

// Inicio del programa
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

vector<string> split(string str, char pattern)
{

    int posInit = 0;
    int posFound = 0;
    string splitted;
    vector<string> results;

    while (posFound >= 0)
    {
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }

    return results;
}

int escribirEnArchivo(string texto, string path)
{
    ofstream out_file; // Output File Stream para escribir (writing)
    ifstream in_file;  // Input File Stream  para leer (reading)

    // Escribir el archivo
    out_file.open(path, ios::app); // ios::app es lo paralello a "a" que significa append agregar al final del archivo
    out_file << texto << endl;     // agregamos al buffer del stream
    out_file.close();              // flush el buffer y cerramos. flush el buffer basicamente hace write en el archivo.
    return 1;
}

// calcula el precio total de un producto
float calcularPrecio(int cantidad, float precio)
{
    float precioTotal = cantidad * precio;
    return precioTotal;
}

// buscar producto en el inventario
int buscarProducto(string codigoProducto, string path, int opt)
{
    if(opt != 3){
    system("cmd /c cls");

    }
    int posicion = -1;
    ifstream in_file; // Input File Stream  para leer (reading)
    in_file.open(path);
    string linea;
    while (getline(in_file, linea))
    {

        vector<string> producto = split(linea, ',');
        if (producto[0] == codigoProducto)
        {

            if (opt == 1)
            {
                cout << "Ingresar producto al inventario" << endl
                     << endl;
            }
            if (opt == 2)
            {
                cout << "Extraer producto del inventario" << endl
                     << endl;
            }
            if (opt != 3)
            {
                cout << "Producto encontrado" << endl
                     << endl;

                cout << "Codigo"
                     << ","
                     << "Nombre"
                     << ","
                     << "Cantidad"
                     << ","
                     << "Precio"
                     << ","
                     << "total"
                     << endl;
                cout << producto[0]
                     << ","
                     << producto[1]
                     << ","
                     << producto[2]
                     << ","
                     << producto[3]
                     << ","
                     << calcularPrecio(stoi(producto[2]), stof(producto[3]))
                     << endl
                     << endl;

            }
                posicion = 1;
                break;
        }
    }
    in_file.close();
    return posicion;
}

// update file
int updateFile(string codigo, int cantidad, string path)
{
    // make a copy content file
    vector<string> lines;
    ifstream in_file; // Input File Stream  para leer (reading)
    in_file.open(path);
    string line;
    while (getline(in_file, line))
    {
        lines.push_back(line);
    }
    in_file.close();

    // update file
    // for in lines vector
    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> producto = split(lines[i], ',');
        if (producto[0] == codigo)
        {
            int cantidadActual = stoi(producto[2]);
            int cantidadNueva = cantidadActual + cantidad;
            string cantidadNuevaString = to_string(cantidadNueva);
            lines[i] = codigo + "," + producto[1] + "," + cantidadNuevaString + "," + producto[3];
            break;
        }
    }

    // write file with new content escribirEnArchivo
    ofstream file;
    file.open(path);
    file.close();
    for (int i = 0; i < lines.size(); i++)
    {
        escribirEnArchivo(lines[i], path);
    }

    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> producto = split(lines[i], ',');
        if (producto[0] == codigo)
        {
            system("cmd /c cls");
            cout << "Agrregar producto al inventario" << endl
                 << endl;
            cout << "Producto actualizado" << endl
                 << endl;

            cout << "Codigo"
                 << ","
                 << "Nombre"
                 << ","
                 << "Cantidad"
                 << ","
                 << "Precio"
                 << ","
                 << "total"
                 << endl;
            cout << producto[0]
                 << ","
                 << producto[1]
                 << ","
                 << producto[2]
                 << ","
                 << producto[3]
                 << ","
                 << calcularPrecio(stoi(producto[2]), stof(producto[3]))
                 << endl
                 << endl;
        }
    }
    return 1;
}

int existFile(string path)
{
    ifstream in_file; // Input File Stream  para leer (reading)
    in_file.open(path);
    if (in_file.is_open())
    {
        in_file.close();
        return 1;
    }
    else
    {
        in_file.close();
        return 0;
    }
}

// update file
int updateFileRemove(string codigo, int cantidad, string path)
{
    // make a copy content file
    vector<string> lines;
    ifstream in_file; // Input File Stream  para leer (reading)
    in_file.open(path);
    string line;
    while (getline(in_file, line))
    {
        lines.push_back(line);
    }
    in_file.close();

    // update file
    // for in lines vector
    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> producto = split(lines[i], ',');
        if (producto[0] == codigo)
        {
            int cantidadActual = stoi(producto[2]);
            int cantidadNueva = cantidadActual - cantidad;

            if (cantidadNueva < 0)
            {
                system("cmd /c cls");

                cout << "Extraer producto del inventario" << endl
                     << endl;
                cout << "No hay suficiente cantidad" << endl
                     << endl;
                return 0;
            }
            else
            {
                string cantidadNuevaString = to_string(cantidadNueva);
                lines[i] = codigo + "," + producto[1] + "," + cantidadNuevaString + "," + producto[3];
                break;
            }
        }
    }

    // write file with new content escribirEnArchivo
    ofstream file;
    file.open(path);
    file.close();
    for (int i = 0; i < lines.size(); i++)
    {
        escribirEnArchivo(lines[i], path);
    }

    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> producto = split(lines[i], ',');
        if (producto[0] == codigo)
        {
            system("cmd /c cls");
            cout << "Extraer producto del inventario" << endl
                 << endl;
            cout << "Producto actualizado" << endl
                 << endl;

            cout << "Codigo"
                 << ","
                 << "Nombre"
                 << ","
                 << "Cantidad"
                 << ","
                 << "Precio"
                 << ","
                 << "total"
                 << endl;
            cout << producto[0]
                 << ","
                 << producto[1]
                 << ","
                 << producto[2]
                 << ","
                 << producto[3]
                 << ","
                 << calcularPrecio(stoi(producto[2]), stof(producto[3]))
                 << endl
                 << endl;
        }
    }
    return 1;
}

int leerArchivo(string path)
{
    vector<string> results;
    float grandTotal = 0;

    ifstream in_file; // Input File Stream  para leer (reading)
    string line;
    in_file.open(path);

    cout << "Mostar productos del inventario" << endl
         << endl;

    cout << "Codigo"
         << ","
         << "Nombre"
         << ","
         << "Cantidad"
         << ","
         << "Precio"
         << ","
         << "total"
         << endl;

    while (getline(in_file, line))
    {
        results = split(line, ',');

        cout << results[0]
             << ","
             << results[1]
             << ","
             << results[2]
             << ","
             << results[3]
             << ","
             << calcularPrecio(stoi(results[2]), stof(results[3]))
             << endl;

        grandTotal += calcularPrecio(stoi(results[2]), stof(results[3]));

        // cout << line << endl;
    }
    cout << "Gran Total: " << grandTotal << endl
         << endl;

    in_file.close();
    return 1;
}

// function count lines file
int countLines(string path)
{
    ifstream in_file;
    int lines = 0;
    string line;
    in_file.open(path);
    while (getline(in_file, line))
    {
        lines++;
    }
    in_file.close();
    return lines;
}

// Nueva estrcutura Produto
struct Producto
{
    string codigoProducto;
    string nombreProducto;
    string cantidadExistente;
    string precioUntario;
};

int main()
{

    // Declaracion de variables
    string pathFile = "C:\\Users\\dsdev\\OneDrive\\Escritorio\\UMG\\Progra1\\parte2\\laboratorio\\archivo.txt";
    int opcion;
    int seguir = 0;
    int cantidadNueva;
    string codigoProducto;
    string cadena;
    Producto producto;

    ifstream fe(pathFile);

    if (existFile(pathFile) == 0)
    {
        ofstream file;
        file.open(pathFile);
        file.close();
    }

    // Menu de opciones
    do
    {
        // Menu de opciones
        cout << "Menu principal de productos" << endl
             << endl;
        cout << "1. Registrar producto en el inventario" << endl;
        cout << "2. Mostar productos del inventario" << endl;
        cout << "3. Ingresar producto al inventario" << endl;
        cout << "4. Extraer producto del inventario" << endl;
        cout << "5. Salir" << endl
             << endl;
        cout << "Ingrese una opcion: " << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // Registrar productos hasta que el usuario decida salir
            system("cmd /c cls");
            do
            {
                cout << "Registrar productos" << endl
                     << endl;

                cout << "Ingrese el codigo del producto: ";
                cin >> producto.codigoProducto;
                
                while (buscarProducto(producto.codigoProducto, pathFile, 3) == 1)
                {
                    cout << "Codigo ya existe, ingrese otro codigo: ";
                    cin >> producto.codigoProducto;
                }
                

                cout << "Ingrese el nombre del producto: ";
                cin >> producto.nombreProducto;
                cout << "Ingrese el precio unitario del producto: ";
                cin >> producto.precioUntario;
                // cantidad 0
                producto.cantidadExistente = "0";

                // Escribir producto en el archivo con funcion escribirEnArchivo
                escribirEnArchivo(producto.codigoProducto + "," + producto.nombreProducto + "," + producto.cantidadExistente + "," + producto.precioUntario, pathFile);

                system("cmd /c cls");

                cout << "Registrar producto en el inventario" << endl
                     << endl;
                cout << "Producto guardado exitosamente" << endl
                     << endl;

                cout << "Desea ingresar otro producto? " << endl;
                cout << "1. Si" << endl;
                cout << "2. No" << endl;

                cin >> seguir;
                system("cmd /c cls");

            } while (seguir != 2);

            break;
        case 2:
            // Mostar productos
            system("cmd /c cls");
            // Si el archivo esta vacio mostrar mensaje “Lo siento!!! No hay productos”

            // leerArchivo
            if (countLines(pathFile) == 0)
            {
                cout << "Mostar productos del inventario" << endl
                     << endl;
                cout << "No hay productos registrados" << endl
                     << endl;
            }
            else
            {
                leerArchivo(pathFile);
            }

            system("cmd /c pause");
            system("cmd /c cls");
            break;

        case 3:
            system("cmd /c cls");
            // Ingresar productos al inventario
            // Solicitar codigo del producto
            if (countLines(pathFile) == 0)
            {
                cout << "Ingresar producto al inventario" << endl
                     << endl;
                cout << "No hay productos registrados" << endl
                     << endl;
            }
            else
            {
                cout << "Ingresar producto al inventario" << endl
                     << endl;
                cout << "Ingrese el codigo del producto: ";
                cin >> codigoProducto;
                // Buscar producto en el archivo
                if (buscarProducto(codigoProducto, pathFile, 1) == 1)
                {
                    // Si el producto existe solicitar cantidad a ingresar
                    cout << "Ingrese la cantidad a ingresar: ";

                    do
                    {
                        cin >> cantidadNueva;
                        if (cantidadNueva < 0)
                        {
                            cout << "La cantidad de producto no puede ser negativa" << endl;
                        }
                    } while (cantidadNueva < 0);

                    updateFile(codigoProducto, cantidadNueva, pathFile);
                }
                else
                {
                    cout << "Ingresar producto al inventario" << endl
                         << endl;
                    cout << "Producto no encontrado" << endl
                         << endl;
                }
            }

            system("cmd /c pause");
            system("cmd /c cls");
            break;
        case 4:
            system("cmd /c cls");

            // Extraer productos
            if (countLines(pathFile) == 0)
            {
                cout << "Extraer producto del inventario" << endl
                     << endl;
                cout << "No hay productos registrados" << endl
                     << endl;
            }
            else
            {
                cout << "Extraer producto del inventario" << endl
                     << endl;
                cout << "Ingrese el codigo del producto: ";
                cin >> codigoProducto;
                // Buscar producto en el archivo
                if (buscarProducto(codigoProducto, pathFile, 2) == 1)
                {
                    // Si el producto existe solicitar cantidad a ingresar
                    cout << "Ingrese la cantidad a extraer: ";

                    do
                    {
                        cin >> cantidadNueva;
                        if (cantidadNueva < 0)
                        {
                            cout << "La cantidad de producto no puede ser negativa" << endl;
                        }
                    } while (cantidadNueva < 0);

                    updateFileRemove(codigoProducto, cantidadNueva, pathFile);
                }
                else
                {
                    cout << "Extraer producto del inventario" << endl
                         << endl;
                    cout << "Producto no encontrado" << endl
                         << endl;
                }
            }
            system("cmd /c pause");
            system("cmd /c cls");
            break;
        case 5:
            // Salir
            // Salir del programa
            system("cmd /c cls");
            break;
        default:
            // Opcion invalida
            // Mostrar mensaje de error
            system("cmd /c cls");
            cout << "Opcion invalida" << endl;
            break;
        }

    } while (opcion != 5);

    return 0;
}
