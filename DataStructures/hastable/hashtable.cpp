#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP

static const unsigned int default_capacity = 11;
static const char salt[] = "$1$########";


namespace cop4530
{

const char * encrypt(string pw)
{
    char * password = new char [100];
    strcpy ( password, crypt(pw.c_str(), salt));
    string new_pw = password;
    return new_pw.substr(new_pw.find_last_of("$")+1).c_str();//make sure not store salt
}
  //Returns the bucket index where the pair should be inserted
  unsigned int HashTable::Index (const string & key)
  {
    return hash_function(key) % bucketVector.capacity();
  }

  //Returns the hashed index
  unsigned int HashTable::hash_function (const string & s)
  {
    unsigned int i;
    unsigned long bigval = s[0];
    for (i = 1; i < s.size(); ++i)
      bigval = ((bigval & 65535) * 18000) + (bigval >> 16) + s[i];
    bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
    return bigval & 65535;

  }

  // returns largest prime number <= n or zero if input is too large
  // This is likely to be more efficient than prime_above(), because
  // it only needs a vector of size n
  unsigned int HashTable::prime_below (unsigned int n)
  {
    if (n > max_prime)
      {
    std::cerr << "** input too large for prime_below()\n";
    return 0;
      }
    if (n == max_prime)
      {
    return max_prime;
      }
    if (n <= 1)
      {
    return 0;
      }

    // now: 2 <= n < max_prime
    vector <unsigned int> v (n + 1);
    setPrimes(v);
    while (n > 2)
      {
    if (v[n] == 1)
      return n;
    --n;
      }

    return 2;
  }

