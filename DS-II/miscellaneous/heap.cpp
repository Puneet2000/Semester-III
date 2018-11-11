#include <bits/stdc++.h> 
using namespace std;

struct heapNode {
	int vertex;
	int weight;
};

class MinHeap{
	struct heapNode *weights;
	int V;
	int size;
	int *map;
public:

	MinHeap(int V){
		this->V = V;
		this->size =0;
		this->weights = (struct heapNode*)malloc(V*sizeof(heapNode));
		this->map = (int*)malloc((V+1)*sizeof(int));
		memset (this->map, -1, sizeof (int) * (V+1));
	}

	~MinHeap(){
		free(map);
		free(weights);
	}

	int parent(int i){
		return (i-1)/2;
	}

	int left_child(int i){
		return 2*i+1;
	}

	int right_child(int i){
		return 2*i+2;
	}

	void swap(int i,int j){
		struct heapNode node;
		node = weights[i];
		map[weights[i].vertex] = j;
		map[weights[j].vertex] = i;
		weights[i] = weights[j];
		weights[j] = node;	
	}

	void insert(int vertex , int weight){
		struct heapNode node;
		node.vertex = vertex;
		node.weight = weight;
		weights[size] = node;
		map[node.vertex] = size;
		int index = size;
		while(index!=0){
			if(weights[parent(index)].weight > weights[index].weight){
				swap(index, parent(index));
				index  = parent(index);
			}
			else
				break;
		}
		size++;

	}

	struct heapNode extractMin(){
		if(size==1){
			size--;
			return weights[0];
		}
		struct heapNode min = weights[0];
		size--;
		weights[0] = weights[size];
		map[weights[size].vertex] = 0;
		map[min.vertex]=-1;
		Heapify(0);
		//printHeap();
		return min;
	}

	void printHeap(){
		for (int i=0;i<size;i++){
			cout<<"( "<<weights[i].vertex<<" , "<<weights[i].weight<<" )\n";
		}
	}

	void Heapify(int i){
		int left = left_child(i) , right = right_child(i);
		int min = i;
		if (left<size && weights[left].weight <  weights[i].weight)
			min = left;
		if (right<size && weights[right].weight < weights[min].weight)
			min = right;
		if (min!=i){
			swap(i,min);
			Heapify(min);
		}

	}

	void decreaseKey(int vertex , int weight){
		int index = map[vertex];
		weights[index].weight = weight;
		while (index != 0 && weights[parent(index)].weight > weights[index].weight) 
	    { 
	       swap(index , parent(index)); 
	       index = parent(index); 
	    }  
	}

	bool isEmpty(){
		if(size==0)
			return true;
		else
			return false;
	}
};

int main(){
	MinHeap heap(10);
	heap.insert(1,3);
	heap.insert(3,5);
	heap.insert(2,4);
	heap.insert(5,7);
	heap.insert(4,6);
	heap.insert(6,9);
	heap.insert(7,8);
	heap.insert(8,10);
	heap.insert(9,2);
	heap.insert(10,11);
	heap.printHeap();
	while(!heap.isEmpty()){
		struct heapNode min = heap.extractMin();
		cout<<min.vertex<<" "<<min.weight<<endl;
	}
	return 0;
}
