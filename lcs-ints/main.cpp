//
//  main.cpp
//  lcs-ints
//
//  Created by mndx on 24/10/2021.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

typedef struct memo_table_ints {
    bool is_set;
    std::vector<int> vec;
} m_table_ints;

std::vector<int> lcs_ints(std::vector<int>& x, std::vector<int>& y, m_table_ints** memo_table) {
    
    int length_x = (int) x.size();
    int length_y = (int) y.size();
    
    std::vector<int> result;

    //Compute longest common subsequence of substring
    if(length_x > 0 && length_y > 0) {
        
        //Get results from memo table if available
        if(memo_table[length_x - 1][length_y - 1].is_set) {
            return memo_table[length_x - 1][length_y - 1].vec;
        }
        
        if(x[length_x - 1] != y[length_y - 1]) {
            std::vector<int> x_subvec = {x.begin(), x.end() - 1};
            std::vector<int> y_subvec = {y.begin(), y.end() - 1};

            std::vector<int> vec1 = lcs_ints(x_subvec, y, memo_table);
            std::vector<int> vec2 = lcs_ints(x, y_subvec, memo_table);
            
            int length_vec1 = (int) vec1.size();
            int length_vec2 = (int) vec2.size();
            
            if(length_vec1 > length_vec2) {
                result.insert(result.end(), vec1.begin(), vec1.end());
            }
            else {
                result.insert(result.end(), vec2.begin(), vec2.end());
            }
        }
        
        if(x[length_x - 1] == y[length_y - 1]) {
            std::vector<int> x_subvec = {x.begin(), x.end() - 1};
            std::vector<int> y_subvec = {y.begin(), y.end() - 1};
            result.push_back(x[length_x - 1]);
            std::vector<int> result_loc = lcs_ints(x_subvec, y_subvec, memo_table);
            result.insert(result.end(), result_loc.begin(), result_loc.end());
        }
        
        //Add results to memo table
        memo_table[length_x - 1][length_y - 1].is_set = true;
        memo_table[length_x - 1][length_y - 1].vec = result;
    }
    
    return result;
}

std::vector<int> longest_common_subs(std::vector<int>& x, std::vector<int>& y) {
    int max_size = 0;
    
    int len1 = (int) x.size();
    int len2 = (int) y.size();
    
    //Compute max length input strings
    if(len1 < len2) {
        max_size = len2;
    }
    else {
        max_size = len1;
    }
    
    //Initialize memo table
    m_table_ints** memo_table = new m_table_ints*[max_size];
    for(int i = 0; i < max_size; ++i) {
        memo_table[i] = new m_table_ints[max_size];
    }
    
    for(int i = 0; i < max_size; ++i) {
        for(int j = 0; j < max_size; ++j) {
            memo_table[i][j].is_set = false;
        }
    }
    
    //Compute longest common subsequence
    std::vector<int> longest_cs = lcs_ints(x, y, memo_table);
    
    //Reverse results
    std::vector<int> l_c_s;
    int lcs_len = (int) longest_cs.size();
    
    for(int i = lcs_len - 1; i > -1; --i) {
        l_c_s.push_back(longest_cs[i]);
    }
    
    return l_c_s;
}

void print_array(std::vector<int> arr) {
    int size = (int) arr.size();
    
    for(int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    
    //Input
    int n1 = 10; //Length input array 1
    int n2 = 18; //Length input array 2
    
    //Create input arrays
    std::vector<int> x;
    std::vector<int> y;
    
    //Initialize x sequence
    srand((unsigned) time(NULL));
    for(int i = 0; i < n1; ++i) {
        int val = rand() % n1 + 1;
        x.push_back(val);
    }
    
    //Initialize y sequence
    for(int i = 0; i < n2; ++i) {
        int val = rand() % n2 + 1;
        y.push_back(val);
    }
    
    //Compute longest comon subsequence
    std::vector<int> results = longest_common_subs(x, y);
    
    //Print results
    print_array(x);
    print_array(y);
    print_array(results);
    std::cout << "done" << std::endl;
    
    return 0;
}
