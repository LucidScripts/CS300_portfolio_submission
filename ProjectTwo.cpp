#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> // for sorting - seemed to be the easiest way to handle it

using namespace std;

// Course struct holds course number, title, and list of prerequisite course numbers
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    // Prints course info to the console
    void printCourseInfo() {
        cout << courseNumber + ": " + courseTitle << endl;
        if (!prerequisites.empty()) {
            cout << "Prerequisites: " << endl;
            for (string prereq : prerequisites) {
                cout << " " << prereq << endl;
            }
        }
        else {
            cout << "No prerequisites" << endl;
        }
    }
};

// Node struct
struct Node {
    string key;
    Course course;
    Node* next;

    Node(Course c, string k) {
        course = c;
        key = k;
        next = nullptr;
    }
};

// HashTable class to store and manage course data
class HashTable {
private:
    int tableSize;
public:
    vector<Node*> table;

    // Constructor initializes hash table with given size
    HashTable(int size) {
        tableSize = size;
        table.resize(size, nullptr);
    }

    void insert(string idString, Course course);
    Course Search(string key);
    unsigned int hash(string key);
    void printAllCourses();
};

// Hash function
unsigned int HashTable::hash(string key) {
    std::hash<string> str_hash;
    return str_hash(key) % tableSize;
}

// Insert a course into the hash table
void HashTable::insert(string idString, Course course) {
    int hashedKey = hash(idString);
    Node* newNode = new Node(course, idString);

    // Insert into empty bucket
    if (table[hashedKey] == nullptr) {
        table[hashedKey] = newNode;
    }
    // Handle collision with chaining
    else {
        Node* temp = table[hashedKey];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Search for a course by its course number
Course HashTable::Search(string idString) {
    int hashedKey = hash(idString);
    Node* current = table[hashedKey];

    // Traverse the linked list to find the course
    while (current != nullptr) {
        if (current->key == idString) {
            return current->course;
        }
        current = current->next;
    }

    // Course not found
    cout << "Course not found" << endl;
    return Course();
}

// Print all courses sorted by course number
void HashTable::printAllCourses() {
    vector<Course> allCourses;

    // Collect all courses from the hash table
    for (Node* bucket : table) {
        Node* current = bucket;
        while (current != nullptr) {
            allCourses.push_back(current->course);
            current = current->next;
        }
    }

    // Sort the courses alphabetically by course number
    sort(allCourses.begin(), allCourses.end(), [](Course a, Course b) {
        return a.courseNumber < b.courseNumber;
        });

    // Display the sorted course list
    for (Course c : allCourses) {
        cout << c.courseNumber << ": " << c.courseTitle << endl;
    }
}

// take a line from the CSV file and convert it into a Course object
Course lineParser(string line) {
    Course course;
    string token;
    int tokenIndex = 0;
    stringstream ss(line);

    // Split line
    while (getline(ss, token, ',')) {
        if (tokenIndex == 0) course.courseNumber = token;
        else if (tokenIndex == 1) course.courseTitle = token;
        else course.prerequisites.push_back(token);
        tokenIndex++;
    }
    return course;
}

// Load data from CSV file into the hash table
void loadCSV(HashTable& table) {
    cout << "Please enter the file name:" << endl;
    string fileName;
    cin.ignore();
    getline(cin, fileName);
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Course course = lineParser(line);
        table.insert(course.courseNumber, course);
    }
    cout << "File loaded successfully." << endl;
}


int main() {
    HashTable table(100);  // Initialize hash table with 100 buckets - not sure if this could be problematic for larger files
    int choice = 0;
    string courseInput;

    // Main menu loop
    while (choice != 9) {
        cout << "Please choose from the options below:" << endl;
        cout << "1. Load file into data structure" << endl;
        cout << "2. Print alphanumeric list of all courses" << endl;
        cout << "3. Print course title and prerequisites for a course of your choice" << endl;
        cout << "9. Exit the program" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            loadCSV(table);
            break;
        case 2:
            table.printAllCourses();
            break;
        case 3:
            cout << "Please enter course number:" << endl;
            cin >> courseInput;
            table.Search(courseInput).printCourseInfo();
            break;
        case 9:
            cout << "Exiting. Good bye!" << endl;
            break;
        default:
            cout << "Invalid option, please try again." << endl;
        }
    }
    return 0;
}
