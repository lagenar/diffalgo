#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>

using namespace std;

class Archivo
{
    public:
        Archivo(ifstream &);
        ~Archivo();
        string getLinea(int);
        void setLinea(int, string);
        static int nroLineas(ifstream &);
        int getCantLineas();
    private:
        int cantLineas;
        string * lineas;
};

#endif // ARCHIVO_H
