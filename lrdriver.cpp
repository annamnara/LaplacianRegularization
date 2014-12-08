# include <sstream> 
# include<iostream>
# include <fstream>
# include <string>
# include <vector>
# include <stdlib.h>
# include <algorithm>
# include <iterator>
# include <cstdlib>
# include <math.h>
# include <iterator>
#include <ctime> 
#include <cstring> 
#include <stdio.h> 
# include "LaplacianReg.hpp"

using namespace std;
int main(int argc, char* argv[])
{


LaplacianReg  lr;

FILE* fp;
fp=fopen(argv[1],"r");
char  paramName[50];
char  paramType[50];
char  paramValue[50];
char  line[100];

while (fgets(line,500,fp) != NULL) {
if(line[0]!='#')
{

sscanf(line,"%s %s %s",paramName,paramType,paramValue);

if(strcmp(paramName,"weightFile")==0)
lr.weightFile=paramValue;

if(strcmp(paramName,"IplabelFile")==0)
lr.IplabelFile=paramValue;

if(strcmp(paramName,"OplabelFile")==0)
lr.OplabelFile=paramValue;

if(strcmp(paramName,"noExamples")==0)
lr.noExamples=atoi(paramValue);

if(strcmp(paramName,"noLExamples")==0)
lr.noLExamples=atoi(paramValue);


if(strcmp(paramName,"p")==0)
lr.p=atoi(paramValue);

if(strcmp(paramName,"noClasses")==0)
lr.noClasses=atoi(paramValue);


if(strcmp(paramName,"noitr")==0)
lr.noIterations=atoi(paramValue);

if(strcmp(paramName,"algoChoice")==0)
lr.algoChoice=atoi(paramValue);

if(strcmp(paramName,"alpha")==0)
lr.alpha=atof(paramValue);

}
 
}
cout<< "params are: "<< "No. of Exmaples"<<lr.noExamples<<" \t"<< " Weight filename:"<< lr.weightFile<<"\t"<< "Iterations:"<<lr.noIterations<< "\t"<<lr.alpha<<endl;


lr.LoadWeightMatrix();
//lr.DisplayWeightMatrix();

lr.TransitionMatrixCal();
//lr.DisplayTransitionMatrix();

lr.DiagonalMatrixCal();
lr.NormLaplacianMatrixCal();

//lr.DisplayNormLaplacianMatrix();


lr.PrepareYMatrix();
//lr.DisplayOrgYMatrix();


lr.RunAlgorithm();
//lr.WriteOutput();
//lr.DisplayActYMatrix();

}

