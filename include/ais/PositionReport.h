#ifndef AIS_POSITIONREPORT_H
#define AIS_POSITIONREPORT_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include <cmath>

#include "Header.h"
#include "common.h"
namespace ais
{

/// Messages 1, 2, 3: Position reports.
/// The position report should be output periodically by mobile stations.
struct PositionReport: public Header, LonLatAccuracy, COG, Timestamp, RAIM, SyncState
{
    /// Navigational status.
    /// 0 = under way using engine, 1 = at anchor, 2 = not under command, 
    /// 3 = restricted manoeuvrability, 4 = constrained by her draught, 
    /// 5 = moored, 6 = aground, 7 = engaged in fishing, 8 = under way 
    /// sailing, 9 = reserved for future amendment of navigational status for 
    /// ships carrying DG, HS, or MP, or IMO hazard or pollutant category C, 
    /// high speed craft (HSC), 10 = reserved for future amendment of 
    /// navigational status for ships carrying dangerous goods (DG), harmful 
    /// substances (HS) or marine pollutants (MP), or IMO hazard or pollutant 
    /// category A, wing in grand (WIG); 
    /// 11-13 = reserved for future use, 
    /// 14 = AIS-SART (active), 
    /// 15 = not defined = default  (also used by AIS-SART under test)
    int nav_status;
    
    /// Rate of turn (decoded).
    /// 0 to +126 = turning right at up to 708° per min or higher 
    /// 0 to –126 = turning left at up to 708° per min or higher  
    /// Values between 0 and 708° per min coded by  
    /// ROTAIS = 4.733 SQRT(ROTsensor) degrees per min 
    /// where ROTsensor is the Rate of Turn as input by an external Rate of 
    /// Turn Indicator (TI). ROTAIS is rounded to the nearest integer value
    /// +127 = turning right at more than 5º per 30 s (No TI available) 
    /// –127 = turning left at more than 5º per 30 s (No TI available) 
    /// –128 (80 hex) indicates no turn information available (default). 
    /// ROT data should not be derived from COG information. 
    float rot;

    /// No turn information available (default).
    bool rot_not_available;
    
    /// Rate of Turn Indicator (TI) not available.
    /// turning at more than 5º per 30 s
    bool rot_no_ti;
    
    /// SOG (decoded).
    /// Speed over ground in 1/10 knot steps (0-102.2 knots) 
    /// 1 023 = not available, 1 022 = 102.2 knots or higher
    float sog;
    
    bool sog_not_available;
    
    
    /// True heading.
    /// Degrees (0-359) (511 indicates not available = default)
    int true_heading;
    
    /// special manoeuvre indicator.
    /// 0 = not available = default 
    /// 1 = not engaged in special manoeuvre 
    /// 2 = engaged in special manoeuvre 
    /// (i.e.: regional passing arrangement on Inland Waterway) 
    int special_manoeuvre;
    
    /// Spare.
    /// Not used. Should be set to zero. Reserved for future use.
    int spare;
    
    
    PositionReport():nav_status(15),
        rot(0.0),rot_not_available(true),rot_no_ti(true),
        sog(0.0),sog_not_available(true),
        true_heading(511),
        special_manoeuvre(0),
        spare(0)
    {}
    
    PositionReport(const BinaryPayload &payload):nav_status(15),
        rot(0.0),rot_not_available(true),rot_no_ti(true),
        sog(0.0),sog_not_available(true),
        true_heading(511),
        special_manoeuvre(0),
        spare(0)
    {
        BinaryPayload::Cursor c = payload.new_cursor();
        decode(c);
    }
    
    void decode(BinaryPayload::Cursor &payload_cursor)
    {
        Header::decode(payload_cursor);
        
        nav_status = payload_cursor.uread(4);
        
        int rot_raw = payload_cursor.sread(8);
        if(rot_raw == -128)
        {
            rot_not_available = true;
            rot = 0.0;
        }
        else if(std::abs(rot_raw) == 127)
        {
            rot = 10.0;
            rot_no_ti = true;
            rot_not_available = false;
        }
        else
        {
            rot = pow( (rot_raw/4.733), 2 );
            rot_no_ti = false;
            rot_not_available = false;
        }
        
        if (rot_raw < 0) rot = -rot;
        
        int sog_raw = payload_cursor.uread(10);
        if(sog_raw == 1023)
        {
            sog = 0.0;
            sog_not_available = true;
        }
        else
        {
            sog = sog_raw / 10.;
            sog_not_available = false;
        }

        LonLatAccuracy::decode(payload_cursor);

        COG::decode(payload_cursor);

        true_heading = payload_cursor.uread(9);
        
        Timestamp::decode(payload_cursor);

        special_manoeuvre = payload_cursor.uread(2);
        spare = payload_cursor.uread(3);
        RAIM::decode(payload_cursor);
        SyncState::decode(payload_cursor);
    }
    
