#include "ClothingQueue.h"
#include <fstream>
#include <iostream>
#include <utility>
using namespace std;

ClothingQueue::ClothingQueue(string filename) : filename_(filename) {
	ifstream in(filename.c_str());

	string line;

	getline(in, line);

	while (getline(in, line)) {
		ClothingItem *item = new ClothingItem(line);
		//cout << "Loading " << item->shortInfo() << endl;
		addItemToWardrobe(item);
	}

	in.close();
}

void ClothingQueue::addNewItem() {
	ClothingItem *item = new ClothingItem(totalNumPieces() + 1);
	setItemsMatches(item);

	cout << "Adding " << item->shortInfo() << " to queue\n";
	
    cleanQueue_.push_back(item);

	updateDatabase();
}

int ClothingQueue::totalNumPieces() {
	return cleanQueue_.size() + dirtyQueue_.size() + removedQueue_.size();
}

void ClothingQueue::setItemsMatches(ClothingItem *item) {
	if (totalNumPieces() - removedQueue_.size() > 0) {
		cout << "All items in the wardrobe will be shown.\n";
		cout << "Picture the new item with the given item by themselves.\n";
		cout << "Respond whether they match or not. [y/n]\n";

		for (unsigned int i = 0; i < cleanQueue_.size(); i++) {
			queryNonMatch(item, cleanQueue_[i]);
		}

		for (unsigned int i = 0; i < dirtyQueue_.size(); i++) {
			queryNonMatch(item, dirtyQueue_[i]);
		}
	}
}

void ClothingQueue::queryNonMatch(ClothingItem *originalItem, ClothingItem *comparedItem) {
	if (!(originalItem->getType() == comparedItem->getType() && 
		(originalItem->getType() == SHOE || originalItem->getType() == BOTTOM))) {
		cout << comparedItem->shortInfo() << endl;
		string response;
		cout << "Does this match?\n";
		getline(cin, response);
		originalItem->addNonMatch(response, comparedItem);
		comparedItem->addNonMatch(response, originalItem);
	}
}

void ClothingQueue::updateDatabase() {
	// Open new file with the data in it.
	ofstream out(filename_.c_str());

	out << "ID #,Type,Style,Color,Brand,Gets dirty?,Num wears left,";
	out << "Max num wears,Min temp,Max temp,Rain?,Snow?,Walking?,Informal,";
	out << "Casual,Business casual,Business formal,Formal,Active,Unmatches ->";
	out << endl;

	for (unsigned int i = 0; i < cleanQueue_.size(); i++) {
		out << cleanQueue_[i]->CSVInfo() << endl;
	}

	for (unsigned int i = 0; i < dirtyQueue_.size(); i++) {
		out << dirtyQueue_[i]->CSVInfo() << endl;
	}

	for (unsigned int i = 0; i < removedQueue_.size(); i++) {
		out << removedQueue_[i]->CSVInfo() << endl;
	}

	out.close();
}

void ClothingQueue::addItemToWardrobe(ClothingItem *item) {
	if (item->getActive()) {
		if (item->getNumWearsLeft() > 0 || !item->getGetsDirty()) {
			cleanQueue_.push_back(item);
		} else {
			dirtyQueue_.push_back(item);
		}
	} else {
		removedQueue_.push_back(item);
	}
}

void ClothingQueue::viewQueue() {
  string type;
  cout << "Input item type:\n";
  cout << "O: outerwear\n";
  cout << "D: dress\n";
  cout << "T: top\n";
  cout << "B: bottom\n";
  cout << "S: shoe\n";
  cout << "A: all\n";
  getline(cin, type);

  if (type.compare("a") == 0 || type.compare("A") == 0) {
  	printAllItems();
  } else {
  	printItemsOfType(ClothingItem::getItemType(type));
  }
}

