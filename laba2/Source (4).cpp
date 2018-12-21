#include<iostream>
#include<fstream>

using namespace std;

void show_array(char *array, int n)//функція виводу 
{
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

void match(char*bolt, char*gaika, int left, int right);
int main()
{
	setlocale(LC_ALL, "Russian");
	char gaika[] = { '@', '#', '$', '%', '^', '&' };
	char bolts[] = { '$', '%', '&', '^', '@', '#' };
	int n = sizeof(gaika) / sizeof(gaika[0]);// підраховуємо к-то елементів 


	cout << "Початковi не вiдсортованi елементи " << endl;
	show_array(bolt, n);//відображаємо иболти та гайки
	show_array(gaika, n);
	match(bolt, gaika, 0, n - 1);
	cout << "елементи пiсля сортування " << endl;
	show_array(bolt, n);
	show_array(gaika, n);

	system("pause");
	return 0;
}


int pod(char *array, int left, int right, char pivot) //поділ елементів 
{
	int i = left;//починаємо сортування з ліва 
	for (int j = left; j < right; j++)
	{
		if (array[j] < pivot)
		{
			swap(array[i], array[j]);
			i++;
		}
		else if (array[j] == pivot)
		{
			swap(array[j], array[right]);
			j--;
		}
	}
	swap(array[i], array[right]);//міняємо лівий елемент в право
	// повертає індекс розділу масиву 
	
	return i;
}

void match(char * bolt, char * gaika, int left, int right)
{
	if (left < right)
	{
		// виберaємо останній символ масиву болтів для розділу гайок
		int pivot = pod(gaika, left, right, bolt[right]);

		// тепер використовуючи розділ гайок розділимо болти
		pod(bolt, left, right, gaika[pivot]);

		//рекурсивно розділяємо масиви на менші підмасиви
		match(gaika, bolt, left, pivot - 1)//робимо це для пришвидшення алгориму 
		match(gaika, bolt, left, pivot - 1)
		matcha(gaika, bolt, pivot + 1, right);
	}
}