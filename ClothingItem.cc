#include "ClothingItem.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

ClothingItem::ClothingItem(string csvClothingData) {
  vector<string> itemElements;

  split(csvClothingData, ',', itemElements);

  id_ = atoi(itemElements[0].c_str());
  type_ = getItemType(itemElements[1]);
  style_ = itemElements[2];
  color_ = itemElements[3];
  brand_ = itemElements[4];
  getsDirty_ = atoi(itemElements[5].c_str());
  numWearsLeft_ = atoi(itemElements[6].c_str());
  maxWears_ = atoi(itemElements[7].c_str());
  minTemp_ = atoi(itemElements[8].c_str());
  maxTemp_ = atoi(itemElements[9].c_str());
  rainAppropriate_ = atoi(itemElements[10].c_str());
  snowAppropriate_ = atoi(itemElements[11].c_str());
  walkAppropriate_ = atoi(itemElements[12].c_str());

  appropriateEvents_[0] = atoi(itemElements[13].c_str());
  appropriateEvents_[1] = atoi(itemElements[14].c_str());
  appropriateEvents_[2] = atoi(itemElements[15].c_str());
  appropriateEvents_[3] = atoi(itemElements[16].c_str());
  appropriateEvents_[4] = atoi(itemElements[17].c_str());

  active_ = atoi(itemElements[18].c_str());

  for (unsigned int i = 19; i < itemElements.size(); i++) {
    nonMatches_.push_back(atoi(itemElements[i].c_str()));
  }
}

string ClothingItem::CSVInfo() {
  string result = intToString(id_) + "," + typeAsString(type_);
  result += "," + style_;
  result += "," + color_;
  result += "," + brand_;
  result += "," + intToString(getsDirty_);
  result += "," + intToString(numWearsLeft_);
  result += "," + intToString(maxWears_);
  result += "," + intToString(minTemp_);
  result += "," + intToString(maxTemp_);
  result += "," + intToString(rainAppropriate_);
  result += "," + intToString(snowAppropriate_);
  result += "," + intToString(walkAppropriate_);
  result += "," + intToString(appropriateEvents_[0]); 
  result += "," + intToString(appropriateEvents_[1]); 
  result += "," + intToString(appropriateEvents_[2]);
  result += "," + intToString(appropriateEvents_[3]);
  result += "," + intToString(appropriateEvents_[4]);
  result += "," + intToString(active_);

  for (unsigned int i = 0; i < nonMatches_.size(); i++) {
    result += "," + intToString(nonMatches_[i]);
  }

  return result;
}

ClothingItem::ClothingItem(int id) : id_(id) {
  active_ = true;

  // Get the basic information about the item.
  string type;
  cout << "Input item type:\n";
  cout << "O: outerwear\n";
  cout << "D: dress\n";
  cout << "T: top\n";
  cout << "B: bottom\n";
  cout << "S: shoe\n";
  getline(cin, type);
  type_ = getItemType(type);

  cout << "Input item style:\n";
  getline(cin, style_);

  cout << "Input item color:\n";
  getline(cin, color_);

  cout << "Input item brand:\n";
  getline(cin, brand_);

  cout << "Input warmest temperature it can be worn alone:\n";
  string maxTemp;
  getline(cin, maxTemp);
  maxTemp_ = atoi(maxTemp.c_str());

  cout << "Input coldest temperature it can be worn alone\n";
  string minTemp;
  getline(cin, minTemp);
  minTemp_ = atoi(minTemp.c_str());

  string snowAppropriate;
  cout << "Can it be worn in snow? [y/n]\n";
  getline(cin, snowAppropriate);
  snowAppropriate_ = getTrueOrFalse(snowAppropriate);

  string rainAppropriate;
  cout << "Can it be worn in rain? [y/n]\n";
  getline(cin, rainAppropriate);
  rainAppropriate_ = getTrueOrFalse(rainAppropriate);

  string walkAppropriate;
  cout << "Can you walk a lot in it? [y/n]\n";
  getline(cin, walkAppropriate);
  walkAppropriate_ = getTrueOrFalse(walkAppropriate);

  string shouldBeWashed;
  cout << "Should it be washed often?\n";
  getline(cin, shouldBeWashed);
  getsDirty_ = getTrueOrFalse(shouldBeWashed);

  if (getsDirty_) {
    cout << "How many wears can it get before washing?\n";
    string maxWears;
    getline(cin, maxWears);
    maxWears_ = atoi(maxWears.c_str());
    numWearsLeft_ = maxWears_;
  } else {
    maxWears_ = -1;
    numWearsLeft_ = -1;
  }

  string eventAppropriate;

  cout << "The following questions ask about events you can wear the item.\n";
  cout << "Very informal: playing outside, hiking, physical work.\n";
  getline(cin, eventAppropriate);
  appropriateEvents_[0] = getTrueOrFalse(eventAppropriate);

  cout << "Informal: staying at home, with friends/family.\n";
  getline(cin, eventAppropriate);
  appropriateEvents_[1] = getTrueOrFalse(eventAppropriate);

  cout << "Casual: work, class.\n";
  getline(cin, eventAppropriate);
  appropriateEvents_[2] = getTrueOrFalse(eventAppropriate);

  cout << "Formal: interview, professional event.\n";
  getline(cin, eventAppropriate);
  appropriateEvents_[3] = getTrueOrFalse(eventAppropriate);

  cout << "Very formal: fancy dinner or event.\n";
  getline(cin, eventAppropriate);
  appropriateEvents_[4] = getTrueOrFalse(eventAppropriate);
}

