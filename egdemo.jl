typealias FILE Ptr{Void}

require("libeg_h.jl")
require("libeg.jl")

egOpAdd = cglobal((:egOpAdd, "libeg"))
egOpMultiply = cglobal((:egOpMultiply, "libeg"))

println("egOpAdd: ", egOpAdd)
println("egOpMultiply: ", egOpMultiply)

usage(prog) = println("usage: ", prog, " <N> <outfile>")

# Note: Julia uses libuv for cross-platform async i/o, so we define our own ccall's to fopen/fclose for this demo.

fopen(name::ASCIIString, mode::ASCIIString) = ccall(:fopen, Ptr{Void}, (Ptr{Uint8}, Ptr{Uint8}), "foo", "w")
fclose(hnd::Ptr{Void}) = ccall(:fclose, Void, (Ptr{Void},), hnd)

function main(argv)
    me = Base.source_path()
    if (2 != length(argv))
        usage(me)
        return 1
    end

    nn = 0
    try
        nn = uint(argv[1])
    catch
        error(me, " couldn't parse", argv[1], " as uint");
        usage(me)
        return 1
    end
  
    if ((f_out = fopen(argv[2], "w")) == C_NULL)
        error(me, " couldn't open ", argv[2], " for writing")
        usage(me)
        return 1
    end

    A = egVecNew(nn);
    B = egVecNew(nn);
    C = egVecNew(nn);
    D = egVecNew(nn);

    if (egVecSet(A, 1) != 0
        || egVecSet(B, 2) != 0
        || egVecCopy(C, B) != 0
        || egVecOperate(D, egOpAdd, A, C) != 0
        || egVecPrint(f_out, D) != 0)
        error(me, " problem")
        fclose(f_out)
        return 1
    end

    egVecNix(A);
    egVecNix(B);
    egVecNix(C);
    egVecNix(D);

    fclose(f_out);
    return 0
end

main(ARGS)
