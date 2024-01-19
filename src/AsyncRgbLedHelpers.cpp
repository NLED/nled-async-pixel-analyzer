#include "AsyncRgbLedHelpers.h"

#include <cassert>
#include <cstring> // for memcpy

bool TimingTolerance::WithinTolerance( const double t ) const
{
    return ( t >= mMinimumSec ) && ( t <= mMaximumSec );
}

bool BitTiming::WithinTolerance( const double positiveTime, const double negativeTime ) const
{
    return mPositiveTiming.WithinTolerance( positiveTime ) && mNegativeTiming.WithinTolerance( negativeTime );
}

void RGBWValue::ConvertToControllerOrder( ColorLayout layout, U16* values ) const
{
    switch( layout )
    {
    case LAYOUT_RGBW:
        values[ 0 ] = red;
        values[ 1 ] = green;
        values[ 2 ] = blue;
        values[ 3 ] = white;
        break;
    case LAYOUT_GRBW:
        values[ 0 ] = green;
        values[ 1 ] = red;
        values[ 2 ] = blue;
        values[ 3 ] = white;
        break;
    }
}



void RGBValue::ConvertToControllerOrder( ColorLayout layout, U16* values ) const
{
    switch( layout )
    {
    case LAYOUT_GRB:
        values[ 0 ] = green;
        values[ 1 ] = red;
        values[ 2 ] = blue;
        break;

    case LAYOUT_RGB:
        values[ 0 ] = red;
        values[ 1 ] = green;
        values[ 2 ] = blue;
        break;

    }
}

RGBValue RGBValue::CreateFromControllerOrder( ColorLayout layout, U16* values )
{
    switch( layout )
    {
    case LAYOUT_GRB:
        return RGBValue{ values[ 1 ], values[ 0 ], values[ 2 ] };

    case LAYOUT_RGB:
        return RGBValue{ values[ 0 ], values[ 1 ], values[ 2 ] };
    }
}


RGBWValue RGBWValue::CreateFromControllerOrder( ColorLayout layout, U16* values )
{
    switch( layout )
    {
    case LAYOUT_RGBW:
        return RGBWValue{ values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ] };
    case LAYOUT_GRBW:
        return RGBWValue{ values[ 1 ], values[ 0 ], values[ 2 ], values[ 3 ] };
    }
}



RGBValue RGBValue::CreateFromU64( U64 raw )
{
    static_assert( sizeof( RGBValue ) == sizeof( U64 ), "Compiler U64 size doesn't match RGBValue struct sizeof" );
    RGBValue result;
    memcpy( &result, &raw, sizeof( RGBValue ) );
    return result;
}

RGBWValue RGBWValue::CreateFromU64( U64 raw )
{
    static_assert( sizeof( RGBWValue ) == sizeof( U64 ), "Compiler U64 size doesn't match RGBWValue struct sizeof" );
    RGBWValue result;
    memcpy( &result, &raw, sizeof( RGBWValue ) );
    return result;
}


U64 RGBValue::ConvertToU64() const
{
    static_assert( sizeof( RGBValue ) == sizeof( U64 ), "Compiler U64 size doesn't match RGBValue struct sizeof" );
    U64 result;
    memcpy( &result, this, sizeof( RGBValue ) );
    return result;
}


U64 RGBWValue::ConvertToU64() const
{
    static_assert( sizeof( RGBWValue ) == sizeof( U64 ), "Compiler U64 size doesn't match RGBWValue struct sizeof" );
    U64 result;
    memcpy( &result, this, sizeof( RGBWValue ) );
    return result;
}



void RGBValue::ConvertTo8Bit( U8 bitSize, U8* values ) const
{
    // we could choose to support smaller bit formats here, but
    // no existing LED controller does that, so let's omit for now
    assert( bitSize >= 8 );
    values[ 0 ] = static_cast<U8>( red >> ( bitSize - 8 ) );
    values[ 1 ] = static_cast<U8>( green >> ( bitSize - 8 ) );
    values[ 2 ] = static_cast<U8>( blue >> ( bitSize - 8 ) );
}


void RGBWValue::ConvertTo8Bit( U8 bitSize, U8* values ) const
{
    // we could choose to support smaller bit formats here, but
    // no existing LED controller does that, so let's omit for now
    assert( bitSize >= 8 );
    values[ 0 ] = static_cast<U8>( red >> ( bitSize - 8 ) );
    values[ 1 ] = static_cast<U8>( green >> ( bitSize - 8 ) );
    values[ 2 ] = static_cast<U8>( blue >> ( bitSize - 8 ) );
    values[ 3 ] = static_cast<U8>( white >> ( bitSize - 8 ) );
}

