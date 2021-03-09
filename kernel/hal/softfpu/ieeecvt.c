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

#if INTEGER_TYPE_BITS >= B_MANTISSA_BITS
#define extend_11	extend_fname
#define truncate_11	truncate_fname
#elif INTEGER_TYPE_BITS >= S_MANTISSA_BITS
#define extend_12	extend_fname
#define truncate_21	truncate_fname
#else
#define extend_22	extend_fname
#define truncate_22	truncate_fname
#endif

#define UP_MSB ((INTEGER_TYPE) 1 << (INTEGER_TYPE_BITS - 1))
#define UP_MANT_MASK (UP_MSB - 1)

union s_real_extract_1
{
  S_FLOATING_TYPE d;
  INTEGER_TYPE u:S_MANTISSA_BITS+S_EXP_BITS;
};

union s_real_extract_2
{
  S_FLOATING_TYPE d;
  struct
    {
#if defined (FLOAT_WORDS_BIG_ENDIAN)
      INTEGER_TYPE h, l;
#else
      INTEGER_TYPE l, h;
#endif
    } ii;
};

#if INTEGER_TYPE_BITS >= B_MANTISSA_BITS
union b_real_extract_1
{
  B_FLOATING_TYPE d;
  INTEGER_TYPE u:B_MANTISSA_BITS+B_EXP_BITS;
};
#endif

union b_real_extract_2
{
  B_FLOATING_TYPE d;
  struct
    {
#if defined (FLOAT_WORDS_BIG_ENDIAN)
      INTEGER_TYPE h, l;
#else
      INTEGER_TYPE l, h;
#endif
    } ii;
};

/* Macros for handling packed floats.  */
#define S_EXP_MASK ((1 << S_EXP_BITS) - 1)
#define B_EXP_MASK ((1 << B_EXP_BITS) - 1)
#define S_STICKY_MASK ((1 << (S_EXP_BITS - 1)) - 1)
#define B_STICKY_MASK ((1 << (B_EXP_BITS - 1)) - 1)
#define S_SIGN_POS (S_MANTISSA_BITS + S_EXP_BITS - 1)
#define B_SIGN_POS (B_MANTISSA_BITS + B_EXP_BITS - 1)
#define S_HIGM_MANT_MASK (((INTEGER_TYPE) 1 << (INTEGER_TYPE_BITS - S_EXP_BITS - 1)) - 1)
#define B_HIGM_MANT_MASK (((INTEGER_TYPE) 1 << (INTEGER_TYPE_BITS - B_EXP_BITS - 1)) - 1)
#define S_EXP_BIAS ((1 << (S_EXP_BITS - 1)) - 2)
#define B_EXP_BIAS ((1 << (B_EXP_BITS - 1)) - 2)

/* Unpack the IEEE double DBL.  The mantissa is put in M.  The sign bit and
   the biased exponent are put in EXP, in such a way that the sign bit is
   replicated into all remaining bits.  */
#define s_unpack_1(m, exp, dbl) \
  do {									\
    union s_real_extract_1 di;						\
    di.d = (dbl);							\
    (exp) = ((INTEGER_STYPE) di.u >> (S_MANTISSA_BITS - 1));		\
    (m) = (di.u & (((INTEGER_TYPE) 1 << (S_MANTISSA_BITS - 1)) - 1)) << S_EXP_BITS; \
  } while (0)
#define b_unpack_1(m, exp, dbl) \
  do {									\
    union b_real_extract_1 di;						\
    di.d = (dbl);							\
    (exp) = ((INTEGER_STYPE) di.u >> (B_MANTISSA_BITS - 1));		\
    (m) = (di.u & (((INTEGER_TYPE) 1 << (B_MANTISSA_BITS - 1)) - 1)) << B_EXP_BITS; \
  } while (0)

#define s_round_and_pack_1(dbl, m, exp) \
  do {									\
    union s_real_extract_1 di;						\
    INTEGER_TYPE __t;							\
    di.u = ((INTEGER_TYPE) (exp) << (S_MANTISSA_BITS - 1)) | ((m) >> S_EXP_BITS); \
    __t = (((m >> (S_EXP_BITS - 1)) & 1)					\
           & (((m & S_STICKY_MASK) != 0) | ((m >> S_EXP_BITS) & 1)));	\
    di.u += __t;	/* round up, possibly carrying into exp */	\
    dbl = di.d;								\
  } while (0)
#define s_pack_1(dbl, m, exp) \
  do {									\
    union s_real_extract_1 di;						\
    di.u = ((INTEGER_TYPE) (exp) << (S_MANTISSA_BITS - 1)) | ((m) >> S_EXP_BITS); \
    dbl = di.d;								\
  } while (0)

