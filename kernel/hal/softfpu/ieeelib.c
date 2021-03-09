/* IEEE 754 format floating-point routines.  */
/* Copyright (C) 1991, 1995, 1998 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

/*
#include "config.h"
#include "real.h"
*/

#include "ieee.h"

union real_extract_1
{
  FLOATING_TYPE d;
  COMPUTE_TYPE u;
};

union real_extract_2
{
  FLOATING_TYPE d;
  struct
    {
#if defined (FLOAT_WORDS_BIG_ENDIAN)
      COMPUTE_TYPE h, l;
#else
      COMPUTE_TYPE l, h;
#endif
    } ii;
};

#define OVERFLOW \
  return 0.0

#define UWtype COMPUTE_TYPE		/* needed by longlong.h */
#define UHWtype unsigned int		/* needed by longlong.h */
#define UDWtype unsigned long long	/* needed by longlong.h */
#define W_TYPE_SIZE COMPUTE_TYPE_BITS	/* needed by longlong.h */
#define UQItype unsigned char		/* needed by obsolete longlong.h */

typedef signed int HItype __attribute__ ((mode (HI)));
typedef signed int SItype __attribute__ ((mode (SI)));
typedef signed int DItype __attribute__ ((mode (DI)));
typedef unsigned int UHItype __attribute__ ((mode (HI)));
typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));

/* Make longlong avoid depending on separate, machine-dependent files.  */
#define LONGLONG_STANDALONE

#include "longlong.h"

typedef float SFtype __attribute__ ((mode (SF)));
typedef float DFtype __attribute__ ((mode (DF)));

/* The type of the result of a fp compare */
#ifndef CMPtype
#define CMPtype SItype
#endif

/* Macros for handling packed floats.  */
#define EXP_MASK ((1 << EXP_BITS) - 1)
#define STICKY_MASK ((1 << (EXP_BITS - 1)) - 1)
#define SIGN_POS (MANTISSA_BITS + EXP_BITS - 1)
#define HIGM_MANT_MASK (((COMPUTE_TYPE) 1 << (COMPUTE_TYPE_BITS - EXP_BITS - 1)) - 1)
#define EXP_BIAS ((1 << (EXP_BITS - 1)) - 2)

/* Macros for handling unpacked ("UP") floats.  */
#define UP_MSB ((COMPUTE_TYPE) 1 << (COMPUTE_TYPE_BITS - 1))
#define UP_MANT_MASK (UP_MSB - 1)
#define UP_NAN_NONSIGNALLING \
 (((COMPUTE_TYPE) EXP_MASK << (MANTISSA_BITS - 1))			\
  | ((COMPUTE_TYPE) 1 << (MANTISSA_BITS - 2)))
#define UP_NAN_NONSIGNALLING_HI \
 (((COMPUTE_TYPE) EXP_MASK << (MANTISSA_BITS - COMPUTE_TYPE_BITS - 1))	\
  | ((COMPUTE_TYPE) 1 << (MANTISSA_BITS - COMPUTE_TYPE_BITS - 2)))
#define UP_NAN_NONSIGNALLING_LO 0
#define UP_INF \
 ((COMPUTE_TYPE) EXP_MASK << (MANTISSA_BITS - 1))
#define UP_INF_HI \
 ((COMPUTE_TYPE) EXP_MASK << (MANTISSA_BITS - COMPUTE_TYPE_BITS - 1))
#define UP_INF_LO 0

/* Unpack the IEEE double DBL.  The mantissa is put in M.  The sign bit and
   the biased exponent are put in EXP, in such a way that the sign bit is
   replicated into all remaining bits.  */
#define unpack_1(m, exp, dbl) \
  do {									\
    union real_extract_1 di;						\
    di.d = (dbl);							\
    (exp) = ((COMPUTE_STYPE) di.u >> (MANTISSA_BITS - 1));		\
    (m) = (di.u & (((COMPUTE_TYPE) 1 << (MANTISSA_BITS - 1)) - 1)) << EXP_BITS; \
  } while (0)

#define unpack_for_compare_1(m, exp, dbl) \
  do {									\
    union real_extract_1 di;						\
    di.d = (dbl);							\
    (exp) = ((di.u >> (MANTISSA_BITS - 1)) & EXP_MASK) ^ (di.u >> SIGN_POS); \
    (m) = (di.u & (((COMPUTE_TYPE) 1 << (MANTISSA_BITS - 1)) - 1)) << EXP_BITS; \
  } while (0)

#define round_and_pack_1(dbl, m, exp) \
  do {									\
    union real_extract_1 di;						\
    COMPUTE_TYPE __t;							\
    di.u = ((COMPUTE_TYPE) (exp) << (MANTISSA_BITS - 1)) | ((m) >> EXP_BITS); \
    __t = (((m >> (EXP_BITS - 1)) & 1)					\
           & (((m & STICKY_MASK) != 0) | ((m >> EXP_BITS) & 1)));	\
    di.u += __t;	/* round up, possibly carrying into exp */	\
    dbl = di.d;								\
  } while (0)

/* Unpack the IEEE double DBL.  The most significant bits of the mantissa are
   put in HM.  The remaining bits are put in LM.  The sign bit and the biased
   exponent bits are put in EXP, in such a way that the sign bit is replicated
   in all remaining bits.  */
#define unpack_2(hm, lm, exp, dbl) \
  do {									\
    union real_extract_2 di;						\
    di.d = (dbl);							\
    (exp) = ((COMPUTE_STYPE) di.ii.h >> (COMPUTE_TYPE_BITS - EXP_BITS - 1)); \
    (lm) = di.ii.l << EXP_BITS;						\
    (hm) = (((di.ii.h & HIGM_MANT_MASK) << EXP_BITS)			\
		   | (di.ii.l >> (COMPUTE_TYPE_BITS - EXP_BITS)));	\
  } while (0)

#define unpack_for_compare_2(hm, lm, exp, dbl) \
  do {									\
    union real_extract_2 di;						\
    di.d = (dbl);							\
    (exp) = (((di.ii.h >> (COMPUTE_TYPE_BITS - EXP_BITS - 1)) & EXP_MASK) \
	     ^ ((COMPUTE_STYPE) di.ii.h >> (COMPUTE_TYPE_BITS - 1)));	\
    (lm) = di.ii.l << EXP_BITS;						\
    (hm) = (((di.ii.h & HIGM_MANT_MASK) << EXP_BITS)			\
		   | (di.ii.l >> (COMPUTE_TYPE_BITS - EXP_BITS)));	\
  } while (0)

#define round_and_pack_2(dbl, hm, lm, exp) \
  do {									\
    union real_extract_2 di;						\
    COMPUTE_TYPE __t;							\
    di.ii.h = (((COMPUTE_TYPE) (exp) << (COMPUTE_TYPE_BITS - EXP_BITS - 1)) \
	       | ((hm) >> EXP_BITS));					\
    di.ii.l = ((hm) << (COMPUTE_TYPE_BITS - EXP_BITS)) | ((lm) >> EXP_BITS); \
    __t = (((lm >> (EXP_BITS - 1)) & 1)					\
	   & (((lm & STICKY_MASK) != 0) | ((lm >> EXP_BITS) & 1)));	\
    di.ii.l += __t;		/* round up low word */			\
    di.ii.h += di.ii.l < __t;	/* propagate carry to high word */	\
    dbl = di.d;								\
  } while (0)

#if defined (SFmode)
#define add_1		__addsf3
#define sub_1		__subsf3
#define mul_1		__mulsf3
#define div_1		__divsf3
#define cmp_1		__cmpsf2
#define neg_1		__negsf2
#define eq_1		__eqsf2
#define ne_1		__nesf2
#define gt_1		__gtsf2
#define ge_1		__gesf2
#define lt_1		__ltsf2
#define le_1		__lesf2
#define floatsifp_1	__floatsisf
#define floatunssifp_1	__floatunsisf
#define fixfpsi_1	__fixsfsi
#define fixunsfpsi_1	__fixunssfsi
#define truncdfsf_1	__extendsfdf2
#endif

#if defined (DFmode)
#if COMPUTE_TYPE_BITS < MANTISSA_BITS + 3
#define add_2		__adddf3
#define sub_2		__subdf3
#define mul_2		__muldf3
#define div_2		__divdf3
#define cmp_2		__cmpdf2
#define neg_2		__negdf2
#define eq_2		__eqdf2
#define ne_2		__nedf2
#define gt_2		__gtdf2
#define ge_2		__gedf2
#define lt_2		__ltdf2
#define le_2		__ledf2
#define floatsifp_2	__floatsidf
#define floatunssifp_2	__floatunsidf
#define fixfpsi_2	__fixdfsi
#define fixunsfpsi_2	__fixunsdfsi
#define truncdfsf_2	__truncdfsf2
#else
#define add_1		__adddf3
#define sub_1		__subdf3
#define mul_1		__muldf3
#define div_1		__divdf3
#define cmp_1		__cmpdf2
#define neg_1		__negdf2
#define eq_1		__eqdf2
#define ne_1		__nedf2
#define gt_1		__gtdf2
#define ge_1		__gedf2
#define lt_1		__ltdf2
#define le_1		__ledf2
#define floatsifp_1	__floatsidf
#define floatunssifp_1	__floatunssidf
#define fixfpsi_1	__fixdfsi
#define fixunsfpsi_1	__fixunsdfsi
#define truncdfsf_1	__truncdfsf2
#endif
#endif

