#include "Include.h"

class QueryResult {

friend ostream& print(ostream&, const QueryResult&);

public:
	typedef std::vector<std::string>::size_type line_no;
	QueryResult(string s, 
				shared_ptr<set<line_no>> p, 
				shared_ptr<vector<string>> f): 
		sought(s), lines(p), file(f) {}

private:
	string sought;	//查询单词
	shared_ptr<set<line_no>> lines;	//出现的行号
	shared_ptr<vector<string>> file;			//输入文件
};

ostream& print(ostream& os, const QueryResult& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " << "time(s)" << endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") "<< *(qr.file->begin() + num) << endl;
	return os;
}