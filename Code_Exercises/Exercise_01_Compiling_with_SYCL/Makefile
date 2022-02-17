export SYCL_LANGUAGE_VERSION := 2020
CXX = dpcpp
CXXFLAGS = -O2 -g -std=c++17 -I../../External/Catch2/single_include
LDFLAGS = -lOpenCL -lsycl

BUFFER_EXE_NAME = exercise01.out
BUFFER_SOURCES = solution.cpp
# BUFFER_SOURCES = source.cpp

USM_EXE_NAME = exercise01-usm
# USM_SOURCES = src/vector-add-usm.cpp

all: build_buffers

build_buffers:
	echo SYCL_LANGUAGE_VERSION: $$SYCL_LANGUAGE_VERSION
	$(CXX) $(CXXFLAGS) -o $(BUFFER_EXE_NAME) $(BUFFER_SOURCES) $(LDFLAGS)

# build_usm:
# 	$(CXX) $(CXXFLAGS) -o $(USM_EXE_NAME) $(USM_SOURCES)

run: 
	./$(BUFFER_EXE_NAME)

# run_usm: 
# 	./$(USM_EXE_NAME)

clean: 
	rm -f $(BUFFER_EXE_NAME) $(USM_EXE_NAME)
