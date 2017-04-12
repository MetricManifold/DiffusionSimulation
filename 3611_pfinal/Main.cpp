
#include <Windows.h>
#include <iostream>
#include <iostream>

#include "Problems.h"

int main()
{
	short question;
	problems *p = new problems();
	bool loop = true;

	std::cout << "WELCOME TO 3611 FINAL PROJECT" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	while (loop)
	{
		// Option menu.
		std::cout << "Select problem number [1, 2, 3, 4 | 0 to quit]: ";
		std::cin >> question;
		std::cout << std::endl;

		switch (question)
		{
		case 1:
			// Problem 1
			std::cout << "PROBLEM 1" << std::endl;
			std::cout << "********************************************************************************" << std::endl;
			p->problem1();
			std::cout << std::endl;
			break;

		case 2:
			// Problem 2
			std::cout << "PROBLEM 2" << std::endl;
			std::cout << "********************************************************************************" << std::endl;
			p->problem2();
			std::cout << std::endl;
			break;

		case 3:
			// Problem 3
			std::cout << "PROBLEM 3" << std::endl;
			std::cout << "********************************************************************************" << std::endl;
			p->problem3();
			std::cout << std::endl;
			break;

		case 4:
			// Problem 4
			std::cout << "PROBLEM 4" << std::endl;
			std::cout << "********************************************************************************" << std::endl;
			p->problem4();
			std::cout << std::endl;
			break;

		case 0:
			loop = false;
			break;

		default:
			break;
		}
	}

	std::cout << "Thank you for using this project." << std::endl << std::endl;

	delete p;

	system("pause");
	return 0;
}