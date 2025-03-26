/**
 * Лабораторная работа №2. Массивы объектов, простое наследование, виртуальные
 * функции, применение наследования.
 *
 * В этой работе и далее предполагается, что вы будете использовать классы,
 * написанные в прошлых работах, и дополнять их по необходимости. Эти классы
 * будут называться по имени без дополнительных указаний, что их надо взять из
 * прошлой работы.
 *
 * Предполагается, что новый классы будут созданы по аналогии с предыдущими
 * работами в отдельных файлах, которые будут включены в сборку.
 *
 * При работе с классами - в учебных целях - нельзя пользоваться контейнерами
 * стандартной библиотеки и нужно следовать принципам инкапсуляции.
 */

#include "libs.h"
#include "base_file/base_file.h"
#include "file32/file32.h"
#include "file32/file32_2.h"
#include "rle_file/rle_file.h"
#include "rle_file/rle_file_2.h"
#include "my_string/my_string.h"

#define BUFFER_SIZE 256

void write_int(IFile *file, int n) {
    if (n < 0) {
        char minus = '-';
        file->write(&minus, 1); 
        n = -n; 
    }

    char buffer[BUFFER_SIZE];
	for (int i = 0; i < BUFFER_SIZE; ++i)
		buffer[i] = 0;

    int index = 0;
    do {
        buffer[index++] = '0' + (n % 10);
        n /= 10;
    } while (n > 0);

	char reverse[BUFFER_SIZE];
	for (int i = 0; i < BUFFER_SIZE; ++i)
		reverse[i] = 0;

	int rev_index = 0;

    while (index > 0) {
		reverse[rev_index++] = buffer[--index];
    }
	file->write(reverse, rev_index);
}

