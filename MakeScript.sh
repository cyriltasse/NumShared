
mkdir -p FLOAT32
mkdir -p FLOAT64
touch FLOAT32/__init__.py
touch FLOAT64/__init__.py
make -f Makefile_FLOAT64
make -f Makefile_FLOAT32
rm *.o
