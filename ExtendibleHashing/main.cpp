#include "menuFifa.h"
using namespace std;


int main() {
    try
    {
        // check if fifa.dat exists
        ifstream fin("fifa.dat", ios::binary);
        if (!fin.is_open())
        {
            cout << "File not found. Creating new file..." << endl;
            buildFifa();
        }
        fin.close();
        cout << search("Pele") << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // read_record_dat(71);
}