void ClothingQueue::printAllItems() {
	if (cleanQueue_.size() > 0) {
		cout << "------- ITEMS IN CLEAN QUEUE ------\n";
		for (unsigned int i = 0; i < cleanQueue_.size(); i++) {
			ClothingItem *item = cleanQueue_[i];
			cout << item->shortInfo();
			if (item->getGetsDirty()) {
				cout << " - " << cleanQueue_[i]->getNumWearsLeft();
				cout << " wears left";
			}
			cout << endl;
		}
		cout << endl;
	}

	if (dirtyQueue_.size() > 0) {
		cout << "------- ITEMS IN DIRTY QUEUE ------\n";
		for (unsigned int i = 0; i < dirtyQueue_.size(); i++) {
			cout << dirtyQueue_[i]->shortInfo() << endl;
		}
		cout << endl;
	}

	if (removedQueue_.size() > 0) {
		cout << "------- ITEMS IN REMOVED QUEUE ------\n";
		for (unsigned int i = 0; i < dirtyQueue_.size(); i++) {
			cout << dirtyQueue_[i]->shortInfo() << endl;
		}
		cout << endl;	
	}
}

void ClothingQueue::printItemsOfType(ItemType type) {
	if (cleanQueue_.size() > 0) {
		cout << "------- ITEMS IN CLEAN QUEUE ------\n";
		for (unsigned int i = 0; i < cleanQueue_.size(); i++) {
			ClothingItem *item = cleanQueue_[i];
			if (item->getType() == type) {
				ClothingItem *item = cleanQueue_[i];
				cout << item->shortInfo();
				if (item->getGetsDirty()) {
					cout << " - " << cleanQueue_[i]->getNumWearsLeft();
					cout << " wears left";
				}
				cout << endl;
			}
		}
		cout << endl;
	}

	if (dirtyQueue_.size() > 0) {
		cout << "------- ITEMS IN DIRTY QUEUE ------\n";
		for (unsigned int i = 0; i < dirtyQueue_.size(); i++) {
			ClothingItem *item = dirtyQueue_[i];
			if (item->getType() == type) {
				cout << item->shortInfo() << endl;
			}
		}
		cout << endl;
	}

	if (removedQueue_.size() > 0) {
		cout << "------- ITEMS IN REMOVED QUEUE ------\n";
		for (unsigned int i = 0; i < dirtyQueue_.size(); i++) {
			ClothingItem *item = removedQueue_[i];
			if (item->getType() == type) {
				cout << item->shortInfo() << endl;
			}
		}
		cout << endl;	
	}
}

void ClothingQueue::pickItemManually() {
  string typeS;
  cout << "Input item type:\n";
  cout << "O: outerwear\n";
  cout << "D: dress\n";
  cout << "T: top\n";
  cout << "B: bottom\n";
  cout << "S: shoe\n";
  getline(cin, typeS);
  ItemType type = ClothingItem::getItemType(typeS);

  string confirmation = "";
  vector<int> validItems;
  int chosenIndex;

  while (confirmation.compare("y") != 0 && confirmation.compare("Y") != 0) {
  	  int validCounter = 0;
	  for (unsigned int i = 0; i < cleanQueue_.size(); i++) {
	  	ClothingItem *item = cleanQueue_[i];
	  	if (item->getType() == type) {
	  		cout << validCounter << ": " << item->shortInfo() << endl;
	  		validItems.push_back(i);
	  		validCounter++;
	  	}
	  }
	  string whichPiece;
	  cout << "Which piece would you like to pick?\n";
	  getline(cin, whichPiece);

	  if (whichPiece.compare("q") == 0 || whichPiece.compare("Q") == 0) {
	  	return;
	  }

	  int index = atoi(whichPiece.c_str());
	  chosenIndex = validItems[index];

	  cout << "Choose this piece: " << cleanQueue_[chosenIndex]->shortInfo() << "?\n";
	  getline(cin, confirmation);
  }

  wearPiece(chosenIndex);

  updateDatabase();
}

