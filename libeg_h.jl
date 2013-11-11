macro c(ret_type, func, arg_types, lib)
    local args_in = Any[ symbol(string('a',x)) for x in 1:length(arg_types.args) ]
    quote
        $(esc(func))($(args_in...)) = ccall( ($(string(func)), $(Expr(:quote, lib)) ), $ret_type, $arg_types, $(args_in...) )
    end
end


const EG_PI = 3.14159265358979323846
# Skipping MacroDefinition: EG_AFFINE(i,x,I,o,O)(((double)(O)-(o))*((double)(x)-(i))/((double)(I)-(i))+(o))
# Skipping MacroDefinition: EG_CALLOC(N,T)(T*)(calloc((N),sizeof(T)))
# begin enum ANONYMOUS_1
typealias ANONYMOUS_1 Cint
const egEnumNegOne = -1
const egEnumZero = 0
const egEnumOne = 1
const egEnumTwo = 2
const egEnumThree = 3
# end enum ANONYMOUS_1
type egOp
    str::Ptr{Uint8}
    f::Ptr{Void}
end
type egVec
    desc::Ptr{Uint8}
    nn::Uint32
    vv::Ptr{Cfloat}
end
