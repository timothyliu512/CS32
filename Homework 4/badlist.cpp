void removeBad(list<Restaurant*>& li)
{
    for ( list<Restaurant*>::iterator p = li.begin(); p != li.end() ; p++)
    {
        if ( (*p)->stars() <= 2 )
        {
            delete *p;  // delete the Restaurant object
            li.erase(p);  // remove the pointer from the list
            p = li.begin(); // Check from beginning
        }
    }
}
