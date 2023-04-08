
#include <autoconf.h>
#include <sel4test-vbtalloc/gen_config.h>

#include <stdio.h>			/* enable sprintf(), etc. */
#include <string.h>
#include <stdlib.h>			/* for wait(), etc. */
#include <unistd.h>			/* enable close(), pause(), etc. */
#include <sys/types.h>			/* types */
#include <sys/wait.h>			/* wait */
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>			/* for use in link_test */
#include <signal.h>			/* for signal test */
#include <math.h>

#include "aimbench.h"

static int
add_double()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt = 20,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	double
	  d1 = 3.1415,				/* copy of arg 1 */
	  d2 = 3.926,				/* copy of arg 2 */
	  td1 = 3.1415, td2 = 3.926 ,			/* temp copy of args */
	  d;				/* result goes here */


	d1 = td1;			/* use register variables */
	d2 = td2;
	loop_cnt = tloop_cnt;

	d = 0.0;
	/*
	 * Variable Values 
	 */
	/*
	 * d    d1    d2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		d += d1;		/*    x    x     -x   */
		d1 += d2;		/*    x    0     -x   */
		d1 += d2;		/*    x    -x    -x   */
		d2 += d;		/*    x    -x    0    */
		d2 += d;		/*    x    -x    x    */
		d += d1;		/*    0    -x    x    */
		d += d1;		/*    -x   -x    x    */
		d1 += d2;		/*    -x   0     x    */
		d1 += d2;		/*    -x   x     x    */
		d2 += d;		/*    -x   x     0    */
		d2 += d;		/*    -x   x     -x   */
		d += d1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, d1 = -d2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

static int
add_float()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt = 20,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	float
	  f1 = 128.101,				/* copy of arg 1 */
	  f2 = 0.365,				/* copy of arg 2 */
	  tf1 = 128.101, tf2 = 0.365,			/* temp copy of args */
	  f;				/* result goes here */


	f1 = tf1;			/* use register variables */
	f2 = tf2;
	loop_cnt = tloop_cnt;

	f = 0.0;
	/*
	 * Variable Values 
	 */
	/*
	 * f    f1    f2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		f += f1;		/*    x    x     -x   */
		f1 += f2;		/*    x    0     -x   */
		f1 += f2;		/*    x    -x    -x   */
		f2 += f;		/*    x    -x    0    */
		f2 += f;		/*    x    -x    x    */
		f += f1;		/*    0    -x    x    */
		f += f1;		/*    -x   -x    x    */
		f1 += f2;		/*    -x   0     x    */
		f1 += f2;		/*    -x   x     x    */
		f2 += f;		/*    -x   x     0    */
		f2 += f;		/*    -x   x     -x   */
		f += f1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, f1 = -f2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

static int
add_long()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt = 20,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	long
	  l1 = 102023,				/* copy of arg 1 */
	  l2 = 562131,				/* copy of arg 2 */
	  tl1 = 102023, tl2 = 562131,			/* temp copy of args */
	  l;				/* result goes here */

	l1 = tl1;			/* use register variables */
	l2 = tl2;
	loop_cnt = tloop_cnt;

	l = 0;
	/*
	 * Variable Values 
	 */
	/*
	 * l    l1    l2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		l += l1;		/*    x    x     -x   */
		l1 += l2;		/*    x    0     -x   */
		l1 += l2;		/*    x    -x    -x   */
		l2 += l;		/*    x    -x    0    */
		l2 += l;		/*    x    -x    x    */
		l += l1;		/*    0    -x    x    */
		l += l1;		/*    -x   -x    x    */
		l1 += l2;		/*    -x   0     x    */
		l1 += l2;		/*    -x   x     x    */
		l2 += l;		/*    -x   x     0    */
		l2 += l;		/*    -x   x     -x   */
		l += l1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, l1 = -l2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

static int
add_int()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt = 20,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	int
	  i1 = 32,				/* copy of arg 1 */
	  i2 = 64,				/* copy of arg 2 */
	  ti1 = 32, ti2 = 64,			/* temp copy of args */
	  i;				/* result goes here */


	i1 = ti1;			/* use register variables */
	i2 = ti2;
	loop_cnt = tloop_cnt;

	i = 0;
	/*
	 * Variable Values 
	 */
	/*
	 * i    i1    i2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		i += i1;		/*    x    x     -x   */
		i1 += i2;		/*    x    0     -x   */
		i1 += i2;		/*    x    -x    -x   */
		i2 += i;		/*    x    -x    0    */
		i2 += i;		/*    x    -x    x    */
		i += i1;		/*    0    -x    x    */
		i += i1;		/*    -x   -x    x    */
		i1 += i2;		/*    -x   0     x    */
		i1 += i2;		/*    -x   x     x    */
		i2 += i;		/*    -x   x     0    */
		i2 += i;		/*    -x   x     -x   */
		i += i1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, i1 = -i2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

static int
add_short()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt = 20,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	short
	  s1 = 10,				/* copy of arg 1 */
	  s2 = 20,				/* copy of arg 2 */
	  ts1 = 10, ts2 = 20,			/* temp copy of args */
	  s;				/* result goes here */

	
	s1 = ts1;			/* use register variables */
	s2 = ts2;
	loop_cnt = tloop_cnt;

	s = 0;
	/*
	 * Variable Values 
	 */
	/*
	 * s    s1    s2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		s += s1;		/*    x    x     -x   */
		s1 += s2;		/*    x    0     -x   */
		s1 += s2;		/*    x    -x    -x   */
		s2 += s;		/*    x    -x    0    */
		s2 += s;		/*    x    -x    x    */
		s += s1;		/*    0    -x    x    */
		s += s1;		/*    -x   -x    x    */
		s1 += s2;		/*    -x   0     x    */
		s1 += s2;		/*    -x   x     x    */
		s2 += s;		/*    -x   x     0    */
		s2 += s;		/*    -x   x     -x   */
		s += s1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, s1 = -s2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

int aimbench_testcase_add_test(){
  add_double(),
  add_float(),
  add_long(),
  add_short(),
  add_int();
}

