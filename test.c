#include "includes/libftprintf.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define LOCKFILE "/etc/ptmp"
#define PASSWDFILE "/etc/passwd"

static int nr = 1;

static void test(const char *strformat, const char *strargs, const char *format, ...)
{
  va_list ap;
  char s[32];
  int n;

  va_start(ap, format);
  n = vsnprintf(s, 32, format, ap);
  va_end(ap);
  printf("Test %d: printf(%s%s%s)\n", nr, strformat, strargs[0] ? ", " : "", strargs);
  ft_printf("Test %d: printf(%s%s%s)\n", nr, strformat, strargs[0] ? ", " : "", strargs);
  printf("%3d", n);
  if (n >= 0)
    printf("  %s\n", s);
  printf("\n");
  printf("\n");
  nr++;
}

static void test0(const char *strformat, const char *strargs, const char *format, ...)
{
  va_list ap;
  int n;

  va_start(ap, format);
  n = vsnprintf(NULL, 0, format, ap);
  va_end(ap);
  printf("Test %d: printf(%s%s%s)\n", nr, strformat, strargs[0] ? ", " : "", strargs);
  ft_printf("Test %d: printf(%s%s%s)\n", nr, strformat, strargs[0] ? ", " : "", strargs);
  printf("%3d\n", n);
  printf("\n");
  nr++;
}

static void testn()
{
  int nb;
  char s[32];
  int n;

  nb = -1;
  n = snprintf(s, 32, "%d %d %n %d", 1, 2, &nb, 3);
  printf("Test %d: printf(\"%%d %%d %%n %%d\", 1, 2, &n, 3)\n", nr);
  ft_printf("Test %d: printf(\"%%d %%d %%n %%d\", 1, 2, &n, 3)\n", nr);
  printf("%3d", n);
  if (n >= 0)
    printf("  %s  %d\n", s, nb);
  printf("\n");
  printf("\n");
  nr++;
}

#define TEST(format, ...) test(#format, #__VA_ARGS__, format, ## __VA_ARGS__)
#define TEST0(format, ...) test0(#format, #__VA_ARGS__, format, ## __VA_ARGS__)
#define TESTn() testn()

