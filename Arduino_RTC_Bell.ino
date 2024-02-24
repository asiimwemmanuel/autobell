#include <Wire.h>
#include <RTClib.h>

// Create an instance of the DS3231 RTC
RTC_DS3231 rtc;

// Define the pin connected to the electric bell
const int bellPin = 15;

// Define the school schedule ringing times
const char *ringTimes[] = {
    "05:30", // Wake up
    "06:00", // Breakfast
    "07:00", // Morning prep
    "08:00", // Class start
    "09:20", // Class Period
    "10:40", // Class Period
    "13:00", // Lunch
    "14:40", // Class Period
    "15:20", // End of class
    "15:20", // Leisure
    "17:00", // Organize
    "18:00", // Supper
    "19:00"  // Evening prep
};

int currentRingIndex = 0;

void setup()
{
    pinMode(bellPin, OUTPUT);
    Wire.begin();
    rtc.begin();
    // set the following line to set the initial time for the RTC:
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop()
{
    DateTime now = rtc.now();
    char currentTime[6];
    sprintf(currentTime, "%02d:%02d", now.hour(), now.minute());

    if (strcmp(currentTime, ringTimes[currentRingIndex]) == 0)
    {
        ringBell();
        // Delay for 1 minute to avoid repeated ringing at the same minute
        delay(60000);
        currentRingIndex = (currentRingIndex + 1) % (sizeof(ringTimes) / sizeof(ringTimes[0]));
    }
}

void ringBell()
{
    digitalWrite(bellPin, HIGH);
    // Adjust this delay for your bell's needs
    delay(500);
    digitalWrite(bellPin, LOW);
}
