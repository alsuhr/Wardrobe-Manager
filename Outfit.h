#ifndef OUTFIT_H_
#define OUTFIT_H_
#include "ClothingItem.h"

class Outfit {
public:
	void setPrimaryTop(int indexInCleanQueue, ClothingItem *item);
	void setSecondaryTop(int indexInCleanQueue, ClothingItem *item);
	void setOuterwear(int indexInCleanQueue, ClothingItem *item);
	void setBottom(int indexInCleanQueue, ClothingItem *item);
	void setShoes(int indexInCleanQueue, ClothingItem *item);

	void addThermalBottom();
	void addSocks();
	void addThermalTop();

	void printInformation();

	int equivalentTopMaxTemp();
	int equivalentTopMinTemp();

	int equivalentBottomMaxTemp();
	int equivalentBottomMinTemp();

	int equivalentFootMaxTemp();
	int equivalentFootMinTemp();

	bool hasSecondaryTop();
	bool hasOuterwear();
	bool hasBottom();
	bool hasShoes();

	bool hasThermalTop();

	ClothingItem *getPrimaryTop();
	ClothingItem *getSecondaryTop();
	ClothingItem *getOuterwear();
	ClothingItem *getBottom();
	ClothingItem *getShoes();

	int getPrimaryTopIndex();
	int getSecondaryTopIndex();
	int getOuterwearIndex();
	int getBottomIndex();
	int getShoesIndex();

private:
	ClothingItem *primaryTop_;
	ClothingItem *secondaryTop_;
	ClothingItem *outerwear_;
	ClothingItem *bottom_;
	ClothingItem *shoes_;

	int primaryTopIndex_;
	int secondaryTopIndex_;
	int outerwearIndex_;
	int bottomIndex_;
	int shoesIndex_;

	bool thermalBottom_;
	bool socks_;
	bool thermalTop_;

	static const int THERMAL_DEGREES_HIGH = 20;
	static const int THERMAL_DEGREES_LOW = 40;
	static const int THERMAL_DEGREES_TOP = 20;
};

#endif