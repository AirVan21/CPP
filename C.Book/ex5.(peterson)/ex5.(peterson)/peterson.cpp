#include <stdio.h>

/*
	Global variable definition
*/
const unsigned int processAmount = 2;
bool interested[processAmount];

/*
	Enter a critical section
*/
void enter_section(int process)
{
	int other = 1 - process;
	interested[process] = true;
	int turn = process;
	while (turn == process && interested[other] == true)
		; // Lock spin
}

/*
	Leave the critical section
*/
void leave_process(int process)
{
	interested[process] = false;
}

int main() 
{

}