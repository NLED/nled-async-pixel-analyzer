#include "AsyncRgbLedAnalyzerSettings.h"

#include <iostream>

#include <cassert>

#include <AnalyzerHelpers.h>

const char* DEFAULT_CHANNEL_NAME = "Addressable LEDs (Custom3)";

double operator"" _ns( unsigned long long x )
{
    return x * 1e-9;
}

double operator"" _us( unsigned long long x )
{
    return x * 1e-6;
}

AsyncRgbLedAnalyzerSettings::AsyncRgbLedAnalyzerSettings()
{
    InitControllerData();

    mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mInputChannelInterface->SetTitleAndTooltip( "LED Channel", "Standard Addressable LEDs (Custom)" );
    mInputChannelInterface->SetChannel( mInputChannel );

    mControllerInterface.reset( new AnalyzerSettingInterfaceNumberList() );
    mControllerInterface->SetTitleAndTooltip( "LED Controller", "Specify the LED controller in use." );

    int index = 0;

    for( const auto& controllerData : mControllers )
    {
        mControllerInterface->AddNumber( index++, controllerData.mName.c_str(), controllerData.mDescription.c_str() );
    }

    mControllerInterface->SetNumber( mLEDController );

    AddInterface( mInputChannelInterface.get() );
    AddInterface( mControllerInterface.get() );

    AddExportOption( 0, "Export as text/csv file" );
    AddExportExtension( 0, "text", "txt" );
    AddExportExtension( 0, "csv", "csv" );

    ClearChannels();
    AddChannel( mInputChannel, DEFAULT_CHANNEL_NAME, false );
}

AsyncRgbLedAnalyzerSettings::~AsyncRgbLedAnalyzerSettings()
{
}