#if defined (TFmode) && 2 * COMPUTE_TYPE_BITS >= MANTISSA_BITS + 3
#define add_2		__addtf3
#define sub_2		__subtf3
#define mul_2		__multf3
#define div_2		__divtf3
#define cmp_2		__cmptf2
#define neg_2		__negtf2
#define eq_2		__eqtf2
#define ne_2		__netf2
#define gt_2		__gttf2
#define ge_2		__getf2
#define lt_2		__lttf2
#define le_2		__letf2
#define floatsifp_2	__floatsitf
#define floatunssifp_2	__floatunssitf
#define fixfpsi_2	__fixtfsi
#define fixunsfpsi_2	__fixunstfsi
#define trunctfsf_2	__trunctfsf2
#endif

#if defined (COUNT_LEADING_ZEROS_NEED_CLZ_TAB)
const unsigned char __clz_tab[] =
{
  0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};
#endif

#ifdef add_1
FLOATING_TYPE
add_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  COMPUTE_TYPE um, vm, rm;
  int ue, ve, re;
  int e;
  FLOATING_TYPE r;

  unpack_1 (um, ue, u);
  unpack_1 (vm, ve, v);

  /* Determine if we are to add or subtract.  */
  if ((ue ^ ve) >= 0)	/* ADDITION */
    {
      /* Subtract the exponents.  They are both biased, so their
	 difference reflects the true, unbiased difference.  */
      e = ue - ve;
      if (e > 0)
	{				/* U > V */
	  re = ue;
	  if ((ve & EXP_MASK) == 0)
	    {
	      /* V is zero or denormalized.  */
	      if (vm == 0)
		return u;		/* ANY+0 */
	      else
		{			/* ANY+D */
		  e--;
		  if (e == 0)
		    {
		      rm = um + vm;
		      goto add3;
		    }
		  goto add1;
		}
	    }
	  else if ((~ue & EXP_MASK) == 0)
	    return u;			/* NaN+R or Inf+R */

	  /* Insert the implicit most significant bit of V.  Shift the mantissa
	     of V to the right E steps.  Don't bother about the implicit most
	     significant bit of U, as we know it's there and compensate for it
	     later.  We need some special cases here, depending on if E is less
	     than, equal to, or greater than our word size.  */
	  vm |= UP_MSB;
	add1:
	  if (e >= COMPUTE_TYPE_BITS) /* could say MANTISSA_BITS + 1 ??? */
	    return u;
	  else
	    {
	      COMPUTE_TYPE lw;
	      lw = vm >> e;
	      lw |= (vm << (COMPUTE_TYPE_BITS - e)) != 0;
	      rm = um + lw;
	    }
	}
      else if (e < 0)
	{				/* U < V */
	  e = -e;
	  re = ve;
	  /* This is very similar to the code above, with U and V swapped.
	     For comments, see above.  */
	  if ((ue & EXP_MASK) == 0)
	    {
	      /* U is zero or denormalized.  */
	      if (um == 0)
		return v;		/* 0+ANY */
	      else
		{			/* D+ANY */
		  e--;
		  if (e == 0)
		    {
		      rm = vm + um;
		      goto add3;
		    }
		  goto add2;
		}
	    }
	  else if ((~ve & EXP_MASK) == 0)
	    return v;			/* R+NaN or 0+Inf */

	  um |= UP_MSB;
	add2:
	  if (e >= COMPUTE_TYPE_BITS)
	    return v;
	  else
	    {
	      COMPUTE_TYPE lw;
	      lw = um >> e;
	      lw |= (um << (COMPUTE_TYPE_BITS - e)) != 0;
	      rm = vm + lw;
	    }
	}
      else /* (e == 0) */
	{
	  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
	    {
	      if ((ue & EXP_MASK) == 0)
		{
		  /* U and V are zero or denormalized.  */
		  if (um == 0)
		    return v;		/* (+0)+(+0), (+0)+(+D), (-0)+(-0) or (-0)+(-D) */
		  else
		    {
		      /* U is denormalized.  V is zero or denormalized.  */
		      if (vm == 0)
			return u;	/* (+D)+(+0) or (-D)+(-0) */
		      else
			{		/* (+D)+(+D) or (-D)+(-D) */
			  rm = um + vm;
			  if ((COMPUTE_STYPE) rm < 0)
			    {
			      /* Got a normalized result.  */
			      rm &= UP_MANT_MASK;
			      re = ue + 1;
			    }
			  else
			    {
			      re = ue;
			    }
			  goto done;
			}
		    }
		}
	      else /* ((~ue & EXP_MASK) == 0) */
		{
		  /* NaN+NaN or NaN+Inf or (-NaN)+(-NaN) or (-NaN)+(-Inf)
		     Inf+NaN or Inf+Inf or (-Inf)+(-NaN) or (-Inf)+(-Inf) */
		  if (um == 0)
		    return v;
		  else
		    return u;
		}
	    }
	  /* The exponents of U and V are equal.  The implicit most significant
	     bits of U and V make it necessary to always shift back the result
	     of the addition below.  */
	  rm = um + vm;

	  rm = rm >> 1;
	  re = ue + 1;
	  if ((~re & EXP_MASK) == 0)
	    rm = 0;		/* Got a too large result, R = Inf */
	  goto done;
	}

    add3:
      if ((COMPUTE_STYPE) rm < 0)
	{
	  /* We got overflow.  The exponent of R needs adjustment, and
	     the mantissa needs to be shifted back.  */
	  re++;
	  rm = ((rm & UP_MANT_MASK) >> 1) | (rm & 1);
	  if ((~re & EXP_MASK) == 0)
	    rm = 0;			/* R = Inf */
	}
    }
  else			/* SUBTRACTION */
    {
      e = (ue & EXP_MASK) - (ve & EXP_MASK);
      if (e > 0)
	{				/* |U| > |V| */
	  re = ue;
	  if ((ve & EXP_MASK) == 0)
	    {
	      /* V is zero or denormalized.  */
	      if (vm == 0)
		return u;		/* ANY+(-0) */
	      else
		{			/* ANY+(-D) */
		  e--;
		  if (e == 0)
		    {
		      rm = um - vm;
		      goto sub3;
		    }
		  goto sub1;
		}
	    }
	  else if ((~ue & EXP_MASK) == 0)
	    return u;			/* NaN+(-R) or Inf+(-0) */

	  /* Insert the implicit most significant bit of V.  Shift the mantissa
	     of V to the right E steps.  Don't bother about the implicit most
	     significant bit of U, as we know it's there and compensate for it
	     later.  We need some special cases here, depending on if E is less
	     than, equal to, or greater than our word size.  */
	  vm |= UP_MSB;
	sub1:
	  if (e >= COMPUTE_TYPE_BITS)
	    return u;
	  else
	    {
	      COMPUTE_TYPE lw;;
	      lw = vm >> e;
	      lw |= (vm << (COMPUTE_TYPE_BITS - e)) != 0;
	      rm = um - lw;
	    }
	}
      else if (e < 0)
	{				/* |U| < |V| */
	  e = -e;
	  re = ve;
	  /* This is very similar to the code above, with U and V swapped.
	     For comments, see above.  */
	  if ((ue & EXP_MASK) == 0)
	    {
	      /* U is zero or denormalized.  */
	      if (um == 0)
		return v;		/* 0+(-ANY) */
	      else
		{			/* D+(-ANY) */
		  e--;
		  if (e == 0)
		    {
		      rm = vm - um;
		      goto sub3;
		    }
		  goto sub2;
		}
	    }
	  else if ((~ve & EXP_MASK) == 0)
	    return v;			/* R-NaN or 0-Inf */

	  um |= UP_MSB;
	sub2:
	  if (e >= COMPUTE_TYPE_BITS)
	    return v;
	  else
	    {
	      COMPUTE_TYPE lw;
	      lw = um >> e;
	      lw |= (um << (COMPUTE_TYPE_BITS - e)) != 0;
	      rm = vm - lw;
	    }
	}
      else /* (e == 0) */
	{
	  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
	    {
	      if ((ue & EXP_MASK) == 0)
		{
		  /* U and V are zero or denormalized.  */
		  if (um == 0)
		    {
		      if (vm == 0)
			return 0.0;	/* (+0)+(-0) or (-0)+(+0) */
		      return v;		/* (+0)+(-D) or (-0)+(+D) */
		    }
		  else
		    {
		      /* U is denormalized.  V is zero or denormalized.  */
		      if (vm == 0)
			return u;	/* (+D)+(-0) or (-D)+(+0) */
		      else
			{		/* (+D)+(-D) or (-D)+(+D) */
			  rm = um - vm;
			  if ((COMPUTE_STYPE) rm < 0)
			    {
			      /* |U| < |V|.  Negate result.  */
			      rm = -rm;
			      re = ve;
			    }
			  else
			    {
			      /* |U| >= |V|.  */
			      if (rm == 0)
				return 0.0;
			      re = ue;
			    }
			  goto done;
			}
		    }
		}
	      else /* ((~ue & EXP_MASK) == 0) */
		{
		  /* NaN+NaN or NaN+Inf or (-NaN)+(-NaN) or (-NaN)+(-Inf)
		     Inf+NaN or Inf+Inf or (-Inf)+(-NaN) or (-Inf)+(-Inf) */
		  if ((ue ^ ve) < 0)
		    {
		      union real_extract_1 NaN;
		      NaN.u = UP_NAN_NONSIGNALLING;
		      return NaN.d;
		    }
		  if (um == 0)
		    return v;
		  else
		    return u;
		}
	    }
	  /* The exponents of U and V are equal.  The implicit most significant
	     bits of U and V cancel.  */
	  re = ue;
	  rm = um - vm;

	  if ((COMPUTE_STYPE) rm < 0)
	    {
	      /* |U| < |V|.  Negate result.  */
	      rm = -rm;
	      re = ve;
	    }
	  goto norm;
	}

    sub3:
      if ((COMPUTE_STYPE) rm < 0)
	{
	  /* We got carry into the implicit most significant bit of U,
	     canceling it.  We need to re-normalize R.  */
	  /* Actually, we will need just 1 step on average here, so using
	     count_leading_zeros is usually overkill, unless it is a
	     single-cycle operation.  */
	  rm &= UP_MANT_MASK;
	norm:
	  if (rm != 0)
	    {
	      int cnt;
	      count_leading_zeros (cnt, rm);
	      rm = rm << cnt;

	      if ((re & EXP_MASK) <= cnt)
		{
		  /* R is a denorm.  Shift it away... */
		  cnt = cnt - (re & EXP_MASK) + 1;
		  rm = rm >> cnt;
		  re &= ~EXP_MASK;
		}
	      else
		{
		  re -= cnt;
		  rm &= UP_MANT_MASK;
		}
	    }
	  else
	    re = 0;			/* Result is 0.0 */
	}
    }

 done:
  round_and_pack_1 (r, rm, re);
  return r;
}
#endif

