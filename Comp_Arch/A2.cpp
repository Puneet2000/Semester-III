#include<iostream>
using namespace std;

class Cache {
	int start;
	int end;
	int enteries , hits , accesses;
	string *cache;

public:
	Cache(int enteries){
		this->enteries = enteries;
		cache = new string[enteries];
		this->start = this->end =-1;
		this->accesses = this->hits =0;
	}

	void addBlockLRU(string s){
			if((start==end+1)||(start==0 && end==enteries-1))
				evict();
			if(start==-1)
				start=end=0;
			else
				end = (end+1)%enteries;

			cache[end]=s;
	}

	void addBlockFIFO(string s){

	}

	void evict(){
		if(start==end)
			start = front = -1;
		else
			start = (start+1)%enteries;
	}

	bool isHit(string s){
		int i;
		bool hit = false;
		for(i=start;i!=end;i=(i+1)%enteries){
			if(cache[i]==s){
				hit = true;
				break;
			}
		}
		hit = hit or (cache[end]==s);
		if(hit){
			for(int j=i;j!=end;j=(j+1)%enteries)
				cache[j]=cache[j+1];
			cache[end]=s;
			return true;
		}
		addBlockLRU(s);
		return false;
	}
	
};

int main(){
	Cache mycache(10);
	mycache.printCache();
	return 0;
}