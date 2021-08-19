//============================================================================
// Name        : Source.cpp
// Author      : Sergio H. Passos
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Project Two
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string> 
#include <sstream>


using namespace std;


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold bid information
struct Course {
    string id; // unique identifier
    string title;
    vector<string> prereqs;
};

/**
* @param two Course objects
* @return the comparison between them using id
*/
bool compareCourseFunction(Course a, Course b) { 
    return a.id < b.id; 
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Course> loadCourses(string csvPath) {
    cout << "\nLoading CSV file\n\n" << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Course> courses;

    // file pointer
    fstream fin;

    fin.open(csvPath, ios::in);

    string line, word;
    vector<string> row;

    while (getline(fin, line, '\n')) {
        
        // break up words
        stringstream s(line);

        // reset row
        row.clear();

        // get data for course
        Course course;
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        // load course data into object
        // id: [0]
        // title: [1]
        // prereqL [2:]
        for (int i = 0; i < row.size(); i++) {
            // id
            if (i == 0) {
                course.id = row[i];
            }
            // title
            else if (i == 1) {
                course.title = row[i];
            }
            // prereq
            else {
                course.prereqs.push_back(row[i]);
            }
        }

        // add course
        courses.push_back(course);


    }

    // sort list
    sort(courses.begin(), courses.end(), compareCourseFunction);

    // return courses
    return courses;
    
}


/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course, bool prereg=false) {
    // ensure the course isn't empty and doesn't displays empty info
    if (!(course.id == "")) {
        // check for prereq boolean
        if (prereg) {
            cout << "\n\t" << course.id << ", " << course.title;
            cout << "\n\tPrerequisites: ";

            // loop through a courses prereqs and display
            for (string _prereq: course.prereqs) {
                cout << _prereq << " ";
            }
        }
        else {
            cout << "\n\t" << course.id << ", " << course.title;
        }        
    }
}


/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
Course getCourse(string courseName, vector<Course> &courses) {
    
    for (Course course: courses) {
        if (courseName == course.id) {
            return course;
        }
    }

    // return upper case warning
    cout << "\nPlease user uppercase!" << endl;

    // return empty course if no course is found
    Course n;
    return n;
}


/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "input-data.csv";
    }

    // Define a vector to hold all the courses
    vector<Course> courses;

    // main used variables
    int choice = 0;
    string _choice = "";
    Course course;
    while (choice != 9) {
        cout << "  1.  Load Data Structure." << endl;
        cout << "  2.  Print Course List." << endl;
        cout << "  3.  Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // input error
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            system("cls");
        }
        else {
            switch (choice) {
            case 1:
                // Complete the method call to load the bids
                courses = loadCourses(csvPath);

                break;

            case 2:
                // user feedback
                cout << endl << "Here is the schedule:\n";

                // Loop and display the bids read
                for (int i = 0; i < courses.size(); ++i) {
                    displayCourse(courses[i]);
                }

                // new line
                cout << "\n\n";

                break;

            case 3:
                // ask question and get input
                cout << "\nWhat is the course you are looking for:\n";
                cin >> _choice;

                // get course
                course = getCourse(_choice, courses);

                // display course info
                displayCourse(course, true);

                // newline
                cout << "\n\n";

                break;
            default:
                cout << "\n" << choice << " is not a valid option.\n\n";
                break;
            }
        }
    }

    cout << "Good bye." << endl;

    return 0;
}