#ifndef NASM_WARNINGS_H
#define NASM_WARNINGS_H

#ifndef WARN_SHR
# error "warnings.h should only be included from within error.h"
#endif

enum warn_index {
	WARN_IDX_NONE                    =   0, /* not suppressible */
	WARN_IDX_BND                     =   1, /* invalid BND prefixes */
	WARN_IDX_DB_EMPTY                =   2, /* no operand for data declaration */
	WARN_IDX_ENVIRONMENT             =   3, /* nonexistent environment variable */
	WARN_IDX_FLOAT_DENORM            =   4, /* floating point denormal */
	WARN_IDX_FLOAT_OVERFLOW          =   5, /* floating point overflow */
	WARN_IDX_FLOAT_TOOLONG           =   6, /* too many digits in floating-point number */
	WARN_IDX_FLOAT_UNDERFLOW         =   7, /* floating point underflow */
	WARN_IDX_HLE                     =   8, /* invalid HLE prefixes */
	WARN_IDX_LABEL_ORPHAN            =   9, /* labels alone on lines without trailing `:' */
	WARN_IDX_LABEL_REDEF             =  10, /* label redefined to an identical value */
	WARN_IDX_LABEL_REDEF_LATE        =  11, /* label (re)defined during code generation */
	WARN_IDX_LOCK                    =  12, /* LOCK prefix on unlockable instructions */
	WARN_IDX_MACRO_DEF_CASE_SINGLE   =  13, /* single-line macro defined both case sensitive and insensitive */
	WARN_IDX_MACRO_DEF_GREEDY_SINGLE =  14, /* single-line macro */
	WARN_IDX_MACRO_DEF_PARAM_SINGLE  =  15, /* single-line macro defined with and without parameters */
	WARN_IDX_MACRO_DEFAULTS          =  16, /* macros with more default than optional parameters */
	WARN_IDX_MACRO_PARAMS_LEGACY     =  17, /* improperly calling multi-line macro for legacy support */
	WARN_IDX_MACRO_PARAMS_MULTI      =  18, /* multi-line macro calls with wrong parameter count */
	WARN_IDX_MACRO_PARAMS_SINGLE     =  19, /* single-line macro calls with wrong parameter count */
	WARN_IDX_NEGATIVE_REP            =  20, /* regative %rep count */
	WARN_IDX_NUMBER_OVERFLOW         =  21, /* numeric constant does not fit */
	WARN_IDX_OBSOLETE_NOP            =  22, /* instruction obsolete and is a noop on the target CPU */
	WARN_IDX_OBSOLETE_REMOVED        =  23, /* instruction obsolete and removed on the target CPU */
	WARN_IDX_OBSOLETE_VALID          =  24, /* instruction obsolete but valid on the target CPU */
	WARN_IDX_PHASE                   =  25, /* phase error during stabilization */
	WARN_IDX_PRAGMA_BAD              =  26, /* malformed %pragma */
	WARN_IDX_PRAGMA_EMPTY            =  27, /* empty %pragma directive */
	WARN_IDX_PRAGMA_NA               =  28, /* %pragma not applicable to this compilation */
	WARN_IDX_PRAGMA_UNKNOWN          =  29, /* unknown %pragma facility or directive */
	WARN_IDX_PTR                     =  30, /* non-NASM keyword used in other assemblers */
	WARN_IDX_REGSIZE                 =  31, /* register size specification ignored */
	WARN_IDX_UNKNOWN_WARNING         =  32, /* unknown warning in -W/-w or warning directive */
	WARN_IDX_USER                    =  33, /* %warning directives */
	WARN_IDX_WARN_STACK_EMPTY        =  34, /* warning stack empty */
	WARN_IDX_ZEROING                 =  35, /* RESx in initialized section becomes zero */
	WARN_IDX_ZEXT_RELOC              =  36, /* relocation zero-extended to match output format */
	WARN_IDX_OTHER                   =  37, /* any warning not specifially mentioned above */
	WARN_IDX_ALL                     =  38  /* all possible warnings */
};

enum warn_const {
	WARN_NONE                        =   0 << WARN_SHR,
	WARN_BND                         =   1 << WARN_SHR,
	WARN_DB_EMPTY                    =   2 << WARN_SHR,
	WARN_ENVIRONMENT                 =   3 << WARN_SHR,
	WARN_FLOAT_DENORM                =   4 << WARN_SHR,
	WARN_FLOAT_OVERFLOW              =   5 << WARN_SHR,
	WARN_FLOAT_TOOLONG               =   6 << WARN_SHR,
	WARN_FLOAT_UNDERFLOW             =   7 << WARN_SHR,
	WARN_HLE                         =   8 << WARN_SHR,
	WARN_LABEL_ORPHAN                =   9 << WARN_SHR,
	WARN_LABEL_REDEF                 =  10 << WARN_SHR,
	WARN_LABEL_REDEF_LATE            =  11 << WARN_SHR,
	WARN_LOCK                        =  12 << WARN_SHR,
	WARN_MACRO_DEF_CASE_SINGLE       =  13 << WARN_SHR,
	WARN_MACRO_DEF_GREEDY_SINGLE     =  14 << WARN_SHR,
	WARN_MACRO_DEF_PARAM_SINGLE      =  15 << WARN_SHR,
	WARN_MACRO_DEFAULTS              =  16 << WARN_SHR,
	WARN_MACRO_PARAMS_LEGACY         =  17 << WARN_SHR,
	WARN_MACRO_PARAMS_MULTI          =  18 << WARN_SHR,
	WARN_MACRO_PARAMS_SINGLE         =  19 << WARN_SHR,
	WARN_NEGATIVE_REP                =  20 << WARN_SHR,
	WARN_NUMBER_OVERFLOW             =  21 << WARN_SHR,
	WARN_OBSOLETE_NOP                =  22 << WARN_SHR,
	WARN_OBSOLETE_REMOVED            =  23 << WARN_SHR,
	WARN_OBSOLETE_VALID              =  24 << WARN_SHR,
	WARN_PHASE                       =  25 << WARN_SHR,
	WARN_PRAGMA_BAD                  =  26 << WARN_SHR,
	WARN_PRAGMA_EMPTY                =  27 << WARN_SHR,
	WARN_PRAGMA_NA                   =  28 << WARN_SHR,
	WARN_PRAGMA_UNKNOWN              =  29 << WARN_SHR,
	WARN_PTR                         =  30 << WARN_SHR,
	WARN_REGSIZE                     =  31 << WARN_SHR,
	WARN_UNKNOWN_WARNING             =  32 << WARN_SHR,
	WARN_USER                        =  33 << WARN_SHR,
	WARN_WARN_STACK_EMPTY            =  34 << WARN_SHR,
	WARN_ZEROING                     =  35 << WARN_SHR,
	WARN_ZEXT_RELOC                  =  36 << WARN_SHR,
	WARN_OTHER                       =  37 << WARN_SHR
};

struct warning_alias {
	const char *name;
	enum warn_index warning;
};

#define NUM_WARNING_ALIAS 42
extern const char * const warning_name[39];
extern const char * const warning_help[39];
extern const struct warning_alias warning_alias[NUM_WARNING_ALIAS];
extern const uint8_t warning_default[38];
extern uint8_t warning_state[38];

#endif /* NASM_WARNINGS_H */