#ifdef add_2
FLOATING_TYPE
add_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  COMPUTE_TYPE uh, ul, vh, vl, rh, rl;
  int ue, ve, re;
  int e;
  FLOATING_TYPE r;

  unpack_2 (uh, ul, ue, u);
  unpack_2 (vh, vl, ve, v);

  /* Determine if we are to add or subtract.  */
  if ((ue ^ ve) >= 0)	/* ADDITION */
    {
      /* Subtract the exponents.  They are both biased, so their
	 difference reflects the true, unbiased difference.  */
      e = ue - ve;
      if (e > 0)
	{				/* U > V */
	  re = ue;
	  if ((ve & EXP_MASK) == 0)
	    {
	      /* V is zero or denormalized.  */
	      if ((vh | vl) == 0)
		return u;		/* ANY+0 */
	      else
		{			/* ANY+D */
		  e--;
		  if (e == 0)
		    {
		      add_ssaaaa (rh, rl, uh, ul, vh, vl);
		      goto add3;
		    }
		  goto add1;
		}
	    }
	  else if ((~ue & EXP_MASK) == 0)
	    return u;			/* NaN+R or Inf+0 */

	  /* Insert the implicit most significant bit of V.  Shift the mantissa
	     of V to the right E steps.  Don't bother about the implicit most
	     significant bit of U, as we know it's there and compensate for it
	     later.  We need some special cases here, depending on if E is less
	     than, equal to, or greater than our word size.  */
	  vh |= UP_MSB;
	add1:
	  if (e >= COMPUTE_TYPE_BITS)
	    {
	      if (e >= 2 * COMPUTE_TYPE_BITS)
		return u;
	      else
		{
		  COMPUTE_TYPE lw; int e2;
		  e2 = e & (COMPUTE_TYPE_BITS - 1);
		  lw = vh >> e2;
		  lw |= e2 != 0 ? (vh << (COMPUTE_TYPE_BITS - e2)) != 0 : 0;
		  lw |= vl != 0;
		  add_ssaaaa (rh, rl, uh, ul, 0, lw);
		}
	    }
	  else
	    {
	      COMPUTE_TYPE lw; int e2;
	      e2 = COMPUTE_TYPE_BITS - e;
	      lw = (vh << e2) | (vl >> e);
	      lw |= (vl << e2) != 0;
	      add_ssaaaa (rh, rl, uh, ul, vh >> e, lw);
	    }
	}
      else if (e < 0)
	{				/* U < V */
	  e = -e;
	  re = ve;
	  /* This is very similar to the code above, with U and V swapped.
	     For comments, see above.  */
	  if ((ue & EXP_MASK) == 0)
	    {
	      /* U is zero or denormalized.  */
	      if ((uh | ul) == 0)
		return v;		/* 0+ANY */
	      else
		{			/* D+ANY */
		  e--;
		  if (e == 0)
		    {
		      add_ssaaaa (rh, rl, vh, vl, uh, ul);
		      goto add3;
		    }
		  goto add2;
		}
	    }
	  else if ((~ve & EXP_MASK) == 0)
	    return v;			/* R+NaN or 0+Inf */

	  uh |= UP_MSB;
	add2:
	  if (e >= COMPUTE_TYPE_BITS)
	    {
	      if (e >= 2 * COMPUTE_TYPE_BITS)
		return v;
	      else
		{
		  COMPUTE_TYPE lw; int e2;
		  e2 = e & (COMPUTE_TYPE_BITS - 1);
		  lw = uh >> e2;
		  lw |= e2 != 0 ? (uh << (COMPUTE_TYPE_BITS - e2)) != 0 : 0;
		  lw |= ul != 0;
		  add_ssaaaa (rh, rl, vh, vl, 0, lw);
		}
	    }
	  else
	    {
	      COMPUTE_TYPE lw; int e2;
	      e2 = COMPUTE_TYPE_BITS - e;
	      lw = (uh << e2) | (ul >> e);
	      lw |= (ul << e2) != 0;
	      add_ssaaaa (rh, rl, vh, vl, uh >> e, lw);
	    }
	}
      else /* (e == 0) */
	{
	  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
	    {
	      if ((ue & EXP_MASK) == 0)
		{
		  /* U and V are zero or denormalized.  */
		  if ((uh | ul) == 0)
		    return v;		/* (+0)+(+0), (+0)+(+D), (-0)+(-0) or (-0)+(-D) */
		  else
		    {
		      /* U is denormalized.  V is zero or denormalized.  */
		      if ((vh | vl) == 0)
			return u;	/* (+D)+(+0) or (-D)+(-0) */
		      else
			{		/* (+D)+(+D) or (-D)+(-D) */
			  add_ssaaaa (rh, rl, uh, ul, vh, vl);
			  if ((COMPUTE_STYPE) rh < 0)
			    {
			      /* Got a normalized result.  */
			      rh &= UP_MANT_MASK;
			      re = ue + 1;
			    }
			  else
			    {
			      re = ue;
			    }
			  goto done;
			}
		    }
		}
	      else /* ((~ue & EXP_MASK) == 0) */
		{
		  /* NaN+NaN or NaN+Inf or (-NaN)+(-NaN) or (-NaN)+(-Inf)
		     Inf+NaN or Inf+Inf or (-Inf)+(-NaN) or (-Inf)+(-Inf) */
		  if ((uh | ul) == 0)
		    return v;
		  else
		    return u;
		}
	    }
	  /* The exponents of U and V are equal.  The implicit most significant
	     bits of U and V make it necessary to always shift back the result
	     of the addition below.  */
	  add_ssaaaa (rh, rl, uh, ul, vh, vl);

	  rl = (rh << (COMPUTE_TYPE_BITS - 1)) | (rl >> 1);
	  rh = rh >> 1;
	  re = ue + 1;
	  if ((~re & EXP_MASK) == 0)
	    rh = rl = 0;	/* Got a too large result, R = Inf */
	  goto done;
	}

    add3:
      if ((COMPUTE_STYPE) rh < 0)
	{
	  /* We got overflow.  The exponent of R needs adjustment, and
	     the mantissa needs to be shifted back.  */
	  re++;
	  rl = (rh << (COMPUTE_TYPE_BITS - 1)) | (rl >> 1) | (rl & 1);
	  rh = (rh & UP_MANT_MASK) >> 1;
	  if ((~re & EXP_MASK) == 0)
	    rh = rl = 0;		/* R = Inf */
	}
    }
  else			/* SUBTRACTION */
    {
      e = (ue & EXP_MASK) - (ve & EXP_MASK);
      if (e > 0)
	{				/* |U| > |V| */
	  re = ue;
	  if ((ve & EXP_MASK) == 0)
	    {
	      /* V is zero or denormalized.  */
	      if ((vh | vl) == 0)
		return u;		/* ANY+(-0) */
	      else
		{			/* ANY+(-D) */
		  e--;
		  if (e == 0)
		    {
		      sub_ddmmss (rh, rl, uh, ul, vh, vl);
		      goto sub3;
		    }
		  goto sub1;
		}
	    }
	  else if ((~ue & EXP_MASK) == 0)
	    return u;			/* NaN+(-R) or Inf+(-0) */

	  /* Insert the implicit most significant bit of V.  Shift the mantissa
	     of V to the right E steps.  Don't bother about the implicit most
	     significant bit of U, as we know it's there and compensate for it
	     later.  We need some special cases here, depending on if E is less
	     than, equal to, or greater than our word size.  */
	  vh |= UP_MSB;
	sub1:
	  if (e >= COMPUTE_TYPE_BITS)
	    {
	      if (e >= 2 * COMPUTE_TYPE_BITS)
		return u;
	      else
		{
		  COMPUTE_TYPE lw; int e2;
		  e2 = e & (COMPUTE_TYPE_BITS - 1);
		  lw = vh >> e2;
		  lw |= e2 != 0 ? (vh << (COMPUTE_TYPE_BITS - e2)) != 0 : 0;
		  lw |= vl != 0;
		  sub_ddmmss (rh, rl, uh, ul, 0, lw);
		}
	    }
	  else
	    {
	      COMPUTE_TYPE lw; int e2;
	      e2 = COMPUTE_TYPE_BITS - e;
	      lw = (vh << e2) | (vl >> e);
	      lw |= (vl << e2) != 0;
	      sub_ddmmss (rh, rl, uh, ul, vh >> e, lw);
	    }
	}
      else if (e < 0)
	{				/* |U| < |V| */
	  e = -e;
	  re = ve;
	  /* This is very similar to the code above, with U and V swapped.
	     For comments, see above.  */
	  if ((ue & EXP_MASK) == 0)
	    {
	      /* U is zero or denormalized.  */
	      if ((uh | ul) == 0)
		return v;		/* 0+(-ANY) */
	      else
		{			/* D+(-ANY) */
		  e--;
		  if (e == 0)
		    {
		      sub_ddmmss (rh, rl, vh, vl, uh, ul);
		      goto sub3;
		    }
		  goto sub2;
		}
	    }
	  else if ((~ve & EXP_MASK) == 0)
	    return v;			/* R-NaN or 0-Inf */

	  uh |= UP_MSB;
	sub2:
	  if (e >= COMPUTE_TYPE_BITS)
	    {
	      if (e >= 2 * COMPUTE_TYPE_BITS)
		return v;
	      else
		{
		  COMPUTE_TYPE lw; int e2;
		  e2 = e & (COMPUTE_TYPE_BITS - 1);
		  lw = uh >> e2;
		  lw |= e2 != 0 ? (uh << (COMPUTE_TYPE_BITS - e2)) != 0 : 0;
		  lw |= ul != 0;
		  sub_ddmmss (rh, rl, vh, vl, 0, lw);
		}
	    }
	  else
	    {
	      COMPUTE_TYPE lw; int e2;
	      e2 = COMPUTE_TYPE_BITS - e;
	      lw = (uh << e2) | (ul >> e);
	      lw |= (ul << e2) != 0;
	      sub_ddmmss (rh, rl, vh, vl, uh >> e, lw);
	    }
	}
      else /* (e == 0) */
	{
	  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
	    {
	      if ((ue & EXP_MASK) == 0)
		{
		  /* U and V are zero or denormalized.  */
		  if ((uh | ul) == 0)
		    {
		      if ((vh | vl) == 0)
			return 0.0;	/* (+0)+(-0) or (-0)+(+0) */
		      return v;		/* (+0)+(-D) or (-0)+(+D) */
		    }
		  else
		    {
		      /* U is denormalized.  V is zero or denormalized.  */
		      if ((vh | vl) == 0)
			return u;	/* (+D)+(-0) or (-D)+(+0) */
		      else
			{		/* (+D)+(-D) or (-D)+(+D) */
			  sub_ddmmss (rh, rl, uh, ul, vh, vl);
			  if ((COMPUTE_STYPE) rh < 0)
			    {
			      /* |U| < |V|.  Negate result.  */
			      rl = -rl;
			      rh = -rh - (rl != 0);
			      re = ve;
			    }
			  else
			    {
			      /* |U| >= |V|.  */
			      if ((rh | rl) == 0)
				return 0.0;
			      re = ue;
			    }
			  goto done;
			}
		    }
		}
	      else /* ((~ue & EXP_MASK) == 0) */
		{
		  /* NaN+NaN or NaN+Inf or (-NaN)+(-NaN) or (-NaN)+(-Inf)
		     Inf+NaN or Inf+Inf or (-Inf)+(-NaN) or (-Inf)+(-Inf) */
		  if ((ue ^ ve) < 0)
		    {
		      union real_extract_2 NaN;
		      NaN.ii.h = UP_NAN_NONSIGNALLING_HI;
		      NaN.ii.l = UP_NAN_NONSIGNALLING_LO;
		      return NaN.d;
		    }
		  if ((uh | ul) == 0)
		    return v;
		  else
		    return u;
		}
	    }
	  /* The exponents of U and V are equal.  The implicit most significant
	     bits of U and V cancel.  */
	  re = ue;
	  sub_ddmmss (rh, rl, uh, ul, vh, vl);

	  if ((COMPUTE_STYPE) rh < 0)
	    {
	      /* |U| < |V|.  Negate result.  */
	      rl = -rl;
	      rh = -rh - (rl != 0);
	      re = ve;
	    }
	  goto norm;
	}

    sub3:
      if ((COMPUTE_STYPE) rh < 0)
	{
	  /* We got carry into the implicit most significant bit of U,
	     canceling it.  We need to re-normalize R.  */
	  /* Actually, we will need just 1 step on average here, so using
	     count_leading_zeros is usually overkill, unless it is a
	     single-cycle operation.  */
	  rh &= UP_MANT_MASK;
	norm:
	  if (rh != 0)
	    {
	      int cnt;
	      count_leading_zeros (cnt, rh);
	      rh = (rh << cnt) | (rl >> (COMPUTE_TYPE_BITS - cnt));
	      rl = rl << cnt;

	      if ((re & EXP_MASK) <= cnt)
		{
		  /* R is a denorm.  Shift it away... */
		  cnt = cnt - (re & EXP_MASK) + 1;
		  rl = (rh << (COMPUTE_TYPE_BITS - cnt)) | (rl >> cnt);
		  rh = rh >> cnt;
		  re &= ~EXP_MASK;
		}
	      else
		{
		  re -= cnt;
		  rh &= UP_MANT_MASK;
		}
	    }
	  else if (rl != 0)
	    {
	      int cnt;
	      count_leading_zeros (cnt, rl);
	      rh = rl << cnt;
	      rl = 0;

	      if ((re & EXP_MASK) <= COMPUTE_TYPE_BITS + cnt)
		{
		  /* R is a denorm.  Shift it away... */
		  cnt = COMPUTE_TYPE_BITS + cnt - (re & EXP_MASK) + 1;
		  if (cnt >= COMPUTE_TYPE_BITS)
		    {
		      rl = rh >> (cnt - COMPUTE_TYPE_BITS);
		      rh = 0;
		    }
		  else
		    {
		      rl = rh << (COMPUTE_TYPE_BITS - cnt);
		      rh = rh >> cnt;
		    }
		  re &= ~EXP_MASK;
		}
	      else
		{
		  re -= COMPUTE_TYPE_BITS + cnt;
		  rh &= UP_MANT_MASK;
		}
	    }
	  else
	    re = 0;			/* Result is 0.0 */
	}
    }

 done:
  round_and_pack_2 (r, rh, rl, re);
  return r;
}
#endif

