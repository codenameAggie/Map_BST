#include "text_freq.h"
#include "my_map.h"
#include "key_value.h"
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <functional>
#include <string>
#include <streambuf> //for file reading
using namespace std;

string read_file(string file_name)
{
    //FINISH THIS FUNCTION
    //this should read the file, and return the string of the whole file
	ifstream file;
	file.open(file_name);
	if (!file.is_open()) {
		cerr << "The file is not open;" << endl;
	}
	string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	return str;
}

string remove_punctuation(string& text)
{
    string result;
    remove_copy_if(text.begin(), text.end(),            
                        back_inserter(result), //Store output           
                        ptr_fun<int, int>(&ispunct));
    return result;
}

my_map<string, double> create_freq_map(const string& text)
{
    my_map<string,double> freq_map;

    //FINISH THIS FUNCTION
    //this should find the frequecies of every word in the text
	stringstream ss(text);
	string word;
	int size_of_map = 0;
	while (!ss.eof())
	{
		ss >> word;
		freq_map[word]++;
   size_of_map++;
	}
	//size_of_map = freq_map.container.get_size();
 cout << endl << endl << size_of_map << endl;
	word.clear();


	for (auto word : freq_map) {
		freq_map[word.key] = freq_map[word.key] / double(size_of_map);
	};


    return freq_map;
}

vector<key_value<string,double>> vectorize_map(my_map<string, double>& freq_map)
{
    vector<key_value<string,double>> freq_vec;

    //FINISH THIS FUNCTION
    //this should return a sorted vector of the results
	for (auto word : freq_map) {
		freq_vec.push_back(word);
	}

    return freq_vec;
}

void remove_stop_words(vector<key_value<string,double>>& freq_vec, vector<string> stop_words)
{
   //FINISH THIS FUNCTION
   //this function should remove the elements contained in stop_words from freq_vec 
	for (int i = 0; i < freq_vec.size(); i++) {
		for (int j = 0; j < stop_words.size(); j++) {
			if (freq_vec.at(i).key == stop_words.at(j)) {
				freq_vec.erase(freq_vec.begin() + i);
			}
		}
	}
}

void print_top_20_freqs(const vector<key_value<string,double>>& freq_vec, ostream& out)
{
	cout << endl << "Here are 20 of the most frequent words: " << endl;
	//First this sorts the vector according to the freq: 
	//used insertion sort from PA2
	vector<key_value<string, double>> a = freq_vec;
	for (int i = 1; i < a.size(); i++) {
		auto temp = a.at(i);
		int j = i;
		for (; j > 0 && (a.at(j - 1).value < temp.value); j--) {
			a.at(j) = a.at(j - 1);
		}
		a.at(j) = temp;
	}






	//vector is sorted
	int counter = 0;
	for (int i = 0; i < a.size(); i++) {
		cout << a.at(i) <<endl;
		counter++;
		if (counter == 20) break;
	}



    //prints the top 20 frequencies to out
}