bool ClothingQueue::newPieceMatchesOutfit(Outfit *originalOutfit, ClothingItem *newItem) {
  bool result = true;

  if (!newItem->matches(originalOutfit->getPrimaryTop())) {
    result = false;
  }

  if (originalOutfit->hasSecondaryTop() && !newItem->matches(originalOutfit->getSecondaryTop())) {
    result = false;
  }

  if (originalOutfit->hasOuterwear() && !newItem->matches(originalOutfit->getOuterwear())) {
    result = false;
  }

  if (originalOutfit->hasBottom() && !newItem->matches(originalOutfit->getBottom())) {
  	result = false;
  }

  if (originalOutfit->hasShoes() && !newItem->matches(originalOutfit->getShoes())) {
  	result = false;
  }

  return result;
}

void ClothingQueue::returnItemToQueue() {
  string confirmation = "";
  int index;

  while (confirmation.compare("y") != 0 && confirmation.compare("Y") != 0) {
  	for (unsigned int i = 0; i < dirtyQueue_.size(); i++) {
  		cout << i << ": " << dirtyQueue_[i]->shortInfo() << endl;
  	}

  	string whichPiece;
  	cout << "Which piece would you like to return?\n";
  	getline(cin, whichPiece);

	if (whichPiece.compare("q") == 0 || whichPiece.compare("Q") == 0) {
 		return;
	}

	index = atoi(whichPiece.c_str());
	cout << "Choose this piece: " << dirtyQueue_[index]->shortInfo() << "?\n";
	getline(cin, confirmation);
  }

  returnPiece(index);
  updateDatabase();
}

void ClothingQueue::wearPiece(int indexInCleanQueue) {
	ClothingItem *item = cleanQueue_[indexInCleanQueue];
	cout << "Wearing " << item->shortInfo() << endl;

	if (item->getGetsDirty()) {
		item->decreaseWears();

		if (item->getNumWearsLeft() > 0) {
			cleanQueue_.push_back(item);
		} else {
			cout << "You should wash this item after wearing.\n";
			dirtyQueue_.push_back(item);
		}
	} else {
		cleanQueue_.push_back(item);
	}

	cleanQueue_.erase(cleanQueue_.begin() + indexInCleanQueue);
}

void ClothingQueue::returnPiece(int indexInDirtyQueue) {
	ClothingItem *item = dirtyQueue_[indexInDirtyQueue];

	item->resetWears();

	cleanQueue_.push_back(item);

	dirtyQueue_.erase(dirtyQueue_.begin() + indexInDirtyQueue);
}

void ClothingQueue::pickOutfit() {
	OutfitRequirements requirements = getOutfitRequirements();

	Outfit *finalOutfit = getTopPart(requirements, false);
	if (finalOutfit == NULL) {
		cout << "There were no outfits that worked, possibly due to cold.\n";
		cout << "Wear the following suggestions with a thermal top underneath.\n";
		finalOutfit = getTopPart(requirements, true);
	}

	if (finalOutfit == NULL) {
		cout << "Error in picking top part of outfit.\n";
		return;
	}

	finalOutfit = addOuterwear(finalOutfit, requirements);

	if (finalOutfit == NULL) {
		cout << "Error in picking outerwear.\n";
		return;
	}

	finalOutfit = addBottom(finalOutfit, requirements);

	if (finalOutfit == NULL) {
		cout << "Error in picking bottom.\n";
		return;
	}

	finalOutfit = addShoes(finalOutfit, requirements);

	if (finalOutfit == NULL) {
		cout << "Error in picking shoes.\n";
		return;
	}

	cout << "\nYour outfit:\n";
	finalOutfit->printInformation();

	cout << "Are you sure you want to wear this?\n";
	string confirmation;
	getline(cin, confirmation);
	if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
		wearOutfit(finalOutfit);
		updateDatabase();
	}
}

void ClothingQueue::wearOutfit(Outfit *outfit) {
	vector<int> indices;

	indices.push_back(outfit->getPrimaryTopIndex());

	if (outfit->hasSecondaryTop()) {
		indices.push_back(outfit->getSecondaryTopIndex());
	}

	if (outfit->hasOuterwear()) {
		indices.push_back(outfit->getOuterwearIndex());
	}

	indices.push_back(outfit->getBottomIndex());
	indices.push_back(outfit->getShoesIndex());

	sort(indices.begin(), indices.end(), greater<int>());

	for (unsigned int i = 0; i < indices.size(); i++) {
		wearPiece(indices[i]);
	}
}

