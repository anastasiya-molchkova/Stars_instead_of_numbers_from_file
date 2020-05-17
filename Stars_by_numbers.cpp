/*
Напишите программу, которая считывает из файла целые числа, которые рандомно генерируются в диапазоне от 1 до 72. 
Для каждого считанного числа ваша программа должна вывести строку, 
содержащую соответствующее количество звёздочек. 
Например, если ваша программа считала из файла число 7, то она должна вывести 7 звёздочек: *******.
Пример выполнения программы:
Числа из файла: 3 17 48 52 46 58 59 64 57
Результат:
Число №1 = 3 ***
*/

#include <iostream>
#include <fstream>   // для работы с файлами
#include <cstdlib>   // для функций выбора случайного числа srand() и rand() и exit из файла
#include <ctime>     // чтобы в randomize опираться на время запуска программы

// функция выбора случайного числа между двумя заданными значениями
static unsigned short getRandomNumber(unsigned short min, unsigned short max)
{
	static const double fraction = 1.0 / static_cast<double>(RAND_MAX + 1.0);
	return static_cast<unsigned short>(rand() * fraction * (max - min + 1) + min);
}

// записываем рандомные числа в файл
void record_to_file(std::fstream& data_file, const unsigned& rows_number)
{
	for (unsigned short i = 1; i <= rows_number; i++)
		data_file << getRandomNumber(1, 72) << std::endl;
}

// считываем значения из файла, выводим ***
void read_from_file(std::fstream& data_file, const unsigned& rows_number)
{
	// т.к. до этого была запись в файл, перемещаем файловый указатель в начало файла для чтения
	data_file.seekp(0, std::ios::beg);

	// цикл по строкам файла
	for (unsigned short i = 1; i <= rows_number; i++)
	{
		unsigned short number_from_file;
		data_file >> number_from_file;
		
		// выводим результат:
		std::cout << "Число №" << i << " = " << number_from_file << " ";
		// выводим нужное количество звёздочек
		for (unsigned short j = 1; j <= number_from_file; j++)
			std::cout << "*";
		std::cout << std::endl;
	}
	data_file.clear(); // очищаем файл, чтобы использовать его повторно при следующем запуске программы
}

int main()
{
	// подключаем кириллицу для вывода сообщений
	setlocale(LC_CTYPE, "rus");

	//аналог randomize с привязкой ко времени запуска:
	srand(static_cast<unsigned int>(time(0)));
	rand();

	// создаём файловую переменную для файла и проверяем файл:
	std::fstream data_file("numbers.txt");
	if (!data_file)
	{
		std::cerr << "Невозможно открыть файл для записи и чтения значений!" << std::endl;
		exit(1);
	}

	const unsigned rows_number = 10;        //  задаём количество чисел для работы
	record_to_file(data_file, rows_number);
	read_from_file(data_file, rows_number);

	return 0;
}