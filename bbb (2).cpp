#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

int ref(int n){
    if(n==0 || n==1){
        return n;
    }
    else{
        return (ref(n-1)+ref(n-2));
    }
}

long long modref(int n, long long ar[]){
    if(ar[n] != -1){
        return ar[n];
    }
    if(n==0 || n==1){
        ar[n] = n;
        return n;
    }
    ar[n] = modref(n-1, ar) + modref(n-2, ar);
    return ar[n];
}

long long nref(int n){
    int f[100];
    f[0]=0; f[1]=1;
    for(int i = 2; i<=n; i++){
        f[i]=f[i-1]+f[i-2];
    }
    return f[n];
}

int main() {
    int n[]={1,5,10,15,20,25,30,35,40,45,50,55,60};
    cout<<"Integer\t\t\tFiboR(seconds)\t\t\tMODFibR\t\t\tFiboNR(seconds)\t\t\tFibo-value"<<endl;
    
    for(int i = 0; i < 13; i++){
        int ni = n[i];
        clock_t start, end;
        
        start = clock();
            ref(ni);
        end = clock();
        double r_time = (double)(end - start) / CLOCKS_PER_SEC;
        
        long long ar[100];
        for(int j = 0; j < 100; j++){
            ar[j] = -1;
        }
        start = clock();
        long long mod_r = modref(ni, ar);
        end = clock();
        double m_time = (double)(end - start) / CLOCKS_PER_SEC;
        
        start = clock();
        nref(ni);
        end = clock();
        double n_time = (double)(end - start) / CLOCKS_PER_SEC;
        
         cout<<ni<<"\t\t\t"<<fixed<<setprecision(6)<<r_time<<"\t\t\t"<<m_time<<"\t\t"<<n_time<<"\t\t\t"<<mod_r<<endl;
    }
    return 0;
}