Outfit *ClothingQueue::getTopPart(OutfitRequirements requirements, bool thermalTop) {
	unsigned int indexInCleanQueue = 0;
	cout << "You will be presented with some options for tops. Type y if you want to wear it.\n";
	Outfit *result = new Outfit();
	bool hasFoundOutfit = false;

	while (!hasFoundOutfit && indexInCleanQueue < cleanQueue_.size()) {
		ClothingItem *item = cleanQueue_[indexInCleanQueue];
		if (item != NULL) {
			while (!((item->getType() == TOP || item->getType() == DRESS) 
				&& item->fitsRequirementsExceptTemp(requirements)) && 
				indexInCleanQueue + 1 < cleanQueue_.size()) {
				indexInCleanQueue ++;
				item = cleanQueue_[indexInCleanQueue];
			} 

			if ((item->getType() == TOP || item->getType() == DRESS) 
				&& item->fitsRequirementsExceptTemp(requirements)) {
				Outfit *potentialOutfit = new Outfit();
				potentialOutfit->setPrimaryTop(indexInCleanQueue, item);
				if (thermalTop) {
					potentialOutfit->addThermalTop();
				}

				if (requirements.highTemp <= item->getMaxTemp() && requirements.highTemp >= item->getMinTemp()) {
					string confirmation;
					cout << endl << item->shortInfo() << "? ";
					getline(cin, confirmation);
					if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
						result = potentialOutfit;
						hasFoundOutfit = true;
					} 
				} else if (requirements.highTemp <= item->getMinTemp()) {
					Outfit *matchedWithTop = findTopMatch(indexInCleanQueue, item, requirements, thermalTop);
					if (matchedWithTop != NULL) {
						hasFoundOutfit = true;
						result = matchedWithTop;
					}
				}
			}

			indexInCleanQueue ++;
		}
	}

	if (!hasFoundOutfit) {
		return NULL;
	}

	return result;
}

Outfit *ClothingQueue::findTopMatch(int primaryIndexInQueue, ClothingItem *item, OutfitRequirements requirements, bool thermalTop) {
	unsigned int indexInCleanQueue = 0;

	Outfit *result;
	bool hasFoundMatch = false;
	bool isFirstMatch = true;

	while (!hasFoundMatch && indexInCleanQueue < cleanQueue_.size()) {
		ClothingItem *potentialMatch = cleanQueue_[indexInCleanQueue];

		while (((potentialMatch->getType() != TOP && potentialMatch->getType() != DRESS && potentialMatch->getType() != OUTERWEAR)
			|| !potentialMatch->fitsRequirementsExceptTemp(requirements) 
			|| (potentialMatch->getItemID() == item->getItemID())
			|| !(item->matches(potentialMatch)))
			&& indexInCleanQueue + 1 < cleanQueue_.size()) {
			indexInCleanQueue ++;
			potentialMatch = cleanQueue_[indexInCleanQueue];
		}

		if (!((potentialMatch->getType() != TOP && potentialMatch->getType() != DRESS && potentialMatch->getType() != OUTERWEAR)
			|| !potentialMatch->fitsRequirementsExceptTemp(requirements) 
			|| (potentialMatch->getItemID() == item->getItemID())
			|| !(item->matches(potentialMatch)))) {
			Outfit *potentialOutfit = new Outfit();
			potentialOutfit->setPrimaryTop(primaryIndexInQueue, item);
			potentialOutfit->setSecondaryTop(indexInCleanQueue, potentialMatch);

			if (thermalTop) {
				potentialOutfit->addThermalTop();
			}

			if (requirements.highTemp <= potentialOutfit->equivalentTopMaxTemp() 
				&& requirements.highTemp >= potentialOutfit->equivalentTopMinTemp()
				&& potentialMatch != NULL) {
				if (isFirstMatch) {
					cout << "\nThis top needs a match:\n";
					cout << item->shortInfo() << endl;
				}

				string confirmation;
				cout << potentialMatch->shortInfo() << "(" << potentialOutfit->equivalentTopMinTemp();
				cout << "-" << potentialOutfit->equivalentTopMaxTemp() << " F)? ";
				getline(cin, confirmation);
				if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
					hasFoundMatch = true;
					result = potentialOutfit;
				} else if (confirmation.compare("q") == 0 || confirmation.compare("Q") == 0) {
					return NULL;
				}

				isFirstMatch = false;
			}
		}

		indexInCleanQueue++;
	}

	if (!hasFoundMatch) {
		return NULL;
	}

 	return result;
}

