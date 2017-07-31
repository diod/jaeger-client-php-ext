#ifndef IREPORTER_H
#define IREPORTER_H

class IReporter
{
public:
    //IReporter() = delete;
    //IReporter(const IReporter&) = delete;
    //IReporter(const IReporter&&) = delete;
    //IReporter& operator=(const IReporter&) = delete;
    //IReporter& operator=(const IReporter&&) = delete;

    //IReporter(const Php::Value &params){};

    virtual ~IReporter()
    {
        Php::out << "    IReporter::~IReporter addr: " << this << std::endl;
    }

    virtual void flush() const = 0;


    /*Add logs*/
    //public function addLogs(array $logs);

};


#endif /* IREPORTER_H */

