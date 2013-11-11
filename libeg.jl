# Julia wrapper for header: eglib/eglib.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0

@c Ptr{egVec} egVecNew (Uint32,) libeg
@c None egVecNix (Ptr{egVec},) libeg
@c Cint egVecSet (Ptr{egVec}, Cfloat) libeg
@c Cint egVecCopy (Ptr{egVec}, Ptr{egVec}) libeg
@c Cint egVecPrint (Ptr{FILE}, Ptr{egVec}) libeg
@c Cint egVecOperate (Ptr{egVec}, Ptr{egOp}, Ptr{egVec}, Ptr{egVec}) libeg

