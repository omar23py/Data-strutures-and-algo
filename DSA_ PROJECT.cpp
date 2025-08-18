#include <bits/stdc++.h>
using namespace std;

class BST_NODE{
public:
    BST_NODE*lchild;
    BST_NODE*rchild;
    int CourseID,CourseCredits;
    string CourseName,CourseInstructor;

    BST_NODE():lchild(nullptr),rchild(nullptr){}
};
class hash_node{
public:
    int data;
    hash_node*next;
    hash_node():next(nullptr){}

};

class hash_table{
public:
    hash_node**ht;
    hash_table(){
        ht=new hash_node*[30];
        for (int i = 0; i < 30; i++)
        {
            ht[i]=nullptr;
        }

    }
    int hashfunc(int course_ID){
        return course_ID%30;
    }
    void insert_in_hash(int course_ID){
        hash_node*newnode=new hash_node;
        newnode->data=course_ID;
        int index=hashfunc(course_ID);
        if(ht[index]==nullptr){
            ht[index]=newnode;
            return;

        }
        hash_node*t=ht[index];
        hash_node*q=ht[index];
        while (t&& t->data < course_ID){
            q=t;
            t=t->next;
        }
        if(q==ht[index]){
            newnode->next=ht[index];
            ht[index]=newnode;
            return;
        }
        newnode->next=q->next;
        q->next=newnode;
    }

    int search_ht(int course_ID){
        int index=hashfunc(course_ID);

        hash_node*t=ht[index];
        while (t)
        {
            if(course_ID==t->data)
                return course_ID;
            t=t->next;
        }
        return 0 ;
    }

    int Delete_Ht(int course_ID){
        int index=hashfunc(course_ID);

        hash_node*t=ht[index];
        hash_node*q=ht[index];

        while (t!=nullptr&&t->data!=course_ID )
        {
            q=t;
            t=t->next;
        }
        if(t==nullptr)
            return 0;

        if(q==ht[index]){
            ht[index]=t->next;

        }
        else{
            q->next=t->next;
        }
        delete t;
        return course_ID;

    }

};





class bst {
private:
    hash_table ht;
    BST_NODE *root;
    BST_NODE *Insert(int ID,int coursecredit,string coursename,string courseinstructor,BST_NODE *p) {
        if (p == nullptr) {
            BST_NODE *newNode = new BST_NODE;
            newNode->CourseID = ID;
            newNode->CourseCredits=coursecredit;
            newNode->CourseName=coursename;
            newNode->CourseInstructor=courseinstructor;
            if (root == nullptr)
                root = newNode;
            return newNode;
        }
        if (ID > p->CourseID)
            p->rchild = Insert(ID,coursecredit,coursename,courseinstructor, p->rchild);
        else if (ID < p->CourseID)
            p->lchild = Insert(ID,coursecredit,coursename,courseinstructor, p->lchild);
        else if(ID==p->CourseID)
            return nullptr;
        return p;
    }

    int height(BST_NODE *p) {
        int x, y;
        if (p == nullptr) {
            return -1;
        }
        x = height(p->lchild);
        y = height(p->rchild);
        return x > y ? x + 1 : y + 1;

    }

    BST_NODE *insucc(BST_NODE *p) {
        while (p != nullptr && p->lchild != nullptr) {
            p = p->lchild;
        }
        return p;

    }

    BST_NODE *presucc(BST_NODE *p) {
        while (p != nullptr && p->rchild != nullptr) {
            p = p->rchild;
        }
        return p;

    }