    /// Returns string description of Navigational status.
    std::string nav_status_str() const
    {
        switch(nav_status)
        {
            case 0:
                return "under way using engine";
            case 1:
                return "at anchor";
            case 2:
                return "not under command";
            case 3:
                return "restricted manoeuvrability";
            case 4:
                return "constrained by her draught";
            case 5:
                return "moored";
            case 6:
                return "aground";
            case 7:
                return "engaged in fishing";
            case 8:
                return "under way, sailing";
            case  9:
                return "reserved for future amendment of navigational status for ships carrying DG, HS, or MP, or IMO hazard or pollutant category C, high speed craft (HSC)";
            case 10:
                return "reserved for future amendment of navigational status for ships carrying dangerous goods (DG), harmful substances (HS) or marine pollutants (MP), or IMO hazard or pollutant category A, wing in grand (WIG)";
            case 11:
            case 12:
            case 13:
                return "reserved for future use";
            case 14:
                return "AIS-SART (active)";
            case 15:
                return "not defined";
        }
        return "invalid value";
    }
};


/// Position Report (1 or 2) with SOTDMA link information.
/// Scheduled position report; (Class A shipborne mobile equipment)
/// or
/// Assigned scheduled position report; (Class A shipborne mobile equipment)
struct PositionReport_SOTDMA: public PositionReport, public SOTDMA
{
    PositionReport_SOTDMA()
    {}

    PositionReport_SOTDMA(const BinaryPayload &payload)
    {
        BinaryPayload::Cursor c = payload.new_cursor();
        decode(c);
    }

    void decode(BinaryPayload::Cursor &payload_cursor)
    {
        PositionReport::decode(payload_cursor);
        SOTDMA::decode(payload_cursor);
    }
};

/// Position Report (3) with ITDMA link information.
/// Special position report, response to interrogation; (Class A shipborne mobile equipment)
struct PositionReport_ITDMA: public PositionReport, ITDMA
{

    PositionReport_ITDMA(){}
    
    PositionReport_ITDMA(const BinaryPayload &payload)
    {
        BinaryPayload::Cursor c = payload.new_cursor();
        decode(c);
    }
    
    void decode(BinaryPayload::Cursor &payload_cursor)
    {
        PositionReport::decode(payload_cursor);
        ITDMA::decode(payload_cursor);
    }
};


/// Message 9: Standard SAR aircraft position reports.
/// This message should be used as a standard position report for aircraft involved in SAR operations.
/// Stations other than aircraft involved in SAR operations should not transmit this message. The
/// default reporting interval for this message should be 10 s.
struct SARPositionReport: public Header, LonLatAccuracy, COG, Timestamp, DTE, RAIM, SyncState, SOTDMA, ITDMA
{
    /// Altitude (GNSS)
    /// Altitude (derived from GNSS or barometric (see altitude sensor
    /// parameter below)) (m) (0-4 094 m) 4 095 = not available,
    /// 4 094 = 4 094 m or higher
    int alt;

    /// SOG.
    /// Speed over ground in knot steps (0-1 022 knots)
    /// 1 023 = not available, 1 022 = 1 022 knots or higher
    int sog;

    /// Altitude sensor.
    /// 0 = GNSS
    /// 1 = barometric source
    int alt_sensor;

    /// Spare.
    /// Not used. Should be set to zero. Reserved for future use.
    int spare;

    /// Spare.
    /// Not used. Should be set to zero. Reserved for future use.
    int spare2;

    /// Assigned mode flag
    /// 0 = Station operating in autonomous and continuous mode = default
    /// 1 = Station operating in assigned mode
    int assigned_mode;

    /// Communication state selector flag
    /// 0 = SOTDMA communication state follows
    /// 1 = ITDMA communication state follows
    int commstate_flag;

    SARPositionReport()
    :alt(4095),sog(1023),alt_sensor(-1),spare(0),spare2(0),assigned_mode(0),commstate_flag(-1)
    {}

    SARPositionReport(const BinaryPayload &payload)
    :alt(4095),sog(1023),alt_sensor(-1),spare(0),spare2(0),assigned_mode(0),commstate_flag(-1)
    {
        BinaryPayload::Cursor c = payload.new_cursor();
        decode(c);
    }

    void decode(BinaryPayload::Cursor &payload_cursor)
    {
        Header::decode(payload_cursor);

        alt = payload_cursor.uread(12);
        sog = payload_cursor.uread(10);

        LonLatAccuracy::decode(payload_cursor);
        COG::decode(payload_cursor);
        Timestamp::decode(payload_cursor);

        alt_sensor = payload_cursor.uread(1);
        spare = payload_cursor.uread(7);

        DTE::decode(payload_cursor);

        spare2 = payload_cursor.uread(3);
        assigned_mode = payload_cursor.uread(1);

        RAIM::decode(payload_cursor);

        commstate_flag = payload_cursor.uread(1);
        SyncState::decode(payload_cursor);
        if(commstate_flag)
            ITDMA::decode(payload_cursor);
        else
            SOTDMA::decode(payload_cursor);
    }
};

}

#endif
