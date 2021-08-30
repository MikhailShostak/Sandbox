#pragma once

using Year = std::chrono::year;
using Month = std::chrono::month;
using Day = std::chrono::day;
using Weekday = std::chrono::weekday;

namespace Date
{

namespace Weekday
{

using std::chrono::Sunday;
using std::chrono::Monday;
using std::chrono::Tuesday;
using std::chrono::Wednesday;
using std::chrono::Thursday;
using std::chrono::Friday;
using std::chrono::Saturday;

}

namespace Month
{

using std::chrono::January;
using std::chrono::February;
using std::chrono::March;
using std::chrono::April;
using std::chrono::May;
using std::chrono::June;
using std::chrono::July;
using std::chrono::August;
using std::chrono::September;
using std::chrono::October;
using std::chrono::November;
using std::chrono::December;

}

}
