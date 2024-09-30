#include <iostream>
using namespace std; 
template <typename Item_Type>
class Node {  //Create a class 
public:
    Item_Type item; 
    Node* next;

    Node(const Item_Type& item) : item(item), next(nullptr) {}
};

template <typename Item_Type>
class Single_Linked_List { //Create the single linked list 
private:
    Node<Item_Type>* head; //define the head and tial 
    Node<Item_Type>* tail;
    size_t num_items; //define num items 

public:
    Single_Linked_List() : head(nullptr), tail(nullptr), num_items(0) {} //define the pointers 

    ~Single_Linked_List() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_front(const Item_Type& item) { //create the function for pushing to the front 
        Node<Item_Type>* new_node = new Node<Item_Type>(item);
        new_node->next = head; //define the new node as the head 
        head = new_node;
        if (tail == nullptr) { //check to make sure there is a tail 
            tail = new_node;
        }
        num_items++; //incriment num items 
    }

    void push_back(const Item_Type& item) { //create the push back function
        Node<Item_Type>* new_node = new Node<Item_Type>(item);
        if (tail) {
            tail->next = new_node; //create the new node at the end of the list 
        }
        else {
            head = new_node;
        }
        tail = new_node;
        num_items++; //add one to num items 
    }

    Item_Type pop_front() {
        if (empty()) {
            throw std::out_of_range("Pop from empty list"); //check to make sure that there is an item to pop 
        }
        Node<Item_Type>* temp = head; //create a temp value as the head 
        Item_Type removed_item = temp->item;
        head = head->next; //re assign the pointers 
        delete temp; //delete the temp variable 
        if (head == nullptr) { //if head is null then make tail null too 
            tail = nullptr;
        }
        num_items--; //subtract from num items 
        return removed_item;
    }

    Item_Type pop_back() {
        if (empty()) {
            throw std::out_of_range("Pop from empty list"); //check to make sure the list isnt empty 
        }
        if (head == tail) {
            Item_Type removed_item = head->item; //checking if th head was the removed item or if the list was only one item
            delete head;
            head = tail = nullptr;
            num_items--;
            return removed_item;
        }

        Node<Item_Type>* current = head; //checking to see if the first one was the head  
        while (current->next != tail) { // if the next node is not the tail 
            current = current->next; //the node pointers get updated 
        }

        Item_Type removed_item = tail->item; //making sure that the new item 
        delete tail;
        tail = current;
        tail->next = nullptr;
        num_items--; //lower the count of num items 
        return removed_item; //return the removed item 
    }

    Item_Type front() const { //function to find the front 
        if (empty()) { //check to make sure list is not empty 
            throw std::out_of_range("List is empty");
        }
        return head->item; //return the head 
    }

    Item_Type back() const { //function to check the back of the list 
        if (empty()) {
            throw std::out_of_range("List is empty"); //check to make sure its not empty 
        }
        return tail->item; //tail == items 
    }

    bool empty() const { //check to see if the list is empty 
        return num_items == 0; // return if num items is 0 
    }

    void insert(size_t index, const Item_Type& item) { //fucntion to insert a new value 
        if (index <= 0) {
            push_front(item);// if insertion is the front then just push front 
        }
        else if (index >= num_items) {
            push_back(item); //if fucntion is the back then just push back 
        }
        else {
            Node<Item_Type>* new_node = new Node<Item_Type>(item);
            Node<Item_Type>* current = head;
            for (size_t i = 0; i < index - 1; i++) { //set i = 0 and the index -1 
                current = current->next; //upodate the pointers of the lsit 
            }
            new_node->next = current->next; //update the pointers of the lsit 
            current->next = new_node;
            num_items++; // add one to num items 
        }
    }

    bool remove(size_t index) { //function to remove an item from a index 
        if (index < 0 || index >= num_items) {
            return false; //check to make sure index is in bounds 
        }
        if (index == 0) {
            pop_front(); //if index is front then call pop front function
            return true;
        }

        Node<Item_Type>* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next; //update the pointers of the function 
        }
        Node<Item_Type>* to_remove = current->next; // temo variable = current next 
        if (to_remove == tail) { 
            tail = current;
        }
        current->next = to_remove->next;
        delete to_remove; //delete the temp value 
        num_items--; //deincrement num items
        return true;
    }

    size_t find(const Item_Type& item) const { //function to find a number 
        Node<Item_Type>* current = head;
        size_t index = 0; 
        while (current != nullptr) { //update the pointer when it is not null 
            if (current->item == item) {
                return index; // return the index 
            }
            current = current->next;
            index++; // increment the index 
        }
        return num_items; // Return size if not found
    }

    size_t size() const { //check the size of the list 
        return num_items; // return the value of num items 
    }

    void print() const { //print the list 
        Node<Item_Type>* current = head;
        while (current != nullptr) {
            cout << current->item << " "; // print the value of the items
            current = current->next; // make current = current next 
        }
        cout << std::endl;
    }
};

// Example usage
int main() {
    int new_number = 0; 
    int num_items = 0; 
    int usrindex = 0; 
    int inserted_number = 0;
    int found_number = 0;
    int index_to_remove = 0;
    Single_Linked_List<int> sll;
    while (num_items <= 2) // check to make sure you are less then or equal to num items 
    {
        cout << "Please add a number to the front of the list. "; //ask for a number 
        cin >> new_number; // user input of new variable 
        sll.push_front(new_number); //call the push front function 
        num_items++; // increment num items 
        

    }
    sll.print(); //exit and print the loop 

    while (num_items <= 4)
    {
        cout << "Please add a number to the back of the list "; // ask for numbers to add to the end of a list 
        cin >> new_number; // get the input for the new number 
        sll.push_back(new_number); //call the push back function 
        num_items++; // increment num items 

    }
    sll.print(); //exit the loop and print 
 
    std::cout << "The front of the list is: " << sll.pop_front() << std::endl; // take off the last value and print the item 
    sll.print(); 

    cout << "Please insert the index that you want to insert: "; //ask for the value to insert 
    cin >> usrindex; //get the user input of the index 
    cout << "Please insert the desired number: "; // ask for the number 
    cin >> inserted_number; // get the user inserted number 

    sll.insert(usrindex, inserted_number); //call the insert function 
    sll.print(); 


    cout << "What is the desired number to find: "; // ask for the number to find 
        cin >> found_number;

    cout << "The index of the number is: " << sll.find(found_number) << std::endl; // call the find number function 
    sll.print(); //print 

    cout << "Insert the Index that is desired to be removed: "; //ask for the index to be found 
    cin >> index_to_remove;
    sll.remove(index_to_remove); //call index to remove function. 
    sll.print(); 

    return 0;
}
