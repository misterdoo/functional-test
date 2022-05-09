
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <time.h> 
#include <sys/times.h> 


char *prefix[] = {
    "NOR_",
    "EVT_",
    "TIM_",
    "NOM_",
    "TIN_",
    "PAK_",
    "PAM_",
};

int main(int argc, char** argv)
{
#if 0
	char* new_prefix = "NOM_TEST_";
    int i, to = sizeof(prefix) / sizeof(prefix[0]);

	printf("(%d)\n", &new_prefix);

    for (i = 0; i < to; i++) {
        if (*((int *)prefix[i]) == *((int *)new_prefix)) {
			printf("end (%d), (%p)-(%p)\n", i, *((int *)prefix[i]), *((int *)new_prefix));
			break;
        }
    }
#endif

	clock_t ct0, ct1; 
	struct tms tms0, tms1; 
	int i; 

	long sys_clk_tck = sysconf(_SC_CLK_TCK);
	int period = 2000;

	printf ("_SC_CLK_TCK = %ld, cal= %ld\n", sys_clk_tck, period * sys_clk_tck / 1000);

	if ((ct0 = times (&tms0)) == -1) 
		perror ("times"); 


	sleep(1);

	if ((ct1 = times (&tms1)) == -1) 
		perror ("times"); 

	printf ("ct0 = %ld, times: %ld %ld %ld %ld\n", ct0, tms0.tms_utime, tms0.tms_cutime, tms0.tms_stime, tms0.tms_cstime); 
	printf ("ct1 = %ld, times: %ld %ld %ld %ld\n", ct1, tms1.tms_utime, tms1.tms_cutime, tms1.tms_stime, tms1.tms_cstime); 
	printf ("ct1 - ct0 = %ld\n", ct1 - ct0); 

	return 0;
}

