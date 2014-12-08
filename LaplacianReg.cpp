# include "LaplacianReg.hpp"
# include "StringUtilities.hpp"
# include <sstream> 
# include<iostream>
# include <fstream>
# include <string>
# include <cstring>
# include <vector>
# include <stdlib.h>
# include <algorithm>
# include <iterator>
# include <cstdlib>
# include <cmath>
# include <iterator>
#include <ctime>  
# include <queue>
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "linalg.h"
#include "sort.h"
using namespace std;
using namespace alglib;
StringUtilities su;
LaplacianReg::LaplacianReg()
{

}


void LaplacianReg::LoadWeightMatrix()

{
fstream myweightfile(&weightFile[0]);

WeightMatrix = new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    WeightMatrix[i] = new double[noExamples];
}
string str;
double dummy=0.0;
int nr=0;
while(getline(myweightfile,str)){
   double  *p;
   p= su.SplitString(str,dummy); 
   for ( int i = 0; i < noExamples; i++ ) {
        WeightMatrix[nr][i]=*(p+i);
   }
  nr++;
  delete p;

}
}

void	LaplacianReg::TransitionMatrixCal(){


TransitionMatrix = new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    TransitionMatrix[i] = new double[noExamples];
}

for (int r=0;r<noExamples;r++)
  for(int c=0;c<noExamples;c++)
       TransitionMatrix[r][c]=0.0;


double rowSum=0.0;
for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
     rowSum=rowSum+WeightMatrix[r][c];
}
   for(int l=0;l<noExamples;l++) 
   TransitionMatrix[r][l]=WeightMatrix[r][l] / rowSum;
  rowSum=0.0;

}
}

void	LaplacianReg::DiagonalMatrixCal(){


DiagonalMatrix= new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    DiagonalMatrix[i] = new double[noExamples];
}


for (int r=0;r<noExamples;r++)
  for(int c=0;c<noExamples;c++)
       DiagonalMatrix[r][c]=0.0;

double rowSum=0.0;
for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
     rowSum=rowSum+WeightMatrix[r][c];
}
   DiagonalMatrix[r][r]= rowSum;
  rowSum=0.0;

}
}

void	LaplacianReg::NormLaplacianMatrixCal(){


NormLaplacianMatrix= new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    NormLaplacianMatrix[i] = new double[noExamples];
}


for (int r=0;r<noExamples;r++)
  for(int c=0;c<noExamples;c++)
       NormLaplacianMatrix[r][c]=0.0;


for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
   double temp=0.0;
      for(int c1=0;c1<noExamples;c1++){
  temp=temp+DiagonalMatrix[r][c1]*WeightMatrix[c1][c]; 
}
NormLaplacianMatrix[r][c]=temp;
}
}



for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
 NormLaplacianMatrix[r][c]=DiagonalMatrix[r][c]-WeightMatrix[r][c];
}
}

}


void LaplacianReg::DisplayWeightMatrix()
{


cout<< "Displaying WeightMatrix"<< endl;

for(int i=0;i<noExamples;i++){

    for (int j=0;j<noExamples;j++){

          cout<< WeightMatrix[i][j]<<"\t";



 }
cout<< "\n";

}

}

void LaplacianReg::DisplayTransitionMatrix()
{


cout<< "Displaying TransitionMatrix"<< endl;

for(int i=0;i<noExamples;i++){

    for (int j=0;j<noExamples;j++){

          cout<< TransitionMatrix[i][j]<<"\t";



 }
cout<< "\n";

}

}

void LaplacianReg::DisplayNormLaplacianMatrix()
{


cout<< "Displaying NormLaplacianMatrix"<< endl;

for(int i=0;i<noExamples;i++){

    for (int j=0;j<noExamples;j++){

          cout<< NormLaplacianMatrix[i][j]<<"\t";



 }
cout<< "\n";

}

}

void LaplacianReg::PrepareYMatrix()
{

IndexMatrix=new int[noExamples];
OrgYVector=new int[noExamples];

fstream mylabelfile(&IplabelFile[0]);

string str;
int r=0;
while(getline(mylabelfile,str)){

char *x=&str[0];
IndexMatrix[r]=r;
OrgYVector[r]=atoi(x);
r++;
}

}


