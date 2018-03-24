#include <string>
#include <cstdio>
#include <iostream>
#include <cxxtest/TestSuite.h>

#include "mem/MemScanner.hpp"

using namespace std;

class TestMemScanner : public CxxTest::TestSuite {
public:
  void testScan() {
    MemScanner scanner;
    int memory[] = {100, 200, 100};

    auto buffer = ScanParser::valueToBytes("100", "int32");
    size_t size = std::get<1>(buffer);

    auto list = scanner.scanInner(std::get<0>(buffer), size, (Address)memory, 4 * 3, "int32", ScanParser::OpType::Eq);

    TS_ASSERT_EQUALS(list.size(), 2);

    delete[] std::get<0>(buffer);
  }

  void testFilter() {
    MemScanner scanner;
    int memory[] = {100, 200, 100};

    auto buffer = ScanParser::valueToBytes("100", "int32");
    size_t size = std::get<1>(buffer);

    auto list = scanner.scanInner(std::get<0>(buffer), size, (Address)memory, 4 * 3, "int32", ScanParser::OpType::Eq);
    delete[] std::get<0>(buffer);


    memory[0] = 120;
    buffer = ScanParser::valueToBytes("120", "int32");
    list = scanner.filterInner(list,
                               std::get<0>(buffer),
                               std::get<1>(buffer),
                               "int32",
                               ScanParser::OpType::Eq);
    delete[] std::get<0>(buffer);

    TS_ASSERT_EQUALS(list.size(), 1);
  }

  void testGreater() {
    MemScanner scanner;
    int memory[] = {100, 200, 100};

    auto buffer = ScanParser::valueToBytes("100", "int32");
    size_t size = std::get<1>(buffer);

    auto list = scanner.scanInner(std::get<0>(buffer), size, (Address)memory, 4 * 3, "int32", ScanParser::OpType::Eq);
    delete[] std::get<0>(buffer);


    memory[0] = 120;
    list = scanner.filterUnknownInner(list,
                                      "int32",
                                      ScanParser::OpType::Gt);

    TS_ASSERT_EQUALS(list.size(), 1);
    TS_ASSERT_EQUALS(list[0]->getAddress(), (Address)memory);
  }

  void testMoreChanges() {
    MemScanner scanner;
    int memory[] = {100, 200, 100};

    auto buffer = ScanParser::valueToBytes("100", "int32");
    size_t size = std::get<1>(buffer);

    auto list = scanner.scanInner(std::get<0>(buffer), size, (Address)memory, 4 * 3, "int32", ScanParser::OpType::Eq);
    delete[] std::get<0>(buffer);

    memory[0] = 80;
    memory[2] = 90;
    list = scanner.filterUnknownInner(list,
                                      "int32",
                                      ScanParser::OpType::Lt);

    TS_ASSERT_EQUALS(list.size(), 2);

    memory[2] = 80;
    list = scanner.filterUnknownInner(list,
                                      "int32",
                                      ScanParser::OpType::Lt);

    memory[2] = 110;
    list = scanner.filterUnknownInner(list,
                                      "int32",
                                      ScanParser::OpType::Gt);
    TS_ASSERT_EQUALS(list.size(), 1);
    TS_ASSERT_EQUALS(list[0]->getAddress(), (Address)(&memory[2]));
  }
};