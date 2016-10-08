#ifndef _PROCESSOR_H_

#include <Banner.h>
#include <vector>
#include <set>

class Processor {
public:
	void process(const std::string& filename);
	void write();

private:
	std::vector<Banner> _banners;
};

#endif