from Single import _SharedTool as sNpShared
from Double import _SharedTool as dNpShared
import numpy as np

def m():
    a=sNpShared.CreateShared("abdc",[100,200],"d")
    # print type(a)
    # print a
    # print "============================"
    print sNpShared.GiveShared("abdc")
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
