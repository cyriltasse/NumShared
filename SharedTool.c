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
#include <stdbool.h>

static PyMethodDef _SharedTool_testMethods[] = {
	{"CreateShared", CreateShared, METH_VARARGS},
	{"GiveShared", GiveShared, METH_VARARGS},
	{"Release", Release, METH_VARARGS},
	{"GiveType", GiveType, METH_VARARGS},
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
  char *Name, *Type;

  if (!PyArg_ParseTuple(args, "sO!", 
			&Name,
			&PyList_Type, &LShape//,
			//&Type
			//&PyArray_Type,  &np_A
			))  return NULL;
  
  

  char *NameSharedArray=concat("/",Name);
  char *NameSharedArray_Shape=concat(NameSharedArray,".shape");
  char *NameSharedArray_NDIM=concat(NameSharedArray,".NDIM");
  char *NameSharedArray_Type=concat(NameSharedArray,".Type");
  char *NameSharedArray_FD=concat(NameSharedArray,".FD");
  //  printf("%s\n",NameSharedArray_NDIM);

  //// type
  /* int iType,npType; */
  /* int comp=strcmp(Type,"d"); */
  /* printf("comp %i\n",comp); */
  /* printf("PRECISION %i\n",Precision); */
  
  /* if(strcmp(Type,"d")==0){ */
  /*   printf("set %s\n",Type); */
  /*   iType=0; */
  /*   if(Precision==0){ */
  /*     npType=(int)NPY_FLOAT32; */
  /*   }; */
  /*   if(Precision==1){ */
  /*     npType=(int)NPY_FLOAT64; */
  /*   }; */
  /* }; */

  /* if(strcmp(Type,"c")==0){ */
  /*   printf("set %s\n",Type); */
  /*   iType=1; */
  /*   if(Precision==0){ */
  /*     npType=(int)NPY_COMPLEX64; */
  /*   }; */
  /*   if(Precision==1){ */
  /*     npType=(int)NPY_COMPLEX128; */
  /*   }; */
  /* }; */

  /* printf("NPY_Type in1 %i\n",npType); */
  /* printf("NPY_Type in1 NPY_FLOAT32   : %i\n",NPY_FLOAT32); */
  /* printf("NPY_Type in1 NPY_COMPLEX64: %i\n",NPY_COMPLEX64); */
  /* printf("NPY_Type in1 NPY_FLOAT64   : %i\n",NPY_FLOAT64); */
  /* printf("NPY_Type in1 NPY_COMPLEX128: %i\n",NPY_COMPLEX128); */
  /* printf("NPY_Type in1 NPY_INT16   : %i\n",NPY_INT16); */
  /* printf("NPY_Type in1 NPY_BOOL: %i\n",NPY_BOOL); */

  
  
  /* int ii=0; */
  /* if(ii==0){ */
  /*   #define TYPE  double */
  /* }else{ */
  /*   #define TYPE  int */
  /* } */
  /* typedef TYPE DATATYPE; */
  /* DATATYPE caca=1; */
  /* printf("DATATYPE size %i\n",sizeof(DATATYPE)); */
  /* printf("DATATYPE size %i\n",sizeof(double)); */
  /* printf("DATATYPE size %i\n",sizeof(int)); */
  

  int fd;
  fd=AllocateSharedMem_Int(NameSharedArray_Type,2);
  int* SharedType= ReadSharedMem_Int(NameSharedArray_Type,2);
  SharedType[0]=(int)iType;
  SharedType[1]=(int)npType;
  //  printf("NPY_Type in2 %i\n",SharedType[1]);


  ///////
  int NDIM=PyList_Size(LShape);
  //  printf("NDIM=%i\n",NDIM);
  int i;
  int SizeThisDim;
  PyObject *InList;
  int Shape[NDIM];

  
  for (i=0; i<NDIM; i++) {
    InList = PyList_GetItem(LShape, i);
    //Size = Py_ssize_t((PyList_GetItem(LShape, i));)
    SizeThisDim=(int)PyFloat_AsDouble(InList);
    Shape[i]=SizeThisDim;
    //    printf("dim %i\n",Shape[i]);
  }

  
  int TotSize=GiveTotSize(Shape,NDIM,iType);


  int FD[1];
  fd=AllocateSharedMem_Int(NameSharedArray_NDIM,1);
  int* SharedNDIM= ReadSharedMem_Int(NameSharedArray_NDIM,1);
  *SharedNDIM=NDIM;

  fd=AllocateSharedMem_Int(NameSharedArray_Shape,NDIM);
  int* SharedShape= ReadSharedMem_Int(NameSharedArray_Shape,NDIM);
  for (i=0; i<NDIM; i++) {
    SharedShape[i]=Shape[i];
  }

  fd=AllocateSharedMem(NameSharedArray,TotSize);
  myfloat* SharedArray= ReadSharedMem(NameSharedArray,TotSize);
  FD[0]=fd;

  int fd0=AllocateSharedMem_Int(NameSharedArray_FD,1);
  int* FDShared= ReadSharedMem_Int(NameSharedArray_FD,1);
  FDShared[0]=FD[0];




  //int foo=AllocateSharedMem(NameSharedArray_FD,3);
  //myfloat* SharedFD= ReadSharedMem(NameSharedArray_FD,3);
  //for (i=0; i<3; i++) {
  //  SharedFD[i]=FD[i];
  //}
  

  /* for (i=0; i<TotSize; i++) { */
  /*   SharedArray[i]=0; */
  /* } */

  //int typenum=NPY_FLOAT64;

  npy_intp NpShape[NDIM];
  for (i=0; i<NDIM; i++) {
    NpShape[i]=Shape[i];
  }
  
  //PyArrayObject * Array = (PyArrayObject*)PyArray_SimpleNewFromData(NDIM, NpShape, typenum, SharedArray);
  PyArrayObject * Array = (PyArrayObject*)PyArray_SimpleNewFromData(NDIM, NpShape, npType, SharedArray);

  return PyArray_Return(Array);
  //return Py_None;
}


