/* A file to test imorting C modules for handling arrays to Python */

#include <Python.h>
#include "arrayobject.h"
#include "SharedTool.h"
#include <math.h>
#include "complex.h"

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

static PyMethodDef _SharedTool_testMethods[] = {
	{"NumpyToShared", NumpyToShared, METH_VARARGS},
	{"ReadShared", ReadShared, METH_VARARGS},
	{NULL, NULL}
	  };


void init_SharedTool(){
  (void) Py_InitModule("_SharedTool", _SharedTool_testMethods);
  import_array();  // Must be present for NumPy.  Called first after above line.
};



/* #define MAX_LEN 10000 */
/* struct region {       */
/*   int len; */
/*   char buf[MAX_LEN]; */
/* }; */

static PyObject *NumpyToShared(PyObject *self, PyObject *args){
  PyArrayObject *np_A;
  PyObject *ObjArray;
  if (!PyArg_ParseTuple(args, "O", 
			&ObjArray
			//&PyArray_Type,  &np_A
			))  return NULL;
  np_A = (PyArrayObject *) PyArray_ContiguousFromObject(ObjArray, PyArray_FLOAT64, 0, 3);
  double* NpArray = pyvector_to_Carrayptrs(np_A);
  printf("%f\n",*NpArray);

//  struct region *rptr;
  int fd;

  fd = shm_open("/myregion", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1){
    printf("error0\n");
  };
  
  if (ftruncate(fd, sizeof(double)) == -1)
    {
      printf("error1\n");
    };

  double *rptr;
  rptr = mmap(NULL, sizeof(double),
	      PROT_READ | PROT_WRITE,
	      MAP_SHARED, fd, 0);

  if (rptr == MAP_FAILED){
    printf("error3\n");
  };

//grid->len=2;
  *rptr=*NpArray;

  printf("%f\n",*rptr);

  return PyArray_Return(np_A);//,PyArray_Return(np_grid);

}


static PyObject *ReadShared(PyObject *self, PyObject *args){
  PyArrayObject *np_A;
  PyObject *ObjArray;
  if (!PyArg_ParseTuple(args, "O", 
			&ObjArray
			//&PyArray_Type,  &np_A
			))  return NULL;
  np_A = (PyArrayObject *) PyArray_ContiguousFromObject(ObjArray, PyArray_FLOAT64, 0, 3);
  double* NpArray = pyvector_to_Carrayptrs(np_A);
  int fd;

  fd = shm_open("/myregion", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1){
    printf("error0\n");
  };
  
  double *rptr;
  rptr = mmap(NULL, sizeof(double),
	      PROT_READ | PROT_WRITE,
	      MAP_SHARED, fd, 0);

  if (rptr == MAP_FAILED){
    printf("error3\n");
  };

  printf("%f\n",*rptr);

  return PyArray_Return(np_A);//,PyArray_Return(np_grid);

}








double *pyvector_to_Carrayptrs(PyArrayObject *arrayin)  {
  return (double *) arrayin->data;  /* pointer to arrayin data as double */
}

int *pyvector_to_Carrayptrs2(PyArrayObject *arrayin)  {
  return (int *) arrayin->data;  /* pointer to arrayin data as double */
}


double complex *Complex_pyvector_to_Carrayptrs(PyArrayObject *arrayin)  {
  return (double complex *) arrayin->data;  /* pointer to arrayin data as double */
}

