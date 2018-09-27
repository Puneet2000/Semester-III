/**
@author Puneet Mangla
CS17BTECH11029
**/
#include <bits/stdc++.h> 
using namespace std;
const string ROLL_NO = "CS17BTECH11029";
class Cache {
	int size;  // enteries in cache
	int accesses; // total access
	int cmiss;   // compulsory miss
	string policy;   // policy used
	vector<string> set; // actual cache set
	vector<string> hitmiss; // hitmiss of all acesses
	multimap<string,int> history; // storing history for OPTIMAL policy
public:
	int miss;
	Cache(int size,string policy){
		this->policy = policy;
		this->size = size;
		this->miss = this->accesses = this->cmiss =0;
	}

	void addBlock(string s){
		if(set.size()==size){  // evict one block according to policy
			if(policy=="OPTIMAL"){ // if policy is optimal
				vector<string>::iterator it;
				vector<string>::iterator farit=set.begin();
				multimap<string,int>::iterator mapit;
				int max=0;
				for(it = set.begin() ;it!=set.end();++it){
					mapit = history.find(*it);
					if (mapit == history.end()){ // there exists one block which is never used in future
						set.erase(it); // erase block, push new block and return
						set.push_back(s);
						return;
					}
					if((*mapit).second > max){ // else choose the block in set which is accessed farthest
						max = (*mapit).second;
						farit = it;
					}
				}
				set.erase(farit); // erase the block
			}
			else{
				set.erase(set.begin()); // in case of LRU and FIFO erase frist block in queue
			}
		}
		set.push_back(s);
	}

	bool isHit(string s){
		vector<string>::iterator it;
		it = find (set.begin(), set.end(), s);
		if(it != set.end()){ // if block is found
			if(policy=="LRU"){ // if its LRU policy make this block MRU by pushing it at back
			set.erase(it);
			set.push_back(s);
		}
			return true;
		}
		addBlock(s); // add new block
		return false;		
	}

	void countMisses(char addressFile[]){
		ifstream infile;
		infile.open(addressFile);
		string word;
		map<string, int> mp; 
		if(policy=="OPTIMAL"){ // if optimal read the all file at once and store in history
			ifstream file;
			file.open(addressFile);
			int a =0;
			while (file >> word)
	    	{ 	a++;
	    		history.insert(pair<string,int>(word,a));
	    	} 
    	}

		while (infile >> word){
			if (policy == "OPTIMAL") // if optimal remove blocks that are used
    			history.erase(history.find(word));
    		accesses++;
    		if(!isHit(word)){ // MISS
    			miss++;
    			hitmiss.push_back("MISS");
    		}
    		else{ // HIT
    			hitmiss.push_back("HIT");
    		}
    		if (!mp.count(word)) // counting unique elements for compulsory misses
            	mp.insert(make_pair(word, 1)); 
        	else
            	mp[word]++; 
    	} 
    	cmiss = mp.size();   	
    	infile.close();
	}

	void write(char addressFile[] , char outFile[]){
		ofstream outfile;
		outfile.open(outFile);
		string word;
		countMisses(addressFile);
		// writing in file
		//cout<<"writing\n";
		outfile<<"TOTAL_ACCESSES = "<<accesses<<endl;
		outfile<<"TOTAL_MISSES = "<<miss<<endl;
		outfile<<"COMPULSORY_MISSES = "<<cmiss<<endl;
		outfile<<"CAPACITY_MISSES = "<<miss-cmiss<<endl;
		for(int i=0;i<hitmiss.size();i++)
			outfile<<hitmiss[i]<<endl;  	
    	outfile.close();   	
	}
};

string outFileName(string addressFile){ // extract name of output file
	string s="";
	for(int i=0;i<addressFile.size()-4;i++)
		s=s+addressFile[i];
	return s;
}

int main(int argc, char **argv){
	string policy = argv[1];
	string addressFile = argv[2]; // commandline args
	int cacheEnteries = atoi(argv[3]);
	string outFile = ROLL_NO+"_"+policy+"_"+outFileName(addressFile)+"_"+argv[3]+".out";	 // final output file

	char inputfile [addressFile.size()+1];
	addressFile.copy(inputfile,addressFile.size()+1);
	inputfile[addressFile.size()]='\0';
	char outputfile[outFile.size()+1];
	outFile.copy(outputfile,outFile.size()+1);
	outputfile[outFile.size()]='\0';

	Cache cache(cacheEnteries,policy);
	cache.write(inputfile,outputfile);
	return 0;
}