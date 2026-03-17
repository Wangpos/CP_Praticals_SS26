#include <iostream>
using namespace std;

int main() {
    int attendance_mask = 0;
    int student_id = 5;

    attendance_mask |= (1 << student_id); // shortened form of attendance_mask = attendance_mask | (1 << student_id);
    cout << "Mask after marking student 5 present: " << attendance_mask << endl;

    if (attendance_mask & (1 << student_id))
        cout << "Student " << student_id << " is present." << endl;


    attendance_mask &= ~(1 << student_id);
    if (!(attendance_mask & (1 << student_id)))
        cout << "Student " << student_id << " is now absent." << endl;


    student_id = 10;
    attendance_mask ^= (1 << student_id);
    cout << "Mask after toggling student 10: " << attendance_mask << endl;

    return 0;
}