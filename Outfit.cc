#include "Outfit.h"
#include <iostream>
using namespace std;

void Outfit::setPrimaryTop(int indexInCleanQueue, ClothingItem *item) {
	primaryTopIndex_ = indexInCleanQueue;
	primaryTop_ = item;
}

void Outfit::setSecondaryTop(int indexInCleanQueue, ClothingItem *item) {
	secondaryTopIndex_ = indexInCleanQueue;
	secondaryTop_ = item;
}

void Outfit::setOuterwear(int indexInCleanQueue, ClothingItem *item) {
	outerwearIndex_ = indexInCleanQueue;
	outerwear_ = item;
}

void Outfit::setBottom(int indexInCleanQueue, ClothingItem *item) {
	bottomIndex_ = indexInCleanQueue;
	bottom_ = item;
}

void Outfit::setShoes(int indexInCleanQueue, ClothingItem *item) {
	shoesIndex_ = indexInCleanQueue;
	shoes_ = item;
}

void Outfit::addThermalBottom() {
	thermalBottom_ = true;
}

void Outfit::addSocks() {
	socks_ = true;
}

void Outfit::addThermalTop() {
	thermalTop_ = true;
}

ClothingItem *Outfit::getPrimaryTop() {
	return primaryTop_;
}

ClothingItem *Outfit::getSecondaryTop() {
	return secondaryTop_;
}

ClothingItem *Outfit::getOuterwear() {
	return outerwear_;
}

ClothingItem *Outfit::getBottom() {
	return bottom_;
}

ClothingItem *Outfit::getShoes() {
	return shoes_;
}

int Outfit::getPrimaryTopIndex() {
	return primaryTopIndex_;
}

int Outfit::getSecondaryTopIndex() {
	return secondaryTopIndex_;
}

int Outfit::getOuterwearIndex() {
	return outerwearIndex_;
}

int Outfit::getBottomIndex() {
	return bottomIndex_;
}

int Outfit::getShoesIndex() {
	return shoesIndex_;
}

bool Outfit::hasSecondaryTop() {
	return (secondaryTop_ != NULL);
}

bool Outfit::hasOuterwear() {
	return (outerwear_ != NULL);
}

bool Outfit::hasBottom() {
	return (bottom_ != NULL);
}

bool Outfit::hasShoes() {
	return (shoes_ != NULL);
}

bool Outfit::hasThermalTop() {
	return thermalTop_;
}

int Outfit::equivalentTopMaxTemp() {
	int result;
	int max;
	int min;

	if (!hasSecondaryTop()) {
		result = primaryTop_->getMaxTemp();
	} else {
		/* max = primaryTop_->getMaxTemp();
		min = secondaryTop_->getMaxTemp();

		if (secondaryTop_->getMaxTemp() > max) {
			min = max;
			max = secondaryTop_->getMaxTemp();
		}

		result = max - min / 3; */

		result = (secondaryTop_->getMaxTemp() + primaryTop_->getMaxTemp()) / 2.5;
	} 

	if (hasOuterwear()) {
		result -= 30 - outerwear_->getMaxTemp() / 3;
	}

	if (thermalTop_) {
		result -= THERMAL_DEGREES_TOP;
	}

	return result;
}

int Outfit::equivalentTopMinTemp() {
	int result;

	int max;
	int min;

	if (!hasSecondaryTop()) {
		result = primaryTop_->getMinTemp();
	} else {
		/* max = primaryTop_->getMinTemp();
		min = secondaryTop_->getMinTemp();

		if (secondaryTop_->getMinTemp() > max) {
			min = max;
			max = secondaryTop_->getMinTemp();
		}
		result = max - min / 3; */

		result = (secondaryTop_->getMinTemp() + primaryTop_->getMinTemp()) / 2.5;
	}

	if (hasOuterwear()) {
		result -= 30 - outerwear_->getMinTemp() / 3;
	}

	if (thermalTop_) {
		result -= THERMAL_DEGREES_TOP;
	}

	return result;
}

int Outfit::equivalentBottomMinTemp() {
	int result;

	if (hasBottom()) {
		result = bottom_->getMinTemp();
	} else if (primaryTop_->getType() == DRESS) {
		result = primaryTop_->getMinTemp();
	}

	if (thermalBottom_) {
		result -= THERMAL_DEGREES_LOW;
	}

	return result;
}

int Outfit::equivalentBottomMaxTemp() {
	int result;

	if (hasBottom()) {
		result = bottom_->getMaxTemp();
	} else if (primaryTop_->getType() == DRESS) {
		result = primaryTop_->getMaxTemp();
	}

	if (thermalBottom_) {
		result -= THERMAL_DEGREES_HIGH;
	}

	return result;
}

int Outfit::equivalentFootMinTemp() {
	int result = shoes_->getMinTemp();

	if (socks_) {
		result -= THERMAL_DEGREES_LOW;
	}

	return result;
}

int Outfit::equivalentFootMaxTemp() {
	int result = shoes_->getMaxTemp();

	if (socks_) {
		result -= THERMAL_DEGREES_HIGH;
	}

	return result;
}

void Outfit::printInformation() {
	if (primaryTop_ != NULL) {
		cout << primaryTop_->shortInfo();
		if (thermalTop_) {
			cout << " with thermal top";
		}
		cout << endl;
	}

	if (hasSecondaryTop()) {
		cout << secondaryTop_->shortInfo() << endl;
	}

	if (hasOuterwear()) {
		cout << outerwear_->shortInfo() << endl;
	}

	if (hasBottom()) {
		cout << bottom_->shortInfo();
		if (thermalBottom_) {
			cout << " with thermal bottom";
		}
		cout << endl;
	}

	if (hasShoes()) {
		cout << shoes_->shortInfo();
		if (socks_) {
			cout << " with socks";
		}

		cout << endl;
	}
}