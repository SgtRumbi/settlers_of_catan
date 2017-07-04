#if !defined(SETTLERS_OF_CATAN_UTIL_H)

#if defined(SOC_DEBUG)
#define Assert(Expr) if(!(Expr)) {printf("'%s' failed!", #Expr); *((int *)0) = 0;}
#else
#define Assert(Expr)
#endif

#define SETTLERS_OF_CATAN_UTIL_H
#endif // SETTLERS_OF_CATAN_UTIL_H
