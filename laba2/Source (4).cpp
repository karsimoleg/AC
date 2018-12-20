#include<iostream>
#include<fstream>

using namespace std;

void show_array(char *array, int n)//������� ������ 
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
	int n = sizeof(gaika) / sizeof(gaika[0]);// ���������� �-�� �������� 


	cout << "��������i �� �i���������i �������� " << endl;
	show_array(bolt, n);//���������� ������ �� �����
	show_array(gaika, n);
	match(bolt, gaika, 0, n - 1);
	cout << "�������� �i��� ���������� " << endl;
	show_array(bolt, n);
	show_array(gaika, n);

	system("pause");
	return 0;
}


int pod(char *array, int left, int right, char pivot) //���� �������� 
{
	int i = left;//�������� ���������� � ��� 
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
	swap(array[i], array[right]);//������ ���� ������� � �����
	// ������� ������ ������ ������ 
	
	return i;
}

void match(char * bolt, char * gaika, int left, int right)
{
	if (left < right)
	{
		// �����a��� ������� ������ ������ ����� ��� ������ �����
		int pivot = pod(gaika, left, right, bolt[right]);

		// ����� �������������� ����� ����� �������� �����
		pod(bolt, left, right, gaika[pivot]);

		//���������� ��������� ������ �� ����� ��������
		match(gaika, bolt, left, pivot - 1)//������ �� ��� ������������ �������� 
		match(gaika, bolt, left, pivot - 1)
		matcha(gaika, bolt, pivot + 1, right);
	}
}