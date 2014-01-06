#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
using namespace std;

float perm[5][6] = { {0, 0, 0, 0, 0 }, 
		{ 0, 3, 1, -1, -2 }, 
		{ 0, 1, 4, -2, -3 }, 
		{ 0, 2, -1, 5, -15 }
	};
float A[5][6]; //our matrix
/*float A[5][6] = { {0, 0, 0, 0, 0 }, 
		{ 0, 0.5714, -0.1429, 0.1429, 0.2857 }, 
		{ 0, -0.1, 0.6, 0.2, 0.3 }, 
		{ 0, -0.087, 0.0435, 0.7826, 0.6522 }
	};*/
float B[5][5]; //matrix of random tracing
float W[5];    //values needed for tracing
int N; //order of matrix
int EQ_NUM; //needed equation
int M; //number of random realisations
bool done = false;



int sign(float);
void convert_matrix();
void OneMoreTime(bool,int,int,int,float);
void sec(bool,int,int,int,float);

void main(){
	int i, j;
	

	cout << "Input order of matrix [N]:";
	cin >> N;
	
	convert_matrix();
	/*float A[5][6] = { {0, 0, 0, 0, 0 }, 
		{ 0, 0.5714, -0.1429, 0.1429, 0.2857 }, 
		{ 0, -0.1, 0.6, 0.2, 0.3 }, 
		{ 0, -0.087, 0.0435, 0.7826, 0.6522 }
	};*/
	cout << "\n Input indexes of matrix: \n";
	for (i = 1; i <= N; i++){
		//cin >> A[i][1];
		B[i][1] = abs(A[i][1]);
		for (j = 2; j <= N; j++){
			//cin >> A[i][j];
			B[i][j] = B[i][j - 1] + abs(A[i][j]);
		}
		//cin >> A[i][N + 1];
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
	cin >> EQ_NUM;
	cout << "\nInput number of random realisations [M]:";
	cin >> M;
	
	sec(true, EQ_NUM, 0, 1, 0);
	



	system("pause");
	return;
}

int sign(float value){
	if (value > 0) return 1;
	if (value < 0) return -1;
	return 0;
}

void OneMoreTime(bool enter, int trace, int num_times, int val_sign, float val_of_eq){
	if (done) {
		return;
	} else {
		cout << "false" << endl;
	}
	int s = trace;
	bool cond = enter;
	int t = num_times;
	int v = val_sign;
	float y = val_of_eq;
	int final_val;

	
	if (cond){
		if (t > M) {
			if (y == 0) y = 1;
			final_val = y / M;
			
			done = true;
			return;
		}
		cond = false;
	}
	//random process
	srand(time(NULL));
	float test = rand();
	float c = (float)(rand() % 9999) / (float)10000;

	for (int j = N; j > 1; j--){
		if (c <= B[s][j]) continue;
		if (j == N) {
			t++;
			y += v*W[s];
			OneMoreTime(true, s, t, v, y);
		}
		else{
			v *= sign(A[s][j + 1]);
			OneMoreTime(false, j + 1, t, v, y);
		}
		
	}
	v *= sign(A[s][1]);
	OneMoreTime(false, 1, t, v, y);
}

void sec(bool enter, int trace, int num_times, int val_sign, float val_of_eq){
	if (done) {
		return;
	} else {
		cout << "false" << endl;
	}
	int s = trace;
	bool cond = enter;
	int t = num_times;
	int v = val_sign;
	float y = val_of_eq;
	float final_val;

l180:
	s = trace;
	//y = 1;
	if (t > M) {
		goto l260;
	}
	srand(time(NULL));
	float test = rand();
l200:
	float c = (float)(rand() % 9999) / (float)10000;
	for (int j = N; j > 0; j--) {
		if (c <= B[s][j]) continue;
		if (j == N) {
			t++;
			y += v*W[s];
			goto l180;
		} else {
			v *= sign(A[s][j+1]);
			s = j + 1;
			goto l200;
		}
	}
l260:
	final_val = (float)y / (float)M;
	cout << "Value of equation is X=" << final_val << endl;
}
void convert_matrix(){
	float sum;
	int i, j;
	for (i = 1; i <= (N + 1); i++){
		sum = 0;
		for (j = 1; j <= (N + 1); j++){
			sum += abs(perm[i][j]);
		};
		if (perm[i][i] > 0) {
			for (j = 1; j <= (N + 1); j++) {
				if (j != i)
					A[i][j] = (float)perm[i][j] / (float)(-sum);
				else
					A[i][j] = (float)perm[i][j] / (float)(-sum) + 1;
			}
		}
		else {
			for (j = 1; j <= (N + 1); j++) {
				if (i != j) 
					A[i][j] = (float)perm[i][j] / (float)sum;
				else 
					A[i][j] = (float)perm[i][j] / (float)sum + 1;
			}
		}
	}
}


