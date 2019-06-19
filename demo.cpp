
#include "processor_factory.h"
#include <iostream>
#include <stdint.h>
using namespace std;
using namespace processor_factory;

class test: public BaseProcessor
{
public:
    virtual int Process(int64_t task_id)
    {
        cout << "test_id:" << task_id << endl;
        return 0;
    }
};
REGISTER_PROCESSOR(uint32_t, 100, test);


int main()
{
    shared_ptr<BaseProcessor> test = ProcessorFactory<uint32_t>::Instance().CreateProcessor(100);
    if (test != nullptr)
    {
        test->Process(111);
    }
    return 0;
}
