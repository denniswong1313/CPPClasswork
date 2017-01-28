// array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


int isEmptyString(string a[], int n, int pos){
	if (pos < 0)
		return -1;

	if (n < pos)
		return -1;

	if (a[pos] == "")
		{
			return 1;
		}
	else
		{
			return 0;
		}
}

int toUpperCase(string a[], int n, int pos){
	if (pos < 0)
		return -1;

	for (int i=0; i < a[pos].size(); i++){
	{
		if ((a[pos][i] >= 97) && (a[pos][i] <= 122))
		{
			a[pos][i] -= 32;
		}

			
		}
		

	}
	return pos;

}

int toLowerCase(string a[], int n, int pos){
	if (pos < 0)
		return -1;

	for (int i=0; i < a[pos].size(); i++){
	{
		if ((a[pos][i] >= 65) && (a[pos][i] <= 90))
		{
			a[pos][i] += 32;
		}

			
		}
		

	}
	return pos;

}

bool matchChecker(string a, string b){
	bool something = true;

	for (int i = 0; i < b.size(); i++){
		if (a[i] != b[i])
		{
			something = false;
		}
	} 
	return something;
}


int find(const string a[], int n, string target){
	
	for (int i = 0; i < n; i++){
		if (a[i].size() == target.size())
		{
			if (matchChecker(a[i], target) == true)
				return i;
		}
		
}
	return -1;
}

int findMin(const string a[], int n){
	if (n <= 0)
		return -1;

	int count = 0;
	string test = a[count];

	for (int i = 0; i < n; i++) {
		if (a[i] <= test)
		{
			test = a[i];
			count = i;
		}
		
	}
	return count;
}

int findAny(const string a1[], int n1, const string a2[], int n2){

	for (int i = 0; i < n1; i++){
		
		for (int j = 0; j < n2; j++){

			if (a1[i].size() == a2[j].size())
			{
				if (matchChecker(a1[i], a2[j]) == true)
					return i;
			}

	}

	}
	return -1;
}


int rotateLeft(string a[], int n, int pos){
	if (pos < 0)
		return -1;

	if (n <= 0)
		return -1;

	if (n < pos)
		return -1;

	string freeze = a[pos];

	for (int i = pos; i < n-1; i++){
		a[i] = a[i+1];
	}

	
	a[n-1] = freeze;
	return pos;
}

int rotateRight(string a[], int n, int pos){
	
	if (pos < 0)
		return -1;

	if (n <= 0)
		return -1;

	if (n < pos)
		return -1;

	string freeze = a[pos];

	for (int i = pos; i > 0; i--){
		a[i] = a[i-1];
	}

	
	a[0] = freeze;
	return pos;
}


int subsequence(const string a1[], int n1, const string a2[], int n2){
	if ((n1 < 0) || (n2 < 0))
		return -1;

	for (int i = 0; i < n1; i++){
	
		for (int j = 0; j < n2; j++){
			
			if (a2[j].size() == a1[i].size())
			{
				if (matchChecker(a1[i],a2[j]) == true)
				{
					int start = i;

					for (int x = i +1, y = j + 1; x < n1 && y < n2; x++, y++){

						if (a2[j].size() != a1[i].size())
						{
							return -1;
						}
					}
					return start;
				}
			}
		}
	}
}
		

int sort(string a[], int n){
	if (n < 0)
		return -1;

	string first;
	for (int i = 0; i < n; i++){
		
		for (int j = 0; j < n-1; j++){
			if (a[j] > a[j+1])
			{
				first = a[j];
				a[j] = a[j+1];
				a[j+1] = first;
			}
		
	}
	return n;
}
}

int convertStringToInt(string a[], int n, int pos, int &val){
	if (pos < 0)
		return -1;
	if (n < pos)
		return -1;
	
	for (int i= 0; i < a[pos].size(); i++){
		

		if (((a[pos][i] >= '0') && (a[pos][i] <= '9')) || (a[pos][0] == 45))
		{
			val = 0;
			int j = 1;
			for (int i = a[pos].size(); i > 0; i--, j*=10){
				val += ((a[pos][i-1]) - '0')*j;
				}
			
		}
		else
		{
			return -1;
		}
		//if (a[pos][0] == 45)
		//{
		//		val *= -1;
		//}
	}
	return 0;
}

int main(){
	string lul[7] = {"ZOO","Pee","poo","skee", "doo","boo","shoo"};
	string bang[3] = {"skee","doo","boo"};
	string numeros[3] = {"947","0","2chainz"};
	string test = "Poo";

	int val = 0;
	cout << toLowerCase(lul, 7, 0) << endl;
	cout << lul[0] << endl;
	/*cout << lul[0] << endl;
	cout << lul[1] << endl;
	cout << lul[2] << endl;
	cout << lul[3] << endl;
	cout << lul[4] << endl;
	cout << lul[5] << endl;
	cout << lul[6] << endl;*/

	
	return 0;
}
