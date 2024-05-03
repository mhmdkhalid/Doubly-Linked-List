#include <iostream>
using namespace std;

class student{
public:
    string name;
    int id;
    float gpa;
    student(){}
    student(string name, int id_, float gpa_){
        this->name= name;
        id= id_;
        gpa= gpa_;
    }
};

struct node{
    student data;
    node* next;
    node(){} // default
    node(student student_data){
        data= student_data;
        next= NULL;
    }
};

class studentlist{
private:
    node* head;
    node* tail;
    int size;
public:
    studentlist(){
        head=tail=NULL;
        size= 0;
    }

    ~studentlist(){  //?
        node* current= head;
        while (current!= NULL) {
            node* next= current->next;
            delete current;
            current= next;
        }
        head= NULL;
    }

    void insert(student new_student){
        node* newnode= new node;
        newnode->data= new_student;
        if (head== NULL || head->data.id>new_student.id){
            newnode->next= head;
            head= newnode;
        }
        else{
            node* current= head;
            while(current->next!= NULL && current->next->data.id<new_student.id){
                current= current->next;
            }
            newnode->next= current->next; // current->next=null //mafesh 8er node wa7da
            current->next= newnode;
        }
        size++;
    }

    void remove(int id){
        node* current= head;
        node* prev= NULL;
        while(current!= NULL && current->data.id!= id){
            prev= current;
            current= current->next;
        }
        if(current== NULL){
            cout<<"Student with ID "<<id<<" not found in the list."<<endl;
            return;
        }
        else if (prev== NULL){ // delete first node
            head= current->next;
        }
        else{
            prev->next = current->next;
        }
        delete current;
        size--;
        cout<<"Student with ID "<<id<<" removed from the list."<<endl;
    }

    void Search(int id){
        node* cur= head;
        while(cur!= NULL && cur->data.id!= id){
            cur= cur->next;
        }
        if (cur== NULL){
            cout<< "Student with ID "<<id<<" not found in the list."<<endl;
        }
        else{
            cout<<"Student with ID "<<id<<" found: "<<cur->data.name<<", GPA: "<<cur->data.gpa<<"."<<endl;
        }
    }

    int sizes(){
        return size;
    }

    void Display(){
        if(head== NULL){
            cout<<"Student list is empty."<<endl;
            return;
        }
        cout<<"List of Students:"<<endl;
        node* current= head;
        while(current!= NULL){
            cout<<"Name: "<<current->data.name<<", ID: "<<current->data.id<<", GPA: "<<current->data.gpa<<endl;
            current= current->next;
        }
        cout <<"Number of students in the list: "<<sizes()<<endl;
    }
};
class Doublenode{
public:
    char info;
    Doublenode *next;
    Doublenode* prev;
    Doublenode(){
        next=prev=NULL;
    }
    Doublenode(char data){
        info=data;
        next=prev=NULL;
    }
};
class Doublelinked{
public:
    Doublenode* head;
    Doublenode* tail;
    int size;
    Doublelinked(){
        tail=head=NULL;
        size=0;
    }

    void insertAT_FIRST(char item){
        Doublenode*Newnode= new Doublenode(item);
        if(size==0){
            head=tail=Newnode;
            Newnode->next=Newnode->prev=NULL;
        }
        else{
            Newnode->next=head;
            Newnode->prev=NULL;
            head->prev=Newnode;
            head=Newnode;
        }
        size++;
    }
    void insertAT_Last(char item){
        Doublenode* Newnode=new Doublenode(item);
        if(size==0){
            head=tail=Newnode;
            Newnode->next=Newnode->prev=NULL;
        } else{
            Newnode->next=NULL;
            Newnode->prev=tail;
            tail->next=Newnode;
            tail=Newnode;
        }
        size++;
    }
    void insertAT_pos(int pos,char item){
        if(pos<0 || pos>size){
            cout<<"out of range"<<endl;
        }else{
            Doublenode* Newnode= new Doublenode;
            Newnode->info=item;
            if(pos==0){
                insertAT_FIRST(item);
            }else if(pos==size){
                insertAT_Last(item);
            } else{
                Doublenode* current=head;
                for (int i = 0; i <pos-1 ; ++i) {
                    current=current->next;
                }
                Newnode->next=current->next;
                Newnode->prev=current;
                current->next->prev=Newnode;
                current->next=Newnode;
                size++;
            }
        }
    }
    void displayList(){
        Doublenode* temp = head;
        while (temp != NULL) {
            cout << temp->info;
            temp = temp->next;
        }
        cout << endl;
    }
    void deleteAtPos (int position){
        Doublenode* current= head;
        for (int i= 0;i<position; i++) {
            current=current->next;
        }
        if (current== head){
            head= current->next;
            if (head!= NULL){
                head->prev=NULL;
            }else {
                tail=NULL;
            }
        } else if (current==tail){
            tail = current->prev;
            tail->next=NULL;
        } else{
            current->prev->next=current->next;
            current->next->prev=current->prev;
        }
        delete current;
        size--;
    }
    void concate(Doublelinked Newlist){
        if(head==NULL){
            head=Newlist.head;
            tail=Newlist.tail;
        }else{
            tail->next=Newlist.head;
            Newlist.head->prev=tail;
            tail=Newlist.tail;
            size+=Newlist.size;
        }
    }
    Doublelinked substring(int start,int length){
        Doublelinked sub; // new list to store substring
        Doublenode* ptr=head;
        for (int pos=0;ptr != NULL&& pos<start ;pos ++){
            ptr=ptr->next;
        }
        while(ptr!=NULL && length>0){
            sub.insertAT_Last(ptr->info);
            ptr=ptr->next;
            length--;
        }
        return sub;
    }

