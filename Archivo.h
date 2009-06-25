#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>

using namespace std;

class Archivo
{
    public:
        Archivo(const char []);
        Archivo(int);
        ~Archivo();
        string getLinea(int) const;
        void setLinea(int, const string &);
        int getCantLineas() const;
        bool isOpen() const;
        static int nroLineas(ifstream &);
    private:
        bool errorAbrir;
        int cantLineas;
        string * lineas;
};

#endif // ARCHIVO_H
