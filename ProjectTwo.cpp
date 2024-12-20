
// Shokhrukh Janobilov
// 12/15/2024



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Course structure definition
struct Course {
    string courseID;
    string title;
    vector<string> prerequisites;
};

// Binary Search Tree Node
struct TreeNode {
    Course course;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class CourseTree {
private:
    TreeNode* root;

    // Helper function for inserting a node
    TreeNode* insert(TreeNode* node, Course course) {
        if (!node) return new TreeNode(course);
        if (course.courseID < node->course.courseID)
            node->left = insert(node->left, course);
        else if (course.courseID > node->course.courseID)
            node->right = insert(node->right, course);
        return node;
    }

    // Helper function for in-order traversal
    void inOrderTraversal(TreeNode* node) {
        if (!node) return;
        inOrderTraversal(node->left);
        cout << node->course.courseID << " - " << node->course.title << endl;
        inOrderTraversal(node->right);
    }

    // Helper function to find a course
    TreeNode* find(TreeNode* node, string courseID) {
        if (!node || node->course.courseID == courseID)
            return node;
        if (courseID < node->course.courseID)
            return find(node->left, courseID);
        return find(node->right, courseID);
    }

public:
    // Print function to output results and course details
    CourseTree() : root(nullptr) {}

    void insertCourse(Course course) {
        root = insert(root, course);
    }

    void printSortedCourses() {
        if (!root) {
            cout << "No courses loaded." << endl;
            return;
        }
        inOrderTraversal(root);
    }

    void printCourseDetails(string courseID) {
        TreeNode* node = find(root, courseID);
        if (!node) {
            cout << "Course not found." << endl;
            return;
        }
        Course course = node->course;
        cout << "Course ID: " << course.courseID << endl;
        cout << "Title: " << course.title << endl;
        cout << "Prerequisites: ";
        if (course.prerequisites.empty())
            cout << "None" << endl;
        else {
            for (string prereq : course.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
};

// Function to load data from file
void loadData(string fileName, CourseTree& courseTree) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseID, title, prereq;
        getline(ss, courseID, ',');
        getline(ss, title, ',');

        Course course{courseID, title};
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }
        courseTree.insertCourse(course);
    }
    file.close();
    cout << "Data loaded successfully." << endl;
}

int main() {
    CourseTree courseTree;
    int choice;
    string fileName, courseID;

    while (true) {
        cout << "\nMenu Options:" << endl;
        cout << "1. Load data" << endl;
        cout << "2. Print sorted list of courses" << endl;
        cout << "3. Print course details and prerequisites" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the file name: ";
                cin >> fileName;
                loadData(fileName, courseTree);
                break;
            case 2:
                courseTree.printSortedCourses();
                break;
            case 3:
                cout << "Enter the course ID: ";
                cin >> courseID;
                courseTree.printCourseDetails(courseID);
                break;
            case 9:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
}
