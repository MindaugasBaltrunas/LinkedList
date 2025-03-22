using namespace std;
#include <iostream>
#include <string>
#include <chrono>

class Node {
private:
	string name;
	int price;
	int date;
	Node* next;

public:
	Node(string name, int price, int date) {
		this->name = name;
		this->price = price;
		this->date = date;
		this->next = nullptr;
	}

	friend class LinkedList;
};

class LinkedList {
public:
	Node* head;

	LinkedList() {
		head = nullptr;
	}

	void addFirst() {
		string name;
		int price;
		int date;
		cout << "Enter product name: ";
		cin >> name;
		cout << "Enter product price: ";
		cin >> price;
		cout << "Enter product date (YYYYMMDD): ";
		cin >> date;
		Node* newNode = new Node(name, price, date);
		newNode->next = head;
		head = newNode;
		cout << "Product added at the beginning." << endl;
	}

	void addLast() {
		string name;
		int price;
		int date;
		cout << "Enter product name: ";
		cin >> name;
		cout << "Enter product price: ";
		cin >> price;
		cout << "Enter product date (YYYYMMDD): ";
		cin >> date;
		Node* newNode = new Node(name, price, date);
		if (head == nullptr) {
			head = newNode;
			cout << "Product added as the first element." << endl;
			return;
		}
		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
		cout << "Product added at the end." << endl;
	}

	void removeLast() {
		if (head == nullptr) {
			cout << "List is empty." << endl;
			return;
		}

		Node* temp = head;
		while (temp->next->next != nullptr) {
			temp = temp->next;
		}

		temp->next = nullptr;
	}

	void removeFirst() {
		if (head == nullptr) {
			cout << "List is empty." << endl;
			return;
		}

		Node* temp = head;
		head = head->next;
		delete temp;
	}

	void search() {
		if (head == nullptr) {
			cout << "List is empty." << endl;
			return;
		}

		string name;
		cout << "Enter product name to search: ";
		cin >> name;

		Node* temp = head;
		while (temp != nullptr)
		{
			if (name == temp->name) {
				cout << "Product found: " << temp->name << " Price: " << temp->price
					<< " Date: " << temp->date << endl;
				head = temp;
				temp->next = nullptr;
				break;
			}
			temp = temp->next;
		}
	}

	void removeAll() {
		if (head == nullptr) {
			cout << "List is already empty." << endl;
			return;
		}
		cout << "Removing all products:" << endl;
		print();

		Node* temp = head;
		head = nullptr;
		cout << "All products have been removed." << endl;
	}

	void outOfDate() {
		if (head == nullptr) {
			cout << "List is empty." << endl;
			return;
		}

		Node* temp = head;
		while (temp != nullptr) {
			if (soonOutOfDate(temp->date)) {
				temp->name += " (OUT OF DATE)";
			}
			temp = temp->next;
		}

		cout << "Out of date products have been marked." << endl;
	}

	void orderByPrice() {
		if (!head || !head->next) {
			cout << "List is empty or has only one item." << endl;
			return;
		}

		Node* first = head;
		Node* last = nullptr;
		while (first && first->next != last) {
			Node* sorted = first->next;
			for (Node* current = first; current->next != last; current = current->next) {
				if (current->price > current->next->price) {
					int temp = current->price;
					current->price = current->next->price;
					current->next->price = temp;
					sorted = current->next;
				}
			}
			last = sorted;
		}
		head = first;

		cout << "Products sorted by price." << endl;
	}

	string length() {
		int count = 0;
		Node* temp = head;
		while (temp != nullptr) {
			count++;
			temp = temp->next;
		}
		return to_string(count);
	}

	void print() {
		if (head == nullptr) {
			cout << "List is empty." << endl;
			return;
		}
		Node* temp = head;
		cout << "Products list:" << endl;
		while (temp != nullptr) {
			cout << "Name: " << temp->name
				<< ", Price: " << temp->price
				<< ", Date: " << temp->date << endl;
			temp = temp->next;
		}
	}

	bool soonOutOfDate(int referenceDate) {

		auto now = chrono::system_clock::now();

		auto pastDay = now + chrono::hours(24);

		time_t past_time_t = chrono::system_clock::to_time_t(pastDay);
		tm localTime;
		localtime_s(&localTime, &past_time_t);

		int dateInt = (1900 + localTime.tm_year) * 10000 +
			(localTime.tm_mon + 1) * 100 +
			localTime.tm_mday;

		if (referenceDate < dateInt) {
			return true;
		}

		return false;
	}
};



int main() {
	LinkedList list;
	int choice;
	do {
		cout << "\n*********************************" << endl;
		cout << "[0] - Add First" << endl;
		cout << "[1] - Add Last" << endl;
		cout << "[2] - Search" << endl;
		cout << "[3] - Remove First" << endl;
		cout << "[4] - Remove Last" << endl;
		cout << "[5] - Print List" << endl;
		cout << "[6] - Order By Price" << endl;
		cout << "[7] - Mark Out Of Date" << endl;
		cout << "[8] - Remove All" << endl;
		cout << "[9] - Exit" << endl;
		cout << "Choose an option: ";
		cin >> choice;

		switch (choice) {
		case 0:
			list.addFirst();
			break;
		case 1:
			list.addLast();
			break;
		case 2:
			list.search();
			break;
		case 3:
			list.removeFirst();
			break;
		case 4:
			list.removeLast();
			break;
		case 5:
			list.print();
			break;
		case 6:
			list.orderByPrice();
			break;
		case 7:
			list.outOfDate();
			break;
		case 8:
			list.removeAll();
			break;
		case 9:
			cout << "Exiting program." << endl;
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
			break;
		}
	} while (choice != 9);
	return 0;
}