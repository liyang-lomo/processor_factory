/**********************************
*@项目名称: processor_factory
*@文件名称: processor_factory.h
*@Date 2018-12-26 19:18:53
*@Author liyang
*@Copyright（C）: 2014-2019 「X-Financial」 Inc.   All rights reserved.
***************************************/
#ifndef __PROCESSOR_FACTORY_H__
#define __PROCESSOR_FACTORY_H__
#include <unordered_map>
#include <memory>
using namespace std;

namespace processor_factory
{
class BaseProcessor
{
  public:
    virtual int Process(int64_t task_id)=0;
};

using handler = shared_ptr<BaseProcessor> (*)(void);
template <class T>
class ProcessorFactory
{
  public:
    shared_ptr<BaseProcessor> CreateProcessor(T task_type)
    {
        auto it = handlers_.find(task_type);
        if (it == handlers_.end())
            return nullptr;
        else
            return it->second();
    }

    void Regist(T task_type, handler method)
    {
        handlers_.insert(pair<T, handler>(task_type, method));
    }

    static ProcessorFactory &Instance()
    {
        static ProcessorFactory intstance;
        return intstance;
    }

  private:
    unordered_map<T, handler> handlers_;
    ProcessorFactory(){}; //静态单例工厂
};
} // namespace processor_factory

#define REGISTER_PROCESSOR(T, task_type, ProcessorClassName)                                                     \
    shared_ptr<processor_factory::BaseProcessor> ObjectCreator##ProcessorClassName()                             \
    {                                                                                                            \
        return make_shared<ProcessorClassName>();                                                                \
    }                                                                                                            \
    __attribute__((constructor)) static void ReflectAction##ProcessorClassName()                                 \
    {                                                                                                            \
        processor_factory::ProcessorFactory<T>::Instance().Regist(task_type, ObjectCreator##ProcessorClassName); \
    }

#endif // __PROCESSOR_FACTORY_H__