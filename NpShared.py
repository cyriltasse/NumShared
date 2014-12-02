
from FLOAT32 import _SharedTool as NpShared_FLOAT32

import numpy as np

def GiveArray(Name):
    TypeNum=NpShared_FLOAT32.GiveType(Name)
    if TypeNum==11:
        from FLOAT32 import _SharedTool as Mod_NpShared
    if TypeNum==12:
        from FLOAT64 import _SharedTool as Mod_NpShared
    if TypeNum==14:
        from COMPLEX64 import _SharedTool as Mod_NpShared
    if TypeNum==15:
        from COMPLEX128 import _SharedTool as Mod_NpShared
    if TypeNum==5:
        from INT32 import _SharedTool as Mod_NpShared
    if TypeNum==7:
        from INT64 import _SharedTool as Mod_NpShared
    if TypeNum==0:
        from BOOL import _SharedTool as Mod_NpShared

    return Mod_NpShared.GiveShared(Name)

def DelArray(Name):
    TypeNum=NpShared_FLOAT32.GiveType(Name)
    if TypeNum==11:
        from FLOAT32 import _SharedTool as Mod_NpShared
    if TypeNum==12:
        from FLOAT64 import _SharedTool as Mod_NpShared
    if TypeNum==14:
        from COMPLEX64 import _SharedTool as Mod_NpShared
    if TypeNum==15:
        from COMPLEX128 import _SharedTool as Mod_NpShared
    if TypeNum==5:
        from INT32 import _SharedTool as Mod_NpShared
    if TypeNum==7:
        from INT64 import _SharedTool as Mod_NpShared
    if TypeNum==0:
        from BOOL import _SharedTool as Mod_NpShared
    
    Mod_NpShared.Release(Name)

def CreateArray(Name,Shape,dtype):
    if dtype==np.float32:
        from FLOAT32 import _SharedTool as Mod_NpShared
    if dtype==np.float64:
        from FLOAT64 import _SharedTool as Mod_NpShared
    if dtype==np.complex64:
        from COMPLEX64 import _SharedTool as Mod_NpShared
    if dtype==np.complex128:
        from COMPLEX128 import _SharedTool as Mod_NpShared
    if dtype==np.bool:
        from BOOL import _SharedTool as Mod_NpShared
    if dtype==np.int32:
        from INT32 import _SharedTool as Mod_NpShared
    if dtype==np.int64:
        from INT64 import _SharedTool as Mod_NpShared
    
    a=Mod_NpShared.CreateShared(Name,list(Shape))
    a.fill(0)
    return a




def m():
    a=CreateArray("abdc",[5,5],np.float32)
    print a
    print "============================"
    b=GiveArray("abdc")
    print b.dtype
    print b


def mp():
    a=sNpShared.GiveShared("abdc")
    print type(a)
    print a
    return a
