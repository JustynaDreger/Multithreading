//lab1 - mnożenie 3 macierzy A*B*C

#include<iostream>
#include<thread>
#include<ctime>
#include<cstdlib>
using namespace std;

//tworzy macierz
int **stworz_m(int n){
	int **A=new int*[n];
	for(int i=0;i<n;i++)	A[i]=new int[n];
	return A;
}

//wypełnij macierz losowymi
int **wypelnij(int **A, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			A[i][j]=rand()%10;
			//A[i][j]=2;
			//cout<<A[i][j]<<endl;
		}
	}
	return A;
}

//funkcja do wątków - mnożenie dla jednej komórki
void licz(int i,int j,int **A, int**B,int **C, int n){
	C[i][j]=0;
	for (int k = 0; k < n; k++)	C[i][j] = C[i][j] + A[i][k]*B[k][j];
}

int main(){
	int n=100;
	int **A,**B,**C,**D,**E;//A,B,C - wejściowe  E - wyjściowa
	thread T1[n][n];//tablice wątków
	thread T2[n][n];
	A=stworz_m(n);
	B=stworz_m(n);
	C=stworz_m(n);
	D=stworz_m(n);
	E=stworz_m(n);
	srand(time(NULL));
	A=wypelnij(A,n);
	B=wypelnij(B,n);
	C=wypelnij(C,n);
	//pierwsze mnożenie - A*B
	//cout<<"Pierwsze"<<endl;
	int ile1=0;
	for (int i = 0; i < n; i++) {
			      for (int j = 0; j <n; j++) {
			    	  T1[i][j]= thread (licz,i,j,A,B,D,n);   //wstawianie wątków do tablicy
			    	  ile1++;
			      }
			    }
	//cout<<licznik<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) 	 T1[i][j].join();
	}


	//drugie mnożenie - (A*B)*C
	//cout<<"Drugie"<<endl;
		int ile2=0;
		for (int i = 0; i < n; i++) {
			      for (int j = 0; j <n; j++) {
			    	  T2[i][j]= thread (licz,i,j,D,C,E,n);   //wstawianie wątków do tablicy
			    	  ile2++;
			      }
			    }
		//cout<<licznik<<endl;
		for(int i=0;i<n;i++){
				for(int j=0;j<n;j++) 	 T2[i][j].join();
			}

		for (int i= 0; i < 2; i++) {
			      for (int j = 0; j < 2; j++)	cout<<E[i][j]<<" ";
			      cout<<"..."<<endl;
			    }
		cout<<"..."<<endl;
	//usuwanie macierzy
	for(int i=0;i<n;i++)	delete[] A[i];
	for(int i=0;i<n;i++)	delete[] B[i];
	for(int i=0;i<n;i++)	delete[] C[i];
	delete[] A;
	delete[] B;
	delete[] C;
	return 0;
}
