#include <iostream>
#include <fstream>
#include <iterator>
#include <bits/stdc++.h>
#include<conio.h>
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
void insert_node(Trie*& root, const string& str,const string& frequency)
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
string getFrequency(Trie* root, const string& word)
{

    if (root == NULL)
        return "";

    Trie* temp = root;
    for (int i = 0; i < word.length(); i++)
    {
        temp = temp->ma[word[i]];
        if (temp == NULL)
            return "";
    }
    if (temp->isEndOfWord)
        return temp->frequency;
    return "";
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
    string query;
    cout<<"Enter the word you want to search ";
    cin>>query;
    string f = getFrequency(root,query);
    if (f.length() == 0)
    {
        cout<<"NO";
    }
    else
    {
        cout<<"YES "<<f;
    }
    getch();
    return 0;
}
