echo "==================================================================================================================="
echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/grid.dumpgrid test.table mgard
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/pcf.dumpgrid test.table mgard
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/psfgrid.wr.1.dumpgrid test.table mgard
du -h test.table
rm -rf test.table

echo "==================================================================================================================="
echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/grid.dumpgrid test.table zfp
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/pcf.dumpgrid test.table zfp
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/psfgrid.wr.1.dumpgrid test.table zfp
du -h test.table
rm -rf test.table

echo "==================================================================================================================="
echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/grid.dumpgrid test.table sz
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/pcf.dumpgrid test.table sz
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/psfgrid.wr.1.dumpgrid test.table sz
du -h test.table
rm -rf test.table

echo "==================================================================================================================="
echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/grid.dumpgrid test.table bzip2
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/pcf.dumpgrid test.table bzip2
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/psfgrid.wr.1.dumpgrid test.table bzip2
du -h test.table
rm -rf test.table

echo "==================================================================================================================="
echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/grid.dumpgrid test.table blosc
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/pcf.dumpgrid test.table blosc
du -h test.table
rm -rf test.table

echo "==================================================================================================================="

time ./tableCopy ../OriginalTables/psfgrid.wr.1.dumpgrid test.table blosc
du -h test.table
rm -rf test.table