int aimbench_testcase_page_test()
{
	int
	  i,				/* loop variable */
	  j,				/* dirty page pointer */
	  n = 10,				/* iteration count */
	  i32 = 10,				/* argument */
	  brk();			/* system call */

	void
	 *oldbrk,			/* old top of memory */
	 *newbrk,			/* new top of memory */
	 *sbrk();			/* system call */

	char *cp;			/* pointer to new memory region */

	/*
	 * Step 1: Get argument
	 */

	/*
	 * Step 2: Get old memory top, move top higher
	 */
	oldbrk = sbrk(0);		/* get current break value */
	newbrk = sbrk(16);	/* move up 1 megabyte */
	if ((long)newbrk == -1) {
		perror("\npage_test");	/* tell more info */
		fprintf(stderr, "page_test: Unable to do initial sbrk.\n");
		return (-1);
	}
	/*
	 * Step 3: The loop
	 */
	n = i32;
	while (n--) {			/* while not done */
		newbrk = sbrk(-1024 * 16);	/* deallocate some space */
		for (i = 0; i < 16; i++) {	/* now get it back in pieces */
			newbrk = sbrk(1024);	/* Get pointer to new space */
			if ((long)newbrk == -1) {
				perror("\npage_test");	/* tell more info */
				fprintf(stderr,
					"page_test: Unable to do sbrk.\n");
				return (-1);
			}
			cp = (char *)newbrk;	/* prepare to dirty it so pages into memory */
			for (j = 0; j < 1024; j += 128) {	/* loop through new region */
				cp[j] = ' ';	/* dirty the page */
			}		/* end for */
		}			/* end for */
	}				/* end while */
	/*
	 * Step 4: Clean up by moving break back to old value
	 */
	brk(oldbrk);
	return 0;
}

int aimbench_testcase_brk_test()
{
	int
	  i, n, i32=10, brk();
	void
	 *oldbrk, *newbrk, *sbrk();

	/*
	 * Step 1: get argument
	 */

	/*
	 * Step 2: get old memory top, move top higher
	 */
	oldbrk = sbrk(0);		/* get old break value */
	newbrk = sbrk(1024 * 1024);	/* move up 1 megabyte */
	if ((long)newbrk == -1) {
		//perror("\nbrk_test");	/* tell more info */
		//fprintf(stderr, "brk_test: Unable to do initial sbrk.\n");
		return (-1);
	}
	/*
	 * Step 3: The loop
	 */
	n = i32;
	while (n--) {			/* while not done */
		newbrk = sbrk(-4096 * 16);	/* deallocate some space */
		for (i = 0; i < 16; i++) {	/* allocate it back */
			newbrk = sbrk(4096);	/* 4k at a time (should be ~ 1 page) */
			if ((long)newbrk == -1) {
				perror("\nbrk_test");	/* tell more info */
				fprintf(stderr,
					"brk_test: Unable to do sbrk.\n");
				return (-1);
			}
		}
	}
	/*
	 * Step 4: clean up
	 */
	brk(oldbrk);
	return 0;
}

static int
div_double()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt = 20,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	double
	  d1 = 3.12345,				/* copy of arg 1 */
	  d2 = 1.23456,				/* copy of arg 2 */
	  td1 = 3.12345, td2 = 1.23456,			/* temp copy of args */
	  d;				/* result goes here */


	d1 = td1;			/* use register variables */
	d2 = td2;
	loop_cnt = tloop_cnt;

	d = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * d    d1    d2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		d /= d1;		/*    1/x  x     1/x  */
		d2 /= d;		/*    1/x  x     1    */
		d1 /= d2;		/*    1/x  x     1    */
		d2 /= d1;		/*    1/x  x     1/x  */
		d /= d2;		/*    1    x     1/x  */
		d2 /= d;		/*    1    x     1/x  */
		d /= d1;		/*    1/x  x     1/x  */
		d2 /= d;		/*    1/x  x     1    */
		d1 /= d2;		/*    1/x  x     1    */
		d2 /= d1;		/*    1/x  x     1/x  */
		d /= d2;		/*    1    x     1/x  */
		d2 /= d;		/*    1    x     1/x  */
	}
	return (0);
}

static int
div_float()
{
	int
	  n,				/* loop variable */
	  loop_cnt = 20,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	float
	  f1,				/* copy of arg 1 */
	  f2,				/* copy of arg 2 */
	  tf1 = 123.234, tf2 = 654.123,			/* temp copy of args */
	  f;				/* result goes here */


	f1 = tf1;			/* use register variables */
	f2 = tf2;
	loop_cnt = tloop_cnt;

	f = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * f    f1    f2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		f /= f1;		/*    1/x  x     1/x  */
		f2 /= f;		/*    1/x  x     1    */
		f1 /= f2;		/*    1/x  x     1    */
		f2 /= f1;		/*    1/x  x     1/x  */
		f /= f2;		/*    1    x     1/x  */
		f2 /= f;		/*    1    x     1/x  */
		f /= f1;		/*    1/x  x     1/x  */
		f2 /= f;		/*    1/x  x     1    */
		f1 /= f2;		/*    1/x  x     1    */
		f2 /= f1;		/*    1/x  x     1/x  */
		f /= f2;		/*    1    x     1/x  */
		f2 /= f;		/*    1    x     1/x  */
	}

	return (0);			/* return success */
}

static int
div_short()
{
	int
	  n,				/* internal loop counter */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	short
	  s1,				/* copy of arg 1 */
	  s2,				/* copy of arg 2 */
	  ts1 = 1, ts2 = 1,			/* temp copy of args */
	  s;				/* result goes here */


	s1 = ts1;			/* use register variables */
	s2 = ts2;
	loop_cnt = tloop_cnt;

	s = 1;
	/*
	 * Variable Values 
	 */
	/*
	 * s    s1    s2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1    - initial value */
		s /= s1;		/*    x    1     1    */
		s /= s2;		/*    x    1     1    */
		s1 /= s2;		/*    x    1     1    */
		s2 /= s1;		/*    x    1     1    */
		s /= s1;		/*    x    1     1    */
		s /= s2;		/*    x    1     1    */
		s1 /= s2;		/*    x    1     1    */
		s2 /= s1;		/*    x    1     1    */
		s /= s1;		/*    x    1     1    */
		s /= s2;		/*    x    1     1    */
		s1 /= s2;		/*    x    1     1    */
		s2 /= s1;		/*    x    1     1    */
	}
	return (0);			/* return success */
}