Outfit *ClothingQueue::addOuterwear(Outfit *originalOutfit, OutfitRequirements requirements) {
	Outfit *result;

	if (requirements.lowTemp < originalOutfit->equivalentTopMaxTemp() &&
		requirements.lowTemp > originalOutfit->equivalentTopMinTemp()) {
		cout << "Doesn't need outerwear.\n";
		result = originalOutfit;
	} else {
		cout << "\nPick outerwear for this outfit. Wear outerwear when less than ";
		cout << originalOutfit->equivalentTopMinTemp() << " deg out.\n";
		unsigned int indexInCleanQueue = 0;
		bool hasFoundOuterwear = false;

		while (!hasFoundOuterwear && indexInCleanQueue < cleanQueue_.size()) {
			ClothingItem *potentialOuterwear = cleanQueue_[indexInCleanQueue];
			int secondaryTopID = -1;
			if (originalOutfit->hasSecondaryTop()) {
				secondaryTopID = originalOutfit->getSecondaryTop()->getItemID();
			}

			while (!(potentialOuterwear->getType() == OUTERWEAR 
				&& potentialOuterwear->fitsRequirementsExceptTemp(requirements)
				&& newPieceMatchesOutfit(originalOutfit, potentialOuterwear)
				&& (potentialOuterwear->getItemID() != secondaryTopID))
				&& indexInCleanQueue + 1 < cleanQueue_.size()) {
				indexInCleanQueue ++;
				potentialOuterwear = cleanQueue_[indexInCleanQueue];
			}

			if (potentialOuterwear->getType() == OUTERWEAR 
				&& potentialOuterwear->fitsRequirementsExceptTemp(requirements)
				&& newPieceMatchesOutfit(originalOutfit, potentialOuterwear)
				&& (potentialOuterwear->getItemID() != secondaryTopID)) {
				Outfit *potentialOutfit = new Outfit();
				potentialOutfit->setPrimaryTop(originalOutfit->getPrimaryTopIndex(), 
					originalOutfit->getPrimaryTop());
				potentialOutfit->setSecondaryTop(originalOutfit->getSecondaryTopIndex(), 
					originalOutfit->getSecondaryTop());
				potentialOutfit->setOuterwear(indexInCleanQueue, potentialOuterwear);
				if (originalOutfit->hasThermalTop()) {
					potentialOutfit->addThermalTop();
				}

				//cout << potentialOuterwear->shortInfo() << ": ";
				//cout << potentialOutfit->equivalentTopMinTemp() << "-" << potentialOutfit->equivalentTopMaxTemp() << endl;

				if (requirements.lowTemp <= potentialOutfit->equivalentTopMaxTemp() 
					&& requirements.lowTemp >= potentialOutfit->equivalentTopMinTemp()) {
					string confirmation;
					cout << potentialOuterwear->shortInfo() << "? ";
					getline(cin, confirmation);
					if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
						hasFoundOuterwear = true;
						result = potentialOutfit;
					} else if (confirmation.compare("q") == 0 || confirmation.compare("Q") == 0) {
						return NULL;
					}
				}
			}

			indexInCleanQueue++;
		}

		if (!hasFoundOuterwear) {
			return NULL;
		}
	}

	return result;
}

