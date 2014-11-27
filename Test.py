import _SharedTool
import numpy as np

def m():
    a=_SharedTool.CreateShared("abdc",[200,200])
    print type(a)
    print a

def m0():
    a=np.float64(np.random.randn(2,2))
    print a
    
    _SharedTool.NumpyToShared(a)

def m1():
    a=np.float64(np.random.randn(2,2))
    _SharedTool.ReadShared(a)


#_SharedTool.ReadShared()
m()