void LaplacianReg::RunAlgorithm(){

cout<< "Laplacian Regularization"<<endl;

real_2d_array  L;
real_2d_array  VL;
real_2d_array  VR;
real_1d_array  WR;
real_1d_array  WI;


L.setlength(noExamples,noExamples);

for (int i=0;i<noExamples;i++)
  for(int j=0;j<noExamples;j++)
         L(i,j)=NormLaplacianMatrix[i][j];

rmatrixevd(L,noExamples,3,WR,WI,VL,VR);

vector<double> evals;
vector<size_t> indices;

cout<<"DISPLAYING EIGEN VALUES";

for(int i=0;i<noExamples;i++)
{
cout<<WR[i]<<endl;
evals.push_back(WR[i]);

}

sort(evals,evals,indices);


/*cout<<"\n AFTER SORT- DISPLAYING EIGEN VALUES";

for(int i=0;i<noExamples;i++)
{
cout<<WR[indices[i]]<<endl;

}
*/

ELTMatrix=new double*[p];
for(int i=0;i<p;i++)
ELTMatrix[i]=new double[noLExamples];

ELMatrix=new double*[noLExamples];
for(int i=0;i<noLExamples;i++)
ELMatrix[i]=new double[p];

tempEEMatrix=new double*[p];
for(int i=0;i<p;i++)
tempEEMatrix[i]=new double[p];




for(int i=0;i<p;i++){
for(int j=0;j<noLExamples;j++){

ELTMatrix[i][j]=0.0;
ELMatrix[j][i]=0.0;

}
}

for(int i=0;i<p;i++)
for(int j=0;j<p;j++)
tempEEMatrix[i][j]=0.0;


for(int i=0;i<noLExamples;i++){
for(int j=0;j<p;j++){

ELMatrix[i][j]=VL[i][indices[j]];
ELTMatrix[j][i]=ELMatrix[i][j];

}
}


real_2d_array tempEE;
tempEE.setlength(p,p);


 for (int i=0;i<p;i++){
 for (int j=0;j<p;j++){
 double sum=0.0;
 for (int k=0;k<noLExamples;k++){
   sum=sum+ ELTMatrix[i][k]*ELMatrix[k][j];
   }

tempEEMatrix[i][j]=sum;
tempEE(i,j)=sum;

}
}

ae_int_t info;
matinvreport rep;
rmatrixinverse(tempEE, info, rep);

tempEVector=new double[p];
for(int i=0;i<p;i++)
tempEVector[i]=0.0;
acoefVector=new double[p];
for(int i=0;i<p;i++)
acoefVector[i]=0.0;

 
for (int i=0;i<p;i++){
 double sum=0.0;
 for (int k=0;k<noLExamples;k++){
  sum=sum+ ELTMatrix[i][k]*OrgYVector[k];
}

tempEVector[i]=sum;

}

for (int i=0;i<p;i++){
 double sum=0.0;
 for (int k=0;k<p;k++){
  sum=sum+ tempEE[i][k]*tempEVector[k];
}

acoefVector[i]=sum;

}

cout<<"DISPLAYING P COEFFICIENTS"<<endl;

for(int i=0;i<p;i++)
cout<<acoefVector[i]<<endl;

cout<<"DISPLAYING ORG Y LABLED  VALUES";
for (int i=0;i<noLExamples;i++)
cout<<OrgYVector[i]<<"\t";


/*
cout<<"\n Displaying eigen vector"<<endl;
for(int i=0;i<noExamples;i++)
cout<< VL[i][indices[0]]<<endl;



cout<< "\n Displaying p ELM values"<<endl;

for(int i=0;i<noLExamples;i++){

for(int j=0;j<p;j++){

cout<<ELMatrix[i][j]<<"\t";
if(j==249) 
cout<< "CLASS2";

}

cout<<"\n";
}
*/

cout<< "FINDING ERROR"<<endl;

double Error=0.0;
for (int i=0;i<noLExamples;i++)
{
   double sum=0.0;
   for(int j=0;j<p;j++){
   sum=sum+(ELMatrix[i][j]*acoefVector[j]);}

   Error=Error+pow((OrgYVector[i]-sum),2.0);

}
cout<<"\n TOTAL ERROR="<<Error<<endl;




ofstream filafile;
filafile.open(&OplabelFile[0]);
for (int i=0; i<noExamples;i++){

double esum=0.0;

for(int j=0;j<p;j++)
{

esum=esum+VL[i][indices[j]]*acoefVector[j];

}

if (esum>0)
filafile<<1<<"\n";
else
filafile<<-1<<"\n";

}


cout<<"\n I AM DONE"<<endl;


}


/*

void    LaplacianReg::WriteOutput(){

ofstream filafile;
filafile.open(&OplabelFile[0]);
for (int i=0; i<noExamples;i++){

double esum=0.0;

for(int j=0;j<p;j++)
{

esum=esum+VL[i][indices[j]]*acoefVector[j];

}

if (esum>0)
filafile<<1<<"\n";
else
filafile<<-1<<"\n";

}

}
*/

void LaplacianReg::DisplayOrgYVector()
{

cout<< "DISPLAYING ORG  Y MATRIX"<< endl;
for (int i=0; i<noExamples;i++){
cout<< OrgYVector[i]<<"\t ";
cout<< "\n";
}
}

