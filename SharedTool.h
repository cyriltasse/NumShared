/* Header to test of C modules for arrays for Python: C_test.c */
#include "complex.h"
#include <math.h>

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


static PyObject *NumpyToShared(PyObject *self, PyObject *args);
static PyObject *ReadShared(PyObject *self, PyObject *args);

