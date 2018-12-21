#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string.h>
#include <conio.h>
#define RANGE 255


using namespace std;

struct Elem_of_Arr
{
	int data;
	int key;
};

//////////////////////////////////////////////////////////////////////////////////////////

void Create_Arr(Elem_of_Arr* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i].data = rand() % 50 + 1;
		arr[i].key = rand() % 2;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Show_Arr(Elem_of_Arr* arr, int size)
{
	cout << "Data[key]: ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i].data << " [ " << arr[i].key << " ] ";

		if (i != size - 1)
		{
			cout << ", ";
		}
		else
		{
			cout << ". ";
		}
	}
	cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////

void Copy_Arr(Elem_of_Arr* arr_old, Elem_of_Arr* arr_new, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr_new[i].data = arr_old[i].data;
		arr_new[i].key = arr_old[i].key;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void First_Sort(Elem_of_Arr* arr, Elem_of_Arr* result, int size)
{
	cout << "\n 1) O(n) and stable \n" << endl;

	int left = 0;
	int right = 0;

	for (int i = 0; i < size; i++)
	{
		if (arr[i].key == 0)
		{
			right++;
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (arr[i].key == 0)
		{
			result[left] = arr[i];
			left++;
		}
		else
		{
			result[right] = arr[i];
			right++;
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////

void Second_Sort(Elem_of_Arr* arr, int size)
{
	cout << "\n 2) O(n) and constant auxiliary memory \n" << endl;
	int right = size - 1;
	int left = 0;
	while (left < right)
	{
		while (arr[right].key != 0)
		{
			right--;
			if (right < 0)
			{
				return;
			}
		}
		while (arr[left].key != 1)
		{
			left++;
			if (left >= size)
			{
				return;
			}
		}
		if (right > left)
		{
			swap(arr[left], arr[right]);
			left++;
			right--;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Third_Sort(Elem_of_Arr* array, int size)
{
	cout << "\n 3) Stable sort and constant auxiliary memory \n" << endl;

	for (int i = 0; i < size; i++)
	{
		int j = i;
		while (j > 0 && array[j].key < array[j - 1].key)
		{
			swap(array[j], array[j - 1]);
			j--;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	srand(time(NULL));
	const int size = 3;

	Elem_of_Arr* arr1 = new Elem_of_Arr[size];
	Elem_of_Arr* arr2 = new Elem_of_Arr[size];
	Elem_of_Arr* arr3 = new Elem_of_Arr[size];
	Elem_of_Arr* result = new Elem_of_Arr[size];

	Create_Arr(arr1, size);
	Show_Arr(arr1, size);

	Copy_Arr(arr1, arr2, size);
	Copy_Arr(arr1, arr3, size);

	First_Sort(arr1, result, size);
	Show_Arr(result, size);
	delete[] arr1;


	Second_Sort(arr2, size);
	Show_Arr(arr2, size);
	delete[] arr2;


	Third_Sort(arr3, size);
	Show_Arr(arr3, size);
	delete[] arr3;

	cout << endl;
	_getch();
	return 0;
}