static int
div_int()
{
	int
	  n,				/* inside loop variable */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	int
	  i1,				/* copy of arg 1 */
	  i2,				/* copy of arg 2 */
	  ti1 = 1, ti2 = 1,			/* temp copy of args */
	  i;				/* result goes here */


	i1 = ti1;			/* use register variables */
	i2 = ti2;
	loop_cnt = tloop_cnt;

	i = 1;
	/*
	 * Variable Values 
	 */
	/*
	 * i    i1    i2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1    - initial value */
		i /= i1;		/*    x    1     1    */
		i /= i2;		/*    x    1     1    */
		i1 /= i2;		/*    x    1     1    */
		i2 /= i1;		/*    x    1     1    */
		i /= i1;		/*    x    1     1    */
		i /= i2;		/*    x    1     1    */
		i1 /= i2;		/*    x    1     1    */
		i2 /= i1;		/*    x    1     1    */
		i /= i1;		/*    x    1     1    */
		i /= i2;		/*    x    1     1    */
		i1 /= i2;		/*    x    1     1    */
		i2 /= i1;		/*    x    1     1    */
	}
	
	return (0);			/* return success */
}

static int
div_long()
{
	int
	  n,				/* inside loop variable */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	long
	  l1,				/* copy of arg 1 */
	  l2,				/* copy of arg 2 */
	  tl1 = 1, tl2 = 1,			/* temp copy of args */
	  l;				/* result goes here */


	l1 = tl1;			/* use register variables */
	l2 = tl2;
	loop_cnt = tloop_cnt;

	l = 1;
	/*
	 * Variable Values 
	 */
	/*
	 * l    l1    l2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1    - initial value */
		l /= l1;		/*    x    1     1    */
		l /= l2;		/*    x    1     1    */
		l1 /= l2;		/*    x    1     1    */
		l2 /= l1;		/*    x    1     1    */
		l /= l1;		/*    x    1     1    */
		l /= l2;		/*    x    1     1    */
		l1 /= l2;		/*    x    1     1    */
		l2 /= l1;		/*    x    1     1    */
		l /= l1;		/*    x    1     1    */
		l /= l2;		/*    x    1     1    */
		l1 /= l2;		/*    x    1     1    */
		l2 /= l1;		/*    x    1     1    */
	}
	return (0);			/* return success */
}

int aimbench_testcase_div_test()
{
  div_double();
  div_float();
  div_short();
  div_int();
  div_long();
  return 0;
}

#if 0
#define COUNT_START static int aim_iteration_test_count = 0, caim_iteration_test_count = 0;
#define COUNT_ZERO aim_iteration_test_count = 0; caim_iteration_test_count = 0
#define COUNT_BUMP  { aim_iteration_test_count++; }
#define COUNT_END(a) if (caim_iteration_test_count++ == 0) printf("Count = %d for test %s in file %s at line %d\n", aim_iteration_test_count, a, __FILE__, __LINE__);
#else
#define COUNT_START 
#define COUNT_ZERO
#define COUNT_BUMP
#define COUNT_END(a)
#endif

static int *p_i1;
static long *p_fcount;
static long debug;
int
fcal0()
{
	return ((*p_fcount += *p_i1));
}

int
fcal1(register int n)
{
	return ((*p_fcount += n));
}

int
fcal2(register int n,
      register int i)
{
	return ((*p_fcount += n + i));
}

int
fcal15(register int i1,
       register int i2,
       register int i3,
       register int i4,
       register int i5,
       register int i6,
       register int i7,
       register int i8,
       register int i9,
       register int i10,
       register int i11,
       register int i12,
       register int i13,
       register int i14,
       register int i15)
{
	return ((*p_fcount += i8 + i15));
}

/* special case to foil inlining optimizers */
int
fcalfake()
{
	fprintf(stderr, "\nfun_cal: You should not see this message.\n");
	return (-1);
/*NOTREACHED*/}

int aimbench_testcase_fun_cal()
{
	int
	  (*p_fcal0) (),		/* function to call */

	  i,				/* inside loop variable */

	  n,				/* outside loo variable */

	  i1 = 32;				/* input parameter */

	long
	  fcount = 10;			/* number of iterations? */

	COUNT_START;


	p_i1 = &i1;			/* point to input value */
	p_fcount = &fcount;		/* point to count */

	if (i1)				/* if calling fcal0 */
		p_fcal0 = fcal0;	/* point to it */
	else				/* (not taken) */
		p_fcal0 = fcalfake;	/* fool compilers */

	n = 1000;			/* initialize outside ocunt */
	while (n--)			/* loop this many times */
		for (i = 32; i--;) {	/* internal loop */
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
			(*p_fcal0) ();
			COUNT_BUMP;
		}
	COUNT_END("fun_cal");
	return (0);			/* return success */
}

int aimbench_testcase_fun_cal1()
{
	int
	  i,				/* internal loop variable */
	  n,				/* external loop variable */
	  i1 = 32,				/* argument */
	  (*p_fcal1) ();		/* function pointer */

	long fcount = 10;			/* count */

	COUNT_START;


	p_i1 = &i1;			/* point to arg */
	p_fcount = &fcount;		/* point to other arg */

	if (i1)
		p_fcal1 = fcal1;	/* if ok, point to function */
	else
		p_fcal1 = fcalfake;	/* should not happen */

	n = 1000;			/* initialize count */
	while (n--)			/* loop through it */
		for (i = 32; i--;) {	/* internal loop */
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
			(*p_fcal1) (n);
			COUNT_BUMP;
		}
	COUNT_END("fun_cal1");
	return (0);			/* return success */
}

int aimbench_testcase_fun_cal2()
{
	int
	  (*p_fcal2) (),		/* pointer to function */

	  i,				/* internal loop count */

	  n,				/* external loop count */

	  i1 = 32;				/* argument */

	long fcount = 20;			/* argument */

	COUNT_START;

	p_i1 = &i1;			/* point to arguments */
	p_fcount = &fcount;

	if (i1)
		p_fcal2 = fcal2;	/* point to function */
	else
		p_fcal2 = fcalfake;	/* (shouldn't happen) */

	n = 1000;			/* initialize count */
	while (n--)			/* loop through it */
		for (i = 32; i--;) {	/* internal loop */
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
			(*p_fcal2) (&n, &i);
			COUNT_BUMP;
		}
	
	COUNT_END("fun_cal2");
	return (0);			/* return success */
}

