#include "F:\PROJECT\hm2\GameManager.h"

GameManager::GameManager(): MAX_TRIES(7)
{
    // Make sure the high-score file exists, if not then create one
    ifstream fin("./data/scores.txt");
    if (!fin)
    {
        // File doesn't exist.
        system("mkdir data");
        ofstream fout("./data/scores.txt");
        fout.close();
    }
    fin.close();
}


int countLines(vector<string> words) {
    return words.size();
}
string getWord() {
    ifstream words_file;
    try {
        words_file.open("words.txt");
    }
    catch (...) {//words_file.fail()) {
        cout << "Error" <<endl;
    }

    string line;

    vector<string> words;

    while (getline(words_file,line)) {
        words.push_back(line);
    }

    srand(time(NULL));

    int number_of_words = countLines(words);
    // std::cout << number_of_words << std::endl;

    string word = words.at(rand() % number_of_words);

    return word;

}
void GameManager::showTitle()
{
    cout<<"\t *    *     **     **    *  *****   **   **     **     **    *"<<endl;
    cout<<"\t *    *    *  *    * *   * *        * * * *    *  *    * *   *"<<endl;
    cout<<"\t ******   ******   *  *  * *  ***** *  *  *   ******   *  *  *"<<endl;
    cout<<"\t *    *  *      *  *   * * *      * *     *  *      *  *   * *"<<endl;
    cout<<"\t *    * *        * *    **  ******  *     * *        * *    **"<<endl;
}

void GameManager::showRules()
{
    // welcome the user
    cout<<endl;
    cout<<"\t\t\t HOW TO PLAY"<<endl;
    cout<<"\t\t\t-------------"<<endl;
	cout<<"Welcome to hangman."<<endl;
    cout<<"You have to guess a country Name."<<endl;
	cout<<"Each letter is represented by a star."<<endl;
	cout<<"You have to type only one letter in one try."<<endl;
	cout<< "You have "<<MAX_TRIES<<" tries to try and guess the word."<<endl;
	cout<<"-------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Press any key to continue."<<endl;
    cin.ignore();
    cin.get();
}


int GameManager::letterFill(char guess, string &guessword)
{
	int i;
	int matches = 0;
	int len = word.length();
	for (i = 0; i < len; i++)
	{
		// Did we already match this letter in a previous guess?
		if (guess == guessword[i])
			return 0;
		// Is the guess in the secret word?
		if (guess == word[i])
		{
			guessword[i] = guess;
			matches++;
		}
	}
	return matches;
}

void GameManager::getPlayer1Name()
{
    cout<<"Please enter your name: ";
    cin>>player1_name;
}
void GameManager::getPlayer2Name()
{
    cout<<"Please enter your opponent's name: ";
    cin>>player2_name;
}
bool has_only_alpha(std::string word) {
    char c;
    for (int i = 0; i < word.length(); i++) {
        c = word.at(i);

        if (! ( ( c >= 'a' && c <= 'z' ) ||
                    ( c >= 'A' && c <= 'Z') ) ) {
            return false;
        }
    }
    return true;
}
void GameManager::updateHighScores(int current_score, string pname)
{
    // Stores the top 10 high scores
    ifstream fin("./data/scores.txt");

    priority_queue<pair<int, string>> pq;
    string name;
    int score;
    fin>>name;
    while (!fin.eof())
    {
        fin>>score;
        pq.push({ score, name});
        fin>>name;
    }
    pq.push({ current_score, pname });
    fin.close();

    ofstream fout("./data/scores.txt");
    for (int i = 0; !pq.empty() && i < 5; i++)
    {
        fout<<pq.top().second<<" "<<pq.top().first<<endl;
        pq.pop();
    }
    fout.close();
}

