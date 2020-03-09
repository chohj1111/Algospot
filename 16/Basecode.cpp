fullPizza = (1<<N) - 1; // maximum set

toppings |= (1<<p); //add element 

if(toppings & (1<<p)) // check whether p is in set or not
{}

toppings &= ~(1<<p);  //delete element regardless of where p is 

toppings ^= (1<<p); // toggle

//size of set
int bitCount(int x){
	if(x==0) return 0;
	return x%2 + bitCount(x/2);
}

int firstTopping = (toppings & -toppings); // minimum element

toppings &= (toppings-1); //delete minimum element 

// all Subset without empty set
for(int subset = pizza; subset; subset = ((subset-1)&pizza)) {
	
}