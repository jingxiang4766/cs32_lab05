//  Jing Su, 6839039

#ifndef table_h
#define table_h
#include <vector>
#include "entry.h"
// Note: Your hash table must be implemented using an array of
// std::vector<Entry> as stated in the instructions
class Table {
public:
	Table(unsigned int max_entries = 100);
	Table(unsigned int entries, std::istream& input);
	void put(unsigned int key, std::string data);
	void put(Entry e);
	std::string get(unsigned int key) const;
	bool remove(unsigned int key);
	friend std::ostream& operator<< (std::ostream& out, const Table& t);

private:
	unsigned int max_entries;
	unsigned int numbers;
	std::vector<std::vector<Entry>> v;
};

#endif /* table_h */