Outfit *ClothingQueue::addBottom(Outfit *originalOutfit, OutfitRequirements requirements) {
	Outfit *result;

	if (originalOutfit->getPrimaryTop()->getType() != DRESS) {
		cout << "\nPick a bottom for this outfit.\n";
		unsigned int indexInCleanQueue = 0;
		bool hasFoundBottom = false;

		while (!hasFoundBottom && indexInCleanQueue < cleanQueue_.size()) {
			ClothingItem *potentialBottom = cleanQueue_[indexInCleanQueue];

			while (!(potentialBottom->getType() == BOTTOM 
				&& potentialBottom->fitsRequirementsExceptTemp(requirements)
				&& newPieceMatchesOutfit(originalOutfit, potentialBottom))
				&& indexInCleanQueue + 1 < cleanQueue_.size()) {
				indexInCleanQueue ++;
				potentialBottom = cleanQueue_[indexInCleanQueue];
			}

			if (potentialBottom->getType() == BOTTOM 
				&& potentialBottom->fitsRequirementsExceptTemp(requirements)
				&& newPieceMatchesOutfit(originalOutfit, potentialBottom)) {
				Outfit *potentialOutfit = new Outfit();
				potentialOutfit->setPrimaryTop(originalOutfit->getPrimaryTopIndex(), 
					originalOutfit->getPrimaryTop());
				potentialOutfit->setSecondaryTop(originalOutfit->getSecondaryTopIndex(), 
					originalOutfit->getSecondaryTop());
				potentialOutfit->setOuterwear(originalOutfit->getOuterwearIndex(), originalOutfit->getOuterwear());
				potentialOutfit->setBottom(indexInCleanQueue, potentialBottom);

				if (requirements.lowTemp <= potentialOutfit->equivalentBottomMaxTemp() 
					&& requirements.lowTemp >= potentialOutfit->equivalentBottomMinTemp()) {
					string confirmation;
					cout << potentialBottom->shortInfo() << "? ";
					getline(cin, confirmation);
					if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
						hasFoundBottom = true;
						result = potentialOutfit;
					} else if (confirmation.compare("q") == 0 || confirmation.compare("Q") == 0) {
						return NULL;
					}
				} else {
					potentialOutfit->addThermalBottom();
					
					if (requirements.lowTemp <= potentialOutfit->equivalentBottomMaxTemp() &&
						requirements.lowTemp >= potentialOutfit->equivalentBottomMinTemp()) {
						string confirmation;
						cout << potentialBottom->shortInfo() << ", with thermal bottom? ";
						getline(cin, confirmation);
						if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
							hasFoundBottom = true;
							result = potentialOutfit;
						} else if (confirmation.compare("q") == 0 || confirmation.compare("Q") == 0) {
							return NULL;
						}
					}
				}
			}

			indexInCleanQueue++;
		}

		if (!hasFoundBottom) {
			return NULL;
		}
	} else {
		cout << "Wearing a dress; don't need bottom part.\n";
		if (requirements.lowTemp < originalOutfit->equivalentBottomMinTemp()) {
			originalOutfit->addThermalBottom();
			cout << "Wear thermal tights with this.\n";
		}
		result = originalOutfit;
	}

	return result;
}

