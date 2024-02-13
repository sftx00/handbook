#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class DirectoryEntry {
public:
    string firmName;
    string owner;
    string phoneNumber;
    string address;
    string activityType;

    void display() const {
        cout << "Название фирмы: " << firmName << endl;
        cout << "Владелец: " << owner << endl;
        cout << "Телефон: " << phoneNumber << endl;
        cout << "Адрес: " << address << endl;
        cout << "Род деятельности: " << activityType << endl;
        cout << "----------------------------------------" << endl;
    }
};

class Directory {
private:
    string fileName;
    vector<DirectoryEntry> entries;

public:
    Directory(const string& filename) : fileName(filename) {}

    void loadEntries() {
        ifstream file(fileName);
        if (!file) {
            cerr << "Ошибка при открытии файла." << endl;
            return;
        }

        DirectoryEntry entry;
        while (file >> entry.firmName >> entry.owner >> entry.phoneNumber >> entry.address >> entry.activityType) {
            entries.push_back(entry);
        }

        file.close();
    }

    void saveEntry(const DirectoryEntry& entry) {
        ofstream file(fileName, ios::app);
        if (!file) {
            cerr << "Ошибка при открытии файла." << endl;
            return;
        }

        file << entry.firmName << " " << entry.owner << " " << entry.phoneNumber << " " << entry.address << " " << entry.activityType << endl;

        file.close();
    }

    void displayAllEntries() const {
        for (const auto& entry : entries) {
            entry.display();
        }
    }

    vector<DirectoryEntry> searchByName(const string& name) const {
        vector<DirectoryEntry> results;
        for (const auto& entry : entries) {
            if (entry.firmName == name) {
                results.push_back(entry);
            }
        }
        return results;
    }

    vector<DirectoryEntry> searchByOwner(const string& ownerName) const {
        vector<DirectoryEntry> results;
        for (const auto& entry : entries) {
            if (entry.owner == ownerName) {
                results.push_back(entry);
            }
        }
        return results;
    }

    vector<DirectoryEntry> searchByPhoneNumber(const string& phoneNumber) const {
        vector<DirectoryEntry> results;
        for (const auto& entry : entries) {
            if (entry.phoneNumber == phoneNumber) {
                results.push_back(entry);
            }
        }
        return results;
    }

    vector<DirectoryEntry> searchByActivityType(const string& activityType) const {
        vector<DirectoryEntry> results;
        for (const auto& entry : entries) {
            if (entry.activityType == activityType) {
                results.push_back(entry);
            }
        }
        return results;
    }
};

int main() {
    setlocale(LC_ALL, "RU");

    Directory directory("directory.txt");
    directory.loadEntries();

    DirectoryEntry newEntry; // дозапись
    newEntry.firmName = "Новая фирма";
    newEntry.owner = "Новый владелец";
    newEntry.phoneNumber = "123456789";
    newEntry.address = "Новый адрес";
    newEntry.activityType = "Новый род деятельности";

    directory.saveEntry(newEntry);

    cout << "Результаты поиска по названию:" << endl;
    vector<DirectoryEntry> nameResults = directory.searchByName("Новая фирма");
    for (const auto& result : nameResults) {
        result.display();
    }

    cout << "Результаты поиска по владельцу:" << endl;
    vector<DirectoryEntry> ownerResults = directory.searchByOwner("Новый владелец");
    for (const auto& result : ownerResults) {
        result.display();
    }

    cout << "Результаты поиска по номеру телефона:" << endl;
    vector<DirectoryEntry> phoneResults = directory.searchByPhoneNumber("123456789");
    for (const auto& result : phoneResults) {
        result.display();
    }

    cout << "Результаты поиска по роду деятельности:" << endl;
    vector<DirectoryEntry> activityResults = directory.searchByActivityType("Новый род деятельности");
    for (const auto& result : activityResults) {
        result.display();
    }

    cout << "Все записи в справочнике:" << endl;
    directory.displayAllEntries();

    return 0;
}
