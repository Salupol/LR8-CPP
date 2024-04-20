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
        printf("hello, choose action: \n 1. insert digits in set \n 2. remove digits from set \n 3. print set \n 4. check if digit in set \n 5. exit \n");
        int choice;
        cin >> choice;
        switch(choice){
            case 1:
                char answer1;
                do{
                double answer;
                printf("Enter the number to be inserted: ");
                cin >> answer;
                set.insert(answer);
                printf("number \"%.2f\" is inserted \n", answer);
                printf("Do you want to insert more numbers? (y/n): ");
                cin >> answer1;
                } while (answer1 != 'n');
                break;
            case 2:
                double answer2;
                printf("Enter the number to be removed: ");
                cin >> answer2;
                set.remove(answer2);
                break;
            case 3:
                set.printset();
                break;
            case 4:
                double answer3;
                printf("Enter the number to be checked: ");
                cin >> answer3;
                if(set.contains(answer3)){
                    printf("digit \"%.2f\" is in the set \n", answer3);
                } else {
                    printf("digit \"%.2f\" is not in the set \n", answer3);
                }

            case 5:
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
        /*printf("press any key to start \n");
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
        set.printset();*/
    }
    printf("the size of set is %d", set.size);
    return 0;
}