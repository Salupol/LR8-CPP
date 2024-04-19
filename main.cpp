#include <iostream>

using namespace std;

class MySet {
public:
    double *elements;
    int size;

    MySet() {
        size = 0;
        elements = new double[size];
    }
    ~MySet() {
        delete[] elements;
    }

    void insert(double value) {
        if (!contains(value)) {
            double *temp = new double[size + 1];
            for (int i = 0; i < size; i++) {
                temp[i] = elements[i];
            }
            temp[size] = value;
            delete[] elements;
            elements = temp;
            size++;
        } else{
            cout << "The number is already in the set" << endl;
        }
    }

    bool contains(double value) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == value) {
                return true;
            }
        }
        return false;
    }

    void remove(double value) {
        if (contains(value)) {
            double *temp = new double[size - 1];
            int index = 0;
            for (int i = 0; i < size; i++) {
                if (elements[i] != value) {
                    temp[index] = elements[i];
                    index++;
                }
            }
            delete[] elements;
            elements = temp;
            size--;
        }
    }
    void printset() {
        for (int i = 0; i < size; i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MySet set;
    while (1) {
        printf("press any key to start \n");
        cin.ignore();
        cin.ignore(10000, '\n');
        double answer;
        printf("Enter the number to be inserted or any letter to exit: ");
        cin >> answer;
        if(!cin){
            break;
        } else {
            set.insert(answer);
        }
        set.printset();
    }
    printf("the size of set is %d", set.size);
    return 0;
}