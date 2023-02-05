#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>

// Website node definition

class Website{
private:
    std::string name;                         // Name of the website
    std::string url;                          // URL of the website
    std::string type;                      // Type of resource provided by the website
    Website *next;                            // Next website in the list
    Website *back;                            // Previous website in the list

public:
    Website(){};                              // Constructor with no arguments
    Website(std::string new_name, std::string new_url, std::string new_type, Website *n, Website *b){         // Constructor with arguments
        name = new_name;
        url = new_url;
        type = new_type;
        next = n;
        back = b;
    }

    friend class LinkedList;
};

// Linked List definition
class LinkedList{
private:
    Website *header;
    Website *trailer;
    size_t size;

public:
    LinkedList(){                        // Linked List constructor
        header = new Website;
        trailer = new Website;
        size = 0;
        header->next = trailer;
        trailer->back = header;
    }

    ~LinkedList(){                      // Linked List destructor
        while(size != 0){
            removeFront(); // size-- happens in removeFront() !!!!
        }
        delete header;
        delete trailer;
    }

    int isEmpty(){
        if (header->next == trailer && trailer->back == header){
           return 1; 
        }
        return 0;
    }

    void remove(Website *toRemove){                  // Remove a given website from the list
        if (!isEmpty()){
            toRemove->back->next = toRemove->next;
            toRemove->next->back = toRemove->back;
            delete toRemove;
            size--;
        }
        else {
            std::cout << "There was an error accounting for the number of entries (size)!";
            std::cout << std::endl;
        }

    }

    //accounts for empty list
    void removeFront(){                              // Remove the first website
        if (!isEmpty()){
            Website* temp = new Website;
            temp->next = header->next;
            header->next = header->next->next;
            delete temp->next;
            delete temp;
            size--;
        }
        else {
            std::cout << "List is already empty!" << std::endl;
        }
    }

    void removeBack(){                               // Remove the last website
        if (!isEmpty()){
            //Website* temp = new Website;
            Website* temp = trailer->back;
            //temp->back = trailer->back;
            trailer->back = trailer->back->back;
            //delete temp->back;
            delete temp;
            size--;
        }
        else {
            std::cout << "List is already empty!" << std::endl;
        }
        return;
    }

    void addBefore(Website *beforeMe, const std::string new_name, const std::string new_url, std::string new_type){    // General add function

        // Create new website
        Website *newWebsite = new Website();
        newWebsite->name = new_name;
        newWebsite->url = new_url;
        newWebsite->type = new_type;

        // Add website to linked list
        beforeMe->back->next = newWebsite;
        newWebsite->back = beforeMe->back;
        beforeMe->back = newWebsite;
        newWebsite->next = beforeMe;
        size++; /* I *think* size needs to be increased at every addBefore() call,
            but I could be wrong */
    }

    void addFront(const std::string new_name, const std::string new_url, std::string new_type){   // Adding to the front of the list
        addBefore(header->next,new_name,new_url,new_type);
    }

    void addBack(const std::string new_name, const std::string new_url, std::string new_type){   // Adding to the end of the list
        addBefore(trailer,new_name,new_url,new_type);
    }

    void printList(){             // Function to print entire list
        Website* curWebsite = header->next;
        std::cout << "\n";
        std::cout << "PRINTING LIST... \n\n";
        std::cout.width(20); std::cout << std::left << "Name";
        std::cout.width(80); std::cout << std::left << "URL";
        std::cout.width(20); std::cout << std::left << "Resource type";
        std::cout << "\n===========================================================================================================================\n";
        while (curWebsite != trailer){
            std::cout.width(20); std::cout << std::left << curWebsite->name;
            std::cout.width(80); std::cout << std::left << curWebsite->url;
            std::cout.width(20); std::cout << std::left << curWebsite->type;
            std::cout << "\n";
            curWebsite = curWebsite->next;
        }

        std::cout << "\n";
    }

};

LinkedList readFile(std::string filename){
    std::ifstream infile;
    infile.open(filename);
    LinkedList list;
    std::string name;
    std::string url;
    std::string type;

    std::string str;
    if (infile){
        while (!infile.eof()){
            infile >> name;
            infile >> url;
            infile >> type;
            list.addFront(name,url,type);
        }
    }

    infile.close();
    return list;
}

// Main function
int main(){

    LinkedList myLinkedList =readFile("exampleWebsites.txt");
    myLinkedList.printList();

    return EXIT_SUCCESS;
}