int main() {

	std::cout << "------ Лабороторная 2 ------" << std::endl; 

    /**
     * Задание 1. Массивы объектов класса.
     */

    /**
     * Задание 1.1. Массив объектов.
     *
     * Объявите и проинициализируйте массив ar из объектов типа MyString.
     * Выведите элементы массива на консоль.
     */

    {
		std::cout << "\n------ Задание 1.1 ------" << std::endl; 
		int size = 5;
        MyString ar[size] = {MyString("Hello"), MyString("World"), MyString("!")};
		
		for (int i = 0; i < size; ++i)
			ar[i].print();
    }

    /**
     * Замените размер массива с 3 на 5, не меняя список инициализаторов.
     *
     * Чем были инициализированы последние 2 элемента? Какие значения могут
     * стоять в списке инициализаторов - в вашем случае и в общем случае?
     */

    /**
     * Задание 1.2. Массив указателей на объекты.
     *
     * Объявите и проинициализируйте массив arPtr из трех указателей на объекты
     * типа MyString. Выведите элементы массива на консоль.
     */

    {
		std::cout << "\n------ Задание 1.2 ------" << std::endl; 
		int size = 3;
        MyString *ar[size] = {new MyString("Hello"), new MyString("World"), new MyString("!")};
		
		for (int i = 0; i < size; ++i)
			ar[i]->print();

		for (int i = 0; i < size; ++i)
			delete ar[i];
    }

    /**
     * Задание 2. Простое наследование. Аргументы конструктора, передаваемые в
     * базовый класс.
     */

    /**
     * Задание 2.1. Базовый класс.
     *
     * Создайте класс BaseFile, который будет реализовывать работу с файлами с
     * помощью стандартных средств C (cstdio).
     *
     * Класс должен иметь 3 конструктора: первый - конструктор по умолчанию,
     * второй должен принимать путь к файлу и параметры для открытия (как в
     * fopen), третий должен принимать готовый указатель FILE*.
     *
     * Считается, что этот класс *обладает* своим ресурсом - открытым файлом.
     * Что должно быть в дестукторе этого класса?
     *
     * Добавьте следующие методы:
     * - bool is_open() - возвращает true, если файл успешно открыт;
     * - bool can_read() - возвращает true, если из файла можно считать данные;
     * - bool can_write() - возвращает true, если в файл можно записать данные;
     * - size_t write_raw(const void *buf, size_t n_bytes) - записывает
     *   указанное количество байт в файл и возвращает количество байт, которое
     *   удалось записать;
     * - size_t read_raw(void *buf, size_t max_bytes) - читает доступные данные
     *   в буфер, но не более указанного количества и возвращает количество
     *   байт, которое удалось считать;
     * - long tell() - возвращает текущий сдвиг файла (см. функцию ftell);
     * - bool seek(long offset) - устанавливает сдвиг файла (см. функцию fseek)
     *   и возвращает true, если операция успешна.
     *
     * Добавьте также методы `read` и `write`, которые в этом классе будут
     * делать буквально то же, что `read_raw` и `write_raw`, они понадобятся нам
     * позже.
     *
     * Проверьте работу этого класса.
     */
	{
		std::cout << "\n------ Задание 2.1 (часть 1) ------" << std::endl; 

		const char* source = "Hello, world! My name is Nastya";
		const char *file_name = "build/files/task 2.1 (1).txt";
		char buffer[BUFFER_SIZE];

		BaseFile write_file(file_name, "w");

		for (int i = 0; i < BUFFER_SIZE; ++i) 
			buffer[i] = 0;

		write_file.write(source, std::strlen(source));
		write_file.close();

		std::cout << "Записанные в файл данные: " << source << std::endl;

		BaseFile read_file(file_name, "r");

		for (int i = 0; i < BUFFER_SIZE; ++i) 
			buffer[i] = 0;

		read_file.read(buffer, BUFFER_SIZE);
		std::cout << "Считанные из файла данные: " <<  buffer << std::endl; 
	}
	
	{
		std::cout << "\n------ Задание 2.1 (часть 2) ------" << std::endl; 

		const char* file_name = "build/files/task 2.1 (2).txt";
		BaseFile file(file_name, "r");

		const int size = 10;
		char buffer[size];

		if (file.is_open() && file.can_read()) {
			while (file.read(buffer, size) > 0) {
				std::cout << buffer;
			}
		}	
	}

    /**
     * Задание 2.2. Производные классы.
     *
     * Производный класс *наследуется* от базового класса и каким-то образом
     * расширяет его функциональность, при это все еще умея все, что умеет
     * базовый класс.
     *
     * Реализуйте следующие производные классы от класса BaseFile. Производные
     * классы нужно унаследовать так, чтобы пользователю были все еще доступны
     * методы базового класса. Каким образом нужно унаследовать класс для этого?
     * Как еще можно унаследовать класс?
     *
     * Производные классы могут располагаться в том же файле, где и базовый
     * класс.
     *
     * В производных классах добавьте необходимые конструкторы, которые будут
     * вызывать конструктор базового класса.
     *
     * Проверьте работу производных классов.
     */

    /**
     * Задание 2.2.1. Base32 кодировщик/декодировщик.
     *
     * Создайте производный класс Base32File, который будет проводить при
     * записи кодировку-декодировку данных, по алгоритму, который вы
     * реализовали в лабораторной работе №4 прошлого семестра.
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с декодировкой и запись в файл с кодировкой соответственно.
     *
     * Добавьте возможность пользователю передать в конструктор таблицу
     * кодировки, по умолчанию используется таблица "A..Z1..6".
     */

	{
		std::cout << "\n------ Задание 2.2.1 ------" << std::endl; 

		const char* source = "Hello, world! My name is Nastya";
		const char *file_name = "build/files/task 2.2.1.txt";
		char buffer[BUFFER_SIZE];

		Base32File write_file(file_name, "w");

		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

		write_file.write(source, std::strlen(source));
		write_file.close();

		std::cout << "Запись в файл: " << source << std::endl;

		BaseFile base_read(file_name, "r");

		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

    	base_read.read(buffer, BUFFER_SIZE);
    	base_read.close();
    
    	std::cout << "'Сырые' данные: " << buffer << std::endl;

		Base32File read_file(file_name, "r");

		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

		read_file.read(buffer, std::strlen(source));
		std::cout << "Дешифрованные данные: " <<  buffer << std::endl; 
	}
	
    /**
     * Задание 2.2.2. RLE-сжатие.
     *
     * Создайте производный класс RleFile, который будет проводить побайтовое
     * сжатие при помощи алгоримта RLE (для простоты можно реализовать
     * неэффективный алгоритм, где последовательности без повторений отдельно
     * не кодируются).
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с извлечением сжатой информации и запись в файл со сжатием
     * соответственно.
     *
     * Проверьте сжатие/извлечение на примере какого-нибудь ASCII-арта,
     * например, котенка из лабораторной №3 прошлого семестра. Посмотрите,
     * получилось ли добиться уменьшения размера хранимых данных.
     */

	{
		std::cout << "\n------ Задание 2.2.1 ------" << std::endl; 

		int source_size = 256 * 2; 

		char source[source_size];
		for (int i = 0; i < source_size; ++i)
			source[i] = 0;

		BaseFile source_file("build/files/task 2.1 (2).txt", "r");
		source_file.read(source, source_size);
		source_file.close();
		
    	const char* file_name = "build/files/task 2.2.1.txt";
    	char buffer[source_size];

		RleFile rle_write(file_name, "w");
		std::cout << "Возмьмем файл из задания 2.1 (2): \n" << source << std::endl;
    	rle_write.write(source, strlen(source));
    	rle_write.close();

		BaseFile base_read(file_name, "r");

		for (int i = 0; i < source_size; ++i)
			buffer[i] = 0;

    	base_read.read(buffer, BUFFER_SIZE);
    	base_read.close();
    
    	std::cout << "'Сырые' данные: \n" << buffer << std::endl;

		RleFile rle_read(file_name, "r");

		for (int i = 0; i < source_size; ++i)
			buffer[i] = 0;

    	rle_read.read(buffer, source_size);
    	rle_read.close();
    
    	std::cout << "Распакованные данные: \n" << buffer << std::endl;
	}

    /**
     * Задание 2.3. Конструкторы и деструкторы базового и производного классов.
     *
     * Установите отладочную печать в конструкторах и деструкторах каждого
     * класса из этого задания. Создайте локальные объекты производных классов,
     * отметьте, в каком порядке вызываются конструкторы и деструкторы при
     * инициализации и деинициализации этих классов.
     */

    /**
     * Задание 2.4. Ранее связывание.
     *
     * На основе данной заготовки напишите код, который запишет в файл строковое
     * представление целого числа. Вы должны использовать один и тот же код для
     * всех файлов, меняя только имя объекта (bf / b32f / rf), в который идет
     * запись.
     */

    {
		std::cout << "\n------ Задание 2.4 ------" << std::endl; 

        BaseFile bf("build/files/task 2.4 (1).txt", "w");
        Base32File b32f("build/files/task 2.4 (2).txt", "w");
        RleFile rf("build/files/task 2.4 (3).txt", "w");

        int n = 123456;
        if (n < 0) { 
            char minus = '-'; 
            bf.write(&minus, 1); 
        }
        while (n > 0) {
            char digit = '0' + (n % 10); // Преобразуем цифру в символ
            bf.write(&digit, 1);         // Записываем цифру в файл
            n /= 10;                     // Переходим к следующей цифре
        }

         n = 123456;
        if (n < 0) { 
            char minus = '-'; 
            b32f.write(&minus, 1); // Записываем знак минус для отрицательного числа
        }
        while (n > 0) {
            char digit = '0' + (n % 10); 
            b32f.write(&digit, 1);     
            n /= 10;                  
        }

        n = 123456;
        if (n < 0) { 
            char minus = '-'; 
            rf.write(&minus, 1); 
        }
        while (n > 0) {
            char digit = '0' + (n % 10); 
            rf.write(&digit, 1);      
            n /= 10;               
        }
    }

    /**
     * Задание 2.5. Передача объекта по ссылке / указателю.
     *
     * Прошлое задание выглядит странновато - зачем повторять код три раза?
     * Хорошо бы сделать функцию, которая примет объект файла и число, и
     * выполнит эти действия.
     *
     * Реализуйте функцию `write_int(BaseFile &file, int n)`, которая будет
     * принимать ссылку на файл и число, которое нужно будет напечатать.
     *
     * Принцип наследования предписывает, что везде, где можно использовать
     * базовый класс, можно использовать производный класс. Проверьте, можно
     * ли вызвать функцию, передав в нее объект класса Base32File и RleFile.
     *
     * Имеет ли вызов этой функции для производного класса тот же результат,
     * что и код, который вы написали выше? Почему?
     */

    /**
     * Задание 2.6. Виртуальные функции, позднее связывание.
     *
     * Объявите функции read и write в базовом классе *виртуальными*. Что это
     * означает? Как изменился размер объектов классов BaseFile, Base32File и
     * RleFile? Почему?
     *
     * Как изменилось поведение при вызове функции `write_int` для производных
     * классов? Почему?
     */

    /**
     * Задание 2.7. Виртуальный деструктор.
     *
     * В следующем блоке кода добавьте удаление динамической памяти.
     *
     * Какой деструктор при этом вызывается? Почему? К каким проблемам это может
     * привести?
     *
     * Исправьте эту ситуацию.
     */

    { 
		BaseFile *files[] = { 
			(BaseFile *) new BaseFile("build/files/task 2.7 (1).txt", "w+"), 
            (BaseFile *) new RleFile("build/files/task 2.7 (2).txt", "w+"), 
            (BaseFile *) new Base32File("build/files/task 2.7 (3).txt", "w+"), 
        };

        for (int i = 0; i < 3; ++i) {
            files[i]->write("Hello!", 6);
        }

		for (int i = 0; i < 3; ++i) {
			delete files[i];
		}
    }

    /**
     * Задание 2.8. Массив объектов производных классов.
     *
     * Раскомментируйте следующий блок и объясните, почему:
     * а) не возникает ошибок при компиляции;
     * б) возникают ошибки при выполнении.
     *
     * Этот пример показывает очень плохую практику, которая приводит к ошибкам;
     * для создания массива объектов производного класса и используйте массив
     * указателей на базовый класс, как это было сделано выше. Реализуйте ту же
     * логику, используя массив указателей на объекты базового класса.
     */

    {
        BaseFile *base_files = new BaseFile[2] { BaseFile("build/files/task 2.8 (1).txt", "w"), BaseFile("build/files/task 2.8 (2).txt", "w") };
        // BaseFile *b32_files = new Base32File[2] { Base32File("...", "w"), Base32File("...", "w") };

        for (int i = 0; i < 2; ++i) {
            base_files[i].write("Hello!", 6);
            //b32_files[i].write("Hello!", 6);
        }
        delete [] base_files;
        //delete [] b32_files;
	}
	// Коммент
	//

    /**
     * Задание 3. Чисто виртуальные функции. Интерфейсы. Композиция классов.
     *
     * Наследование позволяет довольно просто переиспользовать данные и логику
     * других классов, однако зачастую этот механизм недостаточно гибкий для
     * полноценного переиспользования.
     *
     * Например, сможем ли мы в получившейся иерархии классов реализовать
     * одновременно и кодирование в base32, и сжатие при записи данных в файл?
     * Или сможем ли мы вместо записи в файл на диске делать запись в строковый
     * буфер в памяти?
     *
     * При дальнейшем рассмотрении окажется, что при помощи наследования мы
     * крепко *связали* логику преобразования данных с записью в конкретный
     * файл. Далее мы рассмотрим один из способов разделения такой логики.
     */

    /**
     * Задание 3.1. Абстрактный базовый класс, чисто виртуальные функции.
     *
     * Первая проблема в нашей реализации - все наследники BaseFile будут всегда
     * обязаны непосредственно писать в файл на диске. Чтобы избавиться от этой
     * необходимости, стоит сделать базовый класс *абстрактным* в том смысле,
     * что у него не будет полей связанных с конкретным способом писать в файл.
     *
     * Создайте класс `IFile`, в котором не будет полей, но будут методы
     * `can_read`, `can_write`, `read` и `write` с такими же сигнатурами, как и
     * классе `BaseFile`. Что именно будут делать эти методы? Класс `IFile` не
     * может знать, поскольку логику этих методов будут определять наследники.
     * В этом классе эти методы не имеют реализации, и они должны быть объявлены
     * *чисто виртуальными*.
     *
     * Какие ограничения накладывает на класс наличие чисто виртуального метода?
     *
     * Получается, что в классе `IFile` есть только чисто виртуальные методы, и
     * единственная цель такого класса - определять, что должны уметь делать его
     * наследники. Совокупность действий, которые можно сделать с объектом,
     * называется его *интерфейсом*, и такие классы тоже часто называются
     * интерфейсами, отсюда берется приставка "I" в имени класса.
     *
     * Унаследуйте класс `BaseFile` от класса `IFile` и измените функцию
     * `write_int`, чтобы она работала с произвольным наследником `IFile`.
     *
     * Убедитесь, что в программе выше ничего не сломалось.
     */

    /**
     * Задание 3.2. Композиция вместо наследования.
     *
     * Реализуйте классы `Base32File2` и `RleFile2`, которые будут унаследованы
     * от класса `IFile` и в конструкторе будут получать другой объект `IFile`,
     * чьи функции они будут использовать вместо функций базового класса.
     *
     * Объекты получают объект `IFile` в виде указателя на динамически
     * выделенную память, и они ответственны за ее очищение.
     *
     * Использование объектом другого объекта в качестве поля называется
     * *композицией*.
     *
     * Проверьте, что используемые ниже объекты работают так же, как объекты
     * классов `Base32File` и `RleFile`.
     */

    {
		std::cout << "\n------ Задание 3.2 ------" << std::endl; 

		int n = 123456;

        Base32File2 b32f(new BaseFile("build/files/task 3.2 (1).txt", "w"));
        RleFile2 rf(new Base32File("build/files/task 3.2 (2).txt", "w"));
        write_int(&b32f, n);
        write_int(&rf, n);

		b32f.close();
		rf.close();

		char buffer[BUFFER_SIZE];
		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

		BaseFile file_read1("build/files/task 3.2 (1).txt", "r");
		BaseFile file_read2("build/files/task 3.2 (2).txt", "r");

		file_read1.read(buffer, BUFFER_SIZE);
		file_read1.close();
		std::cout << "'Сырая' запись числа " << n << " в Base32File2 -> BaseFile: " << buffer << std::endl;

		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

		file_read2.read(buffer, BUFFER_SIZE);
		file_read2.close();
		std::cout << "'Сырая' запись числа " << n << " в RleFile2 -> Base32File: " << buffer << std::endl;

		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

        Base32File2 b32f_read(new BaseFile("build/files/task 3.2 (1).txt", "r"));
        RleFile2 rf_read(new Base32File("build/files/task 3.2 (2).txt", "r"));

		b32f_read.read(buffer, BUFFER_SIZE);
		b32f_read.close();
		std::cout << "Считанное число " << n << " из Base32File2 -> BaseFile: " << buffer << std::endl;

		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

		rf_read.read(buffer, BUFFER_SIZE);
		rf_read.close();
		std::cout << "Считанное число " << n << " из RleFile2 -> Base32File: " << buffer << std::endl;
    }

    /**
     * Задание 3.3. Больше композиции!
     *
     * Не реализовывая больше никаких классов, соорудите объект-наследник IFile,
     * который будет при вызове метода `write` два раза кодировать в base32,
     * после чего применять сжатие RLE и только после этого писать в файл.
     */

    {
		std::cout << "\n------ Задание 3.3 ------" << std::endl;

		int n = 123456;

		// Создаем цепочку композиции: BaseFile -> Base32File2 -> Base32File2 -> RleFile2
		IFile* base_file = new BaseFile("build/files/task 3.3.txt", "w");
		IFile* first_base32 = new Base32File2(base_file);
		IFile* second_base32 = new Base32File2(first_base32);
		IFile* rle_file = new RleFile2(second_base32);

		write_int(rle_file, n);

		rle_file->close();
		delete rle_file; 

		std::cout << "Число записано с двойным кодированием Base32 и сжатием RLE." << std::endl;
    }

    return 0;
}
