#include <Processor.h>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>

void Processor::process(const std::string& filename) {
	std::ifstream file(filename);
	std::string line;
	std::vector<std::string> cnts;
    while(std::getline(file, line)) {
    	std::vector<std::string> tokens;
		boost::split(tokens, line, boost::is_any_of(","));

		std::vector<std::string> typeWithID;
		boost::split(typeWithID, tokens[0], boost::is_any_of(":"));
		const unsigned long long eventID = std::stoull(typeWithID[1]);
		const std::string& requestID = tokens[1];
		if(typeWithID[0] == "sel") {
			std::vector<std::string> bannerWithID;
			boost::split(bannerWithID, tokens[2], boost::is_any_of("-"));
			const unsigned long long bannerID = std::stoull(bannerWithID[1]);
			const double price = std::stold(tokens[3]);
			auto itr =  std::find(_banners.begin(), _banners.end(), bannerID);
			if(itr == _banners.end()) {
				_banners.emplace_back(Banner(bannerID, price));
				itr = --_banners.end();
			}
			itr->sel(eventID, requestID);
		}
		else if(typeWithID[0] == "cnt") {
			cnts.emplace_back(line);
		}
    }

	for(const std::string& l : cnts) {
		std::vector<std::string> tokens;
		boost::split(tokens, l, boost::is_any_of(","));
		std::vector<std::string> typeWithID;
		boost::split(typeWithID, tokens[0], boost::is_any_of(":"));
		const unsigned long long eventID = std::stoull(typeWithID[1]);
		const std::string& requestID = tokens[1];
		auto itr = std::find(_banners.begin(), _banners.end(), requestID);
		itr->cnt(eventID, requestID);
	}

}

void Processor::write() {
	std::ofstream file("output.xml");
	file << "<Banners>" << std::endl;
	for(const Banner& banner : _banners) {
		file << banner.toXML();
	}
	file << "</Banners>" << std::endl;
}