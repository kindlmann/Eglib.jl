using Clang.wrap_c
       context = wrap_c.init(; output_file="libeg.jl",
                             header_library=x->"libeg",
                             header_wrapped=(x,y)->contains(y, "eglib.h"),
                             common_file="libeg_h.jl", clang_diagnostics=true,
                             clang_args=["-v"], clang_includes=["/cmn/julia/usr/bin/", "/home/isaiah/Downloads/eglib/h"])
       context.options.wrap_structs = true
       wrap_c.wrap_c_headers(context, ["h/eglib.h"])
