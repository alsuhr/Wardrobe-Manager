#ifndef CLOTHING_QUEUE_H_
#define CLOTHING_QUEUE_H_
#include <vector>
#include "ClothingItem.h"
#include "Outfit.h"

class ClothingQueue {
public: 
  ClothingQueue(std::string filename);

  void addNewItem();

  void viewQueue();
  void updateDatabase();
  void pickItemManually();
  void returnItemToQueue();
  void pickOutfit();

private:
  void setItemsMatches(ClothingItem *item);
  void queryNonMatch(ClothingItem *item, ClothingItem *comparedItem);
  void addItemToWardrobe(ClothingItem *item);
  void wearPiece(int indexInCleanQueue);
  void returnPiece(int indexInDirtyQueue);
  OutfitRequirements getOutfitRequirements();

  Outfit *getTopPart(OutfitRequirements requirements, bool thermalTop);
  Outfit *addOuterwear(Outfit *originalOutfit, OutfitRequirements requirements);
  Outfit *addBottom(Outfit *originalOutfit, OutfitRequirements requirements);
  Outfit *addShoes(Outfit *originalOutfit, OutfitRequirements requirements);
  Outfit *findTopMatch(int primaryIndexInQueue, ClothingItem *item, OutfitRequirements requirements, bool thermalTop);

  void wearOutfit(Outfit *outfit);

  void printAllItems();
  void printItemsOfType(ItemType type);

  bool getTrueOrFalse(std::string yesOrNo);

  bool newPieceMatchesOutfit(Outfit *originalOutfit, ClothingItem *newItem);

  std::vector<ClothingItem *> cleanQueue_;
  std::vector<ClothingItem *> dirtyQueue_;
  std::vector<ClothingItem *> removedQueue_;

  int totalNumPieces();

  static const int NUM_POT_OUTFITS_SHOWN = 10;

  std::string filename_;
};

#endif /* CLOTHING_QUEUE_H_ */
