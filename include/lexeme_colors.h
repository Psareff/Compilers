#define TYPE              "#6895d2"
#define DIRECTIVE         "#96E9C6"
#define USER_DEFINED_TYPE "#FF6868"

{"int", TYPE},
{"double", TYPE},
{"char", TYPE},
{"typedef", TYPE},
{"unsigned", TYPE},
{"static", TYPE},

{"#define", DIRECTIVE},
{"#include", DIRECTIVE},
{"#ifdef", DIRECTIVE},
{"#include", DIRECTIVE},

{"class", USER_DEFINED_TYPE},
{"struct", USER_DEFINED_TYPE}

#undef TYPE
#undef DIRECTIVE
#undef USER_DEFINED_TYPE