/*-----------------------------------------------------------------------------------------*/
#ifdef sub_1
FLOATING_TYPE
sub_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  return add_1 (u, -v);
}
#endif

#ifdef sub_2
FLOATING_TYPE
sub_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  return add_2 (u, -v);
}
#endif
/*-----------------------------------------------------------------------------------------*/
#ifdef neg_1
FLOATING_TYPE
neg_1 (FLOATING_TYPE u)
{
  union real_extract_1 di;

  di.d = u;
  di.u ^= UP_MSB;
  return di.d;
}
#endif

#ifdef neg_2
FLOATING_TYPE
neg_2 (FLOATING_TYPE u)
{
  union real_extract_2 di;

  di.d = u;
  di.ii.h ^= UP_MSB;
  return di.d;
}
#endif
/*-----------------------------------------------------------------------------------------*/
#ifdef abs_1
FLOATING_TYPE
abs_1 (FLOATING_TYPE u)
{
  union real_extract_1 di;

  di.d = u;
  di.u &= ~UP_MSB;
  return di.d;
}
#endif

#ifdef abs_2
FLOATING_TYPE
abs_2 (FLOATING_TYPE u)
{
  union real_extract_2 di;

  di.d = u;
  di.ii.h &= ~UP_MSB;
  return di.d;
}
#endif

