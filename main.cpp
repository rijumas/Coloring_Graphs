#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <GL/glut.h>
using namespace std;
void init() {
    glClearColor(0.8, 0.8, 0.8, 1.0); // Establece el color de fondo 
    glMatrixMode(GL_PROJECTION); // Establece la matriz de proyección actual
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Establece la proyección ortográfica
}
void drawCircleColor(float cx, float cy, float r, int num_segments, float colorR, float colorG, float colorB) {
    glColor3f(0.0, 0.0, 0.0); // Establece el color de los bordes (en este caso, negro)
    glBegin(GL_LINE_LOOP); // Inicia el dibujo de una serie de segmentos de línea para los bordes
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // Calcula el ángulo de cada segmento
        float x = r * cosf(theta); // Calcula la coordenada x del punto en el círculo
        float y = r * sinf(theta); // Calcula la coordenada y del punto en el círculo
        glVertex2f(x + cx, y + cy); // Dibuja el punto
    }
    glEnd(); // Finaliza el dibujo de los bordes

    glColor3f(colorR, colorG, colorB); // Establece el color del fondo (en este caso, blanco)
    glBegin(GL_POLYGON); // Inicia el dibujo del fondo
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // Calcula el ángulo de cada segmento
        float x = r * cosf(theta); // Calcula la coordenada x del punto en el círculo
        float y = r * sinf(theta); // Calcula la coordenada y del punto en el círculo
        glVertex2f(x + cx, y + cy); // Dibuja el punto
    }
    glEnd(); // Finaliza el dibujo del fondo
}
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        // Define el primer punto de la línea (x, y)
        glVertex2f(x1, y1);
        // Define el segundo punto de la línea (x, y)
        glVertex2f(x2, y2);
    glEnd();
}
void drawText(std::string text, float x, float y) {
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(x, y, 0.0); // Translada al lugar donde queremos dibujar el texto
    glScalef(0.0009, 0.0009, 0.0009); // Escala el texto para que tenga un tamaño adecuado
    for (char c : text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c); // Dibuja cada caracter del texto
    }
    glPopMatrix();
}
struct nodo {
    char letra;
    vector<nodo*> lista;
    string color;
    vector<string> colores;
    nodo(char _l) {
        letra = _l;
        color = "";
        colores.push_back("rojo");
        colores.push_back("verde");
        colores.push_back("azul");
    }
};
struct grafo {
    vector<nodo*> nodos;
    vector<string> colores;