  //Sets all prime number indexes to 1. Called by method prime_below(n)
  void HashTable::setPrimes(vector<unsigned int>& vprimes)
  {
    int root;
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
      vprimes[i] = 1;

    for( i = 2; i*i < n; ++i)
      {
    if (vprimes[i] == 1)
      for(j = i + i ; j < n; j += i)
        vprimes[j] = 0;
      }
  }

HashTable::HashTable()
{
    length = default_capacity;
    bucketVector.resize(length);
}
HashTable::HashTable(size_t n)
{
    length = prime_below(n);
    bucketVector.resize(length);
}
HashTable::~HashTable()
{
    vector < list < pair <string, string> > >::iterator it;
    for(it = bucketVector.begin(); it!= bucketVector.end(); it++)
    {
       (*it).clear();
    }
    bucketVector.clear();
}
//loads username password pairs from a file
bool HashTable::loadFromFile(string filename)
{
    fstream myfile(filename.c_str(), fstream::in);
    string line;
    string uname = "";
    string pw = "";
    string empty = "";
    bool flag = false;// signals whether we're reading uname or pw
    if(myfile)
    {
        while(myfile.good())
        {
            getline(myfile,line);
            for(int x = 0; x < line.length(); x++)
            {
                if(line[x] == ':')
                {
                    flag = true;// now we're readin pw
                    continue; //   don't store colon twice
                }

                if(!flag)
                    uname += line[x];
                else
                    pw += line[x];
            }
            //encrypt_pw flag set false prevents double encrypting when loading from file
            if(uname.compare("") != 0)
                this->addUser(uname, pw, false);
            uname = "";
            pw = "";
            flag = false;
        }
    }else
    {
        cout << endl <<"*****Error: Unable to open file " << filename << endl;
    }
}
//writes the hashtable to a file formtted "username:pasword\n"
bool HashTable::writeToFile(string filename)
{
    fstream myfile(filename.c_str(), fstream::out);
    string buf = "";
    vector < list < pair <string, string> > >::const_iterator it = bucketVector.begin();
    list < pair <string, string> >::const_iterator it2;
    for(; it!= bucketVector.end(); it++)                    //cycle through buckers
    {
        for(it2 = (*it).begin(); it2 != (*it).end(); it2++) //cycle through lists in buckets
        {
            buf = (*it2).first + ":" + (*it2).second + "\n";
            myfile << buf;
        }

    }
    myfile.close();
    return true;
}
//encrypt_pw flag set false prevents double encrypting when loading from file
bool HashTable::addUser(string uname, string pw, bool encrypt_pw = true)
{
    string password = pw;
    if(encrypt_pw)
        password = encrypt(pw);

    bool user_found = false;
    list < pair <string, string> > & theList = bucketVector[Index(uname)];
    //search for username in list
    for(list < pair <string, string> >::iterator it = theList.begin(); it != theList.end(); it++)
    {
        if(uname.compare((*it).first) == 0)
        {
            user_found = true;
            break;
        }

    }
    if(user_found)
    {
        return false; // we don't allow duplicate usernames
    }

    pair <string, string> this_pair = make_pair(uname, password);
    theList.push_back(this_pair);
    return true;
}
//removes user from table
bool HashTable::removeUser(string uname, string pw)
{
    const char * password = encrypt(pw);
    bool uname_found = false;
    list < pair <string, string> > & theList = bucketVector[Index(uname)];
    list < pair <string, string> >::iterator it;
    //search for username in list
    for(it = theList.begin(); it != theList.end(); it++)
    {
        if(uname.compare((*it).first) == 0)
        {
            uname_found = true;
            break;
        }
    }
    if(!uname_found)
    {
        cout << "*****Error: User not found.  Could not delete user" << endl;
        return false;
    }

    theList.erase(it);
    cout << "User " << uname << " deleted." << endl;
    return true;
}
//change a user's password
//we output messages here because there are two reasons for returning false that the user
//should be made aware of: bad uname or bad pw
bool HashTable::changePw(string uname, string pw)
{
    string new_pw;
    cout << endl << "Enter the new password : ";
    cin >> new_pw;

    string password = encrypt(pw);
    string new_password = encrypt(new_pw);

    bool user_found = false;
    bool pw_correct = false;

    list < pair <string, string> > & theList = bucketVector[Index(uname)];
    list < pair <string, string> >::iterator it;
    //search for username
    for(it = theList.begin(); it != theList.end(); it++)
    {
        if(uname.compare((*it).first) == 0)
        {
            user_found = true;
            break;
        }
    }
    //did we find uname?
    if(!user_found)
    {
        cout << endl << "*****Error: User not found.  Could not change user password" << endl;
        return false;
    }else
    {   //we found uname, let's check if pw matches
        if(password.compare((*it).second) == 0)
        {
            pw_correct = true;
        }else
        {
            cout << endl << "*****Error: Password incorrect.  Could not change user password" << endl;
            return false;
        }
    }
    //user is authenticated, so let him change his pw
    if(pw_correct)
    {
        (*it).second = new_password;
        cout << endl << "Password changed for user " << uname << endl;
        return true;
    }
}
bool HashTable::findUser(string uname, string pw)
{
    const char * password = encrypt(pw);

    list < pair <string, string> > & theList = bucketVector[Index(uname)];
    pair <string, string> this_pair = make_pair(uname, password);
    //uname and pw pair must match so we can use find() shortcut
    list < pair <string, string> >::iterator it = find(theList.begin(), theList.end(), this_pair);
    //find() went through list and didn't find the pair
    if(it == theList.end())
    {
        cout << endl << "User '" << uname << "' not found." << endl;
        return false;
    }
    else
    {
        cout << endl << "User '" << uname << "' found." << endl;
        return true;
    }
}
void HashTable::dumpTable()
{
    vector < list < pair <string, string> > >::const_iterator it = bucketVector.begin();
    list < pair <string, string> >::const_iterator it2;
    string output;
    int x = 0;
    for(; it != bucketVector.end(); it++)
    {
        cout << "v[" << x++ << "]: ";
        for(it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            output = (*it2).first + ":" + (*it2).second;
            cout << setw(32) << left << output;
        }
        cout << endl;
    }

}
unsigned int HashTable::size()
{
    vector < list < pair <string, string> > >::const_iterator it = bucketVector.begin();
    list < pair <string, string> >::const_iterator it2;
    int x = 0;
    for(; it != bucketVector.end(); it++)
    {
       if(!(*it).empty())
       for(it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            x++;
        }
    }
    return x;
}

}
#endif