/*-----------------------------------------------------------------------------------------*/
#ifdef mul_1
FLOATING_TYPE
mul_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  COMPUTE_TYPE um, vm, rm;
  int ue, ve, re;
  FLOATING_TYPE r;
  COMPUTE_TYPE ph, pl;

  unpack_1 (um, ue, u);
  unpack_1 (vm, ve, v);

  re = (ue & EXP_MASK) + (ve & EXP_MASK) - EXP_BIAS;

  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
    {					/* U = Nan, +-Inf, +-D, or +-0 */
      if ((ue & EXP_MASK) != 0)
	{				/* U = NaN or +-Inf */
	  if (um == 0)
	    {				/* U = +-Inf */
	      if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
		{			/* V = NaN, +-Inf, +-D, or +-0 */
		  if ((ve & EXP_MASK) != 0)
		    {			/* V = NaN or +-Inf */
		      if (v != 0)
			return v;	/* NaN = +-Inf * NaN */
		      else
			return ve >= 0 ? u : -u; /* +-Inf * +-Inf */
		    }
		  else
		    {			/* V = +-D or +-0 */
		      if (v != 0)
			return ve >= 0 ? u : -u; /* +-Inf * +-D */
		      else
			{
			  union real_extract_1 NaN;
			  NaN.u = UP_NAN_NONSIGNALLING;
			  return NaN.d;	/* +-Inf * +-0 */
			}
		    }
		}
	      else
		return ve >= 0 ? u : -u; /* +-Inf * R */
	    }
	  else
	    return u;			/* NaN * ANY */
	}
      else
	{				/* U = +-D, or +-0 */
	  if (um != 0)
	    {
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) um >= 0)
		{
		  um = um << 1;
		  re--;
		}
	      re++;
	    }
	  else
	    {				/* +-0 * ANY */
	      if ((~ve & EXP_MASK) == 0)
		{			/* 0 * +-Inf  or  0 * NaN */
		  union real_extract_1 NaN;
		  NaN.u = UP_NAN_NONSIGNALLING;
		  return NaN.d;
		}
	      else
		return ve >= 0 ? u : -u; /* (+-0)*(+-0) or (+-0)*R */
	    }
	}
    }

  if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
    {
      if ((ve & EXP_MASK) != 0)
	{				/* V = NaN or +-Inf */
	  if (v == 0)
	    return ue >= 0 ? v : -v;	/* R * +-Inf */
	  else
	    return v;			/* ANY * NaN */
	}
      else
	{
	  if (v == 0)
	    return ue >= 0 ? v : -v;
	  else
	    {
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) vm >= 0)
		{
		  vm = vm << 1;
		  re--;
		}
	      re++;
	    }
	}
    }

  /* Insert implicit bits for both operands.  */
  um |= UP_MSB;
  vm |= UP_MSB;
  /* Generate full two-word product.  (It might be possible to generate just
     the upper word here, as long as we properly compute the sticky bit.)  */
  umul_ppmm (ph, pl, um, vm);

  rm = ph | (pl != 0);

  if ((COMPUTE_STYPE) rm >= 0)
    {
      rm = rm << 1;
      re--;
    }
  rm &= UP_MANT_MASK;
  if (re >= EXP_MASK)
    {				/* Exponent overflow; R = +-Inf */
      re = EXP_MASK;
      rm = 0;
    }
  else if (re <= 0)
    {				/* Exponent underflow; R is denorm or 0 */
      if (re > -MANTISSA_BITS)
	{			/* R is a denorm.  Shift it away... */
	  int cnt = -re + 1;
	  rm |= UP_MSB;
	  rm = rm >> cnt;
	  re = 0;
	}
      else
	{
	  rm = 0;
	  re = 0;
	}
    }

  re |= (ue ^ ve) & ~EXP_MASK;

  round_and_pack_1 (r, rm, re);
  return r;
}
#endif

#ifdef mul_2
FLOATING_TYPE
mul_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  COMPUTE_TYPE uh, ul, vh, vl, rh, rl;
  int ue, ve, re;
  FLOATING_TYPE r;
  COMPUTE_TYPE x31, x21, x22, x12, x23, x13, x14, x04;
  COMPUTE_TYPE p3, p2, p1, p0;
  COMPUTE_TYPE cy;

  unpack_2 (uh, ul, ue, u);
  unpack_2 (vh, vl, ve, v);

  re = (ue & EXP_MASK) + (ve & EXP_MASK) - EXP_BIAS;

  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
    {					/* U = Nan, +-Inf, +-D, or +-0 */
      if ((ue & EXP_MASK) != 0)
	{				/* U = NaN or +-Inf */
	  if ((uh | ul) == 0)
	    {				/* U = +-Inf */
	      if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
		{			/* V = NaN, +-Inf, +-D, or +-0 */
		  if ((ve & EXP_MASK) != 0)
		    {			/* V = NaN or +-Inf */
		      if ((vh | vl) != 0)
			return v;	/* NaN = +-Inf * NaN */
		      else
			return ve >= 0 ? u : -u; /* +-Inf * +-Inf */
		    }
		  else
		    {			/* V = +-D or +-0 */
		      if ((vh | vl) != 0)
			return ve >= 0 ? u : -u; /* +-Inf * +-D */
		      else
			{
			  union real_extract_2 NaN;
			  NaN.ii.h = UP_NAN_NONSIGNALLING_HI;
			  NaN.ii.l = UP_NAN_NONSIGNALLING_LO;
			  return NaN.d;	/* +-Inf * +-0 */
			}
		    }
		}
	      else
		return ve >= 0 ? u : -u; /* +-Inf * R */
	    }
	  else
	    return u;			/* NaN * ANY */
	}
      else
	{				/* U = +-D, or +-0 */
	  if ((uh | ul) != 0)
	    {
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) uh >= 0)
		{
		  uh = (uh << 1) | (ul >> (COMPUTE_TYPE_BITS - 1));
		  ul = ul << 1;
		  re--;
		}
	      re++;
	    }
	  else
	    {				/* +-0 * ANY */
	      if ((~ve & EXP_MASK) == 0)
		{			/* 0 * +-Inf  or  0 * NaN */
		  union real_extract_2 NaN;
		  NaN.ii.h = UP_NAN_NONSIGNALLING_HI;
		  NaN.ii.l = UP_NAN_NONSIGNALLING_LO;
		  return NaN.d;
		}
	      else
		return ve >= 0 ? u : -u; /* (+-0)*(+-0) or (+-0)*R */
	    }
	}
    }

  if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
    {
      if ((ve & EXP_MASK) != 0)
	{				/* V = NaN or +-Inf */
	  if ((vh | vl) == 0)
	    return ue >= 0 ? v : -v;	/* R * +-Inf */
	  else
	    return v;			/* ANY * NaN */
	}
      else
	{
	  if ((vh | vl) == 0)
	    return ue >= 0 ? v : -v;
	  else
	    {
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) vh >= 0)
		{
		  vh = (vh << 1) | (vl >> (COMPUTE_TYPE_BITS - 1));
		  vl = vl << 1;
		  re--;
		}
	      re++;
	    }
	}
    }

  /* Insert implicit bits for both operands.  */
  uh |= UP_MSB;
  vh |= UP_MSB;
  /* Generate full two-word product.  (It might be possible to generate just
     the upper word here, as long as we properly compute the sticky bit.)  */
  umul_ppmm (x31, x21, uh, vh);
  umul_ppmm (x22, x12, uh, vl);
  umul_ppmm (x23, x13, vh, ul);
  umul_ppmm (x14, x04, ul, vl);
  p0 = x04;
  p1 = x12 + x13;
  cy = p1 < x12;
  p2 = x21 + x22;
  p3 = x31 + (p2 < x21);
  p2 += cy;
  p3 += p2 < cy;
  p1 += x14;
  cy = p1 < x14;
  p2 += x23;
  p3 += p2 < x23;
  p2 += cy;
  p3 += p2 < cy;

  rh = p3;
  rl = p2 | ((p1 | p0) != 0);

  if ((COMPUTE_STYPE) rh >= 0)
    {
      rh = (rh << 1) | (rl >> (COMPUTE_TYPE_BITS - 1));
      rl = rl << 1;
      re--;
    }
  rh &= UP_MANT_MASK;
  if (re >= EXP_MASK)
    {				/* Exponent overflow; R = +-Inf */
      re = EXP_MASK;
      rh = 0;
      rl = 0;
    }
  else if (re <= 0)
    {				/* Exponent underflow; R is denorm or 0 */
      if (re > -MANTISSA_BITS)
	{			/* R is a denorm.  Shift it away... */
	  int cnt = -re + 1;
	  rh |= UP_MSB;
	  if (cnt >= COMPUTE_TYPE_BITS)
	    {
	      if (cnt == COMPUTE_TYPE_BITS)
		rl = rh | (rl != 0);
	      else
		rl = ((rh >> (cnt - COMPUTE_TYPE_BITS)) | (rl != 0)
		      | ((rh << (2 * COMPUTE_TYPE_BITS - cnt)) != 0));
	      rh = 0;
	    }
	  else
	    {
	      rl = ((rh << (COMPUTE_TYPE_BITS - cnt)) | (rl >> cnt)
		    | ((rl << (COMPUTE_TYPE_BITS - cnt)) != 0));
	      rh = rh >> cnt;
	    }
	  re = 0;
	}
      else
	{
	  rh = rl = 0;
	  re = 0;
	}
    }

  re |= (ue ^ ve) & ~EXP_MASK;

  round_and_pack_2 (r, rh, rl, re);
  return r;
}
#endif

