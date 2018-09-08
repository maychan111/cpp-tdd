#include <string>
#include <iostream>
#include <chrono>

namespace Lesson7
{
    // cohesion as a way to gauge whether a class is single responsibility 
    //
    // a class has high cohesion when most of its fields are used by most of its methods
    // https://thebojan.ninja/2015/04/08/high-cohesion-loose-coupling/

    // maximum cohesion class: usually only basic utitilty class has maximum cohesion
    struct Rectangle
    {
        int width, height;

        int GetArea() { return width * height; }
        int GetPerimeter() { return (width + height) * 2; }
    };

    // Coincidental Cohesion (undesirable) - arbitrary grouping, no meaningful relationship
    class RegisterContainer;

    // (redacted class from real project, 153 public member functions)
    class SomeHardwareState
    {
        bool IsOwnedByModule();
        uint32_t IncrementCount();
        bool ParseDefinitionFile();
        void *GetDefContainer();
        void setupsignalhandler();
        static void HandleTimerExpired();

        // ...

        uint32_t commandCounts;
        bool isOwnedByModule;
        RegisterContainer *_pRegisterContainer;
    };

    // Logical Cohesion (undesirable): group together for category reasons, not that they will be used together
    struct EthernetProtocolLayer
    {
        void SetSourceMac(std::string s);
        void SetDestMac(std::string s);
        std::string Get();

        std::string SetFromXmlString(std::string s);
        std::string SetFromNetworkString(std::string s);

        std::string GetSourceMac() const;
        std::string GetDestMac() const;

        std::string ToXmlDecoder();
        std::string ToTextDecoder();
    };

    // Functional Cohesion (desirable): grouped together for a single well-defined task
    //
    // pro:
    //    * can add different decoder w/o changing the class (open/close principle)
    //    * clearer intention when user is parsing or building (interface segrgation)
    //    * change only one class at a time if logic in parser or builder is wrong (single responsibility)
    //
    // con:
    //    * for some people, more classes are more confusing
    // 
    // therefore only separate classes if they pull their own weight (which is usually subjective)
    
    class EthernetProtocolLayerBuilder
    {
    public:
		EthernetProtocolLayerBuilder() { _buffer.resize(14); }
        void SetSourceMac(std::string s) { _buffer.replace(6, 6, s); }
        void SetDestMac(std::string s) { _buffer.replace(0, 6, s); }
        std::string ToString() const { return _buffer; }

    private:
        std::string _buffer;
    };

    class EthernetProtocolLayerParser
    {
    public:
		EthernetProtocolLayerParser(std::string s) : _buffer(std::move(s)) {}
        std::string GetSourceMac() const { return _buffer.substr(6, 6); }
        std::string GetDestMac() const { return _buffer.substr(0, 6); }

    private:
        std::string _buffer;
    };

	std::string EthernetToTextDecoder(std::string s) { /* ... */ return std::string();  }
    std::string EthernetToXmlDecoder(std::string s) { /* ... */ return std::string(); }
}