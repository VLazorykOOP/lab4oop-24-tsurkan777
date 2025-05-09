#include <iostream>
#include <string>
#include <map>
using namespace std;

// Клас для асоціації між Email та Phone
class ContactMap {
private:
    map<string, string> data; // Асоціативна структура: email -> phone
    int codeError;            // Код помилки

public:
    enum Errors { OK = 0, NOT_FOUND = 1 };

    ContactMap() : codeError(OK) {}

    // Додавання зв'язку email -> phone
    void add(const string& email, const string& phone) {
        data[email] = phone;
        codeError = OK;
    }

    // Індексація [] по email
    string operator[](const string& email) {
        if (data.count(email)) {
            codeError = OK;
            return data[email];
        } else {
            codeError = NOT_FOUND;
            return "";
        }
    }

    // Альтернативне звернення через виклик функції
    string operator()(const string& email) {
        return (*this)[email];
    }

    // Доступ до коду помилки
    int getCodeError() const { return codeError; }

    // Дружній оператор виводу
    friend ostream& operator<<(ostream& os, const ContactMap& cm) {
        for (const auto& pair : cm.data) {
            os << "Email: " << pair.first << " => Phone: " << pair.second << endl;
        }
        return os;
    }

    // Дружній оператор вводу одного запису
    friend istream& operator>>(istream& is, ContactMap& cm) {
        string email, phone;
        cout << "Enter email: "; is >> email;
        cout << "Enter phone: "; is >> phone;
        cm.add(email, phone);
        return is;
    }
};

// Приклад використання
int main() {
    ContactMap contacts;
    contacts.add("ivan@gmail.com", "+380671234567");
    contacts.add("olena@yahoo.com", "+380991112233");

    cout << contacts;

    string searchEmail;
    cout << "Enter email to find: ";
    cin >> searchEmail;
    string phone = contacts[searchEmail];
    if (contacts.getCodeError() == ContactMap::NOT_FOUND)
        cout << "Email not found!" << endl;
    else
        cout << "Phone: " << phone << endl;

    return 0;
}
