#include <iostream>
using namespace std;
#include <string>

class Node {
private:
	int number;
	Node* next;

public:
	Node(int value) {
		this->number = value;
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

	void addLast(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
			return;
		}

		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}

	void removeLast() {
		Node* temp = head;
		for (size_t i = 1; i < stoi(length())-1; i++) {
			temp = temp->next;
		}

		temp->next = nullptr;
	}

	void addFirst(int value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
	}

	void removeFirst() {
		Node* temp = head;
		temp->next = head->next->next;
		head = temp;
	}

	void addMiddle(int value) {
		Node* newNode = new Node(value);

		int middle = stoi(length()) / 2;

		Node* temp = head;
		for (size_t i = 1; i < middle; i++) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
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
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->number << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};


int main() {
	LinkedList list;

	list.addFirst(8);
	list.addFirst(18);

	list.addLast(10);
	list.addLast(20);
	list.addLast(5);
	list.addLast(30);

	list.addMiddle(100);

	list.removeFirst();
	list.removeLast();

	list.print();

	cout << "Saraso ilgis: " << list.length() << endl;
	return 0;
}

//1) Įterpimas į priekį
//2) Ištrinimas iš galo
//3) Ištrinimas iš priekio
//4) Įterpimas į vidurį