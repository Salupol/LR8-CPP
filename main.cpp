#include <iostream>
using namespace std;
class MySet {
public:
    double *elements;
    int size;

    MySet() {
        size = 0;
        elements = nullptr;
    }
    MySet(const MySet& other) {
        size = other.size;
        elements = new double[size];
        std::copy(other.elements, other.elements + size, elements);

    }

    ~MySet() {
        delete[] elements;
    }


    MySet operator*(const MySet &other) const {
        MySet result;
        for (int i = 0; i < size; i++) {
            if (other.contains(elements[i])) {
                result.insert(elements[i]);
            }
        }
        return result;
    }

    MySet operator=(const MySet &other)  {   // додано - оператор присвоєння для "глибокого"присвоєння, а не "поверхневого" копіювання вказівника
        //cout << "operator=\n";
        size = other.size;
        elements = new double[size];
        std::copy(other.elements, other.elements + size, elements);
        return *this;
    }

    MySet operator+(const MySet &other) const {
        MySet result = *this;
        for (int i = 0; i < other.size; i++) {
            if(!result.contains(other.elements[i])){
                result.insert(other.elements[i]);
            }
        }
        return result;
    }
    MySet operator-(const MySet &other) const {
        MySet result = *this;    // додано:   = *this  (інакше - звідки викидаються елементи?)
        for (int i = 0; i < size; i++) {
            if (other.contains(elements[i])) {   // викинуто    ! (якщо елемент ВХОДИТЬ в другу множину, ми його викидаємо)
                result.remove(elements[i]);
            }
        }
        return result;
    }



    bool operator==(const MySet &other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (!other.contains(elements[i])) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const MySet &other) const {
        return !(*this == other);
    }
    friend istream& operator>>(istream& in, MySet& set) {
        double value;
        in >> value;
        set.insert(value);
        return in;
    }
    friend ostream& operator<<(ostream& out, const MySet& set){
        for (int i = 0; i < set.size; i++){
            out << set.elements[i] << " ";
        }
        return out;
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

        } else {
            cout << "The number is already in the set" << endl;
        }
    }


    bool contains(double value) const {
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
    MySet set1, set2;
    while (1) {
        printf( "\nhello, choose action: \n");    // тут просто глянець, щоб не було довгої інструкції (до речі, чому не cout?)
        printf( "1. insert digits in set \n");
        printf( "2. remove digits from set \n");
        printf( "3. print set \n");
        printf( "4. check if digit in set \n");
        printf( "5. print len of set. \n");
        printf( "6. compare set 1 and set 2. \n");
        printf( "7.add sets \n");
        printf( "8. subtract sets \n");
        printf( "9. multiply sets \n");
        printf( "10.exit \n");
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        MySet* currentSet = nullptr;        // цей динамічний об'єкт ніде реально не створювався (не було new!)
        MySet res, res1;                          //  доданий статичний об'єкт для результатів операторних функцій
        char setChoice;
        //////////////////////////////////////
        if ((1 <= choice) && (choice <= 5))     // додано це розгалуження, інакше вибір множини виникає там, де не треба
        {
            printf("Choose set: 1 or 2: ");
            cin >> setChoice;
            if (!cin){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if (setChoice == '1') {
                currentSet = &set1;
            } else if (setChoice == '2') {
                currentSet = &set2;
            } else {
                cout << "Invalid choice" << endl;
                continue;
            }
        }
        switch (choice) {
            case 1:
                char answer1;
                do {
                    double answer;
                    cout << "Enter the number to be inserted: ";
                    cin >> *currentSet;
                    if (!cin) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input. Please enter a number.\n";
                        continue;
                    }

                    do {
                        cout << "Do you want to insert more numbers? (y/n): ";
                        cin >> answer1;
                        if (!cin) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                        }
                        if (answer1 != 'y' && answer1 != 'n') {
                            cout << "Invalid input. Please enter 'y' or 'n'.\n";
                        }
                    } while (answer1 != 'y' && answer1 != 'n');
                } while (answer1 == 'y');
                break;
            case 2:
                double answer2;
                printf("Enter the number to be removed: ");
                cin >> answer2;
                if(!cin){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    break;
                }
                currentSet->remove(answer2);
                break;
            case 3:
                cout << *currentSet;
                break;
            case 4:
                double answer3;
                printf("Enter the number to be checked: ");
                cin >> answer3;
                if(!cin){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    break;
                }
                if (currentSet->contains(answer3)) {
                    printf("digit \"%.2f\" is in the set \n", answer3);
                } else {
                    printf("digit \"%.2f\" is not in the set \n", answer3);
                }
                break;
            case 5:
                printf("len of set is %d. \n", currentSet->size);
                break;
            case 6:
                if (set1 == set2) {
                    cout << "The sets are equal" << endl;
                } else if( set1 != set2){
                    cout << "The sets are not equal" << endl;
                }
                break;
            case 7:
                //*currentSet = set1 + set2;  // результат не виводиться

                res = set1 + set2;
                cout << "Result operator+: "<< res;   // результат виводиться через статичний об'єкт
                //cout << *currentSet << endl;  // додано вивід результату
                break;
            case 8:
                // *currentSet = set1 - set2; // результат не виводиться
                // cout << *currentSet << endl;   // додано вивід результату
                res = set1 - set2;
                res1 = set2 - set1;
                cout << "Result operator-: "<< res;   // результат виводиться через статичний об'єкт
                cout << "Result operator- #2: "<< res1 << endl;
                break;
            case 9:
                cout << "Here: 9\n";
                // *currentSet = set1 * set2; // результат не виводиться
                // cout << *currentSet << endl;   // додано
                res = set1 * set2;
                cout << "Result operator*: "<< res;   // результат виводиться через статичний об'єкт
                break;
            case 10:
                cout << "Here: 10\n";
                return 0;



            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;   // додано для порядку
}