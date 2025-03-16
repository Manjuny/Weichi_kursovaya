// Weichi_kursovaya.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <string>


struct point
{   
    int row = 0;
    int col = 0;
};

struct read_t {
    int err;
    std::string text;
};

typedef struct read_t read_t;

read_t read_file(const char*);
void print_board_clear(char[18][18]);
void print_board_game();
void print_rules(const char*, char);
int loop();
point matrix(point);
char switch_color(char);
void change_rock(char[18][18], point, char);




int main()
{
    setlocale(LC_ALL, "Ru");
    loop();
}

int loop()
{
    const int SIZE_row = 18;
    const int SIZE_col = 18;
    char print_matrix[SIZE_row][SIZE_col];
    print_board_clear(print_matrix);
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Введите команду: exit для выхода из программы \n";
    std::cout << "Введите команду: rules для повторения нужного правила \n";
    std::cout << "Введите команду: read для того чтобы увидеть ВСЕ правила \n";
    std::cout << "Введите команду: game для того чтобы поиграть с другом \n";
    std::string com;
    std::getline(std::cin, com);
    const char* path = "Pravila.txt";

    if (com == "exit") {
        return 0;
    }
    else if (com == "read") {
        read_t r;
        
        r = read_file(path); // c_str() преобразует string -> const char*
        if (r.err != 0) {
            std::cout << "Чтение файла завершилось с ошибкой: " << r.err << "\n";
        }
        else {
            std::cout << "Файл успешно прочитан.\n" << r.text << "\n";
        }  
    }
    else if (com == "rules")
    {
        char number_line_game = ' ';
        std::cout << "Введите номер повторяемого правила \n";
        std::cin >> number_line_game;
        print_rules(path, number_line_game);
        if (number_line_game == '1') 
        {
            print_board_game();
        }
    }
    else if (com=="game")
    {
        print_board_game();
    }


}

read_t read_file(const char* path) { 
   
        read_t r;
        FILE* file{ nullptr };
        errno_t e = fopen_s(&file, path, "r");
        if (e != 0) {
            r.err = e;
            r.text = "";
            return r;
        }
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != nullptr) {
            r.text += buffer;
        }
        fclose(file);
        r.err = 0;
        return r;
   
}

void print_rules(const char* path,  char number_line_text_char )
{
    read_t r;
    r = read_file(path);
   
   unsigned long long number_line_text = 0;
   
   
    std::string rules{ r.text };//запись текста из файла в массив

    /*std::cout << ruls;*///вывод всего текста для проверки позиции
///Вычисляем начало и конец правила, вопрос можно ли искать не char а string для чисел больше 9
/// или надо будет вычислять по всем позициям нужную, пришла в голову мысль о возможности 
/// wile(for) для этого метода.
   
    std::string::size_type pos_start = r.text.find(number_line_text_char); 
    std::string::size_type pos_end = r.text.rfind(number_line_text_char + 1);

    //вывод нужной части файла

     for (number_line_text=pos_start; number_line_text < pos_end; number_line_text++)
     {
         std::cout << rules[number_line_text];
     }      
       
    

}

void print_board_clear(char print_matrix[18][18])
{
    std::cout << "Ваша пустая доска 9х9 \n";
    const int SIZE_row = 18;
    const int SIZE_col = 18;  
   
    char rock_nul = '|';
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < SIZE_row;i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < SIZE_col; j++)
            {
                if (j % 2 == 0)
                {
                    print_matrix[i][j] = j / 2 + 49;
                    std::cout << " " << print_matrix[i][j] << " ";
                }
                else
                {
                    print_matrix[i][j] = ' ';
                    std::cout << " " << print_matrix[i][j] << " ";
                }
            }

        }
        else if (i % 2 == 0)
        {
            for (int j = 0; j < SIZE_col; j++)
            {

                if (j % 2 != 0)
                {
                    print_matrix[i][j] = ' ';
                    std::cout << " " << print_matrix[i][j] << " ";
                }
                else
                {
                    print_matrix[i][j] = '|';
                    std::cout << " " << print_matrix[i][j] << " ";
                }
            }
        }
        else
            if (i % 2 != 0) {
                for (int j = 0; j < SIZE_col; j++)
                {
                    if (j == 17)
                    {
                        print_matrix[i][j] = i / 2 + 49;
                        std::cout << " " << print_matrix[i][j];
                    }
                    else if (j % 2 == 0)
                    {

                        print_matrix[i][j] = rock_nul;
                        std::cout << "_" << print_matrix[i][j] << " ";
                    }
                    else if (j % 2 != 0)
                    {
                        print_matrix[i][j] = '_';
                        std::cout << "_" << print_matrix[i][j] << "_";
                    }

                }
            }
        std::cout << std::endl;      
    }
}

