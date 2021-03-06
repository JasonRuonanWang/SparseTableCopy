#include <casacore/tables/Tables.h>
#include <casacore/tables/Tables/TableCopy.h>
#include <casacore/tables/DataMan/Adios2StMan.h>

using namespace casacore;
using namespace std;

std::string sparseColumnName = "map";

//std::string useCompressor = "bzip2";
//std::string useCompressor = "blosc";
//std::string useCompressor = "zfp";
std::string useCompressor = "sz";

std::string useAccuracy = "0.01";

bool checkTables(std::string table1, std::string table2)
{
    Table t1(table1);
    Table t2(table2);
    ArrayColumn<Complex> ac1(t1, sparseColumnName);
    ArrayColumn<Complex> ac2(t2, sparseColumnName);

    Array<Complex> a1 = ac1.get(0);
    Array<Complex> a2 = ac2.get(0);

    size_t errorElements = 0;
    for(size_t j=0; j<a1.nelements(); ++j)
    {
        if(useCompressor == "bzip2" || useCompressor == "blosc")
        {
            if(a1.data()[j] != a2.data()[j])
            {
                cerr << "!!!! wrong data at " << j << ", read " << a2.data()[j] << ", should be " << a1.data()[j] << endl;
                ++errorElements;
            }
        }
        else if(useCompressor == "zfp" || useCompressor == "sz")
        {
            if((abs(a1.data()[j].real() - a2.data()[j].real()) > stof(useAccuracy) ||  abs(a1.data()[j].imag() - a2.data()[j].imag()) > stof(useAccuracy)) && errorElements < 10)
            {
                cerr << "!!!! wrong data at " << j << ", read " << a2.data()[j] << ", should be " << a1.data()[j] << endl;
                ++errorElements;
            }
        }
    }

    if(a1.nelements() != a2.nelements())
    {
        cerr << "wrong number of elements " << endl;
    }
    if(errorElements)
    {
        cerr << "total " << errorElements << " errors out of " << a1.nelements() << " elements"  << endl;
    }

    cout << endl << endl;
    cout << "============================== Input Table Structure =======================================" << endl;
    t1.showStructure(cout);
    cout << "============================================================================================" << endl;

    cout << "============================== Output Table Structure ====================================== using ADIOS2 XML" << endl;
    t2.showStructure(cout);
    cout << "============================================================================================" << endl;

    return true;
}


int main (int argc, const char* argv[])
{
    string fileIn, fileOut, xmlFile;

    if(argc<4)
    {
        std::cout << "Please provide filenames for input and output table, and xml configuration file, e.g. run ./tableCopyXml input.table output.table tableCopyXmlZfp.xml" << std::endl;
        return -1;
    }
    else
    {
        fileIn = argv[1];
        fileOut = argv[2];
        xmlFile = argv[3];
    }

    {
        Table tabIn(fileIn);
        ArrayColumn<Complex> mapColumn(tabIn, sparseColumnName);
        TableDesc td("", "1", TableDesc::Scratch);
        td.addColumn (ArrayColumnDesc<Complex>(sparseColumnName, mapColumn.shape(0), ColumnDesc::FixedShape));
        SetupNewTable newtab(fileOut, td, Table::New);

        Adios2StMan a2stman(xmlFile, MPI_COMM_WORLD);

        newtab.bindAll(a2stman);
        Table tabOut(newtab);
        tabOut.addRow(tabIn.nrow());
        TableCopy::copySubTables(tabOut, tabIn);
        TableCopy::copyColumnData(tabIn, sparseColumnName, tabOut, sparseColumnName, false);

    }   // make sure all ADIOS objects are destroyed before moving on

    std::cout << "Table copy finished. Now checking data... " << std::endl;

    checkTables(fileIn, fileOut);

    return 0;
}
