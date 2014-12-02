from FLOAT32 import _SharedTool as NpShared_FLOAT32
from FLOAT64 import _SharedTool as NpShared_FLOAT64
import numpy as np

def m():
    a=NpShared_FLOAT32.CreateShared("abdc",[5,5],"c")
    # print type(a)
    print a
    print "============================"
    b=NpShared_FLOAT32.GiveShared("abdc")
    print b.dtype
    print "========="
    b=NpShared_FLOAT32.GiveShared("abdc")
    print b.dtype
    print "========="
    print NpShared_FLOAT32.GiveType("abdc")
    return a

def mp():
    a=sNpShared.GiveShared("abdc")
    print type(a)
    print a
    return a

def m0():
    a=np.float64(np.random.randn(2,2))
    print a
    
    _SharedTool.NumpyToShared(a)

def m1():
    a=np.float64(np.random.randn(2,2))
    _SharedTool.ReadShared(a)


#_SharedTool.ReadShared()

if __name__=="__main__":
    m()
