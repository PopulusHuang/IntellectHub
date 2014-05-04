#include <stdio.h>
#include <time.h>
int main(int argc, const char *argv[])
{
	time_t now_time;
	time_t old_time;
	time(&now_time);
	old_time=atoi(argv[1]);
	printf("%d\n",now_time-old_time);
	return 0;
}
