#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
using namespace std;

//float C; //random process
float A[5][6]; //our matrix
float B[5][5]; //matrix of random tracing
float W[5];    //values needed for tracing
int N; //order of matrix
int i, j; //index
int Eq; //needed equation
int M; //number of random realisations
int T = 1, Y = 1,
S = Eq;
int V = 1; //simple value for sign
float X; // koren`

void func200();
void func180();
int sign(float);

void main(){

	

	cout << "Input order of matrix [N]:";
	cin >> N;

	//float A[5][6] = { { 0.5714, -0.1429, 0.1429, 0.2857 }, { -0.1, 0.6, 0.2, 0.3 }, {-0.087, 0.0435, 0.7826, 0.6522} };
	cout << "\n Input indexes of matrix: \n";
	for (i = 1; i <= N; i++){
		cin >> A[i][1];
		B[i][1] = abs(A[i][1]);
		for (j = 2; j <= N; j++){
			cin >> A[i][j];
			B[i][j] = B[i][j - 1] + abs(A[i][j]);
		}
		cin >> A[i][N + 1];
		cout << " The "<< i << " row end!\n";
	};



	cout << "\n Our matrix A: \n";
	for (i = 1; i <= N; i++){
		for (j = 1; j <= (N+1); j++)
			cout << A[i][j] << " ";
		cout << "\n";
	}
	cout << "\n Our matrix B: \n";
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++)
			cout << B[i][j] << " ";
		cout << "\n";
	}

	for (i = 1; i <= N; i++){
		W[i] = A[i][N + 1] / (1-B[i][N]);
	}

	cout << "\n Vector W: \n";
	for (i = 1; i <= N; i++)
		cout << " " << W[i];
	cout << "\n";

	cout << "\nInput number of need i [Eq]:";
	cin >> Eq;
	cout << "\nInput number of random realisations [M]:";
	cin >> M;
	S = Eq;
	func200();
	
	
	



	system("pause");
	return;
}
void func200(){
	//C = rand() % 1;
	
	bool repeat = true,
		denied;

	

	while (repeat){
		denied = false;
		srand(time(NULL));
		float C = (float)(rand()%9999)/(float)10000;
		for (j = N; N > 1; j--){
			if (C <= B[S][j]) continue;
			if (j == N) { 
				T = T + 1; 
				Y = Y + V*W[S]; 
				func180(); 
				repeat = false; 
				break;
			}
			else {
				V = V*sign(A[S][j + 1]);
				S = j + 1;
				denied = true;
				break;
			}
			

		}
		if (!denied) {
			V = V*sign(A[S][1]);
			S = 1;
		}
	}
	
}
void func180(){
	S = Eq;
	Y = 1;
	if (T > M) {
		X = (float)Y / (float)M;
		cout << "Our value of " << Eq << " equation is " << X;
	}
	else func200();

}
int sign(float value){
	if (value > 0) return 1;
	if (value < 0) return -1;
	return 0;
}




