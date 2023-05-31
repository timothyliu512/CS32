void listAll(const MenuItem* m, string path) // two-parameter overload
{
    // You will write this code
    // May use a loop to traverse the vector
    // Must not use loops to avoid recursion
    
    // Base Case:
    if ( m == nullptr )
    {
        return;
    }
    
    if ( path != "" ) // Doesn't add / to beginning
    {
        path += "/";
    }
    
    path = path + m->name(); // Add Menu name
    
    if ( m->menuItems() == nullptr )    // PlainMenuItem or no more items
    {
        cout << path << endl;
        return;
    }
    
    cout << path;
    
    if ( path != "" ) // Prevents starting blank line
    {
        cout << endl;
    }
    
    // CompoundMenuItem
    
    const vector<MenuItem*>* subMenus = m->menuItems(); // Point to menus in CompoundMenuItem
    
    for (vector<MenuItem*>::const_iterator i = subMenus->begin(); i != subMenus->end(); i++)
        listAll(*i, path);
    
}
