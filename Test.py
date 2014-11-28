import _SharedTool
import numpy as np

def m():
    a=_SharedTool.CreateShared("abdc",[10000,20000])
    print type(a)
    print a
    print "============================"
    print _SharedTool.GiveShared("abdc")
    return a

def mp():
    a=_SharedTool.GiveShared("abdc")
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