std::vector<std::string> &ClothingItem::split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
      elems.push_back(item);
  }
  return elems;
}

int ClothingItem::getItemID() {
  return id_;
}

bool ClothingItem::getActive() {
  return active_;
}

int ClothingItem::getNumWearsLeft() {
  return numWearsLeft_;
}

ItemType ClothingItem::getType() {
  return type_;
}

bool ClothingItem::getGetsDirty() {
  return getsDirty_;
}

int ClothingItem::getMaxTemp() {
  return maxTemp_;
}

int ClothingItem::getMinTemp() {
  return minTemp_;
}

void ClothingItem::decreaseWears() {
  numWearsLeft_ --;
}

void ClothingItem::resetWears() {
  numWearsLeft_ = maxWears_;
}

string ClothingItem::shortInfo() {
  return color_ + " " + style_ + " from " + brand_ + " (" + typeAsString(type_) + ")";
}

bool ClothingItem::matches(ClothingItem *comparedItem) {
  return find(nonMatches_.begin(), nonMatches_.end(), comparedItem->getItemID()) == nonMatches_.end();
}

string ClothingItem::typeAsString(ItemType type) {
  string result;

  if (type == OUTERWEAR) {
    result = "OUTERWEAR";
  } else if (type == BOTTOM) {
    result = "BOTTOM";
  } else if (type == DRESS) {
    result = "DRESS";
  } else if (type == SHOE) {
    result = "SHOE";
  } else {
    result = "TOP";
  }

  return result;
}

bool ClothingItem::getTrueOrFalse(string yesOrNo) {
  bool result;

  if (yesOrNo.compare("yes") == 0 || yesOrNo.compare("y") == 0 || yesOrNo.compare("Y") == 0) {
    result = true;
  } else {
    result = false;
  }

  return result;
}

ItemType ClothingItem::getItemType(string type) {
  ItemType result;

  if (type.compare("OUTERWEAR") == 0 || type.compare("o") == 0 || type.compare("O") == 0) {
    result = OUTERWEAR;
  } else if (type.compare("DRESS") == 0 || type.compare("d") == 0 || type.compare("D") == 0) {
    result = DRESS;
  } else if (type.compare("TOP") == 0 || type.compare("t") == 0 || type.compare("T") == 0) {
    result = TOP;
  } else if (type.compare("BOTTOM") == 0 || type.compare("b") == 0 || type.compare("B") == 0) {
    result = BOTTOM;
  } else if (type.compare("SHOE") == 0 || type.compare("s") == 0 || type.compare("S") == 0) {
    result = SHOE;
  } else {
    result = TOP;
  }

  return result;
}

void ClothingItem::addNonMatch(string response, ClothingItem *comparedItem) {
  bool isMatch = getTrueOrFalse(response);

  if (!isMatch) {
    nonMatches_.push_back(comparedItem->getItemID());
  }
}

string ClothingItem::intToString(int i) {
  stringstream ss;
  ss << i;
  return ss.str();
}

bool ClothingItem::fitsRequirementsExceptTemp(OutfitRequirements requirements) {
  bool result = true;
  
  if (requirements.willSnow && !snowAppropriate_) {
    result = false;
  }

  if (requirements.willRain && !rainAppropriate_) {
    result = false;
  }

  if (requirements.willWalk && !walkAppropriate_) {
    result = false;
  }

  for (int i = 0; i < 5; i++) {
    if (requirements.formalities[i] && !appropriateEvents_[i]) {
      result = false;
    }
  }

  return result;
}