#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

int main () {
    string line;
    vector<vector<char>> cyphers;
    ifstream myfile ("cyphers.txt");
    int max_len = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            int cur_len = line.length();
            vector<char> cur_line_chars;
            for (int i = 0; i < line.length(); i+=2)
            {
                char curr_char = stoul (line.substr (i,2), nullptr, 16);
                cur_line_chars.push_back(curr_char);
            }
            if (cur_line_chars.size() > max_len)
            {
                max_len = cur_line_chars.size();
            }
            cyphers.push_back(cur_line_chars);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
    vector<char> key;
    for (int i = 0; i < max_len; i++) // for every character in the stream
    {
        char best_key_guess;
        int max_successful_letters = 0;
        
        for (int j = 0; j < cyphers.size(); j++) // for every message
        {
            int successful_letters = 0;    
            char cypher_char = cyphers[j][i];
            for (int k = 0; k < cyphers.size(); k++) // for every message (that has enough letters)
            {
                if (cyphers[k].size() > i)
                {
                    char xored_char = cypher_char ^ cyphers[k][i];
                    if (toupper(xored_char) >= 'A' && toupper(xored_char) <= 'Z')
                    {
                        successful_letters++;
                    }
                    if (successful_letters > max_successful_letters)
                    {
                        max_successful_letters = successful_letters;
                        best_key_guess = cypher_char ^ ' ';
                    }
                }
                
            }
        }
        key.push_back(best_key_guess);
    }
    
    cout << "Broken code:\n";    
    for (int i = 0; i < cyphers.size(); i++)
    {
        cout << i << '|';
        for (int j = 0; j < cyphers[i].size(); j++)
        {
            char text_char = cyphers[i][j] ^ key[j];
            cout << text_char;             
        }

        cout << "|\n";    
    }
    return 0;
}