/*-----------------------------------------------------------------------------------------*/
#ifdef div_1
static int internal_divide_1 ();
FLOATING_TYPE
div_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  COMPUTE_TYPE um, vm, rm;
  int ue, ve, re;
  FLOATING_TYPE r;

  unpack_1 (um, ue, u);
  unpack_1 (vm, ve, v);

  re = (ue & EXP_MASK) - (ve & EXP_MASK) + EXP_BIAS + 1;

  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
    {					/* U = Nan, +-Inf, +-D, or +-0 */
      if ((ue & EXP_MASK) != 0)
	{				/* U = NaN or +-Inf */
	  if (um == 0)
	    {				/* U = +-Inf */
	      if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
		{			/* V = NaN, +-Inf, +-D, or +-0 */
		  if ((ve & EXP_MASK) != 0)
		    {			/* V = NaN or +-Inf */
		      if (v != 0)
			return v;	/* NaN = +-Inf / NaN */
		      else
			{
			  union real_extract_1 NaN;
			  NaN.u = UP_NAN_NONSIGNALLING;
			  return NaN.d;	/* +-Inf / +-Inf */
			}
		    }
		  else
		    return ve >= 0 ? u : -u; /* +-Inf / +-D  or  +-Inf / +-0 */
		}
	      else
		return ve >= 0 ? u : -u; /* +-Inf / R */
	    }
	  else
	    return u;			/* NaN / ANY */
	}
      else
	{				/* U = +-D or +-0 */
	  if (um != 0)
	    {				/* U = +-0 */
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) um >= 0)
		{
		  um = um << 1;
		  re--;
		}
	      re++;
	    }
	  else
	    {				/* U = +-0 */
	      if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
		{
		  if ((ve & EXP_MASK) != 0)
		    {			/* V = NaN or +-Inf */
		      if (v != 0)
			return v;	/* +-0 / NaN */
		      else
			return ve >= 0 ? u : -u; /* +-0 / +-Inf */
		    }
		  else
		    {			/* V = +-D or +-0 */
		      if (v != 0)
			return ve >= 0 ? u : -u; /* (+-0)/D */
		      else
			{
			  union real_extract_1 NaN;
			  NaN.u = UP_NAN_NONSIGNALLING;
			  return NaN.d;	/* (+-0)/(+-0) */
			}
		    }
		}
	      else
		return ve >= 0 ? u : -u; /* +-0 / R */
	    }
	}
    }

  if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
    {
      if ((ve & EXP_MASK) != 0)
	{				/* V = NaN or +-Inf */
	  if (v == 0)
	    return (ue ^ ve) >= 0 ? 0.0 : -0.0;	/* +-R / +-Inf */
	  else
	    return v;			/* ANY / NaN */
	}
      else
	{				/* V = +-D or +-0 */
	  if (v == 0)
	    {
	      union real_extract_1 Inf;
	      Inf.u = UP_INF | ((COMPUTE_TYPE) ((ue ^ ve) < 0) << (COMPUTE_TYPE_BITS - 1));
	      return Inf.d;		/* (+-R)/(+-0) */
	    }
	  else
	    {
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) vm >= 0)
		{
		  vm = vm << 1;
		  re++;
		}
	      re--;
	    }
	}
    }

  /* Insert implicit bits for both operands.  */
  um |= UP_MSB;
  vm |= UP_MSB;

  {
    COMPUTE_TYPE trm;
    int inexact;
    inexact = internal_divide_1 (um, vm, &trm);
    rm = trm | inexact;
  }

  if ((COMPUTE_STYPE) rm >= 0)
    {
      rm = rm << 1;
      re--;
    }
  rm &= UP_MANT_MASK;
  if (re >= EXP_MASK)
    {				/* Exponent overflow; R = +-Inf */
      re = EXP_MASK;
      rm = 0;
    }
  else if (re <= 0)
    {				/* Exponent underflow; R is denorm or 0 */
      if (re > -MANTISSA_BITS)
	{			/* R is a denorm.  Shift it away... */
	  int cnt = -re + 1;
	  rm |= UP_MSB;
	  rm = rm >> cnt;
	  re = 0;
	}
      else
	{
	  rm = 0;
	  re = 0;
	}
    }

  re |= (ue ^ ve) & ~EXP_MASK;

  round_and_pack_1 (r, rm, re);
  return r;
}
#endif

#ifdef div_2
static int internal_divide_2 ();
FLOATING_TYPE
div_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{
  COMPUTE_TYPE uh, ul, vh, vl, rh, rl;
  int ue, ve, re;
  FLOATING_TYPE r;

  unpack_2 (uh, ul, ue, u);
  unpack_2 (vh, vl, ve, v);

  re = (ue & EXP_MASK) - (ve & EXP_MASK) + EXP_BIAS + 1;

  if ((unsigned) ((ue + 1) & EXP_MASK) <= 1)
    {					/* U = Nan, +-Inf, +-D, or +-0 */
      if ((ue & EXP_MASK) != 0)
	{				/* U = NaN or +-Inf */
	  if ((uh | ul) == 0)
	    {				/* U = +-Inf */
	      if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
		{			/* V = NaN, +-Inf, +-D, or +-0 */
		  if ((ve & EXP_MASK) != 0)
		    {			/* V = NaN or +-Inf */
		      if ((vh | vl) != 0)
			return v;	/* NaN = +-Inf / NaN */
		      else
			{
			  union real_extract_2 NaN;
			  NaN.ii.h = UP_NAN_NONSIGNALLING_HI;
			  NaN.ii.l = UP_NAN_NONSIGNALLING_LO;
			  return NaN.d;	/* +-Inf / +-Inf */
			}
		    }
		  else
		    return ve >= 0 ? u : -u; /* +-Inf / +-D  or  +-Inf / +-0 */
		}
	      else
		return ve >= 0 ? u : -u; /* +-Inf / R */
	    }
	  else
	    return u;			/* NaN / ANY */
	}
      else
	{				/* U = +-D or +-0 */
	  if ((uh | ul) != 0)
	    {				/* U = +-0 */
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) uh >= 0)
		{
		  uh = (uh << 1) | (ul >> (COMPUTE_TYPE_BITS - 1));
		  ul = ul << 1;
		  re--;
		}
	      re++;
	    }
	  else
	    {				/* U = +-0 */
	      if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
		{
		  if ((ve & EXP_MASK) != 0)
		    {			/* V = NaN or +-Inf */
		      if ((vh | vl) != 0)
			return v;	/* +-0 / NaN */
		      else
			return ve >= 0 ? u : -u; /* +-0 / +-Inf */
		    }
		  else
		    {			/* V = +-D or +-0 */
		      if ((vh | vl) != 0)
			return ve >= 0 ? u : -u; /* (+-0)/D */
		      else
			{
			  union real_extract_2 NaN;
			  NaN.ii.h = UP_NAN_NONSIGNALLING_HI;
			  NaN.ii.l = UP_NAN_NONSIGNALLING_LO;
			  return NaN.d;	/* (+-0)/(+-0) */
			}
		    }
		}
	      else
		return ve >= 0 ? u : -u; /* +-0 / R */
	    }
	}
    }

  if ((unsigned) ((ve + 1) & EXP_MASK) <= 1)
    {
      if ((ve & EXP_MASK) != 0)
	{				/* V = NaN or +-Inf */
	  if ((vh | vl) == 0)
	    return (ue ^ ve) >= 0 ? 0.0 : -0.0;	/* +-R / +-Inf */
	  else
	    return v;			/* ANY / NaN */
	}
      else
	{				/* V = +-D or +-0 */
	  if ((vh | vl) == 0)
	    {
	      union real_extract_2 Inf;
	      Inf.ii.h = UP_INF_HI | ((COMPUTE_TYPE) ((ue ^ ve) < 0)
				      << (COMPUTE_TYPE_BITS - 1));
	      Inf.ii.l = UP_INF_LO;
	      return Inf.d;		/* (+-R)/(+-0) */
	    }
	  else
	    {
	      /* Shift denorms into position and adjust exponent.  */
	      while ((COMPUTE_STYPE) vh >= 0)
		{
		  vh = (vh << 1) | (vl >> (COMPUTE_TYPE_BITS - 1));
		  vl = vl << 1;
		  re++;
		}
	      re--;
	    }
	}
    }

  /* Insert implicit bits for both operands.  */
  uh |= UP_MSB;
  vh |= UP_MSB;

  {
    COMPUTE_TYPE rm[2];
    int inexact;
    inexact = internal_divide_2 (uh, ul, vh, vl, rm);
    rh = rm[0];
    rl = rm[1] | inexact;
  }

  if ((COMPUTE_STYPE) rh >= 0)
    {
      rh = (rh << 1) | (rl >> (COMPUTE_TYPE_BITS - 1));
      rl = rl << 1;
      re--;
    }
  rh &= UP_MANT_MASK;
  if (re >= EXP_MASK)
    {				/* Exponent overflow; R = +-Inf */
      re = EXP_MASK;
      rh = 0;
      rl = 0;
    }
  else if (re <= 0)
    {				/* Exponent underflow; R is denorm or 0 */
      if (re > -MANTISSA_BITS)
	{			/* R is a denorm.  Shift it away... */
	  int cnt = -re + 1;
	  rh |= UP_MSB;
	  if (cnt >= COMPUTE_TYPE_BITS)
	    {
	      if (cnt == COMPUTE_TYPE_BITS)
		rl = rh | (rl != 0);
	      else
		rl = ((rh >> (cnt - COMPUTE_TYPE_BITS)) | (rl != 0)
		      | ((rh << (2 * COMPUTE_TYPE_BITS - cnt)) != 0));
	      rh = 0;
	    }
	  else
	    {
	      rl = ((rh << (COMPUTE_TYPE_BITS - cnt)) | (rl >> cnt)
		    | ((rl << (COMPUTE_TYPE_BITS - cnt)) != 0));
	      rh = rh >> cnt;
	    }
	  re = 0;
	}
      else
	{
	  rh = rl = 0;
	  re = 0;
	}
    }

  re |= (ue ^ ve) & ~EXP_MASK;

  round_and_pack_2 (r, rh, rl, re);
  return r;
}
#endif