int aimbench_testcase_fun_cal15()
{
	int
	  (*p_fcal15) (),		/* the function pointer */

	  i,				/* internal loop count */

	  n,				/* external loop count */

	  i1 = 32;				/* argument */

	long fcount = 20;			/* argument */

	COUNT_START;

	p_i1 = &i1;			/* point to args */
	p_fcount = &fcount;

	if (i1)
		p_fcal15 = fcal15;	/* point to function */
	else
		p_fcal15 = fcalfake;	/* (shouldn't happen) */

	n = 1000;			/* initialize count */
	while (n--) {			/* loop through it */
		for (i = 512; i--;) {	/* internal counter */
			(*p_fcal15) (&i, &i, &i, &i, &i, &i, &i, &i, &i, &i, &i, &i, &i, &i, &i);	/* call the funciton */
			COUNT_BUMP;
		}
	}				/* end of loop */
	
	COUNT_END("fun_cal15");
	return (0);			/* return success */
}

#define PRIME (1)
#define NONPRIME (0)
#define TOTAL_PRIMES (78500)

int aimbench_testcase_sieve()
{
	int
	  iter,				/* number of times to repeat the test */
	  n,				/* outside loop count */
	  i,				/* internal loop variable */
	  prime_count,			/* count primes when done */
	  max = 64, i32 = 64;			/* internal loop count */

	char
	 *left,				/* points to next factor */
	 *right,			/* points to next non-prime */
	 *table;			/* holds data to be manipulated */


	COUNT_START;
	/*
	 * Step 1: Get arguments
	 */

	/*
	 * Step 2: Allocate space
	 */
	table = (char *)malloc(max);	/* allocate lots of space */
	if (table == NULL) {
		fprintf(stderr,
			"sieve(): Unable to allocate %d bytes of memory.\n",
			max);
		return (-1);
	}
	/*
	 * Step 3: Initialize and run sieve in loop.
	 */
	for (iter = 0; iter < i32; iter++) {
		memset((void *)table, PRIME, (size_t) max);	/* init all to PRIME */
		for (n = 2; n < max; n++) {	/* ignore 0 & 1, known */
			left = &table[n];	/* point to next factor */
			if (*left != PRIME)
				continue;	/* if it isn't prime, skip it */
			right = left + n;	/* point to the table */
			for (i = n + n; i < max; i += n) {	/* look for all multiples of *left */
				*right = NONPRIME;	/* mark this one as not prime */
				right += n;	/* move to next pointer */
			}		/* and loop */
		}			/* next time through */
	}				/* end of test */
	prime_count = 0;
	for (n = 0; n < max; n++)	/* check answer */
		if (table[n] == PRIME)
			prime_count++;
	/*if (prime_count != TOTAL_PRIMES) {
		fprintf(stderr, "sieve(): Problem calculating primes.\n");
		return (-1);
	}*/
	free(table);			/* return the memory */
	return 0;
}

#define PI (3.14159)
#define ONE_OVER_PI (1.0/3.14159)
#define OPS_PER_LOOP 12

static int
mul_double()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	double
	  d1,				/* copy of arg 1 */
	  d2,				/* copy of arg 2 */
	  td1 = 435.42512, td2 = 1.21223,			/* temp copy of args */
	  d;				/* result goes here */


	d1 = td1;			/* use register variables */
	d2 = td2;
	loop_cnt = tloop_cnt;

	d = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * d    d1    d2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		d *= d1;		/*    x    x     1/x */
		d1 *= d2;		/*    x    1     1/x */
		d1 *= d2;		/*    x    1/x   1/x */
		d2 *= d;		/*    x    1/x   1   */
		d2 *= d;		/*    x    1/x   x   */
		d *= d1;		/*    1    1/x   x   */
		d *= d1;		/*    1/x  1/x   x   */
		d1 *= d2;		/*    1/x  1     x   */
		d1 *= d2;		/*    1/x  x     x   */
		d2 *= d;		/*    1/x  x     1   */
		d2 *= d;		/*    1/x  x     1/x */
		d *= d1;		/*    1    x     1/x */
		/*
		 * Note that at loop end, d1 = 1/d2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

static int
mul_float()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	float
	  f1,				/* copy of arg 1 */
	  f2,				/* copy of arg 2 */
	  tf1 = 3.134, tf2 = 5.527,			/* temp copy of args */
	  f;				/* result goes here */


	f1 = tf1;			/* use register variables */
	f2 = tf2;
	loop_cnt = tloop_cnt;

	f = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * f    f1    f2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		f *= f1;		/*    x    x     1/x */
		f1 *= f2;		/*    x    1     1/x */
		f1 *= f2;		/*    x    1/x   1/x */
		f2 *= f;		/*    x    1/x   1   */
		f2 *= f;		/*    x    1/x   x   */
		f *= f1;		/*    1    1/x   x   */
		f *= f1;		/*    1/x  1/x   x   */
		f1 *= f2;		/*    1/x  1     x   */
		f1 *= f2;		/*    1/x  x     x   */
		f2 *= f;		/*    1/x  x     1   */
		f2 *= f;		/*    1/x  x     1/x */
		f *= f1;		/*    1    x     1/x */
		/*
		 * Note that at loop end, f1 = 1/f2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

static int
mul_long()
{
	int
	  n,				/* inside loop variable */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt = 20; 			/* temporary internal loop count */

	long
	  l1, l2,			/* working copies */
	  tl1 = 2416234, tl2 = 263725,			/* temp copy of args */
	  l;				/* result */


	l1 = tl1;			/* use register variables */
	l2 = tl2;
	loop_cnt = tloop_cnt;

	l = 12345678;
	/*
	 * Variable Values 
	 */
	/*
	 * l    l1    l2  
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1   - initial value */
		l *= l1;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l *= l2;		/*    x    1     1   */
		l *= l1;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l *= l2;		/*    x    1     1   */
		/*
		 * Note that at loop end, all values 
		 */
		/*
		 * as we started.  Thus, the values 
		 */
		/*
		 * in the loop are stable 
		 */
	}
	return (0);			/* return success */
}

