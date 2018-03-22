#ifndef FUN
#define FUN
struct time
{
	int Hours;
	int Minutes;
};

typedef struct time time;

struct train
{
	char destination[16];
	int trainNum;
	time tTime;
} temp;

typedef struct train train;

void sortAZ(train *, int);
int writeBinary(train *, int);
int readBinary(train *);
int showTrain(long);
int findTrains(int, int);
int printColumn (int, train *);
void printArray(train *, int);
#endif
