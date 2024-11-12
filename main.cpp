//Name: Jad Saad
//Date: 11/10/2024
//Program: 2
//Class: CS302 In-Person

/*
This program is a turn based card game where you fight against your opponent to the death!
You choose between three decks on each turn, attack, defense, or support. Strategically 
swap between each deck to maximum your strategy and best your opponent!

This program uses a DLL for the deck and prioritizes the use of operator overloading to make
the program much friendlier to outside coders.
*/

#include "main.h"
#include "deck.tpp"
#include "card.h"

int main(){
    char option{};
    bool gameStatus = false;

    displayInstructions();

    do{

        //If game is going change prompt
        if(gameStatus){
            cout << "\nWould you like to rematch?\n Y/N: ";
        }else{
            cout << "\nWould you like to begin a game?\n Y/N: ";
        }

        while(!getOption(option)){
            cerr << "\nInput must be 'Y' or 'N'." << endl;
        }

        //begin game
        if(option == 'Y'){
            gameStatus = true;
            string name;
            Type element;
            
            cout << "Player 1:\n";
            initializePlayer(name, element);

            Player player1(name, element);

            cout << "Player 2:\n";
            initializePlayer(name, element);
            Player player2(name, element);

            beginGame(player1, player2);
        }
 

    }while(option != 'N');

    return 0;
}


//Displays instructions
void displayInstructions() {
    cout << "Welcome to Elemental Battle!" << endl;
    cout << "How to Play:" << endl;
    cout << "1. Choose your Player Type:" << endl;
    cout << "   - Water: Strong against Fire, Weak against Plant Cards." << endl;
    cout << "   - Fire:  Strong against Plant, Weak against Water Cards." << endl;
    cout << "   - Plant: Strong against Water, Weak against Fire Cards." << endl;

    cout << "2. Each player starts with three randomly drawn cards from the deck." << endl;
    cout << "   - You can hold a maximum of five cards." << endl;

    cout << "3. Players take turns to either draw a card or use a card." << endl;
    cout << "   - Playing a card consumes energy based on the card's effect." << endl;

    cout << "4. Card Types:" << endl;
    cout << "   - Offensive: Inflicts damage or stuns your opponent. \n\t- Damage varies on the type of card you have as well as the element of the card" << endl;
    cout << "   - Defensive: Provides damage negation or shields." << endl;
    cout << "   - Support: Gains energy or health." << endl;

    cout << "5. Your goal is to reduce your opponent's health to 0!" << endl;
    cout << "6. Good luck and have fun!" << endl;
}


//Input: userChar
//Output: If the input is valid
bool getOption(char& userChar) {
    string input;
    cin >> input;
    input = toupper(input[0]);//validates both upper and lower case

    if (input.length() != 1 || (input[0] != 'Y' && input[0] != 'N')) {
        return false; // Invalid input
    }

    userChar = input[0];
    return true; // Valid input
}


//get all info needed for each player
void initializePlayer(string& name, Type& type){
    char option{};
    
    do{
        cout << "\nInput Desired Name: ";
        cin >> name;

        cout << "\nInputted: " << name;
        cout << "\nAre you sure?\nY/N: ";
        while(!getOption(option)){
            cerr << "\nInput must be 'Y' or 'N'\n";
        }
    }while(option == 'N');
    
    do{
        cout << "\nAvailable Elements:\n"
             << "1. Fire\n2. Water\n3. Plant";

        cout << "\nInput Your Desired Element (1-3): ";  
        cin >> type;

        option = 'N';

        cout << "\nYou entered: ";

        switch(type){
            case 0:
                cout << "Fire";
                break;
            case 1:
                cout << "Water";
                break;
            case 2: 
                cout << "Plant";
                break;
            default:
                cout << "none";
        }; 

            cout << "\nAre you sure?\nY/N: ";

            while(!getOption(option)){
                cerr << "\nInput must be 'Y' or 'N'\n";
        }
    }while(option == 'N');
}


//get input for element
istream& operator>>(istream& input, Type& type){
    int num;
    input >> num;

    while(!cin || num < 1 || num > 3){
        input.clear();
        input.ignore(100, '\n');
        cout << "Invalid Input, Try Again: ";
        input >> num;
    }

    type = static_cast<Type>(num - 1);

    return input;
}


