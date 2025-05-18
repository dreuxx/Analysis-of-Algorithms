#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long Inser(int A[], int n) {
    int i, j, temp;
    int comp = 0;
    A[0] = -32768;
    for (i = 1; i <= n; i++) {
        j = i;
        while (A[j] < A[j-1]) {
            comp++;
            
            temp = A[j];
            A[j] = A[j-1];
            A[j-1] = temp;
            j--;
        }
        comp++;
    }
    return comp;
}
void CrearSec(int A[], int n) {
    for (int i = 1; i <= n; i++) {
        A[i] = rand() % 10001;
    }
}
int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int tin[] = {100, 500, 1000, 2500, 3000, 3500};
    int can = 6;
    cout<<"Input size\t\t\tCalculated Average\t\t\tReal Average"<<endl;
    for (int t = 0; t < can; t++) {
        int n = tin[t];
        float teorico = (n * (n + 1)) / 4.0;
        long long total = 0;
        int pruebas = 100000;
        
        for (int p = 0; p < pruebas; p++) {
            int* numeros = new int[n + 1];
            CrearSec(numeros, n);
            total += Inser(numeros, n);
            delete[] numeros;
        }
        float real = (float)total / pruebas;
        cout<< n <<"\t\t\t\t\t"<< teorico <<"\t\t\t\t\t\t"<< real << endl;
    }
    
    return 0;
}