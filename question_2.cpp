#include <iostream>
#include <fstream>
#include <iterator>
#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
int end_node = 1;
struct Trie
{
    bool isEndOfWord;
    int n;
    map<char, Trie*> ma;
    string frequency;
};
Trie* getNewTrieNode()
{
    Trie* node = new Trie;
    node->isEndOfWord = false;
    return node;
}
void insert_node(Trie*& root, const string& str,
                 const string& frequency)
{
    if (root == NULL)
        root = getNewTrieNode();

    Trie* temp = root;
    for (int i = 0; i < str.length(); i++)
    {
        char x = str[i];
        if (temp->ma.find(x) == temp->ma.end())
            temp->ma[x] = getNewTrieNode();

        temp = temp->ma[x];
    }
    temp->isEndOfWord = true;
    temp->n = end_node;
    end_node++;
    temp->frequency = frequency;
}

int getNum(Trie* root, const string& word)
{

    if (root == NULL)
        return 0;

    Trie* temp = root;
    for (int i = 0; i < word.length(); i++)
    {
        temp = temp->ma[word[i]];
        if (temp == NULL)
            return 0;
    }
    if (temp->isEndOfWord)
        return temp->n;
    return 0;
}

int main()
{
    ifstream ip("temp.csv");
    if(!ip.is_open()) std::cout << "ERdf" << '\n';
    string name;
    string freq;
    Trie* root = NULL;
    std::map<int, std::string> dicd;
    while(ip.good())
    {
        getline(ip,name,',');
        getline(ip,freq,'\n');
        insert_node(root, name,freq);
    }
    ifstream ip1("temp.csv");
    while(ip1.good())
    {
        getline(ip1,name,',');
        getline(ip1,freq,'\n');
        int res2 = getNum(root,name);
        dicd.insert(std::pair<int,std::string>(res2,name));
    }
    int query;
    cout<<"Enter the number you want to search: ";
    cin>>query;
    cout<<"The word at this number is: "<<dicd[query];
    getch();
    return 0;
}