#define b_pack_1(dbl, m, exp) \
  do {									\
    union b_real_extract_1 di;						\
    di.u = ((INTEGER_TYPE) (exp) << (B_MANTISSA_BITS - 1)) | ((m) >> B_EXP_BITS); \
    dbl = di.d;								\
  } while (0)

/* Unpack the IEEE double DBL.  The most significant bits of the mantissa are
   put in HM.  The remaining bits are put in LM.  The sign bit and the biased
   exponent bits are put in EXP, in such a way that the sign bit is replicated
   in all remaining bits.  */
#define s_unpack_2(hm, lm, exp, dbl) \
  do {									\
    union s_real_extract_2 di;						\
    di.d = (dbl);							\
    (exp) = ((INTEGER_STYPE) di.ii.h >> (INTEGER_TYPE_BITS - S_EXP_BITS - 1)); \
    (lm) = di.ii.l << S_EXP_BITS;						\
    (hm) = (((di.ii.h & S_HIGM_MANT_MASK) << S_EXP_BITS)			\
		   | (di.ii.l >> (INTEGER_TYPE_BITS - S_EXP_BITS)));	\
  } while (0)
#define b_unpack_2(hm, lm, exp, dbl) \
  do {									\
    union b_real_extract_2 di;						\
    di.d = (dbl);							\
    (exp) = ((INTEGER_STYPE) di.ii.h >> (INTEGER_TYPE_BITS - B_EXP_BITS - 1)); \
    (lm) = di.ii.l << B_EXP_BITS;						\
    (hm) = (((di.ii.h & B_HIGM_MANT_MASK) << B_EXP_BITS)			\
		   | (di.ii.l >> (INTEGER_TYPE_BITS - B_EXP_BITS)));	\
  } while (0)

#define s_round_and_pack_2(dbl, hm, lm, exp) \
  do {									\
    union s_real_extract_2 di;						\
    INTEGER_TYPE __t;							\
    di.ii.h = (((INTEGER_TYPE) (exp) << (INTEGER_TYPE_BITS - S_EXP_BITS - 1)) \
	       | ((hm) >> S_EXP_BITS));					\
    di.ii.l = ((hm) << (INTEGER_TYPE_BITS - S_EXP_BITS)) | ((lm) >> S_EXP_BITS); \
    __t = (((lm >> (S_EXP_BITS - 1)) & 1)				\
	   & (((lm & S_STICKY_MASK) != 0) | ((lm >> S_EXP_BITS) & 1)));	\
    di.ii.l += __t;		/* round up low word */			\
    di.ii.h += di.ii.l < __t;	/* propagate carry to high word */	\
    dbl = di.d;								\
  } while (0)
#define s_pack_2(dbl, hm, lm, exp) \
  do {									\
    union s_real_extract_2 di;						\
    di.ii.h = (((INTEGER_TYPE) (exp) << (INTEGER_TYPE_BITS - S_EXP_BITS - 1)) \
	       | ((hm) >> S_EXP_BITS));					\
    di.ii.l = ((hm) << (INTEGER_TYPE_BITS - S_EXP_BITS)) | ((lm) >> S_EXP_BITS); \
    dbl = di.d;								\
  } while (0)

#define  b_pack_2(dbl, hm, lm, exp) \
  do {									\
    union b_real_extract_2 di;						\
    di.ii.h = (((INTEGER_TYPE) (exp) << (INTEGER_TYPE_BITS - B_EXP_BITS - 1)) \
	       | ((hm) >> B_EXP_BITS));					\
    di.ii.l = ((hm) << (INTEGER_TYPE_BITS - B_EXP_BITS)) | ((lm) >> B_EXP_BITS); \
    dbl = di.d;								\
  } while (0)

#if defined (truncate_11)
S_FLOATING_TYPE
truncate_11 (B_FLOATING_TYPE u)
{
  INTEGER_TYPE um;
  int ue;
  S_FLOATING_TYPE r;

  b_unpack_1 (um, ue, u);
  ue = ue - B_EXP_BIAS + S_EXP_BIAS;
  s_round_and_pack_1 (r, um, ue);

  return r;
}
#endif

