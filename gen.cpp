#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    ofstream out;
    out.open("text.txt");

    string t = "abcdefgioh";
    unsigned long long i = 0;

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            for(int x=0; x<10; x++) {
                for(int y=0; y<10; y++) {
                    for(int z=0; z<10; z++) {
                        for(int k=0; k<10; k++) {
                            for(int p=0; p<10; p++) {
                                out << i << " " <<  i << endl;
                                i++;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Finish..." << endl;
    out.close();
    return 0;
}