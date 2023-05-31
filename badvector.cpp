void removeBad(vector<Restaurant*>& v)
{
    for ( size_t i = 0; i < v.size() ;  )
    {
        if(v[i]->stars() <= 2)
        {
            delete v[i]; // Delete Restaurant object
            v.erase(v.begin()+i); // Erase from vector
            i = 0; // Check from beginning again
        }
        else
        {
            i++;
        }
    }
}
