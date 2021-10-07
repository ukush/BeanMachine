#include <iostream>
#include <crtdbg.h>
#include <time.h>

int* determineBallBuckets(const int noOfBalls, const int noOfLevels);
int* tallyBalls(const int noOfBalls, const int* balls, const int noOfBuckets);
void printHashes(int numOfHashes);
void showDistribution(int noOfBuckets, int* bucketCount);

int main()
{

#ifdef _DEBUG
	//_CrtSetBreakAlloc(201);
	_onexit(_CrtDumpMemoryLeaks);
#endif


	//seed random numbers
	srand(time(nullptr));

	// declare variables
	int noOfBalls;
	int noOfLevels;


	//prompt user
	std::cout << "Welcome to Bean Machine!\n";
	std::cout << "How many balls would you like to drop?\n";
	std::cin >> noOfBalls;
	std::cout << "And how many levels would you like to drop them?\n";
	std::cin >> noOfLevels;

	int* balls = determineBallBuckets(noOfBalls, noOfLevels);

	int noofbuckets = noOfLevels + 1;

	int* bucketCount = tallyBalls(noOfBalls, balls, noofbuckets);


	showDistribution(noofbuckets, bucketCount);


	// release memory for balls as you don't need them anymore
	free(balls);
	balls = nullptr;

	// release memory for bucketcount
	free(bucketCount);



	return 0;
}


int* determineBallBuckets(const int noOfBalls, const int noOfLevels)
{
	//allocate memory for each ball on the heap
	int* balls = (int*)malloc(sizeof(int) * noOfBalls);

	for (int i = 0; i < noOfBalls; i++)
	{

		//Assign the values of the array elements (i.e. the buckets)
		balls[i] = 0;

		for (int j = 0; j < noOfLevels; j++)
		{
			// however many times the ball goes right, the destination bucket is always 1 more
			// i.e. if the ball goes right 4 times, it will always land in bucket 5


			// determine whether the ball goes right or left
			if (rand() > RAND_MAX / 2)
			{
				//add 1 to the ball
				++balls[i];
			}
		}
	}

	return balls;
}


int* tallyBalls(const int noOfBalls, const int* balls, const int noOfBuckets)
{
	// number of buckets is equal to the number of leb

	// Allocate more heap memory
	int* bucketCount = (int*)malloc(sizeof(int) * (noOfBuckets));


	// Start each bucket count from 0
	for (int i = 0; i < noOfBuckets; i++)
	{
		bucketCount[i] = 0;
	}


	// count how many balls landed in each bucket
	// The pointer balls[i] contain the number of balls in each bucket
	// make bucketCount[i] = balls[i]

	for (int i = 0; i < noOfBalls; i++)
	{
		bucketCount[balls[i]]++;
	}

	return bucketCount;
}


void showDistribution(int noofbuckets, int* bucketCount)
{
	//Print output
	for (int i = 1; i < (noofbuckets + 1); i++)
	{
		std::cout << "Bucket #" << (i) << ":";
		printHashes(bucketCount[i]);
		std::cout << "\n";
	}

}

void printHashes(int numOfHashes)
{

	for (int i = 0; i < numOfHashes; i++)
	{
		std::cout << "#";
	}
}