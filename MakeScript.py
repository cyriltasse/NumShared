#!/usr/bin/env python

import os

def Make():


    Types=["FLOAT32","FLOAT64","COMPLEX64","COMPLEX128","BOOL","INT32","INT64"]
    for Type in Types:
        DirOut=Type

        os.system("rm -rf %s"%Type)

        os.system("mkdir -p %s"%Type)

        os.system("touch %s/__init__.py"%Type)

        strExec="gcc -c -DUSE_%s=1 SharedTool.c -I/usr/include/python2.7 -I/usr/lib/python2.7/dist-packages/numpy/core/include/numpy -fPIC -lrt	"%Type
        os.system(strExec)

        strExec="gcc -shared SharedTool.o -o %s/_SharedTool.so -lrt"%DirOut
        os.system(strExec)


if __name__=="__main__":
    Make()
