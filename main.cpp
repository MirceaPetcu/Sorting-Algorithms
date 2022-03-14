#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
void shellsort(vector<unsigned int > &v, int n,int &interval) {
    if (interval > 0) {
        for (int i = interval; i < n; i++) {
            int aux = v[i];
            int j;
            j = i;
            while(j >= interval && v[j - interval] > aux)
            {v[j] = v[j - interval];
            j -= interval;}

            v[j] = aux;
        }
        interval /=2;
        shellsort(v,n,interval);
    }
}

void selection_sort(vector<unsigned int > &v)
{
    for(int i = 0;i<v.size()-1;i++)
        for(int j = i+1;j<v.size();j++)
            if(v[i]>v[j])
            {
                int aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
}
int nr_cifre(int x){
    int nr = 0;
    int y = x;
    while (y)
    {
        nr++;
        y/=10;
    }
    if (x == 0) return 1;
    else
        return nr;
}

void countingsort(vector<unsigned int> &v) {
    int mx;
    mx = 0;
    for (int i = 0; i < v.size(); i++) {
        if (mx < v[i])
            mx = v[i];
    }
    int frecv[mx + 1];
    for (int j = 0; j <= mx; j++) { frecv[j] = 0; }
    for (int i = 0; i < v.size(); i++) { frecv[v[i]]++; }
    int k = 0;
    for (int i = 0; i <= mx; ++i) {
        for (int j = 0; j <= frecv[i]-1; j++) {
            v[k++] = i;
        }
    }
}

void radixsort(vector<unsigned int> &v) {
    int i, j, k, mx = 0;
    vector<unsigned int > a;
    vector<vector<unsigned int>> b(10);
    for (i = 0; i < v.size(); i++)
        if (mx < v[i])
            mx = v[i];
    int p = 1;
    while (p <= mx) {
        for (i = 0; i < v.size(); i++)
            if (nr_cifre(v[i])>= nr_cifre(p))
                b[v[i] / p % 10].push_back(v[i]);
        for (i = 0; i < 10; i++) {
            for (j = 0; j < b[i].size(); j++)//aici
                for (k = j + 1; k < b[i].size(); k++)
                    if (b[i][j] > b[i][k])
                    {int aux = b[i][j];
                        b[i][j]=b[i][k];
                        b[i][k]=aux;}

        }
        k = 0;
        if (a.empty()==0)
            for (i = 0;i<a.size();i++)
                v[k++]=a[i];

        for (i = 0;i<10;i++)
        {for (j = 0;j<b[i].size();j++)
            {v[k++]=b[i][j];}}
        for (i = 0;i<v.size();i++)
            if (nr_cifre(v[i])== nr_cifre(p))
                a.push_back(v[i]);
        countingsort(a);



        for (i = 0;i<10;i++)
            b[i].clear();

        p *=10;
    }
}



void mergesort(vector<unsigned int> &v,int st,int dr)
{   int i,j;
    if (st<dr)
    {
        int mij = st + (dr-st)/2;
        mergesort(v,st,mij);
        mergesort(v,mij+1,dr);
        i = st;j = mij+1;
        vector<unsigned int > a;
        while (i<=mij && j<=dr)
        {
            if (v[i]<v[j])
            { a.push_back(v[i]);
                i++;}
            else
            {a.push_back(v[j]);
                j++;}
        }
        while (i<=mij)
        { a.push_back(v[i]);
            i++;}

        while (j<=dr)
        {a.push_back(v[j]);
            j++;}
        i = st;
        j = 0;
        while (i<=dr){
            v[i]=a[j];
            i++;j++;
        }



    }
}

bool is_sorted(vector<unsigned int > v,int n)
{
    int i;
    if (v.size()!=n)
        return false;
    i = 1;
    int ok = 1;
    while (i<n && ok == 1)
    {
        if (v[i]<v[i-1])
            ok = 0;
        i++;
    }
    if (ok) return true;
    else
        return false;
}
int main()
{

    unsigned long long input[8][2] = {{10,10},{1000000,100},{100,1000000},{100000000,1000},{1000000000,10000},{1000000,1000000},{100,100},{10,1000000000}};
    int n,mx,interval,i,j;
    vector<unsigned int> v;
    srand((unsigned int) time(NULL));
        cout<<"alegeti numarul de elemente si numarul maxim din vector din array-ul de input: ";
        int nr_el,nr_mx;
        cin>>nr_el>>nr_mx;
        n = input[nr_el][0];
        mx = input[nr_mx][1];
        cout << "algoritmul va rula pentru " << n << " numere cu numere pana la  " << mx << endl;

        i = 0;
        do {
            int a = rand() % mx;
            v.push_back(a);
            i++;
        } while (i < n);
        int number = 1;
        while (number < 7) {
            interval = n / 2;
            auto start = high_resolution_clock::now();
            switch (number) {
                case 1:
                    mergesort(v, 0, n - 1);
                    cout << "mergesort" << endl;
                    break;
                case 2:
                    radixsort(v);
                    cout << "radixsort" << endl;
                    break;
                case 3:
                    shellsort(v, n, interval);
                    cout << "shellsort" << endl;
                    break;
                case 4:
                    countingsort(v);
                    cout << "countingsort" << endl;
                    break;
                case 5:
                    selection_sort(v);
                    cout << "selectionsort" << endl;
                    break;
                case 6:
                    sort(v.begin(), v.end());
                    cout << "c++_sort" << endl;
                    break;
                default:
                    break;

            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            cout << "Timp de rulare: "
                 << duration.count() << " microseconds" << endl;
            cout<<"Vectorul este: ";
            if (is_sorted(v, n)) cout << "sortat";
            else cout << "nesortat";
            cout << endl;
            number++;
        }



    return 0;


}
