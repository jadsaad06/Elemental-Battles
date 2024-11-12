#include "myutil.h"
#include "player.h"
#include "deck.h"

class FileNotFoundException : public runtime_error {
public:
    FileNotFoundException(const string& message) : runtime_error(message) {}
};

void displayInstructions();
bool getOption(char& option);
void initializePlayer(string& name, Type& type);
void beginGame(Player&, Player&);
int makeMove(int num1, int num2);
vector<Offense*> loadOffDeckFromFile(const string& filename);
vector<Defense*> loadDefDeckFromFile(const string& filename);
vector<Support*> loadSupDeckFromFile(const string& filename);
Type stringToType(const string&);
Type stringToType(const string&);
