#include "pch.h"
#include "CppUnitTest.h"
#include <cmath> // Для функції fabs

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Прототипи тестованих функцій
bool AreParallel(double A1, double B1, double A2, double B2);
bool ArePerpendicular(double A1, double B1, double A2, double B2);

bool AreParallel(double A1, double B1, double A2, double B2) {
    return fabs(A1 * B2 - A2 * B1) < 1e-6;
}

bool ArePerpendicular(double A1, double B1, double A2, double B2) {
    return fabs(A1 * A2 + B1 * B2) < 1e-6;
}

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestParallelLines)
        {
            // Тест: паралельні прямі
            Assert::IsTrue(AreParallel(1, 2, 2, 4), L"Прямі мають бути паралельними");

            // Тест: не паралельні прямі
            Assert::IsFalse(AreParallel(1, 2, 2, 3), L"Прямі не мають бути паралельними");
        }

        TEST_METHOD(TestPerpendicularLines)
        {
            // Тест: перпендикулярні прямі
            Assert::IsTrue(ArePerpendicular(1, 1, -1, 1), L"Прямі мають бути перпендикулярними");

            // Тест: не перпендикулярні прямі
            Assert::IsFalse(ArePerpendicular(1, 1, 1, 1), L"Прямі не мають бути перпендикулярними");
        }
    };
}
