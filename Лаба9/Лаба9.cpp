
#include <iostream>
#include<locale>
#include<conio.h>
#include<io.h>
#include"Saller.h"
#include<windows.h>

void SelectionSort(FILE* stream)
{
	int count = _filelength(_fileno(stream)) / sizeof(Seller);
	for (int i = 0; i < count - 1; i++)
	{
		int max = i;
		for (int j = i + 1; j < count; j++)
		{
			Seller* seller1 = new Seller();
			Seller* seller2 = new Seller();

			fseek(stream, j * sizeof(Seller), 0);
			fread(seller1, sizeof(Seller), 1, stream);

			fseek(stream, max * sizeof(Seller), 0);
			fread(seller2, sizeof(Seller), 1, stream);

			if (seller1->Rating > seller2->Rating) max = j;

			delete seller1;
			delete seller2;

		}
		if (max != i)
		{
			Seller* seller1 = new Seller();
			Seller* seller2 = new Seller();

			fseek(stream, i * sizeof(Seller), 0);
			fread(seller1, sizeof(Seller), 1, stream);

			fseek(stream, max * sizeof(Seller), 0);
			fread(seller2, sizeof(Seller), 1, stream);

			fseek(stream, i * sizeof(Seller), 0);
			fwrite(seller2, sizeof(Seller), 1, stream);

			fseek(stream, max * sizeof(Seller), 0);
			fwrite(seller1, sizeof(Seller), 1, stream);

			delete seller1;
			delete seller2;
		}
	}
}

