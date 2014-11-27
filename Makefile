# ---- Link --------------------------- 
_SharedTool.so:  SharedTool.o 
	gcc -shared SharedTool.o -o _SharedTool.so -lrt

# ---- gcc C compile ------------------
SharedTool.o:  SharedTool.c SharedTool.h
	gcc -c SharedTool.c -I/usr/include/python2.7 -I/usr/lib/python2.7/dist-packages/numpy/core/include/numpy -fPIC -lrt	

#gcc -c Gridder.c -I/usr/include/python2.7 -I/usr/lib/python2.7/dist-packages/numpy/core/include/numpy -fPIC

# # ---- Link --------------------------- 
# _pyGridder1D.so:  Gridder1D.o 
# 	gcc -shared Gridder1D.o -o _pyGridder1D.so

# # ---- gcc C compile ------------------
# Gridder1D.o:  Gridder1D.c Gridder1D.h
# 	gcc -c Gridder1D.c -I/usr/include/python2.7 -I/usr/lib/python2.7/dist-packages/numpy/core/include/numpy -fPIC

