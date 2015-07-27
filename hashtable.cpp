///+++++++++++++++++++++++++++++++++++++++++++++++++
///
///               hashtable class
///
///                 hqwsky 2015
///
///+++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _HASHTABALE_
#define _HASHTABALE_

#include<iostream>
#include<vector>

using namespace std;


class hashtable
{
public:
	hashtable(size_t n);
	~hashtable();

	bool insert(const int val);

    bool find(const int val);

	bool erase(const int val);

	void clear();

	size_t size();

private:
	struct hashtable_node
	{
		int val;
		hashtable_node* next;
		hashtable_node(int _val,hashtable_node* _next = NULL):val(_val),next(_next){}
	};

	hashtable(const hashtable& rhs);
	hashtable& operator=(const hashtable& rhs);
	
	size_t hash(unsigned int long x);

	unsigned long next_prime(unsigned long n);

	vector<hashtable_node*> buckets;

	size_t num_elements;

};


hashtable::hashtable(size_t n)
{
	const size_t n_buckets = next_prime(n);
	buckets.reserve(n_buckets);
	buckets.insert(buckets.end(),n_buckets,NULL);
    num_elements = 0;
}

hashtable::~hashtable()
{
	clear();
}

bool hashtable::insert(const int val)
{
	if(find(val))
		return false;
	const size_t k = hash(val);

	hashtable_node* tmp = new hashtable_node(val);
	tmp->next = buckets[k];
	buckets[k] = tmp;
	++num_elements;
	return true;
}

bool hashtable::find(const int val)
{
	const size_t k = hash(val);
	hashtable_node* p = buckets[k];
	while(p != NULL)
	{
		if(p->val == val)
			return true;
		p = p->next;
	}
	return false;

}

bool  hashtable::erase(const int val)
{
	const size_t k = hash(val);
	hashtable_node* p = buckets[k];
	hashtable_node* pre = NULL;

	while(p != NULL && p->val != val)
	{
		pre = p;
		p = p->next;
	}
	if(p == NULL) 
		return false;
	if(pre == NULL)
		buckets[k] = p->next;
	else
		pre->next = p->next;
	delete p;
	return true;
}

void hashtable::clear()
{
	for(int i = 0; i < buckets.size(); i++)
	{
		hashtable_node* p = buckets[i];
		while(p != NULL)
		{
			hashtable_node* next = p->next;
			delete p;
			p = next;
		}
	}
}


size_t hashtable::size()
{
	return num_elements;

}

size_t hashtable::hash(unsigned int long x)
{
	return x%buckets.size();
}

unsigned long hashtable::next_prime(unsigned long n)
{
	static const int num_primes = 28;
	static const unsigned long prime_list[num_primes] = 
	{  
        53,          97,           193,          389,        769,  
        1543,        3079 ,        6151,         12289,      24593,   
        49157,       98317,        196613,       393241,     786433,    
        1572869,     3145739,      6291469,      12582917,   25165843,    
        50331653,    100663319,    201326611,    402653189,  805306457,    
        1610612741,  3221225473ul, 4294967291ul                                          
    };  

	int i =0;
	while(i < num_primes && prime_list[i] < n)
		i++;
	return i == num_primes?prime_list[num_primes - 1]:prime_list[i];

}


#endif // hashtable







