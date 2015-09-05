WardrobeManager: WardrobeManager.cc
	g++ -Wall -g -c ClothingItem.cc -o ClothingItem.o
	g++ -Wall -g -c ClothingQueue.cc -o ClothingQueue.o
	g++ -Wall -g -c Outfit.cc -o Outfit.o
	g++ -Wall -g -c  WardrobeManager.cc -o WardrobeManager.o
	g++ -Wall -g ClothingItem.o Outfit.o ClothingQueue.o WardrobeManager.o -lm -o WardrobeManager
	#rm ClothingItem.o
	#rm ClothingQueue.o
	#rm WardrobeManager.o