void GameManager::showHighScores()
{
    ifstream fin("data/scores.txt");
    system("cls");
    cout<<"\tTOP SCORERS"<<endl;

    string n;
    int score;
    fin>>n;
    int i = 1;
    while (!fin.eof())
    {
        fin>>score;
        cout<<i<<". "<<n<<"   "<<score<<endl;
        fin>>n;
        i++;
    }
    if (i == 1)
    {
        cout<<"No entries yet."<<endl;
        cout<<"Be the first one to get your name listed."<<endl;
        cout<<"Hurry up!"<<endl;
    }

    cout<<"---------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Press any key to continue."<<endl;
    cin.ignore();
    cin.get();
}

void GameManager::startAIGame()
{
    int num_of_wrong_guesses = 0, cur_score = 100;  // Initialize the current score to 100.
    //choose and copy a word from array of words randomly
	srand(time(NULL));
	word=getWord();
    string unknown = string(word.length(), '*');
    // Loop until the guesses are used up
    system("cls");
	while (num_of_wrong_guesses < MAX_TRIES)
	{
        cout<<endl;
		cout<<unknown<<endl;
		cout<<"\nGuess a letter: ";
        char letter;
		cin>>letter;
		// Fill secret word with letter if the guess is correct,
		// otherwise increment the number of wrong guesses.
        cout<<endl;
		if (letterFill(letter, unknown) == 0)
		{
			cout<<"Whoops! That letter isn't in there!"<<endl;
			num_of_wrong_guesses++;
            cur_score -= 10;    // If player gives a wrong guess deduct 10 pts.
		}
		else
		{
			cout<<"You found a letter! Isn't that exciting!"<<endl;
		}
		// Tell user how many guesses has left.
		cout<<"You have "<<MAX_TRIES - num_of_wrong_guesses;
		cout<<" guesses left."<<endl;
		// Check if user guessed the word.
		if (word == unknown)
		{
			cout<<word<<endl;
			cout<<"Woohoo! You got it!"<<endl;
			break;
		}
	}
	if(num_of_wrong_guesses == MAX_TRIES)
	{
		cout<<"\nSorry, you lose...you've been hanged."<<endl;
		cout<<"The word was : "<<word<<endl;
        cur_score -= 20;    // If player is unable to guess the country then deduct 20 more.
	}
    if (cur_score < 0)
        cur_score = 0;

    cout<<"You scored: "<<cur_score<<endl;
    cout<<endl;
    updateHighScores(cur_score,player1_name);    // Update the scores in the file.
}