    BST_NODE *Delete(int key, BST_NODE *p) {
        BST_NODE *q;
        if (p == nullptr)
            return nullptr;
        if (p->lchild == nullptr && p->rchild == nullptr) {
            if (p == root) {
                root = nullptr;
            }
            delete p;
            return nullptr;
        }
        if (key > p->CourseID)
            p->rchild = Delete(key, p->rchild);
        else if (key < p->CourseID)
            p->lchild = Delete(key, p->lchild);
        else {
            if (height(p->lchild) > height(p->rchild)) {
                q = presucc(p->lchild);
                p->CourseID = q->CourseID;
                p->lchild = Delete(q->CourseID, p->lchild);
            } else {
                q = insucc(p->rchild);
                p->CourseID = q->CourseID;
                p->rchild = Delete(q->CourseID, p->rchild);
            }


        }
        return p;

    }

    BST_NODE *r_search(int ID, BST_NODE *p) {
        if (p == nullptr) {
            return nullptr;
        }
        if (ID == p->CourseID) {

            return p;
        } else if (ID > p->CourseID)
            return r_search(ID, p->rchild);
        else
            return r_search(ID, p->lchild);
    }


public:
    bst(){root = nullptr;}
    void addCourse(int ID,int coursecredit,string coursename,string courseinstructor) {
        Insert(ID,coursecredit,coursename,courseinstructor,root)?cout<<"Course Added":cout<<"Course Already Added";
        ht.insert_in_hash(ID);
        cout<<endl;
    }
    void dropcourse(int ID){
        Delete(ID,root)?cout<<"Course dropped":cout<<"Course not found";
        ht.Delete_Ht(ID);
        cout<<endl;


    }
    bool SearchCourse(int ID){
        if(r_search(ID,root)){
            return true;
        }
        return false;



    }
    bool searchWithHashing(int ID){
        if(ht.search_ht(ID)){
            return true;

        }
        return false;
    }

};



class sll_Node{
public:
    int id;
    string name;
    string email;
    string phone;
    string address;
    string password;
    sll_Node* next;
};
class linkedlist{
public:
    sll_Node* head;

    linkedlist(){
        head=NULL;
    }
    bool isEmpty() {
        return (head == NULL);
    }

    void add(int id, string name, string email, string phone, string address, string password) {
        sll_Node* newNode = new sll_Node();
        newNode->id = id;
        newNode->name = name;
        newNode->email = email;
        newNode->phone = phone;
        newNode->address = address;
        newNode->password = password;
        newNode->next = NULL;

        if (isEmpty() || head->id> id ) {
            newNode->next=head;
            head = newNode;
        } else {
            sll_Node* current=head;
            while (current->next!=NULL && current->next->id <id){
                current=current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        cout << "Student added successfully!\n";
    }
    void deleteStudent(int id) {
        if (isEmpty()) {
            cout << "The list is empty. No student to delete.\n";
            return;
        }
        sll_Node* temp = head;
        sll_Node* prev = NULL;
        if (temp != NULL && temp->id == id) {
            head = temp->next;
            delete temp;
            cout << "Student with ID " << id << " is deleted successfully.\n";
            return;
        }
        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "Student with ID " << id << " not found.\n";
            return;
        }
        prev->next = temp->next;
        delete temp;
        cout << "Student with ID " << id << " deleted successfully.\n";
    }
    void display() {
        if (isEmpty()) {
            cout << "No students in the list.\n";
            return;
        }

        sll_Node* temp = head;
        while (temp != NULL) {
            cout << "ID: " << temp->id << ", Name: " << temp->name
                 << ", Email: " << temp->email << ", Phone: " << temp->phone
                 << ", Address: " << temp->address << ", Password: " << temp->password << endl;
            temp = temp->next;
        }
    }
    bool findstudent(int ID){
        if (isEmpty()) {
            cout << "No students in the list.\n";
            return false;
        }

        sll_Node* temp = head;
        while (temp != NULL) {
            if (temp->id==ID){
                return true;
            }
            temp=temp->next;
        }
        return false;

    }

};
class dll_Node {
public:
    int studentID;
    int courseID;
    dll_Node* next;
    dll_Node* prev;
};
class doublelinkedlist {
public:
    dll_Node * head;

    doublelinkedlist() {
        head = NULL;
    }