    int search(Doublelinked& substring){
        Doublenode * currentNode=head;//start from head of list
        Doublenode * startingNode=substring.head;
        int position= 0;
        //traverse
        while (currentNode!= NULL){
            if (currentNode->info== startingNode->info) {//if we find a node matches the start of substring
                Doublenode* tempCurrent=currentNode;
                Doublenode* tmpsubstring= startingNode;
                bool matched= true;
                while (tmpsubstring!= NULL){ //check if other following nodes match the substring
                    if (tempCurrent== NULL||tempCurrent->info!= tmpsubstring->info) {
                        matched= false;
                        break;
                    }
                    tempCurrent= tempCurrent->next;
                    tmpsubstring= tmpsubstring->next;
                }
                if (matched== true)
                    return position;
            }
            currentNode = currentNode->next;//move to next node
            position++;
        }
        //f we didnt find a match return -1
        return -1;
    }

    void replace(string& currentPart, string& newPart) {
        Doublelinked tmp;
        Doublelinked newList;
        for (int i = newPart.length() - 1; i >= 0; i--) {
            newList.insertAT_FIRST(newPart[i]);
        }
        Doublenode* current=head;
        while (current != nullptr) {
            if (current->info == currentPart[0]) {
                Doublenode* tmpCurrent = current;


                int i = 0;
                while (i<currentPart.length()&& tmpCurrent->info==currentPart[i]&&tmpCurrent!= nullptr){
                    tmpCurrent = tmpCurrent->next;
                    i++;
                }

                if (i == currentPart.length()) { //if full mathced->concate
                    tmp.concate(newList);
                }
                else{
                    tmp.insertAT_Last(current->info);
                }
                current = tmpCurrent;
            }

            else{
                tmp.insertAT_Last(current->info); //no match
                current = current->next;
            }
        }

        head=tail=nullptr;
        concate(tmp);
    }

    void reverse() {
        Doublenode* current = head;
        Doublenode* tmp = NULL;
        while (current != NULL) {
            tmp= current->next;
            current->next= current->prev;
            current->prev= tmp;
            current= tmp;
        }
        swap(head, tail);
    }
};

int main() {
    cout << "choose task 1 or 2: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: {
            studentlist list;
            list.insert(student("Mohamed", 6151, 2.9));
            list.insert(student("Khaled", 6089, 2.8));
            list.insert(student("Noran", 6120, 3.2));
            list.insert(student("Fahmy", 6053, 3.5));
            list.Display();

            list.insert(student("nour", 6110, 3));
            list.Display();

            list.remove(6151);
            list.remove(6120);
            list.remove(6053);
            list.Display();
            list.Search(6089);
            list.Search(6053);
            list.Display();
            break;
        }
        case 2: {

            Doublelinked list1;
            Doublelinked list2;
            char string1;

            cout << "enter string to add to list 1: ";
            cin.ignore();
            cin.get(string1);
            while (string1 != '\n') {
                list1.insertAT_Last(string1);
                cin.get(string1);
            }

            cout << "enter string to add to list 2: ";
            cin.get(string1);
            while (string1 != '\n') {
                list2.insertAT_Last(string1);
                cin.get(string1);

            }

            cout << "concatenated list: ";
            list1.concate(list2);
            list1.displayList();
            int index;
            cout << "choose a char by index to remove:";
            cin >> index;
            list1.deleteAtPos(index);
            cout << "list after removel: ";
            list1.displayList();
            Doublelinked sublist;
            cout << "enter index and length to get substring: ";
            int start, length;
            cin >> start >> length;
            sublist = list1.substring(start, length);
            cout << "Substring: ";
            sublist.displayList();
            cout << "Search for a substring in the list: ";
            char substring;
            Doublelinked search;
            cin.ignore();
            cin.get(substring);
            while (substring != '\n') {
                search.insertAT_Last(substring);
                cin.get(substring);
            }
            int indexFound = list1.search(search);
            cout << "Found at index " << indexFound << endl;

            cout << "Enter 2 substrings to replace one with another: ";
            string old, NEW;
            cin >> old >> NEW;
            list1.replace(old, NEW);
            cout << "List after replacement: ";
            list1.displayList();
            list1.reverse();
            cout << "reversed list: ";
            list1.displayList();
            break;

        }


    }
    return 0;
}