#ifndef _BANNER_H_

#include <set>
#include <string>
#include <map>

class Banner {
public:

	Banner(const std::size_t id, const double price);
	bool operator==(const std::size_t id) const;
	bool operator==(const std::string& requestID) const;
	void sel(const std::size_t eventID, const std::string& requestID);
	void cnt(const std::size_t eventID, const std::string& requestID);
	std::string toXML() const;
	double revenue() const;


private:
	std::size_t _id;
	double _price;
	std::set<std::string> _requestIDs;
	std::map<std::size_t, std::size_t> _eventsCount;

	void incrementEventCount(const std::size_t eventID);
};

#endif