static PyObject *GiveType(PyObject *self, PyObject *args){
  char *Name;

  if (!PyArg_ParseTuple(args, "s", 
			&Name
			))  return NULL;

  
  char *NameSharedArray=concat("/",Name);
  char *NameSharedArray_Shape=concat(NameSharedArray,".shape");
  char *NameSharedArray_NDIM=concat(NameSharedArray,".NDIM");

  char *NameSharedArray_Type=concat(NameSharedArray,".Type");
  int iType, npType;
  int* SharedType= ReadSharedMem_Int(NameSharedArray_Type,2);
  iType=(int)SharedType[0];
  npType=(int)SharedType[1];
  /* printf("read NPY_Type %i\n",SharedType[0]); */
  /* printf("read NPY_Type %i\n",npType); */
  /* printf("read NPY_Type %i\n",SharedType[1]); */

  return PyLong_FromDouble((double) npType);
}



//////////////////////////////////////////////////////////////////////////////



static PyObject *GiveShared(PyObject *self, PyObject *args){
  char *Name;


  if (!PyArg_ParseTuple(args, "s", 
			&Name
			))  return NULL;

  
  char *NameSharedArray=concat("/",Name);
  char *NameSharedArray_Shape=concat(NameSharedArray,".shape");
  char *NameSharedArray_NDIM=concat(NameSharedArray,".NDIM");

  char *NameSharedArray_Type=concat(NameSharedArray,".Type");
  int iType, npType;
  int* SharedType= ReadSharedMem_Int(NameSharedArray_Type,2);
  iType=(int)SharedType[0];
  npType=(int)SharedType[1];
  /* printf("read NPY_Type %i\n",SharedType[0]); */
  /* printf("read NPY_Type %i\n",npType); */
  /* printf("read NPY_Type %i\n",SharedType[1]); */
 



  int NDIM,i;
  int* SharedNDIM= ReadSharedMem_Int(NameSharedArray_NDIM,1);
  NDIM=*SharedNDIM;
  //  printf("NDIM %i\n",NDIM);
  int Shape[NDIM];
  int* SharedShape= ReadSharedMem_Int(NameSharedArray_Shape,NDIM);

  for (i=0; i<NDIM; i++) {
    Shape[i]=SharedShape[i];
    //    printf("Shape %i: %i\n",i,Shape[i]);
  }

  int TotSize=GiveTotSize(Shape,NDIM,iType);
  //  printf("TotSize %i\n",TotSize);


  myfloat* SharedArray= ReadSharedMem(NameSharedArray,TotSize);
  /* printf("val %f\n",SharedArray[0]); */
  /* printf("val %f\n",SharedArray[1]); */
  /* printf("val %f\n",SharedArray[2]); */
  /* printf("val %f\n",SharedArray[3]); */


  npy_intp NpShape[NDIM];
  for (i=0; i<NDIM; i++) {
    NpShape[i]=Shape[i];
  }
  
  
  /* for (i=0; i<TotSize; i++) { */
  /*   printf("val %f\n",SharedArray[i]); */
  /* } */

  //npType=NPY_FLOAT64;


  PyArrayObject * Array = (PyArrayObject*)PyArray_SimpleNewFromData(NDIM, NpShape, npType, SharedArray);

  return PyArray_Return(Array);
  //return Py_None;
}