Outfit *ClothingQueue::addShoes(Outfit *originalOutfit, OutfitRequirements requirements) {
	Outfit *result;

	cout << "\nPick shoes for this outfit.\n";
	unsigned int indexInCleanQueue = 0;
	bool hasFoundShoes = false;

	while (!hasFoundShoes && indexInCleanQueue < cleanQueue_.size()) {
		ClothingItem *potentialShoes = cleanQueue_[indexInCleanQueue];

		while (!(potentialShoes->getType() == SHOE 
			&& potentialShoes->fitsRequirementsExceptTemp(requirements)
			&& newPieceMatchesOutfit(originalOutfit, potentialShoes))
			&& indexInCleanQueue + 1 < cleanQueue_.size()) {
			indexInCleanQueue ++;
			potentialShoes = cleanQueue_[indexInCleanQueue];
		}

		if (potentialShoes->getType() == SHOE 
			&& potentialShoes->fitsRequirementsExceptTemp(requirements)
			&& newPieceMatchesOutfit(originalOutfit, potentialShoes)) {
			Outfit *potentialOutfit = new Outfit();
			potentialOutfit->setPrimaryTop(originalOutfit->getPrimaryTopIndex(), 
				originalOutfit->getPrimaryTop());
			potentialOutfit->setSecondaryTop(originalOutfit->getSecondaryTopIndex(), 
				originalOutfit->getSecondaryTop());
			potentialOutfit->setOuterwear(originalOutfit->getOuterwearIndex(), originalOutfit->getOuterwear());
			potentialOutfit->setBottom(originalOutfit->getBottomIndex(), originalOutfit->getBottom());
			potentialOutfit->setShoes(indexInCleanQueue, potentialShoes);

			if (requirements.lowTemp <= potentialOutfit->equivalentFootMaxTemp() 
				&& requirements.lowTemp >= potentialOutfit->equivalentFootMinTemp()) {
				string confirmation;
				cout << potentialShoes->shortInfo() << "? ";
				getline(cin, confirmation);
				if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
					hasFoundShoes = true;
					result = potentialOutfit;
				} else if (confirmation.compare("q") == 0 || confirmation.compare("Q") == 0) {
					return NULL;
				}
			} else {
				potentialOutfit->addSocks();

				if (requirements.lowTemp <= potentialOutfit->equivalentFootMaxTemp() &&
					requirements.lowTemp >= potentialOutfit->equivalentFootMinTemp()) {
					string confirmation;
					cout << potentialShoes->shortInfo() << ", with socks? ";
					getline(cin, confirmation);
					if (confirmation.compare("y") == 0 || confirmation.compare("Y") == 0) {
						hasFoundShoes = true;
						result = potentialOutfit;
					} else if (confirmation.compare("q") == 0 || confirmation.compare("Q") == 0) {
						return NULL;
					}
				}
			}
		}

		indexInCleanQueue++;
	}

	if (!hasFoundShoes) {
		return NULL;
	}

	return result;
}

bool ClothingQueue::getTrueOrFalse(string yesOrNo) {
  bool result;

  if (yesOrNo.compare("yes") == 0 || yesOrNo.compare("y") == 0 || yesOrNo.compare("Y") == 0) {
    result = true;
  } else {
    result = false;
  }

  return result;
}

OutfitRequirements ClothingQueue::getOutfitRequirements() {
	OutfitRequirements requirements;

	string high;
	cout << "What is the high for the day?\n";
	getline(cin, high);
	requirements.highTemp = atoi(high.c_str());

	string low;
	cout << "What is the low for the day?\n";
	getline(cin, low);
	requirements.lowTemp = atoi(low.c_str());

	string rain;
	cout << "Will it rain today, or will you walk in puddles?\n";
	getline(cin, rain);
	requirements.willRain = getTrueOrFalse(rain);

	string snow;
	cout << "Will it snow today, or will you walk in snow or ice?\n";
	getline(cin, snow);
	requirements.willSnow = getTrueOrFalse(snow);

	string walk;
	cout << "Will you walk a lot today?\n";
	getline(cin, walk);
	requirements.willWalk = getTrueOrFalse(walk);

	cout << "The following are various formalities of outfits.\n";
	cout << "Indicate whether you will need an outfit of this formality.\n";

	string formality;
	cout << "Very casual: outdoor activities: ";
	getline(cin, formality);
	requirements.formalities[0] = getTrueOrFalse(formality);

	cout << "Casual: class or hanging out with friends: ";
	getline(cin, formality);
	requirements.formalities[1] = getTrueOrFalse(formality);

	cout << "Semi-casual: work or presentation: ";
	getline(cin, formality);
	requirements.formalities[2] = getTrueOrFalse(formality);

	cout << "Formal: interview: ";
	getline(cin, formality);
	requirements.formalities[3] = getTrueOrFalse(formality);

	cout << "Very formal: fancy dinner or event: ";
	getline(cin, formality);
	requirements.formalities[4] = getTrueOrFalse(formality);

	return requirements;
}