static int
mul_int()
{
	int
	  n,				/* inside loop variable */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt = 20;			/* temporary internal loop count */

	int
	  i1, i2,			/* working copies */
	  ti1 = 23445, ti2 = 12322,			/* temp copy of args */
	  i;				/* result */


	i1 = ti1;			/* use register variables */
	i2 = ti2;
	loop_cnt = tloop_cnt;

	i = 12345678;
	/*
	 * Variable Values 
	 */
	/*
	 * i    i1    i2  
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1   - initial value */
		i *= i1;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i *= i2;		/*    x    1     1   */
		i *= i1;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i *= i2;		/*    x    1     1   */
		/*
		 * Note that at loop end, all values 
		 */
		/*
		 * as we started.  Thus, the values 
		 */
		/*
		 * in the loop are stable 
		 */
	}
	return (0);			/* return success */
}

static int
mul_short()
{
	int
	  n,				/* inside loop variable */
	  loop_cnt,			/* internal loop count */
	  tloop_cnt=20;			/* temporary internal loop count */

	short
	  s1, s2,			/* working copies */
	  ts1 = 1235, ts2 = 4362,			/* temp copy of args */
	  s;				/* result */


	s1 = ts1;			/* use register variables */
	s2 = ts2;
	loop_cnt = tloop_cnt;

	s = 1234;
	/*
	 * Variable Values 
	 */
	/*
	 * s    s1    s2  
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1   - initial value */
		s *= s1;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s *= s2;		/*    x    1     1   */
		s *= s1;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s *= s2;		/*    x    1     1   */
		/*
		 * Note that at loop end, all values 
		 */
		/*
		 * as we started.  Thus, the values 
		 */
		/*
		 * in the loop are stable 
		 */
	}
	return (0);			/* return success */
}

int aimbench_testcase_mul_test() {
  mul_double(),
  mul_float(),
  mul_long(),
  mul_short(),
  mul_int();
  return 0;
}

#define Members(x)	(sizeof(x)/sizeof(x[0]))	/* number items in array */
#define MAXSTRINGS (100)		/* number of strings */
#define MAXSORTSIZE (10000)		/* make it large enough to matter */
#define MAXTRIES (100)			/* for newton-raphson */
#define M_SIZE (4)			/* size for matrix in matrix_rtns */
#define A_HEIGHT 100			/* height for matrix in array_rtns */
#define A_WIDTH  101			/* width for matrix in array_rtns */
#define A_SIZE   (A_HEIGHT*A_WIDTH)	/* array size for array_rtns */
#define SIZBUF (8192)			/* buffer size for mem ops */
#define NUMVALS (500)			/* size of vals[] arrays */
#define NUM10VALS (10000)		/* size of vals10[] arrays */
#define ARG (vals10[count10++ % Members(vals10)])	/* get a positive, negative or 0 value from vals10[] for use as arg */
#define POS (ARG + 10.0001)		/* get a positive value for use as arg */
#define NEG (ARG - 10.0001)		/* get a negative value for use as arg */


static double vals[NUMVALS];		/* holds floating point values (1..0) */
static double vals10[NUM10VALS];	/* holds floating point values (-10..10) */
int table[MAXSORTSIZE];			/* table to sort of integers */
static int count = 0;			/* counter for vals[] array */
static int count10 = 0;			/* counter for vals10[] array */
double compiler_fake_out1;		/* dummy variable for num_rtns_1()  */
double compiler_fake_out2;		/* and trig_fcns()...since globally */
double compiler_fake_out3;		/* available, compiler can't assume */
double compiler_fake_out4;		/* anything and thus can't opt.     */
double compiler_fake_out5;		/* their assignments out            */

int aimbench_testcase_num_rtns_1()
     /*
      * This routine tests the traditional hard working numeric routines.
      * Ansi C says that function calls cannot be optimized away.....
      * We'll see. Anyway, these functions do the majority of the work
      * in numeric (non-trig) applications. Vendors good at these functions
      * will deliver higher performance for these classes of applications.
      *
      * We try to keep track of parameter values so that no illegal values
      * are fed to these routines.
      * We try to use all results so that a compiler will not omit a call 
      * whose results are never used.
      * We try to keep track of parameter values so that a variety of values
      * are fed to these routines.
      */
{
	int n, i64 = 4, itemp1;
	double d1, d2, dtemp1;

	COUNT_START;

	/*
	 * Get arguments
	 */

	/*
	 * Do the actual loop where the time is spent
	 */
	for (n = 0; n < i64; n++) {
		if (debug < 10) {
			compiler_fake_out1 = floor(exp(ARG))
				+ ceil(log10(POS));
			compiler_fake_out2 = modf(log(POS), &dtemp1)
				+ frexp(NEG, &itemp1);	/* don't want ARG, because of "smallest" */
			compiler_fake_out3 = ldexp(ARG, abs(-itemp1))
				+ fabs(fmod(ARG * 5, POS));	/* try to get 1st fmod() arg larger than second */
			compiler_fake_out4 = sqrt(pow(POS, ARG));	/* pow() will always return pos value */
			srand(itemp1);
			compiler_fake_out5 = labs((long)(-rand() + n));
			/*
			 * rand() often returns same #, +n adds variation, '-' gives labs() something to do 
			 */
		} else {
			/*
			 * compiler_fake_out1 = floor(exp(ARG))
			 */
			d1 = ARG;
			printf("exp<%g> is %g\n", d1, exp(d1));
			fflush(stdout);
			printf("floor<%g> is %g\n", exp(d1), floor(exp(d1)));
			fflush(stdout);

			/*
			 * + ceil(log10(POS)); 
			 */
			d1 = POS;
			printf("log10<%g> is %g\n", d1, log10(d1));
			fflush(stdout);
			printf("ceil<%g> is %g\n", log10(d1), ceil(log10(d1)));
			fflush(stdout);

			/*
			 * compiler_fake_out2 = modf(log(POS), &dtemp1)    
			 */
			d1 = POS;
			printf("log<%g> is %g\n", d1, log(d1));
			fflush(stdout);
			printf("modf<%g> is %g\n", log(d1),
			       modf(log(d1), &dtemp1));
			fflush(stdout);

			/*
			 * + frexp(NEG, &itemp1); 
			 */
			d1 = NEG;
			d2 = frexp(d1, &itemp1);
			printf("frexp<%g> is %g itemp is %d\n", d1, d2,
			       itemp1);
			fflush(stdout);

			/*
			 * compiler_fake_out3 = ldexp(ARG, abs(-itemp1)) 
			 */
			d1 = ARG;
			printf("abs<%d> is %d\n", -itemp1, abs(-itemp1));
			fflush(stdout);
			printf("ldexp<%g, %d> is %g\n", d1, abs(-itemp1),
			       ldexp(d1, abs(-itemp1)));
			fflush(stdout);

			/*
			 * + fabs(fmod(ARG, POS)); 
			 */
			d1 = ARG;
			d2 = POS;
			printf("fmod<%g, %g> is %g\n", d1 * 5, d2,
			       fmod(d1 * 5, d2));
			fflush(stdout);
			printf("fabs(fmod<%g, %g>) is %g\n", d1 * 5, d2,
			       fabs(fmod(d1 * 5, d2)));
			fflush(stdout);

			/*
			 * compiler_fake_out4 = sqrt(pow(POS, ARG)); 
			 */
			d1 = POS;
			d2 = ARG;
			printf("pow<%g, %g> is %g\n", d1, d2, pow(d1, d2));
			fflush(stdout);
			printf("sqrt(pow<%g, %g>) is %g\n", d1, d2,
			       sqrt(pow(d1, d2)));
			fflush(stdout);

			srand(itemp1);
			printf("calling srand<%d>\n", itemp1);
			fflush(stdout);

			/*
			 * compiler_fake_out5 = labs((long)(-rand() + n));
			 */
			itemp1 = -rand() + n;
			printf("labs<%ld> is %ld\n", (long)itemp1,
			       labs((long)itemp1));
			fflush(stdout);
		}
		COUNT_BUMP;
	}
	COUNT_END("num_rtns_1");
	return 0;
}

