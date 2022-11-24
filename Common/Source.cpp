//#include <iostream>
//#include <time.h>
//
//int main()
//{
//	int arr[23];
//	for (int i = 0; i < 23; i++)
//		arr[i] = 0;
//	
//	int rndNum;
//	int total = 0;
//	int groupSize = 4;
//	srand(time(NULL));
//	std::cout << arr[0];
//
//	while(total != 22)
//	{
//		rndNum = rand() % 22 + 1; //1-22 range
//		if (arr[rndNum] == 0)
//		{
//			arr[rndNum] = rndNum;
//			total++;
//		}
//			
//	}
//
//	for (int i = 1; i <= 23; i++)
//	{
//		if (i % groupSize == 0)
//		{
//			std::cout << "Next Group:\n\n";
//		}
//
//		std::cout << arr[i] << "\n";
//
//	}
//
//	std::cout << arr[21] << "\n";
//	std::cout << arr[22] << "\n";
//
//}