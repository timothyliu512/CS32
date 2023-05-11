//
//  main.cpp
//  Homework 3
//
//  Created by Timothy Liu on 5/3/23.
//

#include <iostream>
#include <string>
using namespace std;


class Event
{
public:
    Event(const string& name) : mName(name)
    {
        
    }
    
    virtual string name() const
    {
        return mName;
    }
    
    virtual string need() const = 0;
    
    virtual bool isSport() const {
        return true;
    }
    
    virtual ~Event() {}
    
private:
    string mName;
};



class Concert : public Event
{
public:
    Concert(const string& name, const string& genre) : Event(name),  mGenre(genre)
    {
        
    }
    
    virtual string need() const
    {
        return "a stage";
    }
    
    virtual bool isSport() const {
        return false;
    }
    
    virtual ~Concert() {
        cout << "Destroying the " << name() << " " << mGenre << " concert" << endl;
    }
    
private:
    string mGenre;
};



class BasketballGame : public Event
{
public:
    BasketballGame(const string& name) : Event(name)
    {
        
    }
    
    virtual string need() const
    {
        return "hoops";
    }
    
    virtual bool isSport() const{
        return true;
    }
    
    virtual ~BasketballGame() {
        cout << "Destroying the " << name() << " basketball game" << endl;
    }
    
private:
    
};



class HockeyGame : public Event
{
public:
    
    HockeyGame(const string& name) : Event(name)
    {
        
    }
    
    virtual string need() const
    {
        return "ice";
    }
    
    virtual bool isSport() const {
        return true;
    }
    
    virtual ~HockeyGame() {
        cout << "Destroying the " << name() << " hockey game" << endl;
    }
    
private:
};

void display(const Event* e)
{
    cout << e->name() << ": ";
    if (e->isSport())
    cout << "(sport) ";
    cout << "needs " << e->need() << endl;
}

int main()
{
    Event* events[4];
    events[0] = new BasketballGame("Lakers vs. Warriors");
    // Concerts have a name and a genre.
    events[1] = new Concert("Ricardo Arjona", "Latin pop");
    events[2] = new Concert("Erykah Badu", "neo soul");
    events[3] = new HockeyGame("Kings vs. Oilers");

    cout << "Here are the events." << endl;
    for (int k = 0; k < 4; k++)
        display(events[k]);

    // Clean up the events before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete events[k];
    return 0;
}
