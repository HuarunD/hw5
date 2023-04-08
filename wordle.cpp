#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void fwordle(
		std::string& in,
    std::multiset<char>& floating,
		const std::set<std::string>& dict,
		std::set<std::string>& suggestion,
		int size,
		int r_size
		);

bool check(
	  const std::set<std::string>& dict,
		string& comb
		);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string>suggestion ;
		int size = in.size();
		int r_size = 0;
		std::multiset<char> floating_;
		for(int i=0; i<in.size(); i++){
			if(in[i]=='-'){
				r_size++;
			}
		}
		for(int i=0; i<floating.size(); i++){
			floating_.insert(floating[i]);
		}		
		string temp = in;
		//cout << r_size << endl;
		fwordle(temp, floating_, dict, suggestion, size, r_size);
		return suggestion;
}

// Define any helper functions here
void fwordle(
		std::string& in,
    std::multiset<char>& floating,
		const std::set<std::string>& dict,
		std::set<std::string>& suggestion,
		int size,
		int r_size
		)
{
	//cout << in << " " << size << " " << r_size << " " << floating.size()<< endl;
	if(r_size<floating.size()){
		//cout << "here" << endl;
		return;
	}
	if(size==0){
		if(check(dict,in)){
			suggestion.insert(in);
			return;
		}
		return;
	}
	if(in[in.size()-size]=='-'){
   
		for(int i=97; i<123; i++){
			char temp = i;
			//cout<<temp;
			in[in.size()-size]= temp;
			if(floating.find(temp)!= floating.end()){
				floating.erase(floating.find(temp));
				fwordle(in,floating,dict,suggestion,size-1,r_size-1);
				in[in.size()-size]='-';
				floating.insert(temp);
			}
			else{
				fwordle(in,floating,dict,suggestion,size-1,r_size-1);
				 //cout << size << endl;
				in[in.size()-size]='-';
				//cout << in << endl;
			}
		}
		return;
	}
	else{
		fwordle(in,floating,dict,suggestion,size-1,r_size);
		return;
	}


}

bool check(
	  const std::set<std::string>& dict,
		string& comb
		)
{
	if(dict.find(comb)!=dict.end()){
		return true;
	}
	return false;

}
