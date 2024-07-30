#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class Sports
{
private:
    static int countOfInstance;

protected:
    string eventName;
    int yearOfEvent;

public:
    Sports(string _eventName, int _yearOfEvent)
        : eventName(_eventName), yearOfEvent(_yearOfEvent)
    {
        countOfInstance++;
    }

    static int getCountOfInstance()
    {
        return Sports::countOfInstance;
    }
};

int Sports::countOfInstance = 0;


/*
 * Implement classes 'Indoor', 'Outdoor', 'Badminton', 'Chess', and 'Cricket' below.
 *
 */
 
 class Indoor : public Sports {
     public:
     Indoor
 };
 
 class Outdoor : public Sports {
     
 };

class Badminton : public Indoor, public Outdoor {
    
    public:
    Badminton(string _event, int _year) : Indoor()  {}
    
    string getEventName() {        
        return Indoor::eventName;
    }
    
    int getYearOfEvent() {
        return Indoor::yearOfEvent;
    }
};

class Chess : public Indoor {
    
    public:
    Chess(string _event, int _year) : eventName(_event), yearOfEvent(_year){}
    string getEventName() {   
        return eventName;     
    }
    
    int getYearOfEvent() {
        return yearOfEvent;
        }
};

class Cricket : public Outdoor {
    
    public:
    Cricket(string ) {}
    string getEventName() {    
        return eventName;    
    }
    
    int getYearOfEvent() {
        return yearOfEvent;
    }
};

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> sport(n), eventName(n);
    vector<int> yearOfEvent(n);

    for (int i = 0; i < n; i++)
    {
        string event_item_temp;
        getline(cin, event_item_temp);

        vector<string> event_item = split(rtrim(event_item_temp));

        sport[i] = event_item[0];
        eventName[i] = event_item[1];
        yearOfEvent[i] = stoi(event_item[2]);
    }

    vector<Chess *> chessEvents;
    vector<Badminton *> badmintonEvents;
    vector<Cricket *> cricketEvents;

    if (is_base_of<Sports, Indoor>::value == 0 || is_base_of<Sports, Outdoor>::value == 0)
    {
        fout << "Inheritance is incorrect\n";
        fout.close();
        return 0;
    }

    if (is_base_of<Indoor, Chess>::value == 0 || is_base_of<Indoor, Badminton>::value == 0)
    {
        fout << "Inheritance is incorrect\n";
        fout.close();
        return 0;
    }

    if (is_base_of<Outdoor, Badminton>::value == 0 || is_base_of<Outdoor, Cricket>::value == 0)
    {
        fout << "Inheritance is incorrect\n";
        fout.close();
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        assert(sport[i] == "Chess" || sport[i] == "Badminton" || sport[i] == "Cricket");
        if (sport[i] == "Chess")
        {
            Chess *obj = new Chess(eventName[i], yearOfEvent[i]);
            fout << obj->getEventName() << " " << obj->getYearOfEvent() << "\n";
            chessEvents.push_back(obj);
        }
        else if (sport[i] == "Badminton")
        {
            Badminton *obj = new Badminton(eventName[i], yearOfEvent[i]);
            fout << obj->getEventName() << " " << obj->getYearOfEvent() << "\n";
            badmintonEvents.push_back(obj);
        }
        else if (sport[i] == "Cricket")
        {
            Cricket *obj = new Cricket(eventName[i], yearOfEvent[i]);
            fout << obj->getEventName() << " " << obj->getYearOfEvent() << "\n";
            cricketEvents.push_back(obj);
        }
        if (Sports::getCountOfInstance() != i + 1)
        {
            fout << "countOfInstance property is not working correctly\n";
            fout.close();
            return 0;
        }
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}



/*
2
Cricket CricketChampionship 2000
Chess ChessChampionship 2010
*/