    bool isEmpty() {
        return head == NULL;
    }

    void display(int student_id) {
        if (isEmpty()){
            return;
        }
        dll_Node *temp = head;
        while (temp != NULL) {
            if (temp->studentID==student_id){
            cout << "student ID:"<<temp->studentID << " Course ID: "<<temp->courseID;
            }
            temp = temp->next;
        }
        cout << endl;
    }
    bool search_history(int student_id,int course_id) {
        if(isEmpty()){
            return false;
        }
        dll_Node *temp = head;
        while (temp != NULL) {
            if (temp->studentID==student_id&&temp->courseID==course_id)
                return true;
            temp = temp->next;
        }
        return false;
    }
    void add(int course_id,int  student_id) {
        dll_Node  *newNode = new dll_Node();
        newNode->studentID = student_id;
        newNode->courseID=course_id;
        newNode->next = NULL;

        if (head == NULL) {
            newNode->prev = NULL;
            head = newNode;
        } else {
            dll_Node * temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }

};



class stack_node{
public:
    int course_id;
    stack_node* next;

};

class Stack{
public:
    stack_node * head;
    Stack():head(nullptr){}
    bool isempty(){
        return head== nullptr;

    }
    void push(int courseID){
        stack_node *newnode=new stack_node;
        newnode->next= head;
        newnode->course_id=courseID;
        head=newnode;
    }
    int pop(){
        if (isempty()){
            cout<<"stack is empty"<<endl;
            return 0;
        }
        stack_node *temp=head;
        int saver=temp->course_id;
        head=temp->next;
        delete temp;
        return saver;
    }

    void display(){
        if (isempty()){
            cout<<"stack is empty"<<endl;
            return;
        }
        stack_node  *temp=head;
        while (temp!= nullptr){
            cout<<temp->course_id<<endl;
            temp=temp->next;
        }
    }

};

class queue_node {
public:
    int student_id;
    queue_node *next;
    queue_node():next(nullptr){}

};
class Queue{
private:
    queue_node *front;
    queue_node *back;
public:
    Queue():front(nullptr),back(nullptr){}
    bool isempty(){
        return front== nullptr&&back == nullptr;

    }
    void enqueue(int studentID){
        queue_node * newnode=new queue_node;
        newnode->student_id=studentID;
        if (isempty()){
            front=newnode;
            back=newnode;
            return;
        }
        back->next=newnode;
        back=newnode;

    }
    int dequeue(){
        if (isempty()){
            cout<<"Queue is empty"<<endl;
            return int();
        }
        queue_node* curr=front;
        front=front->next;
        int saver=curr->student_id;
        if (front== nullptr)
            back= nullptr;
        delete curr;
        return saver;


    }
};





class University_System{
private:
    bst Course_Records_Management;
    linkedlist Student_Records_Management;
    doublelinkedlist Course_Enrollment_History;
    Queue Course_Waitlist;

public:
    void Add_Course(int ID,int coursecredit,string coursename,string courseinstructor){
        Course_Records_Management.addCourse(ID,coursecredit,coursename,courseinstructor);
    }
    void Drop_Course(int courseID){
        Course_Records_Management.dropcourse(courseID);
    }

