#include <Banner.h>
#include <algorithm>
#include <stdexcept>

Banner::Banner(const std::size_t id, const double price) : _id(id), _price(price) {
}

bool Banner::operator==(const std::size_t id) const {
	return _id == id;
}

bool Banner::operator==(const std::string& requestID) const {
	return _requestIDs.find(requestID) != _requestIDs.end();
}

void Banner::sel(const std::size_t eventID, const std::string& requestID) {
	_requestIDs.insert(requestID);
	incrementEventCount(eventID);
}

void Banner::cnt(const std::size_t eventID, const std::string& requestID) {
	std::set<std::string>::iterator itr =  _requestIDs.find(requestID);

	if(itr == _requestIDs.end()) {
		throw std::invalid_argument("can not find the request with id: " + 
				requestID + " for banner with id: " + std::to_string(_id));
	}
	incrementEventCount(eventID);
}

void Banner::incrementEventCount(const std::size_t eventID) {
	auto itr = _eventsCount.find(eventID);
	if(itr == _eventsCount.end()) {
		_eventsCount.insert({eventID, 1});
	}
	else {
		itr->second++;
	}
}

double Banner::revenue() const {
	auto itr = _eventsCount.find(1);
	return itr == _eventsCount.end()? 0 : itr->second * _price;
}

std::string Banner::toXML() const {
	const auto& tabs = [](const std::size_t n) -> std::string {
		std::string ret;
		std::string tab("    ");
		for(std::size_t i = 0; i < n; i++) {
			ret += tab;
		}
		return ret;
	};

	std::string xml(tabs(1) + "<Banner id=\"Banner-" + std::to_string(_id) + 
		"\" revenues=\"" + std::to_string(revenue()) + "\">\n" + tabs(2) + "<Events>\n");
	for(const std::pair<const std::size_t, std::size_t>& event : _eventsCount) {
		xml += tabs(3) + "<Event id=\"" + std::to_string(event.first) + "\">" + 
		std::to_string(event.second) + "</Event>\n";
	}
	xml += tabs(2) + "</Events>\n" + tabs(1) + "</Banner>\n";
	return xml;
}