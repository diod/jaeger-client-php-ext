#ifndef JAEGERTRACER_H
#define JAEGERTRACER_H

#include <phpcpp.h>
#include <unordered_map>

#include "ITracer.h"
#include "IReporter.h"
#include "ISampler.h"
#include "Process.h"

namespace OpenTracing
{
    class JaegerTracer : public ITracer
    {
    private:
        // store the same _spans, used to increase ref count
        // so PHP garbage collector will not destroy _spans
        std::vector<Php::Value> _spans_ref; 
    public:
        IReporter* _reporter;
        ISampler* _sampler;
        Process* _process;
        bool _isSampled;
        std::unordered_map<int64_t, ISpan*> _spans;
        std::vector<int64_t> _activeSpans;

        ~JaegerTracer();
        JaegerTracer(IReporter* reporter, ISampler* sampler);
        JaegerTracer(const JaegerTracer&) = delete;

        void init(const std::string& serviceName);
        ISpan* startSpan(const std::string& operationName, const Php::Value& options = nullptr);
        ISpan* getCurrentSpan();
        void finishSpan(ISpan* span, const Php::Value& endTime = nullptr);
        void inject(const Php::Value& context, const std::string& format, std::string& carrier);
        SpanContext* extract(const std::string& format, const std::string& carier) const;
        void flush();

        void clearSpans();
        const char* _name() const;
    };
}

#endif /* JAEGERTRACER_H */

