#include "ClothingQueue.h"
#include "ClothingItem.h"
#include <string>
#include <iostream>
using namespace std;

void performAction(string input, ClothingQueue *queue);
void returnItemsToQueue(ClothingQueue *queue);

int main() {
	string filename = "ClothingItems.csv";

	ClothingQueue *queue = new ClothingQueue(filename);

	string userInput = "";

	while (userInput.compare("q") != 0 && userInput.compare("Q") != 0 && userInput.compare("quit") != 0) {
		cout << "What would you like to do?\n";
		cout << "\tp - pick an outfit\n";
		cout << "\ta - add a new piece\n";
		cout << "\tr - return a piece to the queue\n";
		cout << "\tm - manually pick an outfit\n";
		cout << "\tv - view queue for an item type\n";
		cout << "\tq - quit\n";

		getline(cin, userInput);

		performAction(userInput, queue);
	}

	cout << "Exiting. Goodbye!\n";

	return 0;
}

void performAction(string input, ClothingQueue *queue) {
	if (input.compare("a") == 0 || input.compare("A") == 0) {
		queue->addNewItem();
	} else if (input.compare("v") == 0 || input.compare("V") == 0) {
		queue->viewQueue();
	} else if (input.compare("m") == 0 || input.compare ("M") == 0) {
		queue->pickItemManually();
	} else if (input.compare("r") == 0 || input.compare("R") == 0) {
		returnItemsToQueue(queue);
	} else if (input.compare("p") == 0 || input.compare("P") == 0) {
		queue->pickOutfit();
	}
}

void returnItemsToQueue(ClothingQueue *queue) {
	string userInput = "";

	while (userInput.compare("n") != 0 && userInput.compare("N") != 0 && userInput.compare("no") != 0) {
		queue->returnItemToQueue();
		cout << "Return another?\n";
		getline(cin, userInput);
	}
}