#include "Arduino.h"

/*
TIME_MODE: 

0: simulated time -> every delay increases time counter by given value
1: busy wait -> delay(x) uses millis function and while to wait for millis to increase by given time (this causes CPU to be at 100% usage)
2: external time -> for simulations, time is set externaly by script or other source
3: actual wait/millis -> delay(x) uses task suspention for given milliseconds

*/



#include <chrono>
#include <thread>



#include <sys/time.h>

static uint64_t current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    uint64_t milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}






//Use Real System Time
static time_t millis0 = 0;

void _set_millis(uint32_t millis_new) 
{

	//Use Real System Time
	millis0 = current_timestamp() - millis_new;

}

uint32_t millis()
{

	long long clk = current_timestamp();
	if(millis0 == 0) // init time0 (time of start of program) at first call
		millis0 = clk;

	return (uint32_t) (clk - millis0);
}

uint32_t micros()
{
	return millis() * 1000;
}

void delay(uint32_t ms)
{

	// https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	return;
	
}

void delayMicroseconds(uint32_t us) {
	int ms = us / 1000;
	if(ms < 1)
		ms = 1;
	delay(ms);
}



void randomSeed(uint32_t seed)
{
	// https://cplusplus.com/reference/cstdlib/srand/
	//srand (time(NULL));
	srand(seed);
}


/*
float random()
{
	return ((float) rand() / RAND_MAX);
}
*/

void yield()
{
	
}