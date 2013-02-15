#ifndef AIS_BASESTATIONREPORT_H
#define AIS_BASESTATIONREPORT_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"

namespace ais
{
    /// Message 5: Ship static and voyage related data.
    /// Should only be used by Class A shipborne and SAR aircraft AIS stations when reporting static or
    /// voyage related data.
    struct ShipStaticAndVoyage: public Header, FixType, DTE
    {
        /// AIS version indicator.
        /// 0 = station compliant with Recommendation ITU-R M.1371-1
        /// 1 = station compliant with Recommendation ITU-R M.1371-3
        /// 2-3 = station compliant with future editions
        int ais_version;

        /// IMO number.
        /// 1-999999999; 0 = not available = default - Not applicable to SAR aircraft
        int imo_num;

        /// Call sign.
        /// 7 = 6 bit ASCII characters, @@@@@@@ = not available = default
        std::string callsign;

        /// Name
        /// Maximum 20 characters 6 bit ASCII, as defined in Table 44
        /// "@@@@@@@@@@@@@@@@@@@@" = not available =
        /// default. For SAR aircraft, it should be set to "SAR AIRCRAFT
        /// NNNNNNN" where NNNNNNN equals the aircraft registration
        /// number
        std::string name;

        /// Type of ship and cargo type
        /// 0 = not available or no ship = default
        /// 1-99 = as defined in 3.3.2
        /// 100-199 = reserved, for regional use
        /// 200-255 = reserved, for future use
        /// Not applicable to SAR aircraft
        int type_and_cargo;

        /// Overall dimension/reference for position.
        /// Reference point for reported position.
        /// Also indicates the dimension of ship (m) (see Fig. 42 and 3.3.3)
        /// For SAR aircraft, the use of this field may be decided by the
        /// responsible administration. If used it should indicate the maximum
        /// dimensions of the craft. As default should A = B = C = D be set to “0”
        ///
        /// If reference point is available, A should be in the direction of the transmitted heading information (bow), 0 otherwise.
        /// B is distance from stern to reference point if available, or length if only dimensions are available.
        /// C is distance from port side to reference point, if available, or 0 if reference point not available.
        /// D is distance from reference point to starboard side, if available, or width if only dimensions are available.
        int dim_a;
        int dim_b;
        int dim_c;
        int dim_d;

        /// ETA.
        /// Estimated time of arrival; MMDDHHMM UTC
        /// Bits 19-16: month; 1-12; 0 = not available = default
        /// Bits 15-11: day; 1-31; 0 = not available = default
        /// Bits 10-6: hour; 0-23; 24 = not available = default
        /// Bits 5-0: minute; 0-59; 60 = not available = default
        /// For SAR aircraft, the use of this field may be decided by the
        /// responsible administration
        int eta_month;
        int eta_day;
        int eta_hour;
        int eta_minute;

        /// Maximum present static draught (decoded)
        /// In 1/10 m, 255 = draught 25.5 m or greater, 0 = not available = default;
        /// in accordance with IMO Resolution A.851
        /// Not applicable to SAR aircraft, should be set to 0
        float draught; // present static draft. m

        /// Destination
        /// Maximum 20 characters using 6-bit ASCII;
        /// @@@@@@@@@@@@@@@@@@@@ = not available
        /// For SAR aircraft, the use of this field may be decided by the
        /// responsible administration
        std::string destination;

        /// Spare.
        /// Spare. Not used. Should be set to zero. Reserved for future use
        int spare;

        ShipStaticAndVoyage()
            :ais_version(-1),imo_num(0),callsign("@@@@@@@"),name("@@@@@@@@@@@@@@@@@@@@"),
            type_and_cargo(0),dim_a(0),dim_b(0),dim_c(0),dim_d(0),
            eta_month(0),eta_day(0),eta_hour(24),eta_minute(60),
            draught(0.0),destination("@@@@@@@@@@@@@@@@@@@@"),spare(0)
        {}

