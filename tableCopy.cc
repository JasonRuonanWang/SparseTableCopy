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
            if(abs(a1.data()[j].real() - a2.data()[j].real()) > stof(useAccuracy) ||  abs(a1.data()[j].imag() - a2.data()[j].imag()) > stof(useAccuracy))
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

    cout << "============================== Input Table Structure ==============================" << endl;
    t1.showStructure(cout);
    cout << "===================================================================================" << endl << endl;

    cout << "============================== Output Table Structure =============================" << endl;
    t2.showStructure(cout);
    cout << "===================================================================================" << endl << endl;

    return true;
}


int main (int argc, const char* argv[])
{
    string fileIn, fileOut;

    if(argc<3)
    {
        std::cout << "Please provide filenames for input and output table, e.g. run ./tableCopy input.table output.table" << std::endl;
        return -1;
    }
    else
    {
        fileIn = argv[1];
        fileOut = argv[2];
    }
    if(argc==4)
    {
        useCompressor = argv[3];
    }

    {
        Table tabIn(fileIn);
        ArrayColumn<Complex> mapColumn(tabIn, sparseColumnName);
        TableDesc td("", "1", TableDesc::Scratch);
        td.addColumn (ArrayColumnDesc<Complex>(sparseColumnName, mapColumn.shape(0), ColumnDesc::FixedShape));
        SetupNewTable newtab(fileOut, td, Table::New);

//        Adios2StMan a2stman;

        Adios2StMan a2stman(
                MPI_COMM_WORLD, // MPI communicator
                "",             // ADIOS engine name, empty for default
                {},             // ADIOS engine parameters, std::map<std::string, std::string>
                {{}},           // ADIOS transport parameters, std::vector<std::map<std::string, std::string>>
                {{              // ADIOS operator (compressor) parameters, std::vector<std::map<std::string, std::string>>
                    {"Variable", sparseColumnName},
                    {"Operator", useCompressor},
                    {"Accuracy", useAccuracy}
                }}
                );


        newtab.bindAll(a2stman);
        Table tabOut(newtab);
        tabOut.addRow(tabIn.nrow());
        TableCopy::copySubTables(tabOut, tabIn);
        TableCopy::copyColumnData(tabIn, sparseColumnName, tabOut, sparseColumnName, false);
        std::cout << "Finished copying table using " << useCompressor << ", start checking data now. " << std::endl;

    }   // make sure every destructor is called before opening tables for checking

    checkTables(fileIn, fileOut);

    return 0;
}
