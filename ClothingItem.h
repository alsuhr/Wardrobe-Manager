#ifndef CLOTHING_ITEM_H_
#define CLOTHING_ITEM_H_
#include <vector>
#include <string>

struct  {
  int highTemp;
  int lowTemp;
  bool willRain;
  bool willSnow;
  bool willWalk;

  bool formalities[5];
} typedef OutfitRequirements;

enum ItemType {
  TOP,
  BOTTOM,
  SHOE,
  OUTERWEAR,
  DRESS
};

class ClothingItem {
public: 
  ClothingItem(std::string csvClothingData);
  ClothingItem(int id);
  ClothingItem();

  void addNonMatch(std::string response, ClothingItem *comparedItem);

  std::string shortInfo();
  std::string CSVInfo();

  static std::string typeAsString(ItemType type);
  static ItemType getItemType(std::string type);

  int getItemID();
  bool getActive();
  int getNumWearsLeft();
  ItemType getType();
  bool getGetsDirty();
  int getMaxTemp();
  int getMinTemp();

  void decreaseWears();
  void resetWears();

  bool matches(ClothingItem *comparedItem);

  bool fitsRequirementsExceptTemp(OutfitRequirements requirements);

private:

  std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

  bool getTrueOrFalse(std::string yesOrNo);
  std::string intToString(int i);

  int id_;

  bool active_;

  ItemType type_;
  std::string style_;
  std::string color_;
  std::string brand_;

  int numWearsLeft_;
  int maxWears_;
  bool getsDirty_;

  int minTemp_;
  int maxTemp_;

  bool appropriateEvents_[5];

  bool rainAppropriate_;
  bool snowAppropriate_;
  bool walkAppropriate_;

  std::vector<int> nonMatches_;
};

#endif /* CLOTHING_ITEM_H_ */
