#include <string>
#include <iostream>
#include <chrono>

namespace Lesson7
{
    // tight coupling is when a group of classes are highly dependent on one another.
    //
    // result of classes that are tightly coupled:
    //   the classes cannot indepedently evolve (i.e. fix bugs or add features)
    //   the classes are hard to test indepedently
    //
    // tight coupling can often be spotted by the following code smell:
    //   feature envy: a class that uses methods of another class excessively.
    //   freeloader: a class that does too little (not too be confused with lazy class initialization)
    //   inappropriate intimacy:  a class that has dependencies on implementation details of another class

    // example of tightly coupled classes
    struct Context
    {
        int LockChannel();
        int UnlockChannel();
        void SetLastTransmitPacket();
        void *GetPacketToRetransmit();
        void SetLastTimingComboPacket();
        // many more functions ...
    };
    
    struct DoWorkManager
    {
        // feature envy, complex conditional expressions control an object's state transitions 
        // note: replace conditionals with state classes 
        virtual void *DoWork(int& state)
        {
            switch (state)
            {
            case 1:
            {
                _context->LockChannel();
                // some other logic
                _context->SetLastTransmitPacket();
                _context->UnlockChannel();
                state = 2;
                auto p = _context->GetPacketToRetransmit();
                if (p)
                    state = 2;
                else
                    state = 3;
                return p;
            }
            case 2:
            {
                _context->LockChannel();
                // some other logic
                _context->SetLastTransmitPacket();
                _context->SetLastTimingComboPacket();
                _context->UnlockChannel();
                return nullptr;
            }
            case 3:
                // etc.
                break;
            }
        }

        virtual void SetContext(Context *context)
        { 
            // inappropriate intimacy
            if (context->GetPacketToRetransmit())
            {
                _context = context;
                _shouldRetransmit = true;
            }
            else
            {
                _context = new Context();
                _shouldRetransmit = false;
            }
        }

        Context *_context;
        bool _shouldRetransmit;
    };

    struct DoWorkProxy
    {
        // freeloader example
        virtual void *DoWork() { return _manager.DoWork(_state); }
        virtual void SetContext(Context *context) { _manager.SetContext(context); }

        int _state;
        DoWorkManager _manager;
    };
}