#include <iostream>
#include <conio.h>  // Para gotoxy
#include <windows.h>  // Para gotoxy
#include <iomanip>  // Para setprecision
#include <string>
using namespace std;

#define MAX_CANDIDATOS 10 
#define MAX_USUARIOS 100
int totalCandidatos = 0; 
int totalUsuarios = 0; 

// Estructura para almacenar los datos de los candidatos 
struct Candidato {
    char nombre[50];
    char partido[50];
    char plataforma[100];
    int votos;
};

// Arreglos para almacenar los datos de los candidatos y usuarios //
Candidato candidatos[MAX_CANDIDATOS]; 
string usuarios[MAX_USUARIOS]; 

// Prototipos de funciones
void gotoxy(int x, int y);
void menu();
void ingresarCandidatos();
void registrarVotos();
void mostrarResultados();
bool verificarUsuario(string idUsuario);

// Función principal
int main() {
    menu();
    return 0;
}

// Función para mover el cursor a una posición específica en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para mostrar el menú principal
void menu() {
    int opcion;
    do {
        system("cls");
        gotoxy(30, 5); cout << "Sistema de Votaciones Electronico";
        gotoxy(30, 7); cout << "1. Ingresar Candidatos";
        gotoxy(30, 8); cout << "2. Registrar Votos";
        gotoxy(30, 9); cout << "3. Mostrar Resultados";
        gotoxy(30, 10); cout << "4. Salir";
        gotoxy(30, 12); cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                ingresarCandidatos();
                break;
            case 2:
                registrarVotos();
                break;
            case 3:
                mostrarResultados();
                break;
            case 4:
                gotoxy(30, 14); cout << "Saliendo...";
                break;
            default:
                gotoxy(30, 14); cout << "Opcion no valida. Intente de nuevo.";
                _getch();  // Pausa para que el usuario pueda ver el mensaje
                break;
        }
    } while (opcion != 4);
}

// Función para ingresar los datos de los candidatos
void ingresarCandidatos() {
    if (totalCandidatos >= MAX_CANDIDATOS) {
        gotoxy(30, 14); cout << "No se pueden agregar mas candidatos.";
        _getch();  // Pausa para que el usuario pueda ver el mensaje
        return;
    }
    
    system("cls");
    gotoxy(30, 5); cout << "Ingresar Candidatos";
    
    gotoxy(30, 7); cout << "Nombre: ";
    cin.ignore();
    cin.getline(candidatos[totalCandidatos].nombre, 50);
    
    gotoxy(30, 8); cout << "Partido: ";
    cin.getline(candidatos[totalCandidatos].partido, 50);
    
    gotoxy(30, 9); cout << "Plataforma: ";
    cin.getline(candidatos[totalCandidatos].plataforma, 100);
    
    candidatos[totalCandidatos].votos = 0;  // Inicializar votos a 0
    
    totalCandidatos++;
    
    gotoxy(30, 11); cout << "Candidato agregado exitosamente.";
    _getch();  // Pausa para que el usuario pueda ver el mensaje
}

// Función para registrar votos
void registrarVotos() {
    if (totalCandidatos == 0) {
        gotoxy(30, 14); cout << "No hay candidatos registrados.";
        _getch();  // Pausa para que el usuario pueda ver el mensaje
        return;
    }
    
    string idUsuario;
    system("cls");
    gotoxy(30, 5); cout << "Registrar Votos";
    
    gotoxy(30, 7); cout << "Ingrese su identificacion: ";
    cin >> idUsuario;
    
    if (verificarUsuario(idUsuario)) {
        gotoxy(30, 9); cout << "Usted ya ha votado.";
        _getch();  // Pausa para que el usuario pueda ver el mensaje
        return;
    }
    
    int voto;
    for (int i = 0; i < totalCandidatos; i++) {
        gotoxy(30, 9 + i); cout << i + 1 << ". " << candidatos[i].nombre << " (" << candidatos[i].partido << ")";
    }
    
    gotoxy(30, 11 + totalCandidatos); cout << "Ingrese el numero del candidato para votar: ";
    cin >> voto;
    
    if (voto > 0 && voto <= totalCandidatos) {
        candidatos[voto - 1].votos++;
        usuarios[totalUsuarios++] = idUsuario;
        gotoxy(30, 13 + totalCandidatos); cout << "Voto registrado exitosamente.";
    } else {
        gotoxy(30, 13 + totalCandidatos); cout << "Numero de candidato invalido.";
    }
    
    _getch();  // Pausa para que el usuario pueda ver el mensaje
}

// Función para mostrar los resultados de las votaciones
void mostrarResultados() {
    if (totalCandidatos == 0) {
        gotoxy(30, 14); cout << "No hay candidatos registrados.";
        _getch();  // Pausa para que el usuario pueda ver el mensaje
        return;
    }
    
    system("cls");
    gotoxy(30, 5); cout << "Resultados de las Votaciones";
    
    int totalVotos = 0;
    for (int i = 0; i < totalCandidatos; i++) {
        totalVotos += candidatos[i].votos;
    }
    
    if (totalVotos == 0) {
        gotoxy(30, 7); cout << "No se han registrado votos.";
        _getch();  // Pausa para que el usuario pueda ver el mensaje
        return;
    }
    
    int ganadorIndex = 0;
    for (int i = 0; i < totalCandidatos; i++) {
        if (candidatos[i].votos > candidatos[ganadorIndex].votos) {
            ganadorIndex = i;
        }
    }
    
    for (int i = 0; i < totalCandidatos; i++) {
        gotoxy(30, 7 + i); 
        cout << candidatos[i].nombre << " (" << candidatos[i].partido << "): " 
             << candidatos[i].votos << " votos ("
             << fixed << setprecision(2) << (candidatos[i].votos * 100.0 / totalVotos) << "%)";
    }
    
    gotoxy(30, 9 + totalCandidatos); 
    cout << "Ganador: " << candidatos[ganadorIndex].nombre << " con " << candidatos[ganadorIndex].votos << " votos.";
    
    _getch();  // Pausa para que el usuario pueda ver el mensaje
}

// Función para verificar si un usuario ya ha votado
bool verificarUsuario(string idUsuario) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i] == idUsuario) {
            return true;
        }
    }
    return false;
}

