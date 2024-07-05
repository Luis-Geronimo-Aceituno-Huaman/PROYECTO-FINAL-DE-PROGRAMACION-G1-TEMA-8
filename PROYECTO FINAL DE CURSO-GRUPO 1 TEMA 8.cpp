#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
void opciones();
void opcion_A(int &contador);
int CONTADOR(string texto);
void opcion_B(int &contador);
void opcion_C(int &contador);
void opcion_D(int &contador);
void opcion_E(int &contador);
void LEER();

struct Indice {
    size_t index;
    size_t length;
};
char* cifrarMensaje(const string& mensajeOriginal, const string& claveCorrespondencia) {
    char mapaCorrespondencias[26];
    for (int i = 0; i < 26; ++i) {
        mapaCorrespondencias[i] = claveCorrespondencia[i];
    }

    Indice indice;
    indice.index = 0;
    indice.length = mensajeOriginal.length();

    char* mensajeCifrado = new char[indice.length + 1];

    for (indice.index = 0; indice.index < indice.length; ++indice.index) {
        char caracter = mensajeOriginal[indice.index];
        if (caracter >= 'a' && caracter <= 'z') {
            mensajeCifrado[indice.index] = mapaCorrespondencias[caracter - 'a'];
        } 
        else if(caracter >= 'A' && caracter <= 'Z') {
            mensajeCifrado[indice.index] = mapaCorrespondencias[caracter - 'A'];
        } 
        else {
            mensajeCifrado[indice.index] = caracter;
        }
    }
    mensajeCifrado[indice.length] = '\0';

    return mensajeCifrado;
}

int main() {
    remove("opcion_A.txt");
    remove("opcion_B.txt");
    remove("opcion_C.txt");
    remove("opcion_D.txt");
    remove("opcion_E.txt");
    opciones();
    return 0;
}

void opciones() {
    int contador_a=1, contador_b=1, contador_c=1,contador_d=1,contador_e=1;
    char opcion;
    do {
        cout << "\n\n\t\t\tMENU PRINCIPAL\n";
        cout<<"\t\t\t--------------\n"<<endl;
        cout << "\n\ta. Lee lineas de texto, obtiene las palabras y las muestra en orden alfabetico (maximo 28 palabras por linea).\n";
        cout << "\tb. Encripta un mensaje sustituyendo cada caracter por el que esta tres posiciones adelante en el alfabeto.\n";
        cout << "\tc. Encripta un mensaje sustituyendo cada caracter segun una cadena de correspondencias predefinida (punteros).\n";
        cout << "\td. Encripta un texto sustituyendo letras minusculas por otras segun un array cifrado.\n";
        cout << "\te. Encripta un mensaje sustituyendo cada letra por otra en todo el mensaje.\n";
        cout << "\tf. Mostrar las operaciones realizadas.\n";
        cout << "\tg. Salir.\n\n";
        cout << "\n\tElija que opcion desea (solo con letras minusculas): ";
        cin >> opcion;
        system("cls");
        cin.ignore();
        switch (opcion) {
            case 'a': 
                opcion_A(contador_a); contador_a++;
                break;
            case 'b': 
                opcion_B(contador_b); contador_b++;
                break;
            case 'c': 
                opcion_C(contador_c); contador_c++;
                break;
            case 'd': 
                opcion_D(contador_d); contador_d++;
                break;
            case 'e': 
                opcion_E(contador_e); contador_e++;
                break;
            case 'f': 
                LEER();
                break;
            case 'g': 
                cout << "\n\tPresione ENTER para cerrar la aplicacion.\n";
                break;
            default: 
                cout << "\n\n\t\t\t::: Ingrese una opcion valida ::: \n";
                break;
        }
    } while (opcion != 'g');
}