static PyObject *Release(PyObject *self, PyObject *args){
  char *Name;

  if (!PyArg_ParseTuple(args, "s", 
			&Name
			))  return NULL;
  
  char *NameSharedArray=concat("/",Name);
  char *NameSharedArray_Shape=concat(NameSharedArray,".shape");
  char *NameSharedArray_NDIM=concat(NameSharedArray,".NDIM");
  //char *NameSharedArray_FD=concat(NameSharedArray,".FD");

  //myfloat* SharedFD= ReadSharedMem(NameSharedArray_FD,3);
  
  

  int NDIM,i;
  int* SharedNDIM= ReadSharedMem_Int(NameSharedArray_NDIM,1);
  NDIM=*SharedNDIM;
  int Shape[NDIM];
  int* SharedShape= ReadSharedMem_Int(NameSharedArray_Shape,NDIM);

  for (i=0; i<NDIM; i++) {
    Shape[i]=SharedShape[i];
  }



  char *NameSharedArray_Type=concat(NameSharedArray,".Type");
  int iType, npType;
  int* SharedType= ReadSharedMem_Int(NameSharedArray_Type,2);
  iType=SharedType[0];
  npType=SharedType[1];
  int TotSize=GiveTotSize(Shape,NDIM,iType);
  myfloat* SharedArray= ReadSharedMem(NameSharedArray,TotSize);
  
  /* printf("SharedFD %i\n",(int)SharedFD[0]); */
  /* printf("SharedFD %i\n",(int)SharedFD[1]); */
  /* printf("SharedFD %i\n",(int)SharedFD[2]); */
  

  ClearShared(NameSharedArray,TotSize);
  ClearShared_Int(NameSharedArray_Shape,NDIM);
  ClearShared_Int(NameSharedArray_NDIM,1);




  return Py_None;
}

void ClearShared_Int(char* NameSharedArray, int TotSize){
  int Unlink;
  int fd0 = shm_open(NameSharedArray, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  int* SharedArray= ReadSharedMem_Int(NameSharedArray,TotSize);
  int dummy=ftruncate(fd0, 0);
  int mm0=munmap(SharedArray, TotSize*sizeof(int));
  Unlink=shm_unlink(NameSharedArray);
  close(fd0);
};



int AllocateSharedMem_Int(char* Name, int TotSize){

  int Unlink,fd;

  Unlink=shm_unlink(Name);
  //  printf("Unlink %i\n",Unlink);

  fd = shm_open(Name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  //printf("===================fd %i\n",fd);
  if (fd == -1){
    printf("error0\n");
  };
  
  if (ftruncate(fd, TotSize*sizeof(int)) == -1)
    {
      printf("error1\n");
    };

  return fd;
  
}

int* ReadSharedMem_Int(char* Name, int TotSize){

  int Unlink,fd;

  fd = shm_open(Name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1){
    printf("error0\n");
  };
  
  int *rptr;
  rptr = mmap(NULL, TotSize*sizeof(int),
  	      PROT_READ | PROT_WRITE,
  	      MAP_SHARED, fd, 0);

  if (rptr == MAP_FAILED){
    printf("error3\n");
  };

  return rptr;
}


/////////////////////////////////////////////////////////

void ClearShared(char* NameSharedArray, int TotSize){
  int Unlink;
  int fd0 = shm_open(NameSharedArray, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  myfloat* SharedArray= ReadSharedMem(NameSharedArray,TotSize);
  int dummy=ftruncate(fd0, 0);
  int mm0=munmap(SharedArray, TotSize*sizeof(myfloat));
  Unlink=shm_unlink(NameSharedArray);
  close(fd0);
};



int AllocateSharedMem(char* Name, int TotSize){

  int Unlink,fd;

  Unlink=shm_unlink(Name);
  //  printf("Unlink %i\n",Unlink);

  fd = shm_open(Name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  //printf("===================fd %i\n",fd);
  if (fd == -1){
    printf("error0\n");
  };
  
  if (ftruncate(fd, TotSize*sizeof(myfloat)) == -1)
    {
      printf("error1\n");
    };

  return fd;
  
}

myfloat* ReadSharedMem(char* Name, int TotSize){

  int Unlink,fd;

  fd = shm_open(Name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1){
    printf("error0\n");
  };
  
  myfloat *rptr;
  rptr = mmap(NULL, TotSize*sizeof(myfloat),
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