int aimbench_testcase_trig_rtns()
     /*
      * This routine does the trig and similar functions
      *
      * We try to make sure that no illegal values are fed to these routines.
      * We try to use all results so that a compiler will not omit a call 
      * whose results are never used.
      * We try to keep track of parameter values so that a variety of values
      * are fed to these routines.
      *
      * We nest functions on purpose to allow compilers to reuse floating point 
      * registers but not to optimize out any of the calculations or waste time storing
      * to global variables.
      */
{
	int n, i64 = 4;

	COUNT_START;
	/*
	 * First, get args
	 */

	/*
	 * prepare for the loop
	 */
	i64 *= 100;			/* scale it some */
	/*
	 * Do the actual loop where the time is spent
	 */
	for (n = 0; n < i64; n++) {
		if (debug < 10) {
			compiler_fake_out1 = acos(cos(asin(sin(ARG))));	/* asin{acos} can legally use any output of sin{cos} */
			/*
			 * no bound on sin and cos arg 
			 */
			compiler_fake_out2 = tanh(atan(tan(ARG)));	/* atan can legally use any output of tan; no bound on tanh arg */
			compiler_fake_out3 = atan2(sinh(ARG), cosh(ARG));	/* no bound on sinh & cosh arg; cosh always returns pos # */
		} else {
			double d1, d2;

			d1 = ARG;
			printf("sin(%g) is %g\n", d1, sin(d1));
			fflush(stdout);
			printf("asin(%g) is %g\n", sin(d1), asin(sin(d1)));
			fflush(stdout);
			printf("cos(%g) is %g\n", asin(sin(d1)),
			       cos(asin(sin(d1))));
			fflush(stdout);
			printf("acos(%g) is %g\n", cos(asin(sin(d1))),
			       acos(cos(asin(sin(d1)))));
			fflush(stdout);
			d1 = ARG;
			printf("tan(%g) is %g\n", d1, tan(d1));
			fflush(stdout);
			printf("atan(%g) is %g\n", tan(d1), atan(tan(d1)));
			fflush(stdout);
			printf("tanh(%g) is %g\n", atan(tan(d1)),
			       tanh(atan(tan(d1))));
			fflush(stdout);
			d1 = ARG;
			d2 = ARG;
			printf("sinh(%g) is %g\n", d1, sinh(d1));
			fflush(stdout);
			printf("cosh(%g) is %g\n", d2, cosh(d2));
			fflush(stdout);
			printf("atan2(%g, %g) is %g\n", sinh(d1), cosh(d2),
			       atan2(sinh(d1), cosh(d2)));
			fflush(stdout);
		}
		COUNT_BUMP;
	}
	COUNT_END("trig_rtns");
	return 0;
}

double
next_value()
{
	double temp;

	temp = vals[count++ % Members(vals)];
	return temp;
}

int aimbench_testcase_matrix_rtns()
     /*
      * Rendering routine
      */
{
	int n, i64 = 4, i, j, k;
	double prod;
	double v1[M_SIZE], v2[M_SIZE][M_SIZE], v3[M_SIZE];

	COUNT_START;
	/*
	 * Step 1: get args
	 */

	/*
	 * Step 2: do the routine
	 */
	prod = 0.0;			/* start with nothing */
	for (n = 0; n < i64; n++) {
		/*
		 * First, fetch fresh values for matrices
		 */
		for (i = 0; i < M_SIZE; i++)	/* get new data points */
			v1[i] = next_value();
		for (i = 0; i < M_SIZE; i++)	/* fill transformation matrix */
			for (j = 0; j < M_SIZE; j++)
				v2[i][j] = next_value();
		/*
		 * Now do the matrix arithmetic
		 */
		for (i = 0; i < M_SIZE; i++) {	/* realize each of these values */
			v3[i] = 0.0;	/* clear it out */
			for (j = 0; j < M_SIZE; j++)	/* do the dot product */
				v3[i] += v1[j] * v2[i][j];	/* for the results */
		}
		/*
		 * Now scale and convert to real world coordinates
		 */
		i = v3[0] * 1280.0;	/* convert to screen (int) coords */
		j = v3[1] * 1024.0;	/* y value */
		k = v3[2] * 8192.0;	/* zvalue */
		prod += v3[0] * v3[1] * v3[2];	/* sum magnitude (code motion stopper) */
		compiler_fake_out1 = i + j + k + prod;	/* use the calculated values */
		COUNT_BUMP;
	}
	COUNT_END("matrix_rtns");
	return 0;
}

