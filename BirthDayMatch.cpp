#include <iostream>
#define numsims 20000
#define possibleBdays 364
using namespace std;
void RandomBdays(int *room, int numPeople);
void FindMatch(int *classroomBirthdays, int numPeople, int &mc);

/*
	This program simulates the probability of having two people with matching
	birthdays in rooms of 1 to 50 people. Each room's probability is output
	as well as the number of people in the room needed to have a >= 0.5 probability
*/

int main()
{
	double probability;
	int classroomBirthdays[50];
	int matchcount = 0;
	int magicN; // n value in which probability becomes >= 0.5
	bool foundmagicN = false; // Locks first 'n' value >= 0.5
	
	for (int n = 1; n <= 50; n++) // Simulate probability from 1 to 50 people
	{
		for (int i = 0; i < numsims; i++) // Run simulation for each room 20000 times
		{
			RandomBdays(classroomBirthdays, n);
			FindMatch(classroomBirthdays, n, matchcount);
		}

		probability = (double)matchcount / numsims;
		cout << "Probability of match within class of " << n << " students is " << probability << endl;
		matchcount = 0; // Reset Birthday match counter for next room

		if (foundmagicN == false && probability >= 0.5) // Finds first 'n' value >= 0.5 then locks it
		{
			magicN = n;
			foundmagicN = true;
		}

	}
	cout << endl << "No. of people needed in room for good chances of matching birthday: " << magicN << endl;
	system("pause");
	return 0;
}

// variables for randomBdays function
#define possibleBdays 364 // 0 - 364
long limit = RAND_MAX - RAND_MAX % possibleBdays;
int x;

void RandomBdays(int *classroomBirthdays, int numPeople) // Records random birthdays of room of people
{
	for (int i = 0; i < numPeople; i++)
	{
		do {
			x = rand();
		} while (x >= limit);
		classroomBirthdays[i] = x % possibleBdays;
	}
}

void FindMatch(int *classroomBirthdays, int numPeople, int &mc) // Detects matching birthdays in room
{
	for (int i = 0; i < numPeople; i++)
	{
		for (int j = i + 1; j < numPeople; j++)
		{
			if (classroomBirthdays[i] == classroomBirthdays[j])
			{
				mc++;
				j = i = numPeople; // duplicate has been found; stop searching
			}
		}
	}
}