#if !defined(SETTLERS_OF_CATAN_UTIL_H)

#if defined(SOC_DEBUG)
#define Assert(Expr) if(!(Expr)) {printf("'%s' failed!", #Expr); *((int *)0) = 0;}
#else
#define Assert(Expr)
#endif

#define InvalidDefaultCase default: {printf("Default case is not supported! (in %s(L%d))", __FILE__, __LINE__); *((int *)0) = 0;} break

template <typename t> inline t
Pow(t Base, t Exp) {
    t Result = Base;

    for(uint32 Index = 0;
        Index < Exp;
        ++Index) {
        Result *= Base;
    }

    return(Result);
}

#define SETTLERS_OF_CATAN_UTIL_H
#endif // SETTLERS_OF_CATAN_UTIL_H
