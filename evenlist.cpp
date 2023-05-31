void removeEven(list<int>& li)
{
    
    
    for(list<int>::iterator p = li.begin(); p!= li.end(); p++)
    {
        if ( *p %2 == 0 )
        {
            list<int>::iterator q = li.erase(p);
            q--;
            p = q;
        }
    }
    
}

