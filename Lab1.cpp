#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string file_name = "Nums.txt";

int     count_file();
double* create_arr();
void    arr_view(double* arr, int size);
void    arr_add_first(double*& arr, int& size, double n);
void    arr_add_last(double*& arr, int& size, double n);
void    arr_add(double*& arr, int& size, double n, int index);
void    arr_remove_first(double*& arr, int& size);
void    arr_remove_last(double*& arr, int& size);
void    arr_remove(double*& arr, int& size, int index);
void    arr_add_after(double*& arr, int& size, double after_n, double n);
void    arr_remove_this(double*& arr, int& size, double n);

int main()
{
    setlocale(NULL, "ru");

    int size = count_file();
    double* arr = create_arr();

    arr_view(arr, size); cout << endl;

    //menu
    int command = -1;
    while (command != 0)
    {
        cout << "Command list:\n0: Выход\n1: Добавить первый элемент\n2: Добавить последний элемент\n3: Добавить элемент в k позицию\n";
        cout << "4: Удалить первый элмент\n5: Удалить последний элемент\n6: Удалить k-ый элемент\n";
        cout << "7: Вставить элемент после n\n8: Удалить все элементы n\n\n";

        cout << "Введите номер команды: "; cin >> command;

        if (command == 0)
            return 0;
        else if (command == 1)
        {
            double n;
            cout << "Введите n: "; cin >> n;
            arr_add_first(arr, size, n);
        }
        else if (command == 2)
        {
            double n;
            cout << "Введите n: "; cin >> n;
            arr_add_last(arr, size, n);
        }
        else if (command == 3)
        {
            double n;
            int k;
            cout << "Введите n и k: "; cin >> n >> k;
            arr_add(arr, size, n, k);
        }
        else if (command == 4)
            arr_remove_first(arr, size);
        else if (command == 5)
            arr_remove_last(arr, size);
        else if (command == 6)
        {
            int k;
            cout << "Введите k: "; cin >> k;
            arr_remove(arr, size, k);
        }
        else if (command == 7)
        {
            double n, _n;
            cout << "Введтите элемент и элемент после которого будет вставка: "; cin >> n >> _n;
            arr_add_after(arr, size, _n, n);
        }
        else if (command == 8)
        {
            double n;
            cout << "Введите удаляемый элемент: "; cin >> n;
            arr_remove_this(arr, size, n);
        }
        arr_view(arr, size);
    }

    return 0;
}

int  count_file() // кол-во элементов в файле
{
    ifstream ifs(file_name);
    int count = 0;
    double it;
    while (ifs >> it)
        count++;

    ifs.close();
    return count;
}
bool contains(double* arr, int size, double n) // поиск соответствующего элемента в массиве
{
    for (int i = 0; i < size; i++)
        if (arr[i] == n)
            return true;
    return false;
}
int  index_of(double* arr, int size, double n) //индекс соответствующего числа из массива
{
    if (contains(arr, size, n))
    {
        for (int i = 0; i < size; i++)
            if (arr[i] == n)
                return i;
    }
    else return -1;
}

double* create_arr()
{
    int size = count_file();
    double* arr = new double[size];

    ifstream ifs(file_name);

    for (int i = 0; i < size; i++)
        ifs >> arr[i];

    ifs.close();

    return arr;
}
void    arr_view(double* arr, int size) // вывод массива на экран
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void arr_add_first(double*& arr, int& size, double n)
{
    double* new_arr = new double[size + 1];
    for (int i = 1; i < size + 1; i++)
        new_arr[i] = arr[i - 1];
    new_arr[0] = n;
    delete[] arr;
    size++;
    arr = new_arr;
}
void arr_add_last(double*& arr, int& size, double n)
{
    double* new_arr = new double[size + 1];
    for (int i = 0; i < size; i++)
        new_arr[i] = arr[i];
    new_arr[size] = n;
    delete[] arr;
    size++;
    arr = new_arr;
}
void arr_add(double*& arr, int& size, double n, int index)
{

    double* new_arr = new double[size + 1];
    for (int i = 0; i < index; i++)
        new_arr[i] = arr[i];
    for (int i = index; i < size; i++)
        new_arr[i + 1] = arr[i];

    new_arr[index] = n;

    delete[] arr;
    size++;
    arr = new_arr;
}

void arr_remove_first(double*& arr, int& size)
{
    double* new_arr = new double[size - 1];
    for (int i = 1; i < size; i++)
        new_arr[i - 1] = arr[i];
    size--;
    delete[] arr;
    arr = new_arr;
}
void arr_remove_last(double*& arr, int& size)
{
    double* new_arr = new double[size - 1];
    for (int i = 0; i < size - 1; i++)
        new_arr[i] = arr[i];
    size--;
    delete[] arr;
    arr = new_arr;
}
void arr_remove(double*& arr, int& size, int index) // удаление kго элемента
{

    double* new_arr = new double[size - 1];
    for (int i = 0; i < index; i++)
        new_arr[i] = arr[i];
    for (int i = index + 1; i < size; i++)
        new_arr[i - 1] = arr[i];
    size--;
    delete[] arr;
    arr = new_arr;
}

void arr_add_after(double*& arr, int& size, double after_n, double n)
{
    int index = index_of(arr, size, after_n);
    if (index == -1)
    {
        cout << "В массиве нет такого элмента" << endl << endl;
        return;
    }

    arr_add(arr, size, n, index + 1);
}
void arr_remove_this(double*& arr, int& size, double n)
{
    int index = index_of(arr, size, n);
    if (index == -1)
    {
        cout << "В массиве нет такого элмента" << endl << endl;
        return;
    }

    while (index_of(arr, size, n) != -1)
        arr_remove(arr, size, index_of(arr, size, n));

}