void opcion_A(int &contador) {
    int e = 0;
    string mayuscula = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string minuscula = "abcdefghijklmnopqrstuvwxyz";
    string texto=" ";
    string cadena[28];
    int C;
    cout<<"\n\t\tOPCION A \n\t\t---------\n"<<endl;    
    cout << "\n\tIngrese un texto para dividir (max 28 palabras): ";
    getline(cin, texto);
    C=CONTADOR(texto);
    while(C>28){
        texto="";
        cout << "\n\tIngrese un texto para dividir (max 28 palabras): ";
        getline(cin, texto);
        C=CONTADOR(texto);
    }
    for (int i = 0; i < texto.length(); i++) {
        for (int k = 0; k < 26; k++) {
            if (texto[i] == mayuscula[k]) {
                texto[i] = minuscula[k];
            }
        }
    }
    istringstream palabra(texto);
    while (palabra >> cadena[e]) {
        e++;
    }
    sort(cadena, cadena + e);
    //Escribir en archivo
    ofstream archivo("opcion_A.txt",ios::app); 
    archivo<<"\n\t\t\t::: OPERACION #"<<contador<<" :::\n\n"<<endl;
    for (int i = 0; i < e; i++) {
        cout <<"\n\t\t"<< i + 1 << "..." << cadena[i] << endl;
        archivo<<"\t\t"<<setfill('-')<<setw(21)<<"-"<<endl;
        archivo <<left<<setfill(' ')<<"\t\t"<<"|"<<setw(3)<< i + 1 << "|" <<setw(15)<< cadena[i] <<"|"<< endl;
        archivo<<"\t\t"<<setfill('-')<<setw(21)<<"-"<<endl;
    }
    archivo.close();
}
int CONTADOR(string texto){
    int C;
    if(texto[0]=' '){
        C=0;
    }
    else{
        C=1;
    }
    for(int i=0; i<texto.length();i++){
        if(texto[i]==' ' && texto[i+1]!=' ')
        {
            C++;
        }
        else{
            continue;
        }
    }
    return C;
}

void opcion_B(int &contador) {
    string mensaje;
    string cifrado = "";
    cout<<"\n\t\tOPCION B \n\t\t---------\n"<<endl;
    cout << "\n\tIntroduce el mensaje a cifrar: ";
    getline(cin, mensaje);
    for (size_t i = 0; i < mensaje.size(); ++i) {
        char c = mensaje[i];
        if (c >= 'A' && c <= 'Z') {
            cifrado += char((c - 'A' + 3) % 26 + 'A');
        } else if (c >= 'a' && c <= 'z') {
            cifrado += char((c - 'a' + 3) % 26 + 'a');
        } else {
            cifrado += c;
        }
    }
    cout << "\n\t\tMensaje cifrado: " << cifrado << endl;
    ofstream archivo("opcion_B.txt",ios::app); 
    archivo<<"\t\t::: OPERACION #"<<contador<<" :::\n\n"<<endl;

    archivo<<"\t\t"<<setfill('-')<<setw(71)<<"-"<<endl;
    archivo <<left<<setfill(' ')<<"\t\t|"<< "Mensaje original: " <<"|"<<setw(50)<< mensaje <<"|"<< endl;
    archivo<<"\t\t"<<setfill('-')<<setw(71)<<"-"<<endl;
    archivo <<left<<setfill(' ')<<"\t\t|"<<"Mensaje cifrado:  " <<"|"<<setw(50)<< cifrado <<"|"<< endl;
    archivo<<"\t\t"<<setfill('-')<<setw(71)<<"-"<<endl;
    archivo.close();
}

void opcion_C(int &contador) {
    string mensajeOriginal;
    string claveCorrespondencia;
    cout<<"\n\t\tOPCION C \n\t\t---------\n"<<endl;
    cout << "\n\tIngrese el mensaje codificado: ";
    getline(cin, mensajeOriginal);
    cout << "\n\t\tIngrese la clave de correspondencia: ";
    getline(cin, claveCorrespondencia);
    while(claveCorrespondencia.length()!=26){
        cout << "\n\t\t La clave de correspondencia debe tener 26 caracteres: ";
        getline(cin, claveCorrespondencia);
    }

    char* mensajeCifrado = cifrarMensaje(mensajeOriginal, claveCorrespondencia);

    cout << "\n\tMensaje cifrado: '" << mensajeCifrado << "'" << endl;
    cout << "\n\t\tUbicacion del puntero: " << static_cast<void*>(mensajeCifrado) << endl;

    ofstream archivo("opcion_C.txt",ios::app); 
    archivo<<"\n\t\t::: OPERACION #"<<contador<<" :::\n\n"<<endl;
    archivo<<"\t\t"<<setfill('-')<<setw(79)<<"-"<<endl;
    archivo<<"\t\t" <<left<<setfill(' ')<<"|"<<setw(27)<< "Mensaje original: " <<"|"<< setw(50)<<mensajeOriginal<<"|" << endl;
    archivo<<"\t\t"<<setfill('-')<<setw(79)<<"-"<<endl;
    archivo<<"\t\t" <<left<<setfill(' ')<<"|"<<setw(27)<< "Clave de correspondencia: " <<"|"<<setw(50)<< claveCorrespondencia <<"|"<< endl;
    archivo<<"\t\t"<<setfill('-')<<setw(79)<<"-"<<endl;
    archivo <<"\t\t"<<left<<setfill(' ')<<"|"<<setw(27)<< "Mensaje cifrado: " <<"|"<<setw(50)<< mensajeCifrado <<"|"<< endl;
    archivo<<"\t\t"<<setfill('-')<<setw(79)<<"-"<<endl;
    archivo.close();

    delete[] mensajeCifrado;
}

