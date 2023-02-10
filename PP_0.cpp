#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>


// Website node definition

class Website{
    public:
        std::string name;                         // Name of the website
        std::string url;                          // URL of the website
        std::string type;                      // Type of resource provided by the website
        Website(){};                              // Constructor with no arguments
        Website(std::string new_name, std::string new_url, std::string new_type){         // Constructor with arguments
            name = new_name;
            url = new_url;
            type = new_type;
        }
};


// Node definition
template <typename T>
class Node{
    private:
        T data;
        Node<T> *next;                            // Next website in the list
        Node<T> *back;                            // Previous website in the list

    public:
        Node(){};                              // No argument constructor
        Node(T new_data){                      // Constructor when website is known
            data = new_data;
            next = nullptr;
            back = nullptr;
        }
    
    template <typename E> friend class LinkedList;
};

// Linked List definition
template <typename T>
class LinkedList{
    private:
        Node<T> *header; 
        Node<T> *trailer;
        int size;

    public:
        LinkedList(){                             // Linked List constructor 
            header = new Node<T>;
            trailer = new Node<T>;
            size = 0;
            header->next = trailer;
            trailer->back = header;
        }


        ~LinkedList(){                      // Linked List destructor
            while(size != 0){
                removeFront();
            }
            delete header;
            delete trailer;
        }

        void remove(Node<T> *toRemove){                  // Remove a given website from the list
            toRemove->back->next = toRemove->next;
            toRemove->next->back = toRemove->back;
        }

        void removeFront(){                              // Remove the first website
            remove(header->next);
            size--;
            return;
        }

        void removeBack(){                               // Remove the last website
            remove(trailer->back);
            size--;
            return;
        }

        void add(Node<T> *beforeMe, T data){    // General add function

            // Create new website
            Node<T> *newNode = new Node<T>(data);
            
            // Add website to linked list
            beforeMe->back->next = newNode;
            newNode->back = beforeMe->back;
            beforeMe->back = newNode;
            newNode->next = beforeMe;
        
            return;
        }

        void addFront(T data){   // Adding to the front of the list
            add(header->next,data);

            size++;
            return;
        }

        void addBack(T data){   // Adding to the end of the list
            add(trailer,data);

            size++;
            return;
        }

        void printList(){             // Function to print entire list
            Node<T> *curNode = header->next;
            std::cout << "\n";
            std::cout << "PRINTING LIST... \n\n";
            std::cout.width(20); std::cout << std::left << "Name";
            std::cout.width(80); std::cout << std::left << "URL";
            std::cout.width(20); std::cout << std::left << "Resource type";
            std::cout << "\n===========================================================================================================================\n";
            while (curNode != trailer){
                std::cout.width(20); std::cout << std::left << curNode->data.name;
                std::cout.width(80); std::cout << std::left << curNode->data.url;
                std::cout.width(20); std::cout << std::left << curNode->data.type;
                std::cout << "\n";
                curNode = curNode->next;
            }

            std::cout << "\n";
        }
        
};


// Main function
int main(){
    // Testing all functions of the list
    
    /*
    Website site = Website("geeksforgeeks","https://www.geeksforgeeks.org/c-plus-plus/?ref=shm","Guide");
    Node<Website> node = Node<Website>(site);
    LinkedList<Website> list;
    list.addFront(site);
    list.printList();
    site = Website("w3schools", "https://www.w3schools.com/cpp/" ,"Guide");
    list.addFront(site);
    list.printList();
    list.removeFront();
    list.printList();
    list.addBack(site);
    list.printList();
    list.removeBack();
    list.printList();
    */

    return EXIT_SUCCESS;
}