/* File : example.i */
%module shape

%{
#include "shape.h"
%}

/* Let's just grab the original header file here */
%include "shape.h"