//begin the game

void beginGame(Player& player1, Player& player2) {
    int move = 0;
    Deck<Offense> offDeck(loadOffDeckFromFile("offense_cards.txt"));
    Deck<Defense> defDeck(loadDefDeckFromFile("defense_cards.txt"));
    Deck<Support> supDeck(loadSupDeckFromFile("support_cards.txt"));

    // Play until one player is defeated
    while (player1 && player2) {
        // Player 1's turn
        cout << endl;
        bool turnTaken = false;

        if(player1.isStunned()){
            cout << "\nPlayer Stunned! Turn Skipped.\n";
            turnTaken = true;
            player1.applyStun();
        }

        while (!turnTaken) {
            player1.displayName();
            cout << " make your move...\n";
            cout << "1. Draw Card\n2. Check Stats\n";
            move = makeMove(1, 2);

            switch (move) {
                case 1:
                    cout << "\nWhich deck would you like to draw from?"
                         << "\n1. Attack\n2. Defense\n3. Support\n"
                         << "\nEnter number: ";
                    move = makeMove(1, 3);

                    switch (move) {
                        case 1:
                            player2 += *offDeck.takeCard();
                            break;
                        case 2:
                            player1 += *defDeck.takeCard();
                            break;
                        case 3:
                            player1 += *supDeck.takeCard();
                            break;
                    }
                    turnTaken = true;  // Turn is complete after drawing a card
                    break;

                case 2:
                    cout << player1;  // Show stats - doesn't end turn
                    cout << "\nPress Enter to continue...";
                    cin.ignore(100, '\n');
                    cout << endl;
                    break;
            };
        }

        // Check if player 2 was defeated
        if (!player2) break;

        // Player 2's turn
        cout << endl;
        
        if(player2.isStunned()){
            turnTaken = true;
            player2.applyStun();
            cout << "\nPlayer Stunned! Turn Skipped.\n";
        }else{
            turnTaken = false;
        }

        while (!turnTaken) {
            player2.displayName();
            cout << " make your move...\n";
            cout << "1. Draw Card\n2. Check Stats\n";
            move = makeMove(1, 2);

            switch (move) {
                case 1:
                    cout << "\nWhich deck would you like to draw from?"
                         << "\n1. Attack\n2. Defense\n3. Support\n"
                         << "\nEnter number: ";
                    move = makeMove(1, 3);

                    switch (move) {
                        case 1:
                            player1 += *offDeck.takeCard();
                            break;
                        case 2:
                            player2 += *defDeck.takeCard();
                            break;
                        case 3:
                            player2 += *supDeck.takeCard();
                            break;
                    }
                    turnTaken = true;  // Turn is complete after drawing a card
                    break;

                case 2:
                    cout << player2;  // Show stats - doesn't end turn
                    cout << "\nPress Enter to continue...";
                    cin.ignore(100, '\n');
                    cout << endl;
                    break;
            };
        }
    }
}

// Helper function to convert a string to Type enum
Type stringToType(const string& typeStr) {
    if (typeStr == "fire") return fire;
    if (typeStr == "water") return water;
    if (typeStr == "plant") return plant;
    return fire; // Default case
}

// Helper function to convert a string to Effect enum
Effect stringToEffect(const string& effectStr) {
    if (effectStr == "stun") return stun;
    if (effectStr == "damage") return damage;
    if (effectStr == "shieldGain") return shieldGain;
    if (effectStr == "dmgNegation") return dmgNegation;
    if (effectStr == "healthGain") return healthGain;
    if (effectStr == "energyGain") return energyGain;
    return none; // Default case
}