    bool searchWithHashing(int ID){
        return Course_Records_Management.searchWithHashing(ID);
    }
    void Add_Student(int id, string name, string email, string phone, string address, string password){
        Student_Records_Management.add(id,name,email,phone,address,password);
    }
    void Delete_student(int ID){
        Student_Records_Management.deleteStudent(ID);
    }
    void Display_student(){
        Student_Records_Management.display();
    }
    void Display_History(int ID){
        Course_Enrollment_History.display(ID);
    }
    bool search_student(int id){
        return Student_Records_Management.findstudent(id);

    }
    void Add_Enrollment(int courseID,int StudentID){
        if (Course_Records_Management.searchWithHashing(courseID)&& Student_Records_Management.findstudent(StudentID)){
            Course_Enrollment_History.add(courseID,StudentID);
            cout<<"Added to the  Course_Enrollment_History "<<endl;
            return;
        }

        cout<<"Failed"<<endl;
    }
    void validatePrerequisites(int courseID, int studentID){
        if (!Course_Records_Management.searchWithHashing(courseID)){
            cout<<"course not found"<<endl;
            return;
        }
        if ( !Student_Records_Management.findstudent(studentID)){
            cout<<"student not found"<<endl;
        }
        Stack Course_Registration;
        cout<<" enter prerequsities courses number"<<endl;
        int num;
        cin>>num;
        if (num>0){
            for (int i = 0; i < num; ++i) {
                cout<<"enter course id :" ;
                int id;
                cin>>id;
                Course_Registration.push(id);
            }
        }
        else{
            cout << "Student ID " << studentID << " has met all prerequisites for Course ID " << courseID << "." << endl;
            return;
        }


        bool flag= true;
        while (!Course_Registration.isempty()){
            int precourse=Course_Registration.pop();
            if (Course_Enrollment_History.search_history(studentID,precourse)){
                cout << "Student has  completed prerequisite course ID: " << precourse << endl;

            } else{
                Course_Registration.push(precourse);
                flag= false;
                break;
            }

        }

        if (flag){
            cout << "Student ID " << studentID << " has met all prerequisites for Course ID " << courseID << "." << endl;
        } else{
            cout << "Student ID " << studentID << " has not met all prerequisites for Course ID " << courseID << "." << endl;
            cout << "Remaining prerequisites for Course ID " << courseID << ": ";
            Course_Registration.display();
        }
    }

    void Add_to_waitlist(int student_id){
        Course_Waitlist.enqueue(student_id);

    }
    void Remove_from_waitlist(){
        Course_Waitlist.dequeue();

    }



};



int main() {
    University_System system;

    // Add Courses
    system.Add_Course(101, 3, "Data Structures", "Dr. Smith");
    system.Add_Course(102, 4, "Algorithms", "Prof. Johnson");
    system.Add_Course(103, 2, "Discrete Mathematics", "Dr. Lee");

    // Add Students
    system.Add_Student(1, "Alice", "alice@example.com", "123-456-7890", "123 Maple St", "password123");
    system.Add_Student(2, "Bob", "bob@example.com", "987-654-3210", "456 Oak St", "password456");

    // Display Students
    cout << "Displaying all students:" << endl;
    system.Display_student();

    // Search for a student
    int studentID = 1;
    if (system.search_student(studentID)) {
        cout << "Student with ID " << studentID << " found." << endl;
    } else {
        cout << "Student with ID " << studentID << " not found." << endl;
    }

    // Add Enrollments
    system.Add_Enrollment(101, 1);  // Alice enrolling in Data Structures
    system.Add_Enrollment(102, 1);  // Bob enrolling in Algorithms
    // Validate Prerequisites
    system.validatePrerequisites(102, 1);  // Check if Alice has prerequisites for Algorithms

    // Drop a Course
    system.Drop_Course(102);  // Drop the Algorithms course

    // Check if a course exists using hashing
    int courseID = 101;
    if (system.searchWithHashing(courseID)) {
        cout << "Course with ID " << courseID << " is available." << endl;
    } else {
        cout << "Course with ID " << courseID << " is not available." << endl;
    }
    // delete and search student
    system.Delete_student(1);
    if (system.search_student(1)) {
        cout << "Student with ID " << studentID << " found." << endl;
    } else {
        cout << "Student with ID " << studentID << " not found." << endl;
    }

    // Add Students to Waitlist
    system.Add_to_waitlist(1);  // Add Alice to the waitlist
    system.Add_to_waitlist(2);  // Add Bob to the waitlist

    // Remove from Waitlist
    system.Remove_from_waitlist();  // Remove the first student from the waitlist

}