void Delete(FILE* stream, int i)
{
	int count = _filelength(_fileno(stream)) / sizeof(Seller);
	if (i != count - 1)
	{
		Seller* sel = new Seller();
		fseek(stream, (count - 1) * sizeof(Seller), 0);
		fread(sel, sizeof(Seller), 1, stream);
		fseek(stream, i * sizeof(Seller), 0);
		fwrite(sel, sizeof(Seller), 1, stream);
		delete sel;
	}
	_chsize(_fileno(stream), sizeof(Seller) * (--count));
}
void BinarSort(FILE* stream)
{
	int count = _filelength(_fileno(stream)) / sizeof(Seller);
	for (int i = 1; i < count; i++)
	{
		Seller* seller1 = new Seller();
		Seller* seller2 = new Seller();
		fseek(stream, i * sizeof(Seller), 0);
		fread(seller1, sizeof(Seller), 1, stream);
		fseek(stream, (i - 1) * sizeof(Seller), 0);
		fread(seller2, sizeof(Seller), 1, stream);
		if (strcmp(seller1->Name, seller2->Name) < 0)
		{


			int left = 0;

			int right = i - 1;

			while (left <= right)
			{

				int mid = (left + right) / 2;
				Seller* seller = new Seller();
				fseek(stream, mid * sizeof(Seller), 0);
				fread(seller, sizeof(Seller), 1, stream);
				if (strcmp(seller->Name, seller1->Name) < 0)

					left = mid + 1;

				else right = mid - 1;
				delete seller;
			}
			for (int j = i - 1; j > right; j--)
			{
				Seller* seller = new Seller();
				fseek(stream, sizeof(Seller) * j, 0);


				fread(seller, sizeof(Seller), 1, stream);
				fseek(stream, sizeof(Seller) * (j + 1), 0);
				fwrite(seller, sizeof(Seller), 1, stream);

			}
			fseek(stream, sizeof(Seller) * (right + 1), 0);
			fwrite(seller1, sizeof(Seller), 1, stream);

		}
		delete seller1;
		delete seller2;

	}
}
int main()
{
	//setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const char* fileName = "Seller.bin";
	FILE* stream;
	int k = 0;


	while (k != '5')
	{

		printf("1 - посмотреть продавцов\n");
		printf("2 - добавить продавца\n");
		printf("3 - отсортировать по рейтингу\n");
		printf("4 - отсортировать по фамилии\n");
		printf("5 - выход\n");

		k = _getch();

		if (k == '1')
		{
			system("cls");

			fopen_s(&stream, fileName, "ab+");               // если файл не создан, то
			fclose(stream);                                  // он создастся

			fopen_s(&stream, fileName, "rb+");
			//BinarSort(stream);
			int count = _filelength(_fileno(stream)) / sizeof(Seller);
			if (count == 0)
			{

				printf("Список пуст!\n");
				Sleep(400);
			}
			else
			{
				int num = 0;
				while (num != -1 && count)
				{

					system("cls");
					num = -1;

					fseek(stream, 0, 0);
					for (int i = 0; i < count; ++i)
					{
						Seller* seller = new Seller();
						fread(seller, sizeof(Seller), 1, stream);
						std::cout << i + 1 << ". " << seller->Name << " " << seller->Surname << ": "; printf(".1lf\n", seller->Rating);
						delete seller;
					}

					printf("\n\n");
					printf("Выберите продавца, введя его порядковый номер, имя или фамилию.\n");
					char input[20];
					gets_s(input);


					if (atoi(input))
					{

						if (!(atoi(input) > count || atoi(input) < 1))
						{
							num = atoi(input);
						}
					}
					else
					{
						fseek(stream, 0, 0);
						for (int i = 0; i < count; i++)
						{
							Seller* seller = new Seller();

							fread(seller, sizeof(Seller), 1, stream);
							if (!strcmp(seller->Name, input) || !strcmp(seller->Surname, input))
							{
								num = i + 1;
								break;
							}
							delete seller;
						}

					}
					if (num != -1)
					{
						int key = 0;
						while (key != '3')
						{
							Seller* seller = new Seller();
							fseek(stream, sizeof(Seller) * (num - 1), 0);
							fread(seller, sizeof(Seller), 1, stream);
							system("cls");
							printf("Продавец %s %s \n", seller->Name, seller->Surname);
							printf("Рейтинг: %.1lf\n", seller->Rating);
							printf("\n\n\n\n");
							printf("1 - добавить покупателя\n");
							printf("2 - уволить\n");
							printf("3 - назад\n");

							key = _getch();
							if (key == '1')
							{
								int n1;
								int n2;
								double t;
								printf("Введите количество штучных товаров: ");

								scanf_s("%d", &n1);

								printf("Введите количество весовых: ");
								scanf_s("%d", &n2);

								printf("Введите время в секундах: ");
								scanf_s("%lf", &t);
								seller->AddBuyer(n2, n1, t);
								fseek(stream, sizeof(Seller) * (num - 1), 0);
								fwrite(seller, sizeof(Seller), 1, stream);
								delete seller;

							}
							if (key == '2')
							{
								Delete(stream, num - 1);
								key = '3';
								count--;
							}
						}
					}
					else
					{
						printf("Введено неккоректно число!\n");
						_getch();
					}
				}
			}
			fclose(stream);
		}
		if (k == '2')
		{
			system("cls");
			Seller* seller = new Seller();
			fopen_s(&stream, fileName, "ab+");
			printf("Имя продавца: ");
			gets_s(seller->Name);
			printf("Фамилия продавца: ");
			gets_s(seller->Surname);
			fwrite(seller, sizeof(Seller), 1, stream);
			fclose(stream);
			delete seller;
		}
		if (k == '3')
		{
			fopen_s(&stream, fileName, "ab+");
			fclose(stream);

			fopen_s(&stream, fileName, "rb+");
			SelectionSort(stream);


			if (_filelength(_fileno(stream)))
			{
				printf("Отсортировано!\n");

			}
			else
				printf("Список пуст!\n");
			fclose(stream);
			Sleep(400);

		}
		if (k == '4')
		{
			fopen_s(&stream, fileName, "ab+");
			fclose(stream);

			fopen_s(&stream, fileName, "rb+");
			BinarSort(stream);
			if (_filelength(_fileno(stream)))
			{
				printf("Отсортировано!\n");

			}
			else
				printf("Список пуст!\n");
			fclose(stream);

			Sleep(400);

		}

		system("cls");
	}
}

