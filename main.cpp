#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>

using namespace std;

void quicksort(string* dane[], double a[], int lewy, int prawy)
{
    if (prawy <= lewy){return;}

    int i = lewy - 1, j = prawy + 1;
    double pivot = a[(lewy + prawy) / 2];

    while (1)
    {
        while (pivot > a[++i]);

        while (pivot < a[--j]);

        if (i <= j){
            swap (a[i], a[j]);
            swap (dane[i], dane[j]);
        }
        else{
            break;
        }

    }

    if (j > lewy){
        quicksort(dane, a, lewy, j);
    }
    if (i < prawy){
        quicksort(dane, a, i, prawy);
    }
}

void insertionsort(string* dane[], double a[], int low, int high)
{
    string s[3];
    double value;

    for (int i = low + 1; i <= high; i++)
    {
        value = a[i];
        for (int k=0; k<3; ++k){
            s[k] = dane[i][k];
        }

        int j = i;

        while (j > low && a[j - 1] > value)
        {
            a[j] = a[j - 1];
            for (int k=0; k<3; ++k){
                dane[j][k] = dane[j-1][k];
            }
            j--;
        }

        a[j] = value;
        for (int k=0; k<3; ++k){
            dane[j][k] = s[k];
        }

    }
}

void introsort(string* dane[], double a[], int lewy, int prawy)
{
    if ((prawy - lewy) < 8) {
        insertionsort(dane, a,  lewy, prawy);
    }
    else {

    int i = lewy - 1, j = prawy + 1;
    double pivot = a[(lewy + prawy) / 2];

    while (1)
    {
        while (pivot > a[++i]);

        while (pivot < a[--j]);

        if (i <= j){
            swap (a[i], a[j]);
            swap (dane[i], dane[j]);
        }
        else{
            break;
        }

    }

    if (j > lewy){
        introsort(dane, a, lewy, j);
    }
    if (i < prawy){
        introsort(dane, a, i, prawy);
    }
    }
}

void Merge(string* dane[], double arr[], int p, int q, int r, string* Ls[], string* Ms[]) {

    int n1 = q - p + 1;
    int n2 = r - q;

    double* L = new double[n1];
    double* M = new double[n2];

    for (int i = 0; i < n1; i++){
        L[i] = arr[p + i];
        Ls[i] = dane[p + i];
    }

    for (int j = 0; j < n2; j++){
        M[j] = arr[q + 1 + j];
        Ms[j] = dane[q + 1 + j];
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            dane[k] = Ls[i];
            i++;
        } else {
            arr[k] = M[j];
            dane[k] = Ms[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        dane[k] = Ls[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        dane[k] = Ms[j];
        j++;
        k++;
    }
}

void mergeSort(string* dane[], double arr[], int l, int r, string* Ls[], string* Ms[]) {
  if (l < r) {

    int m = l + (r - l) / 2;

    mergeSort(dane, arr, l, m, Ls, Ms);
    mergeSort(dane, arr, m + 1, r, Ls, Ms);

    Merge(dane, arr, l, m, r, Ls, Ms);
  }
}

int binpoisk(string* daneRef[], string dane, int n)
{
    int left=0, right=n, midd;

    while(left <= right){
        midd = (left + right) / 2;
        //cout << dane << ' ' << daneRef[left][0] << ' ' << daneRef[midd][0] << ' ' << daneRef[right][0] << endl;
        if(daneRef[midd][0] == dane){
            return midd;
        }
        else if(((daneRef[midd][0] > dane) && (daneRef[midd][0].size() == dane.size())) || (daneRef[midd][0].size() > dane.size())){
            right = midd ;
        }
        else left = midd ;
    }
    return -1;
}

int poprawnoscSort(double a[], int n)
{
    int error = 0;
    for(int i=0; i<n-1; ++i){
        if(a[i]>a[i+1]){
            ++error;
        }
    }
    return error;
}

int main() {

    ifstream dane_do_posort ("dane_do_posort.tsv");
    ifstream dane_referenc ("referencyjne.txt");
    ofstream posort ("sort.txt");

    int n, m, nref = 9735226;
    double sum;

    string** daneRef = new string*[nref];
    string line, cell, nazw_kol_pos, nazw_kol_ref, l[9];
    getline(dane_referenc, nazw_kol_ref);
    for (int i=0; i<nref; ++i){
        daneRef[i] = new string[2];
        getline(dane_referenc, line);
        stringstream ss(line);
        getline(ss, cell, '\t');
        cell.erase(remove_if(cell.begin(), cell.end(), ::isspace), cell.end());
        daneRef[i][0] = cell;
        getline(ss, cell, '\n');
        daneRef[i][1] = cell;
    }

        cout << "Wyberz sposob sortowania" << endl;
        cout << "1. Quick sort" << endl;
        cout << "2. Intro sort" << endl;
        cout << "3. Merge sort" << endl;
        cout << "0. Koniec programy" << endl;
        cout << "Twoj wybor: ";
        cin >> m;
        if(m==0){
            return 0;
        }
        else{
            cout << "Podaj ile: ";
             cin >> n;
        }


        string** dane = new string*[n];
        string** Ls = new string*[n];
        string** Ms = new string*[n];
        double* a = new double[n];

        getline(dane_do_posort, nazw_kol_pos);


        for (int i=0; i<n; ++i){
            dane[i] = new string[3];
            Ls[i] = new string[3];
            Ms[i] = new string[3];
            for (int j=0; j<3; ++j){
                dane_do_posort >> dane[i][j];
            }
            a[i]= stof(dane[i][1]);
        }

        cout << endl << endl;
        double start = clock();

        switch(m){
            case 1:{
                quicksort(dane, a, 0, n - 1);
                break;
            }

            case 2:{
                introsort(dane, a, 0, n - 1);
                break;
            }

            case 3:{
                mergeSort(dane, a, 0, n-1, Ls, Ms);
                break;
            }
            default:{
                cout << "Niepoprawna liczba" << endl;
                return 1;
            }
        }

        double finish = clock();
        cout << " Czas dzialania:" << finish - start << " ms" << endl;

        int index;
        start = clock();

        for (int i=0; i<n; ++i){

            index = binpoisk(daneRef, dane[i][0], nref-1);
            if(index == -1){cout << i << ' ' << dane[i][0] << endl;}
            else{
                posort << daneRef[index][0] << " |  | " << dane[i][0] << ' ' << dane[i][1] << ' ' << dane[i][2]  << ' ' << daneRef[index][1] << endl;
            }

        }
        finish = clock();

        sum = 0;
        for (int i=0; i<n; ++i){
            sum = sum + a[i];
        }
        cout << " Sr. wartosc: " << sum/n << endl;
        cout << " Mediana: ";
        if(n%2 == 0){
            cout << (a[n/2] + a[n/2+1])/2 << endl;
        }
        else{
            cout << a[n/2+1] << endl << endl;
        }

  return 0;
}

