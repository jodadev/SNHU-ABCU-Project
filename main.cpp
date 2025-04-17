/******************************************************************************
 * Project: ABCU Software (Project Two)
 * File: main.cpp
 * Description:
 *   Full code to read, parse and load data from file to BST. Search course(s) and print using
 *   a menu system.
 *
 *
 * Version: v1.0.0
 * Author: Edwin Martinez
 * Created On: 04-14-2025
 * Last Modified: 04-14-2025
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
// Used to time the algorithms in ms
#include <thread>
#include <chrono>
using namespace std;

/// @brief Struct for a course object
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

/// @brief Node struct for the binary search tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
};

/// @brief Binary Search Tree class for storing courses
class BinarySearchTree {
private:
    Node* root;

    /// @brief Recursively adds a course to the BST based on courseNumber order.
    /// @param node Pointer to the current node in the tree.
    /// @param course The course to insert.
    void addNode(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            } else {
                addNode(node->left, course);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            } else {
                addNode(node->right, course);
            }
        }
    }

    /// @brief Performs an in-order traversal of the BST and prints course numbers and names.
    /// @param node Pointer to the current node during traversal.
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ": " << node->course.courseName << endl;
            inOrder(node->right);
        }
    }

    /// @brief Validates prerequisites for all courses by ensuring each prerequisite exists in the BST.
    /// @param node Pointer to the current node being validated.
    void validate(Node* node, vector<Course>& courseList) {
        if (node == nullptr) return;

        validate(node->left, courseList);

        vector<string> validPrereqs;
        for (string prereq : node->course.prerequisites) {
            bool found = false;
            for (Course c : courseList) {
                if (c.courseNumber == prereq) {
                    found = true;
                    break;
                }
            }
            if (found) {
                validPrereqs.push_back(prereq);
            }
        }
        node->course.prerequisites = validPrereqs;

        validate(node->right, courseList);
    }

    /// @brief Collects all courses in the BST into a vector using in-order traversal.
    /// @param node Pointer to the current node.
    /// @param courseList Reference to the vector where courses will be stored.
    void collect(Node* node, vector<Course>& courseList) {
        if (node == nullptr) return;
        collect(node->left, courseList);
        courseList.push_back(node->course);
        collect(node->right, courseList);
    }

public:
    /// @brief Constructor. Initializes the BST with an empty root.
    BinarySearchTree() : root(nullptr) {}

    /// @brief Inserts a new course into the BST.
    /// @param course The course to insert.
    void Insert(Course course) { 
        if (root == nullptr) { // assigns to root if root is null
            root = new Node(course);
        } else {
            addNode(root, course);
        }
    }

    /// @brief Searches the BST for a course by course number.
    /// @param courseNumber The course number to search for.
    /// @return The Course object if found, or an empty Course if not found.
    Course Search(string courseNumber) {
        Node* current = root;
        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return current->course;
            } else if (courseNumber < current->course.courseNumber) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return Course(); // empty course if not found
    }

    /// @brief Initiates an in-order traversal of the BST and prints all courses.
    void InOrder() {
        inOrder(root);
    }

    /// @brief Initiates validation of all course prerequisites in the BST.
    void ValidatePrerequisites() { // uses 'collect' to collect all courses from BST and validates their prerequisites
        vector<Course> courseList;
        collect(root, courseList);
        validate(root, courseList);
    }

    /// @brief Checks whether the binary search tree is empty.
    /// @return True if the tree has no nodes; otherwise, false.
    bool IsEmpty() {
        return root == nullptr;
    }

};

/// @brief Read, parse, and load course data from a CSV file into the binary search tree.
///        Also validates that all listed prerequisites exist as courses in the tree.
/// @param filename The name of the input CSV file.
/// @param courses Reference to the BinarySearchTree where the courses will be stored.
void loadCoursesFromFile(string filename, BinarySearchTree& courses) {
    
    ifstream file(filename);
    if (!file.is_open()) { // validate that file is open correctly
        cout << "\033[31m" << "Error: Could not open file." << "\033[0m\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line); // converts line from file to string stream
        string token; // each cell
        vector<string> tokens; // holds each cell of a line

        while (getline(ss, token, ',')) { // get next line in stream split by delimiter comma
            tokens.push_back(token);
        }

        // incorrect format if less than 2 - each line has AT LEAST 2 columns (name and course number)
        if (tokens.size() < 2) {
            cout << "\033[31m" << "Error: Invalid format in line: " << line << "\033[0m\n";
            continue;
        }

        Course newCourse;
        newCourse.courseNumber = tokens[0]; // should be course number
        newCourse.courseName = tokens[1]; // should be name

        for (size_t i = 2; i < tokens.size(); ++i) { // starting at 3rd column, iterate tokens to get each prerequisite
            newCourse.prerequisites.push_back(tokens[i]);
        }

        courses.Insert(newCourse); // insert the new course into BST
    }

    file.close();
    courses.ValidatePrerequisites();
}

// Entry point
int main() {
    BinarySearchTree courses; // declare BST to hold data
    string filename = "CS 300 ABCU_Advising_Program_Input.csv"; // hardcoded name of file
    string courseId = "CSCI400"; // hardcoded for testing
    int choice = 0;

    // MENU
    do {
        cout << R"(
Menu:
    1. Load Data Structure
    2. Print Course List
    3. Print Course
    9. Exit
Enter choice: 
)";
        cin >> choice; // get input from user
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer to prevent issues

        // Options
        switch (choice) {
            case 1:
                {
                    // Prevents loading twice
                    if (!courses.IsEmpty()) {
                        cout << "\033[31m" << "Cannot load again, data was already loaded!" << "\033[0m\n";
                        continue;
                    }

                    auto start = chrono::high_resolution_clock::now();
                    loadCoursesFromFile(filename, courses);
                    auto end = chrono::high_resolution_clock::now();
                    double elapsed = chrono::duration<double, std::milli>(end - start).count();
                    cout << "\n\033[33m  Courses loaded successfully " << elapsed << "ms\033[0m\n"; // note: 
                }
                break;

            case 2: // PRINT ALL
                {
                    // Prevent printing if BST is empty
                    if (courses.IsEmpty()) {
                        cout << "\033[31m" << "No data, Tree is empty!\033[0m\n";
                        continue;
                    }

                    auto start = chrono::high_resolution_clock::now();
                    cout << "\nCourse List:\n";
                    courses.InOrder();
                    auto end = chrono::high_resolution_clock::now();
                    double elapsed = chrono::duration<double, std::milli>(end - start).count();
                    cout << "\033[33m  Printed in " << elapsed << "ms\033[0m\n";
                }
                
                break;

            case 3: // PRINT COURSE BY NUMBER
                {
                    // Prevent printing if BST is empty
                    if (courses.IsEmpty()) {
                        cout << "\033[31m" << "No data, Tree is empty!\033[0m\n";
                        continue;
                    }
                    
                    auto start = chrono::high_resolution_clock::now();
                    Course course = courses.Search(courseId);
                    if (course.courseNumber.empty()) {
                        cout << "\033[31m" << "Course not found.\033[0m\n";
                    } else {
                        cout << course.courseNumber << ": " << course.courseName << "\n";
                        if (course.prerequisites.empty()) {
                            cout << "Prerequisites: None\n";
                        } else {
                            cout << "Prerequisites: ";
                            for (auto prereq : course.prerequisites) {
                                cout << prereq << " ";
                            }
                            cout << "\n";
                        }
                    }
                    auto end = chrono::high_resolution_clock::now();
                    double elapsed = chrono::duration<double, std::milli>(end - start).count();
                    cout << "\033[33m  Printed in " << elapsed << "ms\033[0m\n";
                }
                break;

            case 9:
                cout << "Goodbye." << endl;
                break;

            default:
                cout << "Invalid option. Please try again.\n";
        }
    
    } while (choice != 9); // exit condition

    return 0;
}
