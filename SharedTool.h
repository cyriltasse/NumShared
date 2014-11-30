/* Header to test of C modules for arrays for Python: C_test.c */
#include "complex.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>


/* ==== Prototypes =================================== */

// .... Python callable Vector functions ..................


/* .... C vector utility functions ..................*/
//PyArrayObject *pyvector(PyObject *objin);
double *pyvector_to_Carrayptrs(PyArrayObject *arrayin);
int *pyvector_to_Carrayptrs2(PyArrayObject *arrayin);
//===========================================
double complex *GetCp(PyArrayObject *arrayin);
double complex *Complex_pyvector_to_Carrayptrs(PyArrayObject *arrayin);
int *Int_pyvector_to_Carrayptrs(PyArrayObject *arrayin);
//int  not_doublevector(PyArrayObject *vec);
int nint(double n){
  //  double x=n+0.5;
  //printf("%f+0.5= %f\n",n,x);
  return floor(n+0.5);};

/* .... Python callable Matrix functions ..................*/

int *I_ptr(PyArrayObject *arrayin)  {
	return (int *) arrayin->data;
}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+10);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int GiveTotSize(int* Shape, int NDIM, int iType){
  int TotSize=Shape[0];
  int i;
  if(NDIM>1){
    for (i=1; i<NDIM; i++) {
      TotSize*=Shape[i];
    }
  }

  if(iType==1){TotSize=TotSize*2;};
  
  printf("TotSize %i\n",TotSize);
  return TotSize;
};

//typedef double myfloat;
#ifdef USE_DOUBLES
typedef double myfloat;
int Precision=1;
#else 
typedef float myfloat;
int Precision=0;
#endif



void ClearShared(char* NameSharedArray, int TotSize);
static PyObject *NumpyToShared(PyObject *self, PyObject *args);
static PyObject *CreateShared(PyObject *self, PyObject *args);
static PyObject *GiveShared(PyObject *self, PyObject *args);
static PyObject *Release(PyObject *self, PyObject *args);
int AllocateSharedMem(char* Name, int TotSize);
myfloat* ReadSharedMem(char* Name, int TotSize);
