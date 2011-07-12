/*
# @author Sinu John
#         sinuvian at gmail dot com
#         www.sinujohn.wordpress.com
#

#
# Usage:
#       ./findwords inputfile
#
#         
*/
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

int search(char **mat, int m, int n, int row, int col, char *str, int dir) {
	if(*str=='\0') return 1;
	if(row>m-1 || row<0 || col>n-1 || col<0) return 0;
	
	int found = 0;
	switch(dir) {
		case 1: found = search(mat, m, n, row-1, col-1, str+sizeof(char), dir);
			break;
		case 2:	found = search(mat, m, n, row-1, col, str+sizeof(char), dir);
			break;
		case 3: found = search(mat, m, n, row-1, col+1, str+sizeof(char), dir);
			break;
		case 4: found = search(mat, m, n, row, col-1, str+sizeof(char), dir);
			break;
		case 5:	found = search(mat, m, n, row, col+1, str+sizeof(char), dir);
			break;
		case 6: found = search(mat, m, n, row+1, col-1, str+sizeof(char), dir);
			break;
		case 7: found = search(mat, m, n, row+1, col, str+sizeof(char), dir);
			break;
		case 8: found = search(mat, m, n, row+1, col+1, str+sizeof(char), dir);
			break;
		default: cout<<"ERROR";
	}
	if(found)
		if(mat[row][col]==*str) found = 1;
		else found = 0;
	
	return found;
}

int main(int argc, char **argv) {
	if(argc<2){
		cout<<"Please specify an input file\n";
		return -1;
	}
	
	ifstream fin(argv[1]);
	int m, n, lcol=0, lrow=-1;
	char t, pt=0;
	int matOver=0;
	int i=0, j, k;
	m=n=0;
	
	while(fin){
		if(!matOver) {
			fin.get(t);
			if(t!='\n') n++;
			else if(t=='\n' && pt=='\n') {
				n = n / m;
				matOver=1;
			}
			else m++;
			pt = t;
		}
		if(matOver) {
			fin.get(t);
			if(t!='\n') {  i++; }
			else {
				if(i>lcol) lcol=i;
				i=0;
				lrow++;
			}
		}
	}
	lcol++;
	lrow+=20;
	#ifdef DEBUG
	cout<<"m="<<m<<"\nn="<<n<<"\n";
	cout<<"lcol="<<lcol<<"\nlrow="<<lrow<<"\n";
	#endif
		
	char **mat, **list, **result, *tstr;
	mat = new char *[m];
	for(i=0; i<m; i++) mat[i] = new char[n];
	
	list = new char *[lrow];
	for(i=0; i<lrow; i++) list[i] = new char[lcol];
	
	result = new char *[m];
	for(i=0; i<m; i++) result[i] = new char[n];
	
	if(n>m)	tstr = new char[n+1];
	else tstr = new char[m+1];
	
	fin.close();
	fin.open(argv[1]);
	for(i=0; i<m; i++) 
		for(j=0; j<n; j++) {
			fin>>mat[i][j];
			result[i][j]=1;
		}

	fin>>t;
	fin.seekg(-1, ios::cur);
	for(i=0; i<lrow; i++)
		for(j=0; j<lcol; j++) {
			fin.get(t);
			if(fin.eof()) t='\n';
			if(t!='\n') list[i][j]=t;
			else {
				list[i][j]='\0';
				break;
			}
		}
	fin.close();
		
	int found;	
	for(i=0; i<lrow; i++) {
		found = 0;
		for(j=0; j<m; j++) {
			for(k=0; k<n; k++) {
				if(list[i][0]==mat[j][k]) {
						found = search(mat, m, n, j, k, list[i], 1);
						if(found) {
							#ifdef DEBUG
								cout<<"DIAG U L "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int p=j, q=k, r=0; r<strlen(list[i]); p--, q--, r++) result[p][q]=0;
							break;
						}
					
						found = search(mat, m, n, j, k, list[i], 2);
						if(found) {
							#ifdef DEBUG
								cout<<"UP "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int p=j, r=0; r<strlen(list[i]); p--, r++) result[p][k]=0;
							break;
						}
					
						found = search(mat, m, n, j, k, list[i], 3);
						if(found) {
							#ifdef DEBUG
								cout<<"DIAG U R "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int p=j, q=k, r=0; r<strlen(list[i]); p--, q++, r++) result[p][q]=0;
							break;
						}
					
						found = search(mat, m, n, j, k, list[i], 4);
						if(found) {
							#ifdef DEBUG
								cout<<"LEFT "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int p=k, r=0; r<strlen(list[i]); r++, p--) result[j][p]=0;
							break;
						}

						found = search(mat, m, n, j, k, list[i], 5);
						if(found) {
							#ifdef DEBUG
								cout<<"RIGHT "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int q=k, r=0; r<strlen(list[i]); q++, r++) result[j][q]=0;
							break;
						}
						
						found = search(mat, m, n, j, k, list[i], 6);
						if(found) {
							#ifdef DEBUG
								cout<<"DIAG D L "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int p=j, q=k, r=0; r<strlen(list[i]); p++, q--, r++) result[p][q]=0;
							break;
						}
						
						found = search(mat, m, n, j, k, list[i], 7);
						if(found) {
							#ifdef DEBUG
								cout<<"DOWN "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int p=j, r=0; r<strlen(list[i]); p++, r++) result[p][k]=0;
							break;
						}
						
						found = search(mat, m, n, j, k, list[i], 8);
						if(found) {
							#ifdef DEBUG
								cout<<"DIAG D R "<<j<<" "<<k<<" "<<list[i]<<"\n";
							#endif
							for(int p=j, q=k, r=0; r<strlen(list[i]); p++, q++, r++) result[p][q]=0;
							break;
						}
					}
			}
			if(found) break;
		}
	}
	
	for(i=0; i<m; i++)
		for(j=0; j<n; j++) {
			if(result[i][j]) cout<<mat[i][j];
		}
	cout<<"\n";
			
	#ifdef DEBUG
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) cout<<mat[i][j];
		cout<<"\n";
	}
	for(i=0; i<lrow; i++) {
		cout<<list[i];
		cout<<"\n";
	}
	#endif
		
	for(i=0; i<m; i++) delete[] mat[i];
	delete[] mat;
	
	for(i=0; i<lrow; i++) delete[] list[i];
	delete[] list;
	
	for(i=0; i<m; i++) delete[] result[i];
	delete[] result;
	
	delete[] tstr;
	
	return 0;
}