#define m(x,y) a[x+wide*y]

static void
print_array(double *a,			/* the array to print */
	    int wide,			/* the width of the array */
	    int high)
{					/* the height of the array */
	int ii, jj;			/* loop variables */

	for (ii = 0; ii < high; ii++) {	/* for each row in the array */
		for (jj = 0; jj < wide; jj++)	/* for each column in the array */
			printf("%13g ", m(jj, ii));	/* print the value */
		printf("\n");		/* and then end the line */
	}				/* end of row */
}
static int
solve_array(double *a,			/* input array of wide x high */
	    double *b,			/* result array of size high */
	    int wide,			/* width of array */
	    int high)
{					/* height of array */
	int i, j, k;			/* loop variables */
	double t;			/* temporary (scaling) value */

	/*
	 * Step 1: Make array upper triangular
	 */
	for (i = 0; i < high; i++) {	/* for each row in the array */
		t = m(i, i);		/* pick the scale factor */
		if (t == 0.0) {		/* if it is 0.0, the array is singular */
			printf("Singular:\n");
			print_array(a, wide, high);
			return 0;	/* error here */
		}
		for (j = i; j < wide; j++)	/* scale the row until diagonal point is 1.0 */
			m(j, i) = m(j, i) / t;	/* narrow the loop to reduce load since left of i = 0.0 */

		for (j = i + 1; j < high; j++) {	/* zero out all lower entries in this column */
			t = m(i, j);	/* factor to solve by */
			for (k = 0; k < wide; k++)	/* subtract ith row from jth row t times */
				m(k, j) = m(k, j) - t * m(k, i);	/* to zero out next column */
		}
	}
	/*
	 * Step 2: Make array into identity matrix by eliminating non-diagonal entries in upper triangle.
	 */
	for (i = high - 1; i > 0; i--) {	/* solve for identity matrix */
		for (j = i - 1; j >= 0; j--) {	/* take away one column */
			t = m(i, j);	/* get the factor */
			for (k = 0; k < wide; k++)	/* subtract the t times the i'th equation from the j'th equation */
				m(k, j) = m(k, j) - t * m(k, i);
		}
	}
	/*
	 * Step 3: Get the last column which contains the solution (since the
	 *         array is now the identity matrix).
	 */
	for (i = 0; i < high; i++)
		b[i] = m(wide - 1, i);
	return 1;			/* return success */
}

static int
test(double *a,				/* input array */

     double *b,				/* answers to check */

     int wide,				/* dimensions of array */

     int high)
{
	int i, j;			/* loop variables */
	double t;			/* temporary sum */

	for (i = 0; i < high; i++) {	/* loop through rows */
		t = 0.0;		/* start sum off at zero */
		for (j = 0; j < high; j++)	/* for each term */
			t += m(j, i) * b[j];	/* calculate running sum */
		if (fabs(m(wide - 1, i) - t) > .5) {	/* if sum isn't close to the answer */
			printf("Row %d: Wanted %g, got %g (%g)\n", i,	/* error here */
			       m(wide - 1, i), t, fabs(m(wide - 1, i) - t));
			return 0;	/* return error */
		}
	}
	return 1;			/* else return success */
}

int aimbench_testcase_array_rtns()
     /*
      * Solution to linear system of equations
      */
{
	int n, i64 = 4, high, j, k, wide;
	static double a[A_SIZE], a_orig[A_SIZE], val, results[A_HEIGHT];	/* arguments, results */

	COUNT_START;
	memset(a, 0, A_SIZE * sizeof (double));	/* initialize array */
	memset(a_orig, 0, A_SIZE * sizeof (double));	/* initialize array */
	/*
	 * Step 1: get args
	 */

	/*
	 * Step 2: do the routine
	 */
	val = 1.0;
	for (high = 5, n = 0; n < i64; n++, high += 5) {
		if (high > A_HEIGHT)
			high = 5;	/* wrap around */
		wide = high + 1;
		/*
		 * First, fetch fresh values for matrices
		 */
		for (j = 0; j < high; j++)
			for (k = 0; k < wide; k++) {	/* fetch a bunch of values */
				m(k, j) = val;	/* make it a real one and non-linear */
				val = val * 1.00001 + 1.0;
				if (val > 1e20)
					val -= 1e19;	/* make sure never generate same values */
			}
		memcpy(a_orig, a, A_SIZE * sizeof (double));	/* save the original for test() later */
		/*
		 * Now do the matrix arithmetic
		 */
		if (!solve_array(a, results, wide, high)) {
			fprintf(stderr, "Singular Matrix of size %d\n", high);
			return -1;
		}
		if (!test(a_orig, results, wide, high)) {
			fprintf(stderr,
				"Illegal results from matrix of size %d\n",
				high);
			return -1;
		}
		COUNT_BUMP;
	}
	COUNT_END("array_rtns");
	return 0;
}

int aimbench_testcase_mem_rtns_1()
{
	int n, i64 = 4, i, j;
	char *p;
	char *array[MAXSTRINGS * 3];	/* allocate alot of strings */
	static int malloc_size[] = {	/* table of sizes, roughly real world representative */
		1, 3, 5, 7, 9,		/* 5 25 */
		11, 33, 65, 129, 1024,	/* 5 1262 */
		1025, 1023, 8192, 4096, 4095,	/* 5 18431 */
		11, 33, 65, 129, 1024,	/* 5 1262 */
		1, 3, 5, 7, 9,		/* 5 25 */
		11, 33, 65, 129, 1024,	/* 5 1262 */
		1025, 1023, 8192, 4096, 4095,	/* 5 18431 */
		11, 33, 65, 129, 1024
	};				/* 5 1262 */
	static char *str = "Hello, this is an average length string 1234";
	int count = 0;

	COUNT_START;
	/*
	 * Get args 
	 */

	/*
	 * do the loop
	 */
	for (n = 0; n < i64; n++) {
		/*
		 * First, allocate the memory
		 */
		for (j = i = 0; i < MAXSTRINGS; i++) {
			array[j] = malloc(strlen(str) + 1);
			strcpy(array[j], str);
			count += strlen(array[j++]) + 1;	/* add its length to count */
			array[j++] = malloc(256 * malloc_size[i % Members(malloc_size)]);	/* allocate a block */
			count += malloc_size[i % Members(malloc_size)];	/* update counter */
			array[j++] = calloc(256 * malloc_size[(i + 1) % Members(malloc_size)], 1);	/* allocate a zeroed block */
			count += malloc_size[(i + 1) % Members(malloc_size)];	/* update counter */
		}
		/*
		 * Now touch each of these to force them to be located in main memory
		 */
		for (i = 0; i < MAXSTRINGS * 3; i++) {
			p = array[i];	/* point to it */
			count += *p++;	/* update the count */
			if (count < 0)	/* this won't ever happen */
				count += *p++;	/* update the count */
		}
		/*
		 * Now deallocate the memory in a slightly different order
		 * which isn't quite worst case, but more reasonably reflects
		 * the real world.
		 */
		//for (i = (3 * MAXSTRINGS) - 3; i >= 0; i -= 3) {
		//	free(array[i]);	/* free in reverse order */
		//	COUNT_BUMP;
		//	free(array[i + 2]);	/* free in reverse order */
		//	COUNT_BUMP;
		//	free(array[i + 1]);	/* free in reverse order */
		//	COUNT_BUMP;
		//}
		
	}
	COUNT_END("mem_rtns_1");
	return 0;
}