/*-----------------------------------------------------------------------------------------*/
#ifdef floatsifp_1
FLOATING_TYPE
floatsifp_1 (SItype si)
{
  COMPUTE_TYPE rh;
  FLOATING_TYPE r;
  int cnt;
  COMPUTE_STYPE six = si;

  if (six > 0)
    {
      count_leading_zeros (cnt, six);
      rh = (six << cnt) & UP_MANT_MASK;

      /* ??? No need to round here when MANTISSA_BITS > bits of SImode ??? */
      round_and_pack_1 (r, rh, COMPUTE_TYPE_BITS - cnt + EXP_BIAS);
      return r;
    }
  else if (si < 0)
    {
      six = -six;
      count_leading_zeros (cnt, six);
      rh = (six << cnt) & UP_MANT_MASK;

      /* ??? No need to round here when MANTISSA_BITS > bits of SImode ??? */
      round_and_pack_1 (r, rh, COMPUTE_TYPE_BITS - cnt + (1 << EXP_BITS) + EXP_BIAS);
      return r;
    }
  else
    return 0.0;
}
#endif

#ifdef floatsifp_2
FLOATING_TYPE
floatsifp_2 (SItype si)
{
  COMPUTE_TYPE rh;
  FLOATING_TYPE r;
  int cnt;
  COMPUTE_STYPE six = si;

  if (six > 0)
    {
      count_leading_zeros (cnt, six);
      rh = (six << cnt) & UP_MANT_MASK;

      /* ??? No need to round here when MANTISSA_BITS > bits of SImode ??? */
      round_and_pack_2 (r, rh, 0, COMPUTE_TYPE_BITS - cnt + EXP_BIAS);
      return r;
    }
  else if (si < 0)
    {
      six = -six;
      count_leading_zeros (cnt, six);
      rh = (six << cnt) & UP_MANT_MASK;

      /* ??? No need to round here when MANTISSA_BITS > bits of SImode ??? */
      round_and_pack_2 (r, rh, 0, COMPUTE_TYPE_BITS - cnt + (1 << EXP_BITS) + EXP_BIAS);
      return r;
    }
  else
    return 0.0;
}
#endif
/*-----------------------------------------------------------------------------------------*/
#ifdef floatunssifp_1
FLOATING_TYPE
floatunssifp_1 (USItype ui)
{
  COMPUTE_TYPE rh;
  FLOATING_TYPE r;
  int cnt;
  COMPUTE_TYPE uix = ui;

  if (uix > 0)
    {
      count_leading_zeros (cnt, uix);
      rh = (uix << cnt) & UP_MANT_MASK;

      /* ??? No need to round here when MANTISSA_BITS > bits of SImode ??? */
      round_and_pack_1 (r, rh, COMPUTE_TYPE_BITS - cnt + EXP_BIAS);
      return r;
    }
  else
    return 0.0;
}
#endif

#ifdef floatunssifp_2
FLOATING_TYPE
floatunssifp_2 (USItype ui)
{
  COMPUTE_TYPE rh;
  FLOATING_TYPE r;
  int cnt;
  COMPUTE_TYPE uix = ui;

  if (uix > 0)
    {
      count_leading_zeros (cnt, uix);
      rh = (uix << cnt) & UP_MANT_MASK;

      /* ??? No need to round here when MANTISSA_BITS > bits of SImode ??? */
      round_and_pack_2 (r, rh, 0, COMPUTE_TYPE_BITS - cnt + EXP_BIAS);
      return r;
    }
  else
    return 0.0;
}
#endif
/*-----------------------------------------------------------------------------------------*/
#ifdef fixfpsi_1
SItype
fixfpsi_1 (FLOATING_TYPE u)
{
  COMPUTE_TYPE um;
  int ue;

  unpack_1 (um, ue, u);

  if (ue >= 0)
    {
      ue -= EXP_BIAS + 1;
      if (ue < 0)
	return 0;
      if (ue >= COMPUTE_TYPE_BITS - 1)
	OVERFLOW;
      return ((um | UP_MSB) >> ((COMPUTE_TYPE_BITS - 1) - ue));
    }
  else
    {
      ue += EXP_BIAS + 3;
      if (ue < 0)
	return 0;
      if (ue >= COMPUTE_TYPE_BITS - 1 && !(ue == COMPUTE_TYPE_BITS - 1 && um == 0))
	OVERFLOW;
      return -((um | UP_MSB) >> (COMPUTE_TYPE_BITS - 1 - ue));
    }
}
#endif

#ifdef fixfpsi_2
SItype
fixfpsi_2 (FLOATING_TYPE u)
{
  COMPUTE_TYPE uh, ul;
  int ue;

  unpack_2 (uh, ul, ue, u);

  if (ue >= 0)
    {
      ue -= EXP_BIAS + 1;
      if (ue < 0)
	return 0;
      if (ue >= COMPUTE_TYPE_BITS - 1)
	OVERFLOW;
      return ((uh | UP_MSB) >> ((COMPUTE_TYPE_BITS - 1) - ue));
    }
  else
    {
      ue += EXP_BIAS + 3;
      if (ue < 0)
	return 0;
      if (ue >= COMPUTE_TYPE_BITS - 1 && !(ue == COMPUTE_TYPE_BITS - 1 && uh == 0))
	OVERFLOW;
      return -((uh | UP_MSB) >> (COMPUTE_TYPE_BITS - 1 - ue));
    }
}
#endif
/*-----------------------------------------------------------------------------------------*/
#ifdef fixunsfpsi_1
#ifndef OMIT_FIXUNSFFSI
USItype
fixunsfpsi_1 (FLOATING_TYPE u)
{
  COMPUTE_TYPE um;
  int ue;

  unpack_1 (um, ue, u);

  ue -= EXP_BIAS + 1;
  if (ue < 0)
    return 0;
  if (ue >= COMPUTE_TYPE_BITS)
    OVERFLOW;
  return ((um | UP_MSB) >> (COMPUTE_TYPE_BITS - 1 - ue));
}
#endif
#endif