// Function to load cards from a file into a deck
vector<Offense*> loadOffDeckFromFile(const string& filename) {
    vector<Offense*> deck;
    string line;
    
    try{
        ifstream file(filename);
        if(!file.is_open()){
            throw FileNotFoundException("Error opening file: " + filename);
        }
     
        while (getline(file, line)) {
            stringstream ss(line);
            string name, typeStr, effectStr, prompt;
            int value, energyUsed;

            // Parse the line
            getline(ss, name, ';');
            getline(ss, typeStr, ';');
            getline(ss, effectStr, ';');
            ss >> value;
            ss.ignore(1, ';');  // Ignore the semicolon after value
            ss >> energyUsed;
            ss.ignore(1, ';');  // Ignore the semicolon after energyUsed
            getline(ss, prompt, ';');
            
            // Convert strings to enum types
            Type type = stringToType(typeStr);
            Effect effect = stringToEffect(effectStr);

            Offense* card;

            // Create specific card based on effect type
            if (effect == damage || effect == stun) {
                card = new Offense(name, type, energyUsed, effect, prompt, value);
            }

            // Add card to the deck
            deck.push_back(card);
        }


        file.close();  // Close the file after reading
    } catch (const FileNotFoundException& e) {
        cerr << "\nError: File Not Found\n";
    }

    return deck;
}


vector<Defense*> loadDefDeckFromFile(const string& filename) {
    vector<Defense*> deck;
    string line;
    
    try{
        ifstream file(filename);
        if(!file.is_open()){
            throw FileNotFoundException("Error opening file: " + filename);
        }
     
        while (getline(file, line)) {
            stringstream ss(line);
            string name, typeStr, effectStr, prompt;
            int value, energyUsed;

            // Parse the line
            getline(ss, name, ';');
            getline(ss, typeStr, ';');
            getline(ss, effectStr, ';');
            ss >> value;
            ss.ignore(1, ';');  // Ignore the semicolon after value
            ss >> energyUsed;
            ss.ignore(1, ';');  // Ignore the semicolon after energyUsed
            getline(ss, prompt, ';');
            
            // Convert strings to enum types
            Type type = stringToType(typeStr);
            Effect effect = stringToEffect(effectStr);

            Defense* card;

            // Create specific card based on effect type
            if (effect == shieldGain || effect == dmgNegation) {
                card = new Defense(name, type, energyUsed, effect, prompt, value);
            }

            // Add card to the deck
            deck.push_back(card);
        }


        file.close();  // Close the file after reading
    } catch (const FileNotFoundException& e) {
        cerr << "\nError: File Not Found\n";
    }

    return deck;
}

vector<Support*> loadSupDeckFromFile(const string& filename) {
    vector<Support*> deck;
    string line;
    
    try{
        ifstream file(filename);
        if(!file.is_open()){
            throw FileNotFoundException("Error opening file: " + filename);
        }
     
        while (getline(file, line)) {
            stringstream ss(line);
            string name, typeStr, effectStr, prompt;
            int value, energyUsed;

            // Parse the line
            getline(ss, name, ';');
            getline(ss, typeStr, ';');
            getline(ss, effectStr, ';');
            ss >> value;
            ss.ignore(1, ';');  // Ignore the semicolon after value
            ss >> energyUsed;
            ss.ignore(1, ';');  // Ignore the semicolon after energyUsed
            getline(ss, prompt, ';');
            
            // Convert strings to enum types
            Type type = stringToType(typeStr);
            Effect effect = stringToEffect(effectStr);

            Support* card;

            // Create specific card based on effect type
            if (effect == healthGain || effect == energyGain) {
                card = new Support(name, type, energyUsed, effect, prompt, value);
            }

            // Add card to the deck
            deck.push_back(card);
        }


        file.close();  // Close the file after reading
    } catch (const FileNotFoundException& e) {
        cerr << "\nError: File Not Found\n";
    }

    return deck;
}

int makeMove(int num1, int num2) {
    int move;

    // Ensure num1 is smaller than num2
    if (num1 > num2) {
        swap(num1, num2); // If num1 is greater than num2, swap them
    }

    // Loop until valid input is given
    while (true) {
        cout << "Enter a move between " << num1 << " and " << num2 << ": ";
        cin >> move;

        // Check if input is valid
        if (cin.fail() || move < num1 || move > num2) {
            cin.clear(); // Clear the error flag
            cin.ignore(100, '\n'); // Ignore incorrect input
            cout << "Invalid move! Please enter a number between " << num1 << " and " << num2 << ".\n";
        } else {
            return move; // Valid move
        }
    }
}
