#include <string>
#include <iostream>

namespace Lesson7
{
    // Code smell: sequence of conditional tests with the same result
    // http://refactoring.com/catalog/consolidateConditionalExpression.html

    struct Disability
    {
        double GetDisabilityAmout()
        {
            if (_seniority == 0)
                return 0;
            else if (_isPartTime && _monthsDisabled > 6)
                return 0;
            else if (!_isPartTime && _monthsDisabled > 12)
                return 0;

            return 100 + (_baseSalary / 12) * _seniority;
        }

        int _baseSalary;
        int _seniority; // 0 means less than 1 year, 1 means 1 to 5 years, 2 means more than 5 years
        int _monthsDisabled;
        bool _isPartTime;
    };

    // scroll down after discussion

    // Recfactor: Improves relatedness inside classes. Data and the relevant behaviors are inside a single class.
    // ToDo: move magic numbers to constant

    struct RefactoredDisability
    {
        enum class Seniority { NewHire = 0, Junior = 1, Senior = 5 };

        double GetDisabilityAmount() const
        {
            return IsEligible() ? 100 + (_baseSalary / 12) * SeniorityFactor() : 0;
        }

        bool IsEligible() const
        {
            return _seniority != Seniority::NewHire && ((_isPartTime && _monthsDisabled < 6) || (!_isPartTime && _monthsDisabled > 12));
        }

        int SeniorityFactor() const
        {
            switch (_seniority)
            {
            case Seniority::NewHire: return 0;
            case Seniority::Junior: return 1;
            case Seniority::Senior: return 2;
            }
        }

        int _baseSalary;
        Seniority _seniority;
        int _monthsDisabled;
        bool _isPartTime;
    };
}