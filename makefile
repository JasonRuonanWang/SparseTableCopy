all:
	mpic++ -std=c++11 tableCopy.cc -o tableCopy -lcasa_casa -lcasa_tables
	mpic++ -std=c++11 tableCopyXml.cc -o tableCopyXml -lcasa_casa -lcasa_tables