void opcion_D(int &contador) {
    string palabra, alfabeto = "abcdefghijklmnopqrstuvwxyz";
    char codigo[26];
    cout<<"\n\t\tOPCION D \n\t\t---------\n"<<endl;
    for (int i = 0; i < 26; i++) {
        cout << "\n\tIngrese el caracter #" << i + 1 << " que serviran para encriptar: ";
        cin >> codigo[i];

        for (int k = 0; k < i; k++) {
            if (codigo[i] == codigo[k]) {
                while (codigo[i] == codigo[k]) {
                    cout << "\n\t\tIngrese un caracter no repetido: ";
                    cin >> codigo[i];
                }
            } else {
                continue;
            }
        }
    }
    cin.ignore();
    cout << "\n\tIngrese el texto que desea encriptar: ";
    getline(cin, palabra);
    string palabraOriginal = palabra; 
    for (int i = 0; i < palabra.size(); i++) {
        for (int k = 0; k < 26; k++) {
            if (palabra[i] == alfabeto[k]) {
                palabra[i] = codigo[k];
                break;
            } else {
                continue;
            }
        }
    }
    cout << "\n\tEl texto encriptado es: " << palabra << endl;
    ofstream archivo("opcion_D.txt",ios::app); 
    archivo<<"\n\t\t::: OPERACION #"<<contador<<" :::\n\n"<<endl;
    archivo<<"\t\t"<<setfill('-')<<setw(69)<<"-"<<endl;
    archivo <<left<<"\t\t|"<<setfill(' ')<<setw(16)<< "Texto original: " <<"|"<<setw(50)<<palabraOriginal<<"|" << endl;
    archivo<<"\t\t"<<setfill('-')<<setw(69)<<"-"<<endl;
    archivo <<left<<"\t\t|"<<setfill(' ')<<setw(16)<<"Texto encriptado: " <<"|"<<setw(50)<< palabra<<"|" << endl;
    archivo<<"\t\t"<<setfill('-')<<setw(69)<<"-"<<endl;
    archivo.close();
}