int aimbench_testcase_mem_rtns_2()
{
	int n, i64 = 4, i, off1, off2, size;
	static int op_size[] = {
		1, 3, 5, 7, 9,
		11, 33, 65, 129, 1024,
		1025, 1023, 8192, 4096, 4095,
		11, 33, 65, 129, 1024,
		1, 3, 5, 7, 9,
		11, 33, 65, 129, 1024,
		1025, 1023, 8192, 4096, 4095,
		11, 33, 65, 129, 1024
	};

	char
	 
		buff1[SIZBUF + sizeof (double)],
		buff2[SIZBUF + sizeof (double)], *bp1 = buff1, *bp2 = buff2;

	char *p;

	COUNT_START;


	for (n = 0; n < i64; n++) {
		/*
		 * Calculate the offsets (assume memory alignments between 0 and sizeof(double)
		 */
		off1 = n % sizeof (double);
		off2 = (n / sizeof (double)) % sizeof (double);
		size = op_size[n % Members(op_size)];
		/*
		 * Do some operations using these offsets
		 */
		memset(bp1 + off1, 'A', size);
		memset(bp2 + off2, 'A', size);
		(bp1 + off1)[n % size] = 'Z';	/* change one to Z */
		p = (char *)memchr(bp1 + off1, 'Z', size);	/* scan it */
		i = memcmp(bp1 + off1, bp2 + off2, size);	/* compare the two */
		if (i > 0)
			*p = 'A';	/* make it normal again */
		memcpy(bp1 + off1, bp2 + off2, size);	/* do the copy */
		memmove(bp2 + off1, bp1 + off2, size);
		COUNT_BUMP;
	}
	COUNT_END("mem_rtns_2");
	return count;
}

static int
compar1(const void *p1,
	const void *p2)
{
	return (*(int *)p1 - *(int *)p2);	/* make it ascending */
}

static int
compar2(const void *p1,
	const void *p2)
{
	return (*(int *)p2 - *(int *)p1);	/* make it descending */
}

int aimbench_testcase_series_1()
/*
 * Evaluate the infinite series for sin(x) around 0
 *
 * sin(x) = x/1! - x^3/3! + x^5/5!.....
 * 
 * and compare it to the system's sin routine results.
 *
 * Iterate until absolute convergency (each additional term adds no
 * additional precision to the result).
 */
{
	int
	  n, i64 = 4;
	double
	  i, d0,			/* original x for sin(x) */
	  d1,				/* x for sin(x), changed during calc */
	  old, sine, d1_squared, fact;

	COUNT_START;

	/*
	 * Get arguments
	 */

	/*
	 * Do the actual loop where the time is spent
	 */
	for (n = 0; n < i64; n++) {
		d0 = d1 = next_value();	/* fetch next value */
		old = 100.0;		/* illegal possible value */
		sine = 0.0;		/* final sine value goes here */
		d1_squared = d1 * d1;	/* calc once outside of loop */
		fact = 1.0;		/* starting factorial value (1!) */
		i = 1.0;		/* series counter for sine: 1, 3, 5, ... */
		while (sine != old) {	/* loop until we've converged totally */
			old = sine;	/* save last value */
			sine += d1 / fact;	/* add next in series */
			fact *= (i + 1) * (i + 2);	/* i factorial for next time around */
			/*
			 * series advances by 2 
			 */
			i += 2;
			d1 *= -(d1_squared);	/* power of d1 for next in series */
			/*
			 * neg to flip sign 
			 */
		}
		if (fabs(sine - sin(d0)) > .0001) {
			fprintf(stderr,
				"series_1(): calculated sine for %g is %g, sin() returns %g.\n",
				d0, sine, sin(d0));
			return -1;
		}
		COUNT_BUMP;
	}
	COUNT_END("series_1");
	return (0);
}

static int
  sizes[] = {				/* determines how much to copy */
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
	8, 9, 11, 17, 33, 63,
	7, 7, 7, 7, 7, 7,
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
	127, 256, 1001, 1200, 1492, 1500,
	1024, 2048, 3172, 4096, 8192, 512,
	7, 7, 7, 7, 7, 7,
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
	8, 9, 11, 17, 33, 63,
	7, 7, 7, 7, 7, 7,
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
};

static char
  a[8192 + sizeof (double)],		/* source */
  b[8192 + sizeof (double)];		/* destination */

    /*
     * +sizeof(double) because we will be writing 8192 bytes to offset sizeof(double) at some time 
     */

/* Copy data to and from ram at different offsets.  Assume memory alignments between 0 and sizeof(double) */
int aimbench_testcase_ram_copy()
{
	int n, i64 = 4;

	for (n = 0; n < i64; n++) {
		void			/* vary offsets with each call */
		 *src = (void *)&b[n % sizeof (double)],	/* try all src & dest double word offsets */

		 *dst = (void *)&a[(n / sizeof (double)) % sizeof (double)];	/* insure offset always from 0 to sizeof(double) */
		int
		  count = sizes[n % Members(sizes)];	/* vary copy sizes by table above */

		memcpy(src, dst, count);	/* memcpy() can never fail */
	}
	return (0);
}