void print_board_game()
{
   
        const int SIZE_row = 18;
        const int SIZE_col = 18;
        char print_matrix[SIZE_row][SIZE_col];
        int switcher = 1;
        char switcher2 = ' ';
        point buffer;
        int lines = 0;
        char rock_nul = '|';
        char rock = '|';
        point points{};
        print_board_clear(print_matrix);
       
        std::cout << std::endl;
        std::cout << "Ваш ход\n";
        std::cout << "Выберите цвет камня w - для белого, b - для черного\n";
        std::cin >> switcher2;//пока выбор камня в ручную по идее нужно циклическое переключение между 2-мя цветами начиная с черного
        rock = switch_color(switcher2);

        std::cout << "Введите вашу координату по горизонтали\n";
        std::cin >> points.row;
        std::cout << "Введите вашу координату по вертикали\n";
        std::cin >> points.col;


        if (points.row == 0 && points.col == 0)
        {
            std::cout << "Начните игру снова\n";

        }
        else
        {
            point buffer = matrix(points);
            std::cout << std::endl;
            /*std::cout << "Проверка координат из массива пунктов\n";
            std::cout << buffer.row << "  " << buffer.col;*/
            std::cout << std::endl;
            std::cout << std::endl;

            change_rock(print_matrix, buffer, rock);
            
            std::cout << std::endl;
            std::cout << std::endl;
            for (int i = 0;i < SIZE_row;i++)//сделано для проверки записи матрицы
            {
                for (int j = 0;j < SIZE_col;j++)
                {
                    std::cout << print_matrix[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            system("pause");
        }
}
point matrix(point points)
{   
    const int SIZE = 9;
    
    point buffer;
    int point_1= points.row;
    int point_2 = points.col;
    point matrix[SIZE][SIZE]
    {
    { {1,0},{1,2},{1,4},{1,6},{1,8},{1,10},{1,12},{1,14},{1,16} },
    { {3,0},{3,2},{3,4},{3,6},{3,8},{3,10},{3,12},{3,14 },{3,16} },
    { {5,0},{5,2},{5,4},{5,6},{5,8},{5,10},{5,12},{5,14},{5,16} },
    { {7,0},{7,2},{7,4},{7,6},{7,8},{7,10},{7,12},{7,14},{7,16} },
    { {9,0},{9,2},{9,4},{9,6},{9,8},{9,10},{9,12},{9,14},{9,16} },
    { {11,0},{11,2},{11,4},{11,6},{11,8},{11,10},{11,12},{11,14},{11,16} },
    { {13,0},{13,2},{13,4},{13,6},{13,8},{13,10},{13,12},{13,14},{13,16} },
    { {15,0},{15,2},{15,4},{15,6},{15,8},{15,10},{15,12},{15,14},{15,16} },
    { {17,0},{17,2},{17,4},{17,6},{17,8},{17,10},{17,12},{17,14},{17,16} }
    };
    for(int i=0;i<SIZE;i++)//осуществляем поиск координат доски
    {
        for (int j = 0;j < SIZE;j++)
        {
            if (i == point_1-1 && j == point_2-1) 
            {
                buffer = matrix[i][j];
            }
        }
    }
   
    return buffer;

}
char switch_color (char switcher2)
 {
    char rock{};
    switch (switcher2) {

    case 'b':
        rock = 1;
        return rock;
        break;
    case 'w':
        rock = 2;
        return rock;
        break;
    }
 }
void change_rock (char print_matrix[18][18],point buffer,char rock)
{
    
    const int SIZE_row = 18;
    const int SIZE_col = 18;
    
    
    for (int i = 0;i < SIZE_row;i++)//сделано для проверки записи матрицы
    {
       
        for (int j = 0;j < SIZE_col;j++)
        {
            if (i == buffer.row && j == buffer.col) 
            {
                print_matrix[i][j] = rock;
            }
        }
       
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
