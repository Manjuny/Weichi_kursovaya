// Weichi_kursovaya.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>

struct point
{   
    int i = 0;
    int j = 0;
};

void print_error(errno_t);
void read_file(const char*);
void print_board();






int main()
{

    setlocale(LC_ALL, "Ru");
    const char* path = "Pravila.txt";
    std::cout << std::endl;
    read_file(path);
    print_board();


}



void print_error(errno_t err) {
    std::cout << "The file cannot be opened " << "\n";

    switch (err)
    {
    case 2:
        std::cout << "Отсутствует такой файл или каталог. " << "\n";
        break;
    case 13:
        std::cout << "в разрешении отказано.  " << "\n";
        break;
    default:
        std::cout << "Ошибка неизвестна!  " << err << "\n";
        break;
    }
}
// здесь мне надо понять как вычитывать файл из конкретной строки, чтобы дальше реализовывать некий интерактив постепенного вывода правил
void read_file(const char* path) { 
    FILE* in_file{ nullptr };
    errno_t err{};

    err = fopen_s(&in_file, path, "r+");
    if (err != 0) {
        print_error(err);
        return;
    }

    std::cout << "The file be opened \n";

    while (!feof(in_file)) {
        char str[255]{};
        fgets(str, 255, in_file);
        std::cout << str;
    }
    fclose(in_file);
}
//
void print_board()
{
    point rock_p;
    char rock = '|';
    int i = 0;
    std::cout << std::endl;
    std::cout << "  1    2    3    4    5    6    7    8    9" << std::endl;
    for (i; i < 17;i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < 9; j++)
            {
                std::cout << "__ __";
            }

        }
        else
            if (i % 2 == 0) {

                for (int j = 0; j < 8; j++)
                {

                    if (j == 0)
                    {
                        std::cout << "  | _";
                    }
                    if (j == 7)
                    {
                        std::cout << "_ |  ";
                    }
                    else
                        std::cout << "_ | _";


                }
            }
            else
    /* Здесь можно будет менять в зависимости от координат на отображение камня
    через свитч в зависимости от выбора координат будет меняться значение i и j в операторе if который пока закоментировала
    */
                if (i % 2 != 0) {                   

                    for (int j = 0; j < 9; j++)
                    {
                       // rock = 1;//для белых камней
                        rock = 2;          //для черных камней
                       ///if(i== rock_p.i && j== rock_p.j){rock='001';} 
                       /* здесь пока неверно реализованы координаты i и j, 
                        буду писать другую функцию пока только определила где на выводе доски будет хорошо отобразить камень*/
                        std::cout << "  "<< rock <<"  ";



                    }
                }


            std::cout << std::endl;

        
    }

}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