void GameManager::startMultiPlayer()
{
    cout<<"\n"<<player1_name<<"'s Chance to Guess";
    do{
        cout<<"\n"<<player2_name<<" give a word : ";
        cin>>word;

    }while(!has_only_alpha(word));

    int num_of_wrong_guesses = 0, cur_score = 100;  // Initialize the current score to 100.
    //choose and copy a word from array of words randomly
	srand(time(NULL));
	string unknown = string(word.length(), '*');
    // Loop until the guesses are used up
    system("cls");
	while (num_of_wrong_guesses < MAX_TRIES)
	{
        cout<<endl;
		cout<<unknown<<endl;
		cout<<"\nGuess a letter: ";
        char letter;
		cin>>letter;
		// Fill secret word with letter if the guess is correct,
		// otherwise increment the number of wrong guesses.
        cout<<endl;
		if (letterFill(letter, unknown) == 0)
		{
			cout<<"Whoops! That letter isn't in there!"<<endl;
			num_of_wrong_guesses++;
            cur_score -= 10;    // If player gives a wrong guess deduct 10 pts.
		}
		else
		{
			cout<<"You found a letter! Isn't that exciting!"<<endl;
		}
		// Tell user how many guesses has left.
		cout<<"You have "<<MAX_TRIES - num_of_wrong_guesses;
		cout<<" guesses left."<<endl;
		// Check if user guessed the word.
		if (word == unknown)
		{
			cout<<word<<endl;
			cout<<"Woohoo! You got it!"<<endl;
			break;
		}
	}
	if(num_of_wrong_guesses == MAX_TRIES)
	{
		cout<<"\nSorry, you used up all your tries...you've been hanged."<<endl;
		cout<<"The word was : "<<word<<endl;
        cur_score -= 20;    // If player is unable to guess the country then deduct 20 more.
	}
    if (cur_score < 0)
        cur_score = 0;

    int player1_score=cur_score;

    cout<<player1_name<<" scored: "<<cur_score<<endl;
    cout<<endl;


    //player 2 chance to guess
    cout<<"\n"<<player2_name<<"'s Chance to Guess";
    do{
        cout<<"\n"<<player1_name<<" give a word : ";
        cin>>word;

    }while(!has_only_alpha(word));

    num_of_wrong_guesses = 0;
    cur_score = 100;  // Initialize the current score to 100.
    //choose and copy a word from array of words randomly
	srand(time(NULL));
	unknown = string(word.length(), '*');
    // Loop until the guesses are used up
    system("cls");
	while (num_of_wrong_guesses < MAX_TRIES)
	{
        cout<<endl;
		cout<<unknown<<endl;
		cout<<"\nGuess a letter: ";
        char letter;
		cin>>letter;
		// Fill secret word with letter if the guess is correct,
		// otherwise increment the number of wrong guesses.
        cout<<endl;
		if (letterFill(letter, unknown) == 0)
		{
			cout<<"Whoops! That letter isn't in there!"<<endl;
			num_of_wrong_guesses++;
            cur_score -= 10;    // If player gives a wrong guess deduct 10 pts.
		}
		else
		{
			cout<<"You found a letter! Isn't that exciting!"<<endl;
		}
		// Tell user how many guesses has left.
		cout<<"You have "<<MAX_TRIES - num_of_wrong_guesses;
		cout<<" guesses left."<<endl;
		// Check if user guessed the word.
		if (word == unknown)
		{
			cout<<word<<endl;
			cout<<"Woohoo! You got it!"<<endl;
			break;
		}
	}
	if(num_of_wrong_guesses == MAX_TRIES)
	{
		cout<<"\nSorry, you used up all your tries...you've been hanged."<<endl;
		cout<<"The word was : "<<word<<endl;
        cur_score -= 20;    // If player is unable to guess the country then deduct 20 more.
	}
    if (cur_score < 0)
        cur_score = 0;

    cout<<player2_name<<" scored: "<<cur_score<<endl;
    cout<<endl;

    int player2_score=cur_score;

    if(player1_score>player2_score)
    {
        cout<<"\n"<<player1_name<<" wins this round!\n\n";
        updateHighScores(player1_score,player1_name);
    }
    else if(player1_score<player2_score)
    {
        cout<<"\n"<<player2_name<<" wins this round!\n\n";
        updateHighScores(player2_score,player2_name);
    }
    else{
        cout<<"\nThis round is Tied\n\n";
        updateHighScores(player2_score,player2_name);
        updateHighScores(player1_score,player1_name);
    }

}

int main()
{
    GameManager game;

    int choice;
    do
    {
        system("cls");
        game.showTitle();

        cout<<endl;
        cout<<"\t1. Play against the computer\n";
        cout<<"\t2. Play with a Friend\n";
        cout<<"\t3. View scores\n";
        cout<<"\t4. How to play?\n";
        cout<<"\t5. Exit\n";
        cout<<"Enter your choice (1/2/3/4/5): ";
        cin>>choice;

        if (choice == 1)
        {
            game.getPlayer1Name();
            char ch;
            do {
                game.startAIGame();
                cout<<"Want to play again? (y/n): ";
                cin>>ch;
            } while (ch == 'y');
        }
        else if(choice == 2)
        {
            game.getPlayer1Name();
            game.getPlayer2Name();
            char ch;
            do {
                game.startMultiPlayer();
                cout<<"Want to play again? (y/n): ";
                cin>>ch;
            } while(ch == 'y');
        }
        else if (choice == 3)
        {
            game.showHighScores();
        }
        else if (choice == 4)
        {
            game.showRules();
        }
        else if (choice == 5)
        {
            cout<<"Bye bye"<<endl;
        }
        else
        {
            cout<<"Invalid choice"<<endl;
        }
    } while (choice != 5);

    return 0;
}
