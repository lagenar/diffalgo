#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>

using namespace std;

class Archivo
{
    public:
        Archivo(ifstream &);
        ~Archivo();
        string getLinea(int) const;
        void setLinea(int, const string &);
        int getCantLineas() const;
        void guardarArchivo(ostream &);
        static int nroLineas(ifstream &);
    private:
        int cantLineas;
        string * lineas;
};

#endif // ARCHIVO_H
