#include <stdio.h>
#include <limits.h>
#include <float.h>

main()
{
    printf("%s:\n", "limits.h");
	printf("\tCHAR_BIT:%d\n", CHAR_BIT);
	printf("\tCHAR_MAX:%d\n", CHAR_MAX);
	printf("\tCHAR_MIN:%d\n", CHAR_MIN);
	printf("\tINT_MAX:%d\n", INT_MAX);
	printf("\tINT_MIN:%d\n", INT_MIN);
	printf("\tLLONG_MAX:%lld\n", LLONG_MAX);
	printf("\tLLONG_MIN:%lld\n", LLONG_MIN);
	printf("\tLONG_BIT:%d\n", LONG_BIT);
	printf("\tLONG_MAX:%ld\n", LONG_MAX);
	printf("\tLONG_MIN:%ld\n", LONG_MIN);
	printf("\tMB_LEN_MAX:%d\n", MB_LEN_MAX);
	printf("\tSCHAR_MAX:%d\n", SCHAR_MAX);
	printf("\tSCHAR_MIN:%d\n", SCHAR_MIN);
	printf("\tSHRT_MAX:%d\n", SHRT_MAX);
	printf("\tSHRT_MIN:%d\n", SHRT_MIN);
	printf("\tSSIZE_MAX:%ld\n", SSIZE_MAX);
	printf("\tUCHAR_MAX:%u\n", UCHAR_MAX);
	printf("\tUINT_MAX:%u\n", UINT_MAX);
	printf("\tULLONG_MAX:%lld\n", ULLONG_MAX);
	printf("\tULONG_MAX:%lu\n", ULONG_MAX);
	printf("\tUSHRT_MAX:%u\n", USHRT_MAX);
	printf("\tWORD_BIT:%d\n", WORD_BIT);

}