void AsyncRgbLedAnalyzerSettings::InitControllerData()
{
    // order of values here must correspond to the Controller enum

    //timing is {min, nominal, max}


     std::cout << "Initializing NLED Analyzer" << std::endl;

     //Generated from spreadsheet
     //Added: 
     // WS2811, WS2812, WS2812B, WS2812-V4, WS2812-2020, WS2813, WS2814, WS2815, WS2818A, WS2818B, UCS1903, UCS2903, UCS2904B, SM16703, SM16704, PD9823, APA106, SK6822, APA104, SK6805MINI, 
     // LC8806B-2020, SK6805, SK6812, SK6812RGBW, SK6812RGBP8 , SK6812HV-4P, SK6805-EC15, SK6812RGBWP8, SK9816, SK6813, LPD1886, TM1803, TM1804, TM1829(hi speed)
    mControllers = {
        // name, description, bits per channel, channels per frame, reset time nsec, low-speed data nsec, has high speed, high speed data
        // nsec, color layout
         { "WS2811",
           "generated",
           8,
           3,
           { 50_us, 50_us, 50_us },
           {
               { { 100_ns, 250_ns, 400_ns }, { 850_ns, 1000_ns, 1150_ns } }, // 0-bit times
               { { 450_ns, 600_ns, 750_ns }, { 500_ns, 650_ns, 800_ns } },   // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "WS2812",
           "generated",
           8,
           3,
           { 50_us, 50_us, 50_us },
           {
               { { 200_ns, 350_ns, 500_ns }, { 650_ns, 800_ns, 950_ns } }, // 0-bit times
               { { 550_ns, 700_ns, 850_ns }, { 450_ns, 600_ns, 750_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "WS2812B",
           "generated",
           8,
           3,
           { 50_us, 50_us, 50_us },
           {
               { { 250_ns, 400_ns, 550_ns }, { 700_ns, 850_ns, 1000_ns } }, // 0-bit times
               { { 650_ns, 800_ns, 950_ns }, { 300_ns, 450_ns, 600_ns } },  // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "WS2812-V4, WS2812-2020",
           "generated",
           8,
           3,
           { 280_us, 280_us, 280_us },
           {
               { { 220_ns, 300_ns, 380_ns }, { 580_ns, 790_ns, 1000_ns } }, // 0-bit times
               { { 580_ns, 790_ns, 1000_ns }, { 220_ns, 320_ns, 420_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "WS2813",
           "generated",
           8,
           3,
           { 280_us, 280_us, 280_us },
           {
               { { 220_ns, 300_ns, 380_ns }, { 580_ns, 1090_ns, 1600_ns } }, // 0-bit times
               { { 580_ns, 1090_ns, 1600_ns }, { 220_ns, 320_ns, 420_ns } },    // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "WS2814",
           "generated",
           8,
           4,
           { 280_us, 280_us, 280_us },
           {
               { { 220_ns, 300_ns, 380_ns }, { 580_ns, 790_ns, 1000_ns } },  // 0-bit times
               { { 580_ns, 790_ns, 1000_ns }, { 580_ns, 790_ns, 1000_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGBW },
         { "WS2815",
           "generated",
           8,
           3,
           { 280_us, 280_us, 280_us },
           {
               { { 220_ns, 300_ns, 380_ns }, { 580_ns, 1090_ns, 1600_ns } }, // 0-bit times
               { { 580_ns, 1090_ns, 1600_ns }, { 220_ns, 320_ns, 420_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "WS2818A, WS2818B",
           "generated",
           8,
           3,
           { 280_us, 280_us, 280_us },
           {
               { { 220_ns, 300_ns, 380_ns }, { 580_ns, 790_ns, 1000_ns } }, // 0-bit times
               { { 580_ns, 790_ns, 1000_ns }, { 220_ns, 320_ns, 420_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGB },
         { "UCS1903, UCS2903",
           "generated",
           8,
           3,
           { 24_us, 24_us, 24_us },
           {
               { { 100_ns, 250_ns, 400_ns }, { 850_ns, 1000_ns, 1150_ns } }, // 0-bit times
               { { 850_ns, 1000_ns, 1150_ns }, { 100_ns, 250_ns, 400_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGB },
         { "UCS2904B",
           "generated",
           8,
           4,
           { 24_us, 24_us, 24_us },
           {
               { { 100_ns, 250_ns, 400_ns }, { 850_ns, 1000_ns, 1150_ns } }, // 0-bit times
               { { 850_ns, 1000_ns, 1150_ns }, { 100_ns, 250_ns, 400_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGBW },
         { "SM16703",
           "generated",
           8,
           3,
           { 80_us, 80_us, 80_us },
           {
               { { 250_ns, 300_ns, 350_ns }, { 850_ns, 900_ns, 950_ns } }, // 0-bit times
               { { 850_ns, 900_ns, 950_ns }, { 250_ns, 300_ns, 350_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGB },
         { "SM16704",
           "generated",
           8,
           4,
           { 80_us, 80_us, 80_us },
           {
               { { 250_ns, 300_ns, 350_ns }, { 850_ns, 900_ns, 950_ns } }, // 0-bit times
               { { 850_ns, 900_ns, 950_ns }, { 250_ns, 300_ns, 350_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGBW },
         { "PD9823, APA106, SK6822",
           "generated",
           8,
           3,
           { 50_us, 50_us, 50_us },
           {
               { { 200_ns, 350_ns, 500_ns }, { 1210_ns, 1360_ns, 1510_ns } }, // 0-bit times
               { { 1210_ns, 1360_ns, 1510_ns }, { 200_ns, 350_ns, 500_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGB },
         { "APA104",
           "generated",
           8,
           3,
           { 24_us, 24_us, 24_us },
           {
               { { 200_ns, 350_ns, 500_ns }, { 1210_ns, 1360_ns, 1510_ns } }, // 0-bit times
               { { 1210_ns, 1360_ns, 1510_ns }, { 200_ns, 350_ns, 500_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGB },
         { "SK6805MINI, LC8806B-2020",
           "generated",
           8,
           3,
           { 80_us, 80_us, 80_us },
           {
               { { 150_ns, 300_ns, 450_ns }, { 750_ns, 900_ns, 1050_ns } }, // 0-bit times
               { { 750_ns, 900_ns, 1050_ns }, { 150_ns, 300_ns, 450_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "SK6805, SK6812",
           "generated",
           8,
           3,
           { 80_us, 80_us, 80_us },
           {
               { { 150_ns, 300_ns, 450_ns }, { 750_ns, 900_ns, 1050_ns } }, // 0-bit times
               { { 450_ns, 600_ns, 750_ns }, { 450_ns, 600_ns, 750_ns } },  // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "SK6812RGBW",
           "generated",
           8,
           4,
           { 80_us, 80_us, 80_us },
           {
               { { 150_ns, 300_ns, 450_ns }, { 750_ns, 900_ns, 1050_ns } }, // 0-bit times
               { { 450_ns, 600_ns, 750_ns }, { 450_ns, 600_ns, 750_ns } },  // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGBW },
         { "SK6812RGBP8 , SK6812HV-4P, SK6805-EC15",
           "generated",
           8,
           3,
           { 80_us, 80_us, 80_us },
           {
               { { 200_ns, 300_ns, 400_ns }, { 800_ns, 10400_ns, 20000_ns } },  // 0-bit times
               { { 580_ns, 790_ns, 1000_ns }, { 200_ns, 10100_ns, 20000_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         { "SK6812RGBWP8 ",
           "generated",
           8,
           4,
           { 80_us, 80_us, 80_us },
           {
               { { 200_ns, 300_ns, 400_ns }, { 800_ns, 10400_ns, 20000_ns } },  // 0-bit times
               { { 580_ns, 790_ns, 1000_ns }, { 200_ns, 10100_ns, 20000_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGBW },
         { "SK9816",
           "generated",
           8,
           3,
           { 80_us, 80_us, 80_us },
           {
               { { 200_ns, 300_ns, 400_ns }, { 800_ns, 10400_ns, 20000_ns } },  // 0-bit times
               { { 580_ns, 790_ns, 1000_ns }, { 200_ns, 10100_ns, 20000_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_RGB },
         { "SK6813",
           "generated",
           8,
           3,
           { 80_us, 80_us, 80_us },
           {
               { { 200_ns, 300_ns, 400_ns }, { 800_ns, 10400_ns, 20000_ns } },  // 0-bit times
               { { 620_ns, 810_ns, 1000_ns }, { 200_ns, 10100_ns, 20000_ns } }, // 1-bit times
           },
           false,
           { {}, {} },
           LAYOUT_GRB },
         {
             "LPD1886",
             "generated",
             8,
             3,
             { 24_us, 24_us, 24_us },
             {
                 { { 200_ns, 200_ns, 200_ns }, { 600_ns, 600_ns, 600_ns } }, // 0-bit times
                 { { 600_ns, 600_ns, 600_ns }, { 200_ns, 200_ns, 200_ns } }, // 1-bit times
             },
             false,
             { {}, {} },
             LAYOUT_RGB},
             { "TM1803",
               "generated",
               8,
               3,
               { 24_us, 24_us, 24_us },
               {
                   { { 190_ns, 340_ns, 490_ns }, { 530_ns, 680_ns, 830_ns } }, // 0-bit times
                   { { 190_ns, 340_ns, 490_ns }, { 530_ns, 680_ns, 830_ns } }, // 1-bit times
               },
               false,
               { {}, {} },
               LAYOUT_RGB },
             { "TM1804",
               "generated",
               8,
               4,
               { 24_us, 24_us, 24_us },
               {
                   { { 400_ns, 400_ns, 400_ns }, { 320_ns, 320_ns, 320_ns } }, // 0-bit times
                   { { 850_ns, 850_ns, 850_ns }, { 700_ns, 700_ns, 700_ns } }, // 1-bit times
               },
               false,
               { {}, {} },
               LAYOUT_RGBW },
             { "TM1829(hi speed)",
               "generated",
               8,
               3,
               { 500_us, 500_us, 500_us },
               {
                   { { 170_ns, 170_ns, 170_ns }, { 50_ns, 150_ns, 250_ns } },  // 0-bit times
                   { { 300_ns, 425_ns, 550_ns }, { 340_ns, 340_ns, 340_ns } }, // 1-bit times
               },
               false,
               { {}, {} },
               LAYOUT_RGB },
    };
}

bool AsyncRgbLedAnalyzerSettings::SetSettingsFromInterfaces()
{
    mInputChannel = mInputChannelInterface->GetChannel();
    // explicit cast to keep MSVC happy
    const int index = static_cast<int>( mControllerInterface->GetNumber() );
    mLEDController = static_cast<Controller>( index );

    ClearChannels();
    AddChannel( mInputChannel, DEFAULT_CHANNEL_NAME, true );

    return true;
}

void AsyncRgbLedAnalyzerSettings::UpdateInterfacesFromSettings()
{
    mInputChannelInterface->SetChannel( mInputChannel );
    mControllerInterface->SetNumber( mLEDController );
}

void AsyncRgbLedAnalyzerSettings::LoadSettings( const char* settings )
{
    SimpleArchive text_archive;
    text_archive.SetString( settings );

    U32 controllerInt;
    text_archive >> mInputChannel;
    text_archive >> controllerInt;
    mLEDController = static_cast<Controller>( controllerInt );

    ClearChannels();
    AddChannel( mInputChannel, DEFAULT_CHANNEL_NAME, true );

    UpdateInterfacesFromSettings();
}

const char* AsyncRgbLedAnalyzerSettings::SaveSettings()
{
    SimpleArchive text_archive;

    text_archive << mInputChannel;
    text_archive << mLEDController;

    return SetReturnString( text_archive.GetString() );
}

U8 AsyncRgbLedAnalyzerSettings::BitSize() const
{
    return mControllers.at( mLEDController ).mBitsPerChannel;
}

U8 AsyncRgbLedAnalyzerSettings::LEDChannelCount() const
{
    return mControllers.at( mLEDController ).mChannelCount;
}

bool AsyncRgbLedAnalyzerSettings::IsHighSpeedSupported() const
{
    return mControllers.at( mLEDController ).mHasHighSpeed;
}

BitTiming AsyncRgbLedAnalyzerSettings::DataTiming( BitState value, bool isHighSpeed ) const
{
    const auto& c = mControllers.at( mLEDController );
    assert( !isHighSpeed || c.mHasHighSpeed );

    return isHighSpeed ? c.mDataTimingHighSpeed[ value ] : c.mDataTiming[ value ];
}

TimingTolerance AsyncRgbLedAnalyzerSettings::ResetTiming() const
{
    return mControllers.at( mLEDController ).mResetTiming;
}

ColorLayout AsyncRgbLedAnalyzerSettings::GetColorLayout() const
{
    return mControllers.at( mLEDController ).mLayout;
}