    grafo(string r, string v, string a) {
        colores.push_back(r);
        colores.push_back(v);
        colores.push_back(a);
    }
    void conectar(nodo& A, nodo& B) {
        A.lista.push_back(&B);
        B.lista.push_back(&A);
    }
    static bool compa(nodo* A, nodo* B) {
        if (A->lista.size() == B->lista.size())
            return A->letra > B->letra;
        else
            return A->lista.size() > B->lista.size();
    }
    static bool _compa(nodo* A, nodo* B) {
        if (A->colores.size() == B->colores.size())
            return A->letra > B->letra;
        else
            return A->colores.size() < B->colores.size();
    }
    void clean1() {
        for (int i = 0; i < nodos.size(); i++) {
            nodos[i]->color = "";
            nodos[i]->colores = { "rojo","verde","azul" };
        }
    }
    void restrictiva() {
        sort(nodos.begin(), nodos.end(), compa);
        for (int i = 0; i < nodos.size(); i++) {
            int pivot = 0;
            string color = colores[pivot];
            for (int j = 0; j < nodos[i]->lista.size(); j++) {
                if (nodos[i]->lista[j]->color == color) {
                    pivot++;
                    color = colores[pivot];
                }
            }
            for (int j = 0; j < nodos[i]->lista.size(); j++) {
                if (nodos[i]->lista[j]->color == color) {
                    pivot++;
                    color = colores[pivot];
                }
            }
            nodos[i]->color = color;
            cout << nodos[i]->letra << "=" << nodos[i]->color << " ";
            if (i != nodos.size() - 1) {
                for (int z = 0; z < nodos.size(); z++) {
                    if (nodos[z]->color == "") {
                        vector<string> col;
                        cout << nodos[z]->letra << "->";
                        for (int j = 0; j < nodos[z]->lista.size(); j++) {
                            if (nodos[z]->lista[j]->color != "") {
                                col.push_back(nodos[z]->lista[j]->color);
                            }
                        }
                        auto it = find(col.begin(), col.end(), "rojo");
                        if (it == col.end()) {
                            cout << colores[0] << " ";
                        }
                        it = find(col.begin(), col.end(), "verde");
                        if (it == col.end()) {
                            cout << colores[1] << " ";
                        }
                        it = find(col.begin(), col.end(), "azul");
                        if (it == col.end()) {
                            cout << colores[2] << " ";
                        }
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    void restringiva() {
        vector<nodo*> aux = nodos;
        //sort(aux.begin(), aux.end(), _compa);
        cout << "Selecciona tu nodo: ";
        char bus;
        cin >> bus; cout << endl;
        int i = 0;
        for (int in = 0; in < nodos.size(); in++) {
            if (nodos[in]->letra == bus) {
                i = in;
                break;
            }
        }
        bool change = 0, back = 0;;
        while (!(aux.empty())) {
            if (change == 1) {
                i = 0;
            }
            if (back == 1) {
                sort(aux.begin(), aux.end(), compa);
                back = 0;
            }
            int pivot = 0;
            string color = colores[pivot];
            for (int j = 0; j < aux[i]->lista.size(); j++) {
                if (aux[i]->lista[j]->color == color) {
                    pivot++;
                    if (pivot == 3) {
                        cout << "\nBacktracking!!" << endl;
                        back = 1;
                        clean1();
                        break;
                    }
                    color = colores[pivot];
                }
            }
            if (back == 1) {
                aux = nodos;
            }
            else {
                for (int j = 0; j < aux[i]->lista.size(); j++) {
                    if (aux[i]->lista[j]->color == color) {
                        pivot++;
                        if (pivot == 3) {
                            cout << "\nBacktracking!!" << endl;
                            back = 1;
                            aux = nodos;
                            clean1();
                            break;
                        }
                        color = colores[pivot];
                    }
                }
                if (back == 1) {
                    aux = nodos;
                }
                else {
                    for (int j = 0; j < aux[i]->lista.size(); j++) {
                        for (int z = 0; z < aux[i]->lista[j]->colores.size(); z++) {
                            if (aux[i]->lista[j]->colores[z] == colores[pivot]) {
                                auto it = find(aux[i]->lista[j]->colores.begin(), aux[i]->lista[j]->colores.end(), colores[pivot]);
                                aux[i]->lista[j]->colores.erase(it);
                                break;
                            }
                        }
                    }
                    aux[i]->color = color;
                    cout << aux[i]->letra << "=" << aux[i]->color << " ";
                    nodo* temp = aux[i];
                    sort(aux.begin(), aux.end(), _compa);
                    if (i != aux.size() - 1) {
                        for (int z = 0; z < aux.size(); z++) {
                            if (aux[z]->color == "") {
                                vector<string> col;
                                cout << aux[z]->letra << "->";
                                for (int j = 0; j < aux[z]->lista.size(); j++) {
                                    if (aux[z]->lista[j]->color != "") {
                                        col.push_back(aux[z]->lista[j]->color);
                                    }
                                }
                                auto it = find(col.begin(), col.end(), "rojo");
                                if (it == col.end()) {
                                    cout << colores[0] << " ";
                                }
                                it = find(col.begin(), col.end(), "verde");
                                if (it == col.end()) {
                                    cout << colores[1] << " ";
                                }
                                it = find(col.begin(), col.end(), "azul");
                                if (it == col.end()) {
                                    cout << colores[2] << " ";
                                }
                            }
                        }
                    }
                    auto it = find(aux.begin(), aux.end(), temp);
                    aux.erase(it);
                    cout << endl;
                    change = 1;
                }
            }
        }
        cout << endl;
    }
};
grafo uno("rojo", "verde", "azul"); grafo dos("rojo", "verde", "azul");
void display1() {
    glClear(GL_COLOR_BUFFER_BIT); // Borra el buffer de color

    drawLine(-0.8, 0.8, -0.8, 0.36);
    drawLine(-0.8, 0.8, -0.1, 0.8);
    drawLine(-0.8, 0.8, -0.1, 0.36);
    drawLine(-0.8, 0.36, -0.1, 0.36);
    drawLine(-0.1, 0.8, -0.1, 0.36);
    drawLine(-0.1, 0.8, 0.6, 0.58);
    drawLine(-0.1, 0.36, 0.6, 0.58);
    for (int i = 0; i < uno.nodos.size(); i++) {
        char letra = uno.nodos[i]->letra;
        switch (letra) {
        case 'A':
            if (uno.nodos[i]->color == "rojo") {
                drawCircleColor(-0.8, 0.8, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (uno.nodos[i]->color == "verde") {
                drawCircleColor(-0.8, 0.8, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (uno.nodos[i]->color == "azul") {
                drawCircleColor (-0.8, 0.8, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'B':
            if (uno.nodos[i]->color == "rojo") {
                drawCircleColor(-0.8, 0.36, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (uno.nodos[i]->color == "verde") {
                drawCircleColor(-0.8, 0.36, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (uno.nodos[i]->color == "azul") {
                drawCircleColor(-0.8, 0.36, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'C':
            if (uno.nodos[i]->color == "rojo") {
                drawCircleColor(-0.1, 0.8, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (uno.nodos[i]->color == "verde") {
                drawCircleColor(-0.1, 0.8, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (uno.nodos[i]->color == "azul") {
                drawCircleColor(-0.1, 0.8, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'D':
            if (uno.nodos[i]->color == "rojo") {
                drawCircleColor(-0.1, 0.36, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (uno.nodos[i]->color == "verde") {
                drawCircleColor(-0.1, 0.36, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (uno.nodos[i]->color == "azul") {
                drawCircleColor(-0.1, 0.36, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'E':
            if (uno.nodos[i]->color == "rojo") {
                drawCircleColor(0.6, 0.58, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (uno.nodos[i]->color == "verde") {
                drawCircleColor(0.6, 0.58, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (uno.nodos[i]->color == "azul") {
                drawCircleColor(0.6, 0.58, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        default:
            break;
        }
    }
    drawText("A", -0.84, 0.76);
    drawText("B", -0.84, 0.31);
    drawText("C", -0.14, 0.76);
    drawText("D", -0.14, 0.31);
    drawText("E", 0.56, 0.53);
    glFlush(); // Envía todos los comandos al procesador gráfico
}
void display2() {
    glClear(GL_COLOR_BUFFER_BIT); // Borra el buffer de color
    drawLine(-0.85, 0.8, -0.85, 0.36);
    drawLine(-0.85, 0.8, -0.3, 0.8);
    drawLine(-0.85, 0.36, -0.3, 0.36);
    drawLine(-0.3, 0.8, -0.3, 0.36);
    drawLine(-0.85, 0.36, 0.8, 0.58);
    drawLine(-0.3, 0.8, 0.25, 0.8);
    drawLine(-0.3, 0.36, 0.25, 0.36);
    drawLine(-0.3, 0.8, 0.25, 0.36);
    drawLine(0.25, 0.8, 0.25, 0.36);
    drawLine(0.25, 0.8, 0.8, 0.58);
    drawLine(0.25, 0.36, 0.8, 0.58);

    for (int i = 0; i < dos.nodos.size(); i++) {
        char letra = dos.nodos[i]->letra;
        switch (letra) {
        case 'A':
            if (dos.nodos[i]->color == "rojo") {
                drawCircleColor(-0.85, 0.8, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (dos.nodos[i]->color == "verde") {
                drawCircleColor(-0.85, 0.8, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (dos.nodos[i]->color == "azul") {
                drawCircleColor(-0.85, 0.8, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'B':
            if (dos.nodos[i]->color == "rojo") {
                drawCircleColor(-0.85, 0.36, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (dos.nodos[i]->color == "verde") {
                drawCircleColor(-0.85, 0.36, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (dos.nodos[i]->color == "azul") {
                drawCircleColor(-0.85, 0.36, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'C':
            if (dos.nodos[i]->color == "rojo") {
                drawCircleColor(-0.3, 0.8, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (dos.nodos[i]->color == "verde") {
                drawCircleColor(-0.3, 0.8, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (dos.nodos[i]->color == "azul") {
                drawCircleColor(-0.3, 0.8, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'D':
            if (dos.nodos[i]->color == "rojo") {
                drawCircleColor(-0.3, 0.36, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (dos.nodos[i]->color == "verde") {
                drawCircleColor(-0.3, 0.36, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (dos.nodos[i]->color == "azul") {
                drawCircleColor(-0.3, 0.36, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'E':
            if (dos.nodos[i]->color == "rojo") {
                drawCircleColor(0.25, 0.8, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (dos.nodos[i]->color == "verde") {
                drawCircleColor(0.25, 0.8, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (dos.nodos[i]->color == "azul") {
                drawCircleColor(0.25, 0.8, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'F':
            if (dos.nodos[i]->color == "rojo") {
                drawCircleColor(0.25, 0.36, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (dos.nodos[i]->color == "verde") {
                drawCircleColor(0.25, 0.36, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (dos.nodos[i]->color == "azul") {
                drawCircleColor(0.25, 0.36, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        case 'G':
            if (dos.nodos[i]->color == "rojo") {
                drawCircleColor(0.8, 0.58, 0.07, 100, 1.0, 0.0, 0.0);
            }
            else if (dos.nodos[i]->color == "verde") {
                drawCircleColor(0.8, 0.58, 0.07, 100, 0.0, 1.0, 0.0);
            }
            else if (dos.nodos[i]->color == "azul") {
                drawCircleColor(0.8, 0.58, 0.07, 100, 0.0, 0.0, 1.0);
            }
            break;
        default:
            break;
        }
    }
    // Dibuja una frase utilizando la función drawText
    drawText("A", -0.89, 0.76);
    drawText("B", -0.89, 0.31);
    drawText("C", -0.34, 0.76);
    drawText("D", -0.34, 0.31);
    drawText("E", 0.21, 0.76);
    drawText("F", 0.21, 0.31);
    drawText("G", 0.76, 0.54);
    glFlush(); // Envía todos los comandos al procesador gráfico
}

int main(int argc, char** argv) {
    nodo A('A');
    nodo B('B');
    nodo C('C');
    nodo D('D');
    nodo E('E');
    nodo F('F');
    nodo G('G');
    cout << "Selecciona el ejemplo:\n1. De 5 nodos\n2. De 7 nodos\n:";
    int example, caso;
    cin >> example; cout << endl;
    if (example == 1) {
        caso = 1;
        uno.nodos.push_back(&A);
        uno.nodos.push_back(&B);
        uno.nodos.push_back(&C);
        uno.nodos.push_back(&D);
        uno.nodos.push_back(&E);
        uno.conectar(A, B);
        uno.conectar(A, D);
        uno.conectar(A, C);
        uno.conectar(B, D);
        uno.conectar(C, D);
        uno.conectar(C, E);
        uno.conectar(D, E);
        cout << "Selecciona la heuristica:\n1. Restrictiva\n2. Restringida\n:";
        cin >> example; cout << endl;
        if (example == 1) {
            cout << "Ejemplo 1 Restrictiva" << endl;
            uno.restrictiva();
        }
        else {
            cout << "Ejemplo 1 Restringida" << endl;
            uno.restringiva();
        }
    }
    else {
        
        dos.nodos.push_back(&A);
        caso = 2;
        dos.nodos.push_back(&B);
        dos.nodos.push_back(&C);
        dos.nodos.push_back(&D);
        dos.nodos.push_back(&E);
        dos.nodos.push_back(&F);
        dos.nodos.push_back(&G);
        dos.conectar(A, B);
        dos.conectar(A, C);
        dos.conectar(B, G);
        dos.conectar(B, D);
        dos.conectar(D, C);
        dos.conectar(F, C);
        dos.conectar(E, C);
        dos.conectar(F, D);
        dos.conectar(F, E);
        dos.conectar(G, E);
        dos.conectar(G, F);
        cout << "Selecciona la heuristica:\n1. Restrictiva\n2. Restringida\n:";
        cin >> example; cout << endl;
        if (example == 1) {
            cout << "Ejemplo 2 Restrictiva" << endl;
            dos.restrictiva();
        }
        else {
            cout << "Ejemplo 2 Restringida" << endl;
            dos.restringiva();
        }
    }
    glutInit(&argc, argv); // Inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Configura el modo de visualización
    glutInitWindowSize(700, 700); // Configura el tamaño de la ventana
    glutInitWindowPosition(100, 100); // Configura la posición de la ventana
    glutCreateWindow("Circulo OpenGL"); // Crea la ventana con el título especificado
    init(); // Llama a la función de inicialización
    if (caso == 1)
        glutDisplayFunc(display1); // Establece la función de visualización
    else
        glutDisplayFunc(display2);
    glutMainLoop(); // Inicia el bucle principal de GLUT
    return 0;
}