void opcion_E(int &contador) {
    string ALFABETO="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string minuscula = "abcdefghijklmnopqrstuvwxyz";
    struct datos{
    string CODIGO;
    string claveCorrespondencia;
    string DECO;
    };
    int longitud = 0;
    int NUM;
    string auxiliar,auxiliar_2,auxiliar_3;
    cout<<"\n\t\tOPCION E \n\t\t---------\n"<<endl;
    cout<<"Ingrese el numero de decodificaciones que realizara (1<=NUM<=1000):"; cin>>NUM;
    while(NUM<1 or NUM>1000){
        cout<<"Ingrese un numero valido(1<=NUM<=1000):"; cin>>NUM;
    }
    vector<datos>DATOS(NUM);

    for (int h = 0; h < NUM; h++) {
        cin.ignore();
        cout << "\n\tIngresa el mensaje codificado "<<h+1<<": ";
        getline(cin, DATOS[h].CODIGO);
        cin.ignore();
        cout << "\n\tIngrese la clave de correspondencia "<<h+1<<": ";
        getline(cin, DATOS[h].claveCorrespondencia);

        while(DATOS[h].claveCorrespondencia.length()!=26){
            cout << "\n\t\t La clave de correspondencia debe tener 26 caracteres: ";
            getline(cin, DATOS[h].claveCorrespondencia);
        }

        auxiliar_3=DATOS[h].claveCorrespondencia;

        for (int i = 0; i<26; i++) {
                for (int k = 0; k < 26; k++) {
                    if (auxiliar_3[i] == minuscula[k]) {
                        auxiliar_3[i] = ALFABETO[k];
                    }
                }
        }
        DATOS[h].claveCorrespondencia=auxiliar_3;
        auxiliar=DATOS[h].CODIGO;
        auxiliar_2= DATOS[h].claveCorrespondencia;
        longitud = auxiliar.length();
        //decodificar
        for (int i = 0; i < longitud; i++) {
            for (int k = 0; k < 26; k++) {
                if (auxiliar[i]== auxiliar_2[k]) {
                    auxiliar[i] = ALFABETO[k];
                    break;
                } else {
                    continue;
                }
            }
        }
        DATOS[h].DECO = auxiliar;
        auxiliar="";
        auxiliar_2="";
        longitud = 0;
    }
    ofstream archivo("opcion_E.txt",ios::app);
    archivo<<"\t\t::: OPERACION #"<<contador<<" :::"<<endl;
    for (int h = 0; h < NUM; h++) {
        cout<<"\n\n\t\t"<<h+1<<"...Clave de correspondecia: "<<DATOS[h].claveCorrespondencia<<endl;
        cout<<"\t\t"<<h+1<<"...Mensaje codificado: "<<DATOS[h].CODIGO<<endl;
        cout<<"\t\t"<<h+1<<"...Mensaje decodificado: "<<DATOS[h].DECO<<endl;
        archivo<<"\t"<<setfill('-')<<setw(83)<<"-"<<endl;
        archivo<<left<<setfill(' ')<<"\t|"<<setw(2)<<h+1<<setw(28)<<"| Clave de correspondecia: "<<"|"<<setw(50)<<DATOS[h].claveCorrespondencia<<"|"<<endl;
        archivo<<"\t"<<setfill('-')<<setw(83)<<"-"<<endl;
        archivo<<left<<setfill(' ')<<"\t|"<<setw(2)<<h+1<<setw(28)<<"| Mensaje codificado: "<<"|"<<setw(50)<<DATOS[h].CODIGO<<"|"<<endl;
        archivo<<"\t"<<setfill('-')<<setw(83)<<"-"<<endl;
        archivo<<left<<setfill(' ')<<"\t|"<<setw(2)<<h+1<<setw(28)<<"| Mensaje decodificado: "<<"|"<<setw(50)<<DATOS[h].DECO<<"|"<<endl;
        archivo<<"\t"<<setfill('-')<<setw(83)<<"-"<<endl;
    }
    archivo.close();
}

void LEER(){
 ifstream archivo;
 string texto;
 archivo.open("opcion_A.txt",ios::in);
 cout<<"\n\t\tARCHIVO OPCION A \n\t\t-----------------"<<endl;

    if(archivo.fail()){
    cout<<"\n\t\t :::No se realizo ni una operacion en esta opcion:::"<<endl;
    }
    else{
    while(!archivo.eof()){
            getline(archivo,texto);
            cout<<texto<<endl;
            }
    }
    archivo.close();
    texto="";
archivo.open("opcion_B.txt",ios::in);
 cout<<"\n\t\tARCHIVO OPCION B \n\t\t-----------------"<<endl;
    if(archivo.fail()){
    cout<<"\n\t\t :::No se realizo ni una operacion en esta opcion:::"<<endl;
    }
    else{
    while(!archivo.eof()){
            getline(archivo,texto);
            cout<<texto<<endl;
            }
    }
    archivo.close();
archivo.close();
texto="";

archivo.open("opcion_C.txt",ios::in);
 cout<<"\n\t\tARCHIVO OPCION C \n\t\t-----------------"<<endl;
    if(archivo.fail()){
    cout<<"\n\t\t :::No se realizo ni una operacion en esta opcion:::"<<endl;
    }
    else{
    while(!archivo.eof()){
            getline(archivo,texto);
            cout<<texto<<endl;
            }
    }
    archivo.close();
archivo.close();

texto="";
archivo.open("opcion_D.txt",ios::in);
 cout<<"\n\t\tARCHIVO OPCION D \n\t\t-----------------"<<endl;
    if(archivo.fail()){
    cout<<"\n\t\t :::No se realizo ni una operacion en esta opcion:::"<<endl;
    }
    else{
    while(!archivo.eof()){
            getline(archivo,texto);
            cout<<texto<<endl;
            }
    }
    archivo.close();
archivo.close();

texto="";
archivo.open("opcion_E.txt",ios::in);
 cout<<"\n\t\tARCHIVO OPCION E \n\t\t-----------------"<<endl;
    if(archivo.fail()){
    cout<<"\n\t\t :::No se realizo ni una operacion en esta opcion:::"<<endl;
    }
    else{
    while(!archivo.eof()){
            getline(archivo,texto);
            cout<<texto<<endl;
            }
    }
    archivo.close();
archivo.close();

}
