# include <iostream>
# include <string>
using namespace std;
class  LaplacianReg
{

public:
double 	**WeightMatrix;
double 	**TransitionMatrix;
double	**DiagonalMatrix;
double 	**NormLaplacianMatrix;
double 	**ELMatrix;
double 	**ELTMatrix;
double 	**tempEEMatrix;
double 	*tempEVector;
double 	*acoefVector;
double	**Y0Matrix;
int 	*IndexMatrix;
int 	*OrgYVector;

int 	noExamples;
int 	noLExamples;
int 	noClasses;
int	p;
int 	noIterations;
int 	algoChoice;
float  	alpha;
string 	weightFile;
string  IplabelFile;
string  OplabelFile;
string 	methodChoice;

	LaplacianReg();
void 	LoadWeightMatrix();
void	TransitionMatrixCal();
void	DiagonalMatrixCal();
void	NormLaplacianMatrixCal();


void	DisplayWeightMatrix();
void	DisplayTransitionMatrix();
void	DisplayNormLaplacianMatrix();


void 	PrepareYMatrix();
void 	DisplayOrgYVector();


void	RunAlgorithm();
void	WriteOutput();
};

  