int main()
{
  char str[16];
  int n;

  printf("%s\n", "Hello, world");
  sprintf(str, "%s\n", "Hello, world");
  fputs(str, stdout);
  printf("\n");

  /* tests specifiques */

  /* taille nulle */
  printf("/* taille nulle */\n\n");
  TEST0("ABC %d", 7);

  /* chaines simples */
  printf("/* chaines simples */\n\n");
  TEST("some text");
  TEST("abcdefghijklmnopqrstuvwxyz0123"); /* chaine plus courte */
  TEST("abcdefghijklmnopqrstuvwxyz01234"); /* chaine de bonne longueur */
  TEST("abcdefghijklmnopqrstuvwxyz012345"); /* chaine trop longue */

  /* entiers */
  printf("/* entiers */\n\n");
  TEST("%d %d %d %d %d %d %d %d", 0, 1, 9, 10, 11, 9999, 10000, 100001);
  TEST("%d %d %d %d %d %d %d %d", 0, -1, -9, -10, -11, -9999, -10000, -100001);
  TEST("%d", 12345);
  TEST("%d", -12345);
  TEST("%+d", 12345);
  TEST("% d", 12345);
  TEST("% d", -12345);
  TEST("%.8d", 12345);
  TEST("%08d", 12345);
  TEST("%12.8d", 12345);
  TEST("%8.12d", 12345);
  TEST("%-12d", 12345);
  TEST("%-12.8d", 12345);
  TEST("%012.8d", 12345);
  TEST("%012.d", 12345);
  TEST("%012.0d", 12345);
  TEST("%-012d", 12345);
  TEST("%-.12d", 12345);
  TEST("%.0d", 0);
  TEST("% .0d", 0);
  TEST("%d", 258733);
  TEST("%i", 258733);
  TEST("%o", 258733U);
  TEST("%u", 258733U);
  TEST("%x", 258733U);
  TEST("%X", 258733U);
  TEST("%d", 0);
  TEST("%i", 0);
  TEST("%o", 0);
  TEST("%u", 0);
  TEST("%x", 0);
  TEST("%X", 0);
  TEST("%d", -258733);
  TEST("%d", INT_MAX);
  TEST("%d", INT_MIN);
  TEST("%u", UINT_MAX);
  TEST("%o", UINT_MAX);
  TEST("%x", UINT_MAX);

  /* caracteres */
  printf("/* caracteres */\n\n");
  TEST("%c %c", 'a', '%');

  /* chaines de caracteres */
  printf("/* chaines de caracteres */\n\n");
  TEST("%s", NULL);
  TEST("%s", "");
  TEST("%s", "ABCDEF");

  /* pointeurs */
  printf("/* pointeurs */\n\n");
  TEST("%p", NULL);
  TEST("%p", 0x123);
  TEST("%p", main);

  /* n */
  printf("/* n */\n\n");
  TEST("%d %n", 1, &n);
  TESTn();

  /* % */
  printf("/* %% */\n\n");
  TEST("%d %% %d", 1, 2);

  /* modificateurs */
  printf("/* modificateurs */\n\n");
  TEST("-%4d-%-4d-%4d-", 7, 54, 12345); /* field width */
  TEST("-%4s-%4s-", "A", "ABCDEF");
  TEST("-%-4d-", 7);
  TEST("-%4p-", main);
  TEST("-%*d-", 4, 7);
  TEST("-%*d-", -4, 7);
  TEST("-%0*d-", 4, 7);
  TEST("%100000d", 1);
  TEST("-%3c-%-3c-", 'a', 'b');
  TEST("-%3s-%-3s-", "A", "B");
  TEST("-%.4d-%.4d-%.d-%.0d-", 7, 12345, 1, 9); /* precision */
  TEST("-%.4s-%.4s-%.s-", "A", "ABCDEF", "ABC");
  TEST("-%.*d-", 4, 7);
  TEST("-%.*d-", -4, 7);
  TEST("%.1d %.0d %.1u %.0u %.1o %.0o %.1x %.0x", 0, 0, 0, 0, 0, 0, 0, 0);
  TEST("%.5d\n", -17);
  TEST("%.-5d\n", -17);
  TEST("-%6.4d-%4.6d-", 12345, 12345); /* plusieurs ensembles */
  TEST("-%*.*d-%*.*d-", 6, 4, 12345, 4, 6, 12345);
  TEST("-%.012d-", -1234);
  TEST("-%6.4s-%4.6s-", "ABCDE", "ABCDE");

  /* drapeaux */
  printf("/* drapeaux */\n\n");
  TEST("-%4d-%-4d-", 7, 7);
  TEST("%d %d %+d %+d % d % d %+ d %+ d % +d % +d", 7, -7, 7, -7, 7, -7, 7, -7, 7, -7);
  TEST("%o %#o %x %#x %X %#X", 23, 23, 23, 23, 23, 23);
  TEST("%04d %-04d %0-4d", 7, 7, 7);
  TEST("%0-4d", 7);
  TEST("-%0d-", 7);
  TEST("-%012d-", -1234);
  TEST("%04d %0.4d", -12, -12);
  TEST("%.u %.0u % u %+u", 0, 0, 7, 7);

  /* modificateurs de longueur */
  printf("/* modificateurs de longueur */\n\n");
  TEST("%d %hd %d", 7, 7, 7);
  TEST("%d %hd %d", 123456, 123456, 123456);
  TEST("%u %hu %u", 123456U, 123456U, 123456U);
  TEST("%d %ld %d", 123456, 123456, 123456);

  /* combinaisons plus complexes */
  printf("/* combinaisons plus complexes */\n\n");
  TEST("%#012x", 3735928559U);
  TEST("%#-*.*lX", 16, 12, 3735928559UL);
  TEST("%000012x", 3735928559U);
  TEST("-%+-+4d-", 1);
  TEST("-%3d-%3d-%3d-", 12, 123, 1234);
  TEST("-%3d-%3d-%3d-", -1, -12, -123);
  TEST("-%.3d-%.3d-%.3d-", 12, 123, 1234);
  TEST("-%.3d-%.3d-%.3d-", -12, -123, -1234);
  TEST("-%+3d-%+.3d", 12, 12);
  TEST("-%+8.4d-%8.0d-%+8.0d-", 13, 0, 0);
  TEST("-%08.0d-", 0);
  TEST("-%2.0d-\n", 7);
  TEST("-%2.0d-\n", 0);
  TEST("%o %.2o %.4o %.6o", 0123, 0123, 0123, 0123);
  TEST("%#o %#.2o %#.4o %#.6o", 0123, 0123, 0123, 0123);
  TEST("-%#d-%#o-%#x-%#X-", 0, 0, 0, 0);
  TEST("-%#.0d-%#.0o-%#.0x-%#.0X-", 0, 0, 0, 0);
  TEST("-%d-%.0d-%.8d-%8.0d-%8.8d-", 0, 0, 0, 0, 0);
  TEST("%.3d %.-3d", 21, 21);

  /* conversions erronees ou non specifiees */
  printf("/* conversions erronees ou non specifiees */\n\n");
  TEST("-%.4p-", main);
  TEST("-%.-4d-", 7);
  TEST("%#s %0s", "ABC", "ABC");
  TEST("-%%-%-%-%0%-%1%-%2%-%.2%-%.%-%-2%-");
  TEST("%k", 7);
  TEST("%02k", 7);
  TEST("%2");
  TEST("%+s %0-s", "ABC", "ABC");
  TEST("%+c %0-c %.2c", 'a', 'b', 'c');
  TEST("%d %2n", 1, &n);
  TEST("%d %.2n", 1, &n);
  TEST("%d %02n", 1, &n);
  TEST("%d %+n", 1, &n);
  TEST("%d %-2n", 1, &n);
  TEST("%?d", 7);
  TEST("%2*d", 4, 7);
  TEST("%.0*d", 4, 7);
  TEST("%*2d", 4, 7);
  TEST("%.*2d", 4, 7);
  TEST("%+0# -2.k");
  TEST("%*.*k", -32, 5);
  TEST("%+*.*k", -32, 5);
  TEST("% *.*k", -32, 5);
  TEST("%+ *.*k", -32, 5);
  TEST("%16k");
  TEST("%0k %0.1k");
  TEST("%%d", 17);
  TEST("%%%d", 17);
  TEST("%*.*k %0*.*k", 0, 0, 0, 0);
  TEST("%.2p", main);
  TEST("%.12p", main);
  TEST("%2p", main);
  TEST("%12p", main);
  TEST("%012p", main);
  TEST("% 12p", main);
  TEST("%-12p", main);
  TEST("%.2p", NULL);
  TEST("%.12p", NULL);
  TEST("%2p", NULL);
  TEST("%12p", NULL);
  TEST("%012p", NULL);
  TEST("% 12p", NULL);
  TEST("%-12p", NULL);
  TEST("%hp", main);
  TEST("%2s", NULL);
  TEST("%10s", NULL);
  TEST("%.5s", NULL);
  TEST("%.6s", NULL);
  TEST("%zy");

  /* Exemples http://www.opengroup.org/onlinepubs/000095399/functions/printf.html */

  /* Formatting a Decimal String */
  printf("/* Formatting a Decimal String */\n\n");
  TEST("%s Element%0*ld", "keystr", 2, 1);

  /* Exemples http://fr.wikibooks.org/wiki/Programmation_C_Entr%C3%A9es/sorties */

  printf("/* Exemples http://fr.wikibooks.org/wiki/Programmation_C_Entr%%C3%%A9es/sorties */");
  TEST("%10s", "Salut");
  TEST("%-10s", "Salut");
  TEST("%10s", "Salut tout le monde");
  TEST("%10.10s", "Salut tout le monde");
  TEST("%-*d", 10, 1234);
  TEST("%*d",  10, 1234);
  TEST("%+010d", 543);
  TEST("%-+10d", 543);
  TEST("%-+10d", 1234567890);
  TEST("%-+10.10d", 1234567890);
  TEST("%08x", 543);

  /* Anciens tests XOS */

  printf("/* Anciens tests XOS */\n\n");
  TEST("%*d", 10, 2);
  TEST("%.*d", 10, 2);
  TEST("0x%0*x", 8, 0x12345);
  TEST("");

  /* caracteres larges */
#if 0
  TEST("%hs %ls", "ABC", "ABC");
#endif

  /* %n$ et *n$, ainsi que le drapeau ', ne font pas partie du C standard, mais sont definis dans Single Unix Specification. */
#if 0
  struct {
    int tab[6000];
  } dummy;

  /* drapeaux */
  printf("/* drapeaux */\n\n");
  TEST("%'d", 123456789);

  /* nieme argument */
  printf("/* nieme argument */\n\n");
  TEST("%2$d %1$s", "Bonjour", 1);
  TEST("%2$d %2$d", "Bonjour", 1);
  TEST("%2$d %% %1$s", "Bonjour", 1);
  TEST("%1$d:%2$.*3$d:%4$.*3$d", 21, 4, 2, 3);
  TEST("%4000$d", dummy);

  /* combinaisons plus complexes */
  TEST("%2d %2$d %2$2d", 1, 2);
  printf("/* combinaisons plus complexes */\n\n");

  /* conversions erronees ou non specifiees */
  printf("/* conversions erronees ou non specifiees */\n\n");
  TEST("%0$d", 236);
  TEST("%2$c", 'a', 'b', 'c');
  TEST("%2$d %d", 1, 2, 3);
  TEST("%d %2$d", 1, 2, 3);
  TEST("%5000$d", dummy);
  TEST("%5000$d", dummy);

  /* Exemples http://www.opengroup.org/onlinepubs/000095399/functions/printf.html */

  /* Printing Language-Independent Date and Time */
  printf("/* Printing Language-Independent Date and Time */\n\n");
  TEST("%s, %s %d, %d:%.2d", "Sunday", "July", 3, 10, 2);
  TEST("%1$s, %3$d. %2$s, %4$d:%5$.2d", "Sonntag", "Juli", 3, 10, 2);

  /* Anciens tests XOS */

  printf("/* Anciens tests XOS */\n\n");
  TEST("%1$d", 1);
  TEST("%1$d %2$d", 1, 2);
  TEST("%2$d %1$d", 1, 2);
  TEST("%2$d %d %3$d %d %d", 1, 2, 3);
  TEST("%2$d %2$d", 1, 2);
  TEST("%2$*1$d", 10, 2);
  TEST("%*1$d", 10);
  TEST("%1$*d", 10);
  TEST("%0$d", 1);
  TEST("%-1$d", 1);
  TEST("%01$d", 1);
#endif

  return 0;
}
