./tableCopy ../askap/OriginalTables/pcf.dumpgrid test.table zfp

du -h test.table
rm -rf test.table

./tableCopy ../askap/OriginalTables/pcf.dumpgrid test.table sz

du -h test.table
rm -rf test.table

./tableCopy ../askap/OriginalTables/pcf.dumpgrid test.table bzip2

du -h test.table
rm -rf test.table

./tableCopy ../askap/OriginalTables/pcf.dumpgrid test.table blosc

du -h test.table
rm -rf test.table