#if defined (truncate_21)
S_FLOATING_TYPE
truncate_21 (B_FLOATING_TYPE u)
{
  INTEGER_TYPE umh, uml;
  int ue;
  S_FLOATING_TYPE r;

  b_unpack_2 (umh, uml, ue, u);
  if ((unsigned) (ue & B_EXP_MASK) - (B_EXP_BIAS - S_EXP_BIAS)-1 >= S_EXP_MASK - 1)
    {
      int e = (ue & B_EXP_MASK) - B_EXP_BIAS;

      if ((ue & B_EXP_MASK) == 0)
	{
	  /* Input is 0 or denorm.  Generate 0.  */
	  ue = (ue & ~B_EXP_MASK) >> (B_EXP_BITS - S_EXP_BITS);
	  umh = 0;
	}
      else if (e <= -S_EXP_BIAS)
	{
	  int d = -(e + S_EXP_BIAS) + 1;
	  if (d >= INTEGER_TYPE_BITS)
	    {
	      /* Generate 0.  */
	      ue = 0;
	      umh = 0;
	    }
	  else
	    {
	      /* Input is in range where we should generate a denorm.  */
	      ue = (ue & ~B_EXP_MASK) >> (B_EXP_BITS - S_EXP_BITS);
	      umh |= UP_MSB;
	      umh = (umh >> d) | ((umh & ((1 << d) - 1)) != 0);
	      umh |= uml != 0;
	      s_round_and_pack_1 (r, umh, ue);
	      return r;
	    }
	}
      else if (e > (1 << (S_EXP_BITS - 1)))
	{
	  /* Input is Inf or NaN or too large for output format.  */
	  if ((ue & B_EXP_MASK) != B_EXP_MASK)
	    umh = 0;			/* Return Inf if input is not NaN */
	  else if ((umh | uml) != 0)
	    umh = UP_MANT_MASK;
	  ue = ((ue & ~B_EXP_MASK) >> (B_EXP_BITS - S_EXP_BITS)) | S_EXP_MASK;
	}
      else
	ue |= (ue >> B_EXP_BITS) << S_EXP_BITS;
      s_pack_1 (r, umh, ue);
      return r;
    }

  ue = ue - B_EXP_BIAS + S_EXP_BIAS;
  ue |= (ue >> B_EXP_BITS) << S_EXP_BITS;
  umh |= uml != 0;

  s_round_and_pack_1 (r, umh, ue);
  return r;
}
#endif

#if defined (truncate_22)
S_FLOATING_TYPE
truncate_22 (B_FLOATING_TYPE u)
{
  INTEGER_TYPE umh, uml;
  int ue;
  S_FLOATING_TYPE r;

  b_unpack_2 (umh, uml, ue, u);
  ue = ue - B_EXP_BIAS + S_EXP_BIAS;
  s_round_and_pack_2 (r, umh, uml, ue);

  return r;
}
#endif

#if defined (extend_11)
B_FLOATING_TYPE
extend_11 (S_FLOATING_TYPE u)
{
  INTEGER_TYPE um;
  int ue;
  B_FLOATING_TYPE r;

  s_unpack_1 (um, ue, u);
  ue = ue - S_EXP_BIAS + B_EXP_BIAS;
  b_pack_1 (r, um, ue);

  return r;
}
#endif

#if defined (extend_12)
B_FLOATING_TYPE
extend_12 (S_FLOATING_TYPE u)
{
  INTEGER_TYPE um;
  int ue;
  B_FLOATING_TYPE r;

  s_unpack_1 (um, ue, u);

  if ((unsigned) ((ue + 1) & S_EXP_MASK) <= 1)
    {
      ue &= ~((1 << B_EXP_BITS) - (1 << S_EXP_BITS));
      if ((ue & S_EXP_MASK) == 0)
	{
	  if (um != 0)
	    {
	      int d = 0;
	      while ((INTEGER_STYPE) um >= 0)
		{
		  um <<= 1;
		  d++;
		}
	      um &= UP_MANT_MASK;
	      ue += B_EXP_BIAS - S_EXP_BIAS - d + 1;
	    }
	}
      else
	ue = ue - 2 * S_EXP_BIAS + 2 * B_EXP_BIAS;
    }
  else
    {
      ue &= ~((1 << B_EXP_BITS) - (1 << S_EXP_BITS));
      ue = ue - S_EXP_BIAS + B_EXP_BIAS;
    }

  b_pack_2 (r, um, 0, ue);
  return r;
}
#endif

#if defined (extend_22)
B_FLOATING_TYPE
extend_22 (S_FLOATING_TYPE u)
{
  INTEGER_TYPE umh, uml;
  int ue;
  B_FLOATING_TYPE r;

  s_unpack_2 (umh, uml, ue, u);
  ue = ue - S_EXP_BIAS + B_EXP_BIAS;
  b_pack_2 (r, umh, uml, ue);

  return r;
}
#endif