        ShipStaticAndVoyage(const BinaryPayload &payload)
            :ais_version(-1),imo_num(0),callsign("@@@@@@@"),name("@@@@@@@@@@@@@@@@@@@@"),
            type_and_cargo(0),dim_a(0),dim_b(0),dim_c(0),dim_d(0),
            eta_month(0),eta_day(0),eta_hour(24),eta_minute(60),
            draught(0.0),destination("@@@@@@@@@@@@@@@@@@@@"),spare(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            ais_version = payload_cursor.uread(2);
            imo_num = payload_cursor.uread(30);
            callsign = payload_cursor.str_read(42);
            name = payload_cursor.str_read(120);
            type_and_cargo = payload_cursor.uread(8);

            dim_a =  payload_cursor.uread(9);
            dim_b =  payload_cursor.uread(9);
            dim_c =  payload_cursor.uread(6);
            dim_d =  payload_cursor.uread(6);

            FixType::decode(payload_cursor);

            eta_month = payload_cursor.uread(4);
            eta_day = payload_cursor.uread(5);
            eta_hour = payload_cursor.uread(5);
            eta_minute = payload_cursor.uread(6);

            draught = payload_cursor.uread(8)/10.0;
            destination = payload_cursor.str_read(120);

            DTE::decode(payload_cursor);

            spare = payload_cursor.uread(1);
        }

        std::string type_and_cargo_str() const
        {
            if (type_and_cargo == 0)
                return "not available or no ship";
            if (type_and_cargo >= 1 && type_and_cargo <= 99)
            {
                int first_digit = type_and_cargo/10;
                int second_digit = type_and_cargo%10;
                if (first_digit == 5)
                    switch(type_and_cargo)
                    {
                        case 50:
                            return "Pilot vessel";
                        case 51:
                            return "Search and rescue vessels";
                        case 52:
                            return "Tugs";
                        case 53:
                            return "Port tenders";
                        case 54:
                            return "Vessels with anti-pollution facilities or equipment";
                        case 55:
                            return "Law enforcement vessels";
                        case 56:
                        case 57:
                            return "Spare - for assignments to local vessels";
                        case 58:
                            return "Medical transports (as defined in the 1949 Geneva Conventions and Additional Protocols)";
                        case 59:
                            return "Ships and aircraft of States not parties to an armed conflict";
                    }
                std::string ret;
                switch (first_digit)
                {
                    case 1:
                        ret = "Reserved for future use";
                        break;
                    case 2:
                        ret = "WIG";
                        break;
                    case 3:
                        ret = "Vessel";
                        break;
                    case 4:
                        ret = "HSC";
                        break;
                    case 6:
                        ret = "Passenger ships";
                        break;
                    case 7:
                        ret = "Cargo ships";
                        break;
                    case 8:
                        ret = "Tanker(s)";
                        break;
                    case 9:
                        ret = "Other types of ship";
                        break;
                    default:
                        ret = "(invalid)";
                }
                if (first_digit != 3)
                    switch (second_digit)
                    {
                        case 0:
                            return ret + " - All ships of this type";
                        case 1:
                            return ret + " - Carrying DG, HS, or MP, IMO hazard or pollutant category X";
                        case 2:
                            return ret + " - Carrying DG, HS, or MP, IMO hazard or pollutant category Y";
                        case 3:
                            return ret + " - Carrying DG, HS, or MP, IMO hazard or pollutant category Z";
                        case 4:
                            return ret + " - Carrying DG, HS, or MP, IMO hazard or pollutant category OS";
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                            return ret + " - Reserved for future use";
                        case 9:
                            return ret + " - No additional information";
                    }
                switch(second_digit)
                {
                    case 0:
                        return ret + " - Fishing";
                    case 1:
                        return ret + " - Towing";
                    case 2:
                        return ret + " - Towing and length of the tow exceeds 200 m or breadth exceeds 25 m";
                    case 3:
                        return ret + " - Engaged in dredging or underwater operations";
                    case 4:
                        return ret + " - Engaged in diving operations";
                    case 5:
                        return ret + " - Engaged in military operations";
                    case 6:
                        return ret + " - Sailing";
                    case 7:
                        return ret + " - Pleasure craft";
                    case 8:
                    case 9:
                        return ret + " - Reserved for future use";
                }
            }
            if (type_and_cargo >= 100 && type_and_cargo <= 199)
                return "reserved, for regional use";
            if (type_and_cargo >= 200 && type_and_cargo <= 255)
                return "reserved, for future use";
            return "invalid type and cargo";
        }
    };
}

#endif
