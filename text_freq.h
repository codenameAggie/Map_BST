#ifndef TEXT_FREQ_H
#define TEXT_FREQ_H

#include "my_map.h"
#include "key_value.h"
#include <iterator> 
#include <vector>
#include <algorithm>
string read_file(string file_name); //done
string remove_punctuation(string& text); //done
my_map<string, double> create_freq_map(const string& text); //done
vector<key_value<string,double>> vectorize_map(my_map<string, double>& freq_map); //done
void remove_stop_words(vector<key_value<string,double>>& freq_vec, vector<string> stop_words);//done
void print_top_20_freqs(const vector<key_value<string,double>>& freq_vec, ostream& out); //done

#endif