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
	{"CreateShared", CreateShared, METH_VARARGS},
	{"GiveShared", GiveShared, METH_VARARGS},
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

static PyObject *CreateShared(PyObject *self, PyObject *args){
  PyObject *LShape;
  char *Name;

  if (!PyArg_ParseTuple(args, "sO!", 
			&Name,
			&PyList_Type, &LShape
			//&PyArray_Type,  &np_A
			))  return NULL;
  char NameSharedArray[80];
  //NameSharedArray  = (char*)malloc(100);
  strcpy(NameSharedArray,"/");
  strcat(NameSharedArray,Name);
  printf("%s\n",NameSharedArray);
  
  //  char *NameSharedArray_Shape;
  char NameSharedArray_Shape[80];//[80];
  //NameSharedArray_Shape  = (char*)malloc(100);
  strcpy(NameSharedArray_Shape,NameSharedArray);
  strcat(NameSharedArray_Shape,".shape");
  printf("%s\n",NameSharedArray_Shape);
  
  char NameSharedArray_NDIM[80];
  //NameSharedArray_NDIM  = (char*)malloc(100);
  strcpy(NameSharedArray_NDIM,NameSharedArray);
  strcat(NameSharedArray_NDIM,".size");
  printf("%s\n",NameSharedArray_NDIM);
  
  /* char NameSharedArray_Size2[800]; */
  /* strcpy(NameSharedArray_Size2,NameSharedArray); */
  /* strcat(NameSharedArray_Size2,".size2"); */
  /* printf("%s\n",NameSharedArray_Size2); */
  
  
  

  /* char* NameSharedArray=concat("/",Name); */
  /* printf("%s\n",NameSharedArray); */
  
  /* char* NameSharedArray_Shape=concat(NameSharedArray,".shape"); */
  /* printf("%s\n",NameSharedArray_Shape); */
  
  /* char* NameSharedArray_Size=concat(NameSharedArray,".size"); */
  /* printf("%s\n",NameSharedArray_Size); */
  

  
  /* char NameSharedArray_NDIM[80]; */
  /* strcpy(NameSharedArray_NDIM,NameSharedArray); */
  /* strcat(NameSharedArray_NDIM,".ndim"); */
  /* printf("%s\n",NameSharedArray_NDIM); */
  

  int NDIM=PyList_Size(LShape);
  printf("NDIM=%i\n",NDIM);
  int i;
  int SizeThisDim;
  PyObject *InList;
  int Shape[NDIM];

  
  for (i=0; i<NDIM; i++) {
    InList = PyList_GetItem(LShape, i);
    //Size = Py_ssize_t((PyList_GetItem(LShape, i));)
    SizeThisDim=(int)PyFloat_AsDouble(InList);
    Shape[i]=SizeThisDim;
    printf("dim %i\n",Shape[i]);
  }

  
  int TotSize=GiveTotSize(Shape,NDIM);

  AllocateSharedMem(NameSharedArray_NDIM,1);
  double* SharedNDIM= ReadSharedMem(NameSharedArray_NDIM,1);
  *SharedNDIM=NDIM;

  /* AllocateSharedMem(NameSharedArray_NDIM,1); */
  /* double* SharedNDIM= ReadSharedMem(NameSharedArray_NDIM,1); */
  /* *SharedNDIM=NDIM; */

  AllocateSharedMem(NameSharedArray_Shape,NDIM);
  double* SharedShape= ReadSharedMem(NameSharedArray_Shape,NDIM);
  for (i=0; i<NDIM; i++) {
    SharedShape[i]=Shape[i];
  }

  AllocateSharedMem(NameSharedArray,TotSize);
  double* SharedArray= ReadSharedMem(NameSharedArray,TotSize);
  for (i=0; i<TotSize; i++) {
    SharedArray[i]=i;
  }

  int typenum=NPY_FLOAT64;
  npy_intp *NpShape;
  for (i=0; i<NDIM; i++) {
    NpShape[i]=Shape[i];
  }
  
  PyArrayObject * Array = (PyArrayObject*)PyArray_SimpleNewFromData(NDIM, NpShape, typenum, SharedArray);

  return PyArray_Return(Array);
    //return Py_None;
}

//////////////////////////////////////////////////////////////////////////////

static PyObject *GiveShared(PyObject *self, PyObject *args){
  char *Name;

  if (!PyArg_ParseTuple(args, "s", 
			&Name
			))  return NULL;
  char NameSharedArray[80];
  //NameSharedArray  = (char*)malloc(100);
  strcpy(NameSharedArray,"/");
  strcat(NameSharedArray,Name);
  printf("%s\n",NameSharedArray);
  
  //  char *NameSharedArray_Shape;
  char NameSharedArray_Shape[80];//[80];
  //NameSharedArray_Shape  = (char*)malloc(100);
  strcpy(NameSharedArray_Shape,NameSharedArray);
  strcat(NameSharedArray_Shape,".shape");
  printf("%s\n",NameSharedArray_Shape);
  
  char NameSharedArray_NDIM[80];
  //NameSharedArray_NDIM  = (char*)malloc(100);
  strcpy(NameSharedArray_NDIM,NameSharedArray);
  strcat(NameSharedArray_NDIM,".size");
  printf("%s\n",NameSharedArray_NDIM);
  
  int NDIM,i;
  double* SharedNDIM= ReadSharedMem(NameSharedArray_NDIM,1);
  NDIM=*SharedNDIM;
  printf("NDIM %i\n",NDIM);
  int Shape[NDIM];
  double* SharedShape= ReadSharedMem(NameSharedArray_Shape,NDIM);

  for (i=0; i<NDIM; i++) {
    Shape[i]=SharedShape[i];
    printf("Shape %i: %i\n",i,Shape[i]);
  }

  int TotSize=GiveTotSize(Shape,NDIM);
  printf("TotSize %i\n",TotSize);
  double* SharedArray= ReadSharedMem(NameSharedArray,TotSize);
  printf("val %f\n",SharedArray[0]);
  printf("val %f\n",SharedArray[1]);
  printf("val %f\n",SharedArray[2]);
  printf("val %f\n",SharedArray[3]);

  int typenum=NPY_FLOAT64;

  npy_intp NpShape[NDIM];
  for (i=0; i<NDIM; i++) {
    NpShape[i]=Shape[i];
  }
  
  
  for (i=0; i<TotSize; i++) {
    printf("val %f\n",SharedArray[i]);
  }


  PyArrayObject * Array = (PyArrayObject*)PyArray_SimpleNewFromData(NDIM, NpShape, typenum, SharedArray);

  return PyArray_Return(Array);
  //return Py_None;
}





void AllocateSharedMem(char* Name, int TotSize){

  int Unlink,fd;

  Unlink=shm_unlink(Name);
  printf("Unlink %i\n",Unlink);

  fd = shm_open(Name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1){
    printf("error0\n");
  };
  
  if (ftruncate(fd, TotSize*sizeof(double)) == -1)
    {
      printf("error1\n");
    };


  
}

double* ReadSharedMem(char* Name, int TotSize){

  int Unlink,fd;

  fd = shm_open(Name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1){
    printf("error0\n");
  };
  
  double *rptr;
  rptr = mmap(NULL, TotSize*sizeof(double),
  	      PROT_READ | PROT_WRITE,
  	      MAP_SHARED, fd, 0);

  if (rptr == MAP_FAILED){
    printf("error3\n");
  };

  return rptr;
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

