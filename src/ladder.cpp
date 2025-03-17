#include "ladder.h"

void error(string word1, string word2, string msg) {
    std::cout << word1 << ' ' << word2 << ' ' << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int str1_length = str1.length();
    int str2_length = str2.length();

    if (str1 == str2)
        return true;
    if (abs(str1_length - str2_length) > 1)
    	return false;
    
    int i = 0;
    int j = 0;
    int edits = 0;

    while (i < str1_length && j < str2_length) {
        if (str1[i] != str2[j]) {
            edits++;
            if (edits > d) {
                return false;
            }

            if (str1_length > str2_length) {
                i++;
            } else if (str1_length < str2_length) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    
    edits += (str1_length - i) + (str2_length - j);
    
    return edits == d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "First and Last word are the same");
        return {};
    }

    if (word_list.find(end_word) == word_list.end()) {
    	error(begin_word, end_word, ": end word is invalid");
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder; 
                }
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << " ";
        }
        cout << endl;
    }
}

void verify_word_ladder() { }