#ifdef fixunsfpsi_2
#ifndef OMIT_FIXUNSFFSI
USItype
fixunsfpsi_2 (FLOATING_TYPE u)
{
  COMPUTE_TYPE uh, ul;
  int ue;

  unpack_2 (uh, ul, ue, u);

  ue -= EXP_BIAS + 1;
  if (ue < 0)
    return 0;
  if (ue >= COMPUTE_TYPE_BITS)
    OVERFLOW;
  return ((uh | UP_MSB) >> (COMPUTE_TYPE_BITS - 1 - ue));
}
#endif
#endif

/*-----------------------------------------------------------------------------------------*/
#define N_QUOTIENT_BITS (MANTISSA_BITS+1)

#ifdef div_1
/* Divide U by V producing a N_QUOTIENT_BITS quotient in *rp, left-adjusted.
   Both operands (U and V) need to be normalized (i.e., msb must be set).
   Return 0 if division was exact, 1 otherwise.  */
static int
internal_divide_1 (COMPUTE_TYPE u, COMPUTE_TYPE v, COMPUTE_TYPE *rp)
{
  COMPUTE_TYPE q;
  int i;

  q = 0;

  if (u >= v)
    {
      u = u - v;
      q |= 1;
    }

  for (i = N_QUOTIENT_BITS; i != 0; i--)
    {
      q = q << 1;

      if ((COMPUTE_STYPE) u >= 0)
	{
	  u = u << 1;
	  if (u >= v)
	    {
	      u = u - v;
	      q |= 1;
	    }
	}
      else
	{
	  /* We lose a bit here, and thus know the next quotient bit will be one.  */
	  u = u << 1;
	  u = u - v;
	  q |= 1;
	}
    }

  q = q << (COMPUTE_TYPE_BITS - 1 - N_QUOTIENT_BITS);

  *rp = q;
  return u != 0;
}
#endif

#ifdef div_2
/* Divide U=uh,,ul by V=vh,,vl producing a N_QUOTIENT_BITS quotient in
   *rhp,,*rlp, left-adjusted.  Both operands (U and V) need to be normalized
   (i.e., msb must be set).  Return 0 if division was exact, 1 otherwise.  */
static int
internal_divide_2 (COMPUTE_TYPE uh, COMPUTE_TYPE ul,
		   COMPUTE_TYPE vh, COMPUTE_TYPE vl,
		   COMPUTE_TYPE *rm)
{
  COMPUTE_TYPE qh, ql;
  int i;

  qh = ql = 0;

  if (uh > vh || (uh == vh && ul >= vl))
    {
      uh = uh - vh - (ul < vl);
      ul = ul - vl;
      ql |= 1;
    }

  for (i = N_QUOTIENT_BITS; i != 0; i--)
    {
      qh = (qh << 1) | (ql >> (COMPUTE_TYPE_BITS - 1));
      ql = ql << 1;

      if ((COMPUTE_STYPE) uh >= 0)
	{
	  uh = (uh << 1) | (ul >> (COMPUTE_TYPE_BITS - 1));
	  ul = ul << 1;
	  if (uh > vh || (uh == vh && ul >= vl))
	    {
	      uh = uh - vh - (ul < vl);
	      ul = ul - vl;
	      ql |= 1;
	    }
	}
      else
	{
	  /* We lose a bit here, and thus know the next quotient bit will be one.  */
	  uh = (uh << 1) | (ul >> (COMPUTE_TYPE_BITS - 1));
	  ul = ul << 1;
	  uh = uh - vh - (ul < vl);
	  ul = ul - vl;
	  ql |= 1;
	}
    }

  qh = ((qh << (2 * COMPUTE_TYPE_BITS - 1 - N_QUOTIENT_BITS))
	| (ql >> (COMPUTE_TYPE_BITS - (2 * COMPUTE_TYPE_BITS - 1 - N_QUOTIENT_BITS))));
  ql = ql << (2 * COMPUTE_TYPE_BITS - 1 - N_QUOTIENT_BITS);

  rm[0] = qh;
  rm[1] = ql;
  return (uh | ul) != 0;
}
#endif

#ifdef cmp_1
/* Compare two operands.  Assumes NaN has already been taken care of.
   I.e., we can have the operand types: -Inf, -R, -0, +0, +R, +Inf.  */
int
cmp_1 (double u, double v, int nan_retval)
{
  COMPUTE_TYPE um, vm;
  int ue, ve;

  unpack_for_compare_1 (um, ue, u);
  unpack_for_compare_1 (vm, ve, v);

  /* Check for NaN.  ue/ve will be either 0x7ff or 0xfffff800.  */
  if ((COMPUTE_TYPE) ((ue ^ 0x7ff) + 1) <= 1 && um != 0)
    return nan_retval;
  if ((COMPUTE_TYPE) ((ve ^ 0x7ff) + 1) <= 1 && vm != 0)
    return nan_retval;

  /* Check if both operands are 0, either +0 or -0.  Even if the bit patterns
     are not the same for this case, signal operands as being equal.  */
  if ((um | vm) == 0
      && (COMPUTE_TYPE) (ue + 1) <= 1 && (COMPUTE_TYPE) (ve + 1) <= 1)
    return 0;

  /* Compare the exponents.  */
  if (ue > ve)
    return +1;
  if (ue < ve)
    return -1;

  /* Compare the mantissas.  */
  if (um > vm)
    return ue < 0 ? -1 : +1;
  if (um < vm)
    return ue < 0 ? +1 : -1;

  return 0;
}
#endif

#ifdef cmp_2
/* Compare two operands.  Assumes NaN has already been taken care of.
   I.e., we can have the operand types: -Inf, -R, -0, +0, +R, +Inf.  */
int
cmp_2 (double u, double v, int nan_retval)
{
  COMPUTE_TYPE uh, ul, vh, vl;
  int ue, ve;

  unpack_for_compare_2 (uh, ul, ue, u);
  unpack_for_compare_2 (vh, vl, ve, v);

  /* Check for NaN.  ue/ve will be either 0x7ff or 0xfffff800.  */
  if ((COMPUTE_TYPE) ((ue ^ 0x7ff) + 1) <= 1 && (uh | ul) != 0)
    return nan_retval;
  if ((COMPUTE_TYPE) ((ve ^ 0x7ff) + 1) <= 1 && (vh | vl) != 0)
    return nan_retval;

  /* Check if both operands are 0, either +0 or -0.  Even if the bit patterns
     are not the same for this case, signal operands as being equal.  */
  if ((uh | ul | vh | vl) == 0
      && (COMPUTE_TYPE) (ue + 1) <= 1 && (COMPUTE_TYPE) (ve + 1) <= 1)
    return 0;

  /* Compare the exponents.  */
  if (ue > ve)
    return +1;
  if (ue < ve)
    return -1;

  /* Compare the mantissas.  */
  if (uh > vh)
    return ue < 0 ? -1 : +1;
  if (uh < vh)
    return ue < 0 ? +1 : -1;
  if (ul > vl)
    return ue < 0 ? -1 : +1;
  if (ul < vl)
    return ue < 0 ? +1 : -1;

  return 0;
}
#endif

#ifdef eq_1
int
eq_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_1 (u, v, 1); }
#endif

#ifdef eq_2
int
eq_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_2 (u, v, 1); }
#endif

#ifdef ne_1
int
ne_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_1 (u, v, 1); }
#endif

#ifdef ne_2
int
ne_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_2 (u, v, 1); }
#endif

#ifdef gt_1
int
gt_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_1 (u, v, -1); }
#endif

#ifdef gt_2
int
gt_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_2 (u, v, -1); }
#endif

#ifdef ge_1
int
ge_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_1 (u, v, -1); }
#endif

#ifdef ge_2
int
ge_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_2 (u, v, -1); }
#endif

#ifdef lt_1
int
lt_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_1 (u, v, 1); }
#endif

#ifdef lt_2
int
lt_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_2 (u, v, 1); }
#endif

#ifdef le_1
int
le_1 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_1 (u, v, 1); }
#endif

#ifdef le_2
int
le_2 (FLOATING_TYPE u, FLOATING_TYPE v)
{ return cmp_2 (u, v, 1); }
#endif


/* Things to work on:

1. In the integer => floating-point conversion routines, we apply
   count_leading_zeros to arguments just promoted to COMPUTE_TYPE_BITS.  By
   defining count_leading_zeros_si, etc, perhaps in longlong.h, we could save a
   lot in these important routines.
2. The floating-point => floating-point extend and truncate routines don't fit
   nicely in the framework.  We need to know the desired properties of the
   source and target formats.  Now just one format is defined.  Botch it by
   "knowing" some common formats (i.e., IEEE float and double)?
3. We want to override libgcc2.c's DImode <=> floating-point conversion
   routines here. Is doing that straightforward?
4. Integrate comparison routines into this file.
5. Add support for conditional exclusion of denorm code.
6. Add support for conditional exclusion of rounding code.
7. Add support for conditional exclusion of Inf/NaN code.
8. BUG: COMPUTE_TYPE is used in real_extract_*.  For big-endian 64-bit machines that
   is not correct.
*/
