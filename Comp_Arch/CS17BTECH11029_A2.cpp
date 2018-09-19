#include <bits/stdc++.h> 
using namespace std;
const string ROLL_NO = "CS17BTECH11029";
class Cache {
	int size;
	int accesses;
	int cmiss;
	string policy;
	vector<string> set;
public:
	int miss;
	Cache(int size,string policy){
		this->policy = policy;
		this->size = size;
		this->miss = this->accesses = this->cmiss =0;
	}

	void addBlock(string s){
		if(set.size()==size)
			evict();
		set.push_back(s);
	}

	void evict(){
		set.erase(set.begin());
	}

	bool isHit(string s){
		vector<string>::iterator it;
		it = find (set.begin(), set.end(), s);
		if(it != set.end()){
			if(policy=="LRU"){
			set.erase(it);
			set.push_back(s);
		}
			return true;
		}
		addBlock(s);
		return false;		
	}

	void countMisses(string addressFile){
		ifstream infile;
		infile.open(addressFile);
		string word;
		map<string, int> mp; 
		while (infile >> word)
    	{  accesses++;
    		if(!isHit(word))
    			miss++;
    		if (!mp.count(word)) 
            	mp.insert(make_pair(word, 1)); 
        	else
            	mp[word]++; 
    	} 
    	cmiss = mp.size();   	
    	infile.close();
	}

	void write(string addressFile , string outFile){
		ifstream infile;
		ofstream outfile;
		infile.open(addressFile);
		outfile.open(outFile);
		string word;
		countMisses(addressFile);
		outfile<<"TOTAL_ACCESSES = "<<accesses<<endl;
		outfile<<"TOTAL_MISSES = "<<miss<<endl;
		outfile<<"COMPULSORY_MISSES = "<<cmiss<<endl;
		outfile<<"CAPACITY_MISSES = "<<miss-cmiss<<endl;
		while (infile >> word)
    	{  
    		if(isHit(word))
    			outfile<<"HIT\n";
    		else
    			outfile<<"MISS\n";
    	}    	
    	outfile.close();   	
	}
};

string outFileName(string addressFile){
	string s="";
	for(int i=0;i<addressFile.size()-4;i++)
		s=s+addressFile[i];
	return s;
}

int main(int argc, char **argv){
	string policy = argv[1];
	string addressFile = argv[2];
	int cacheEnteries = stoi(argv[3]);
	string outFile = ROLL_NO+"_"+policy+"_"+outFileName(addressFile)+"_"+argv[3]+".out";	
	if(policy!="OPTIMAL"){
		Cache cache(cacheEnteries,policy);
		cache.write(addressFile,outFile);
		cout<<cache.miss<<endl;
	}
	else{
		Cache LRUcache(cacheEnteries,"LRU");
		Cache FIFOcache(cacheEnteries,"FIFO");
		LRUcache.write(addressFile,outFile);
		FIFOcache.write(addressFile,outFile);
		cout<<LRUcache.miss<<" "<<FIFOcache.miss;
		if(LRUcache.miss>FIFOcache.miss)
			LRUcache.write(addressFile,outFile);
		else
			FIFOcache.write(addressFile,outFile);
	}
